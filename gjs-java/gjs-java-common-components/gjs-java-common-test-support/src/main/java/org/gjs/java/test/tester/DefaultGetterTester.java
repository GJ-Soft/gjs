package org.gjs.java.test.tester;

import static com.openpojo.validation.utils.ToStringHelper.safeToString;

import java.util.Objects;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.openpojo.random.RandomFactory;
import com.openpojo.reflection.PojoClass;
import com.openpojo.reflection.PojoField;
import com.openpojo.validation.utils.SameInstanceIdentityHandlerStub;
import com.openpojo.validation.utils.ValidationHelper;

/**
 * The Class DefaultGetterTester.
 *
 * Clase de datos de la librería Gjs
 *
 * Tester de métodos getter.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class DefaultGetterTester extends BaseFieldTester {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(DefaultGetterTester.class);

	/**
	 * Instantiates a new default getter tester.
	 */
	public DefaultGetterTester() {
		super(logger, "Getter");
	}

	/**
	 * Instantiates a new default getter tester.
	 *
	 * @param stopOnError the stop on error
	 */
	public DefaultGetterTester(boolean stopOnError) {
		super(logger, "Getter", stopOnError);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * com.openpojo.validation.test.Tester#run(com.openpojo.reflection.PojoClass)
	 */

	@Override
	public void runTest(final PojoClass pojoClass) {
		beginClass(pojoClass.getClazz().getCanonicalName(), pojoClass.getPojoFields().size());
		final Object classInstance = ValidationHelper.getBasicInstance(pojoClass);
		for (final PojoField fieldEntry : pojoClass.getPojoFields()) {
			if (fieldEntry.hasGetter()) {
				Object value = fieldEntry.get(classInstance);

				if (!fieldEntry.isFinal()) {
					value = setRandomValue(classInstance, fieldEntry);
				}

				SameInstanceIdentityHandlerStub.registerIdentityHandlerStubForValue(value);

				LoggerFactory.getLogger(this.getClass()).debug("Testing Field [{0}] with value [{1}]", fieldEntry,
						safeToString(value));

				final boolean esContenedor = fieldEntry.isParameterized() || fieldEntry.isArray();

				// NOTA: Con los array y colecciones hay implementaciones que permiten nulos
				// pero
				// a veces se fuerza el contenedor vacio.
				if (!esContenedor || Objects.nonNull(value)) {
					affirmEquals(String.format("Class=[%s]: Getter returned non equal value for field=[%s]", className,
							fieldEntry.getName()), value, fieldEntry.invokeGetter(classInstance));
				} else {
					fieldEntry.invokeGetter(classInstance);
				}
				SameInstanceIdentityHandlerStub.unregisterIdentityHandlerStubForValue(value);
				fieldProcessed();
			} else {
				LoggerFactory.getLogger(this.getClass()).debug("Field [{0}] has no getter skipping", fieldEntry);
			}
		}
		endClass();
	}

	/**
	 * Sets the random value.
	 *
	 * @param classInstance the class instance
	 * @param fieldEntry    the field entry
	 * @return the object
	 */
	private Object setRandomValue(Object classInstance, PojoField fieldEntry) {
		Object value = null;
		try {
			value = RandomFactory.getRandomValue(fieldEntry);
		} catch (final Exception e) {
			value = null;
			logger.warn("Can't generate a value for Field [{}]", fieldEntry);
			logger.warn(ExceptionUtils.getStackTrace(e));
		}
		try {
			fieldEntry.set(classInstance, value);
		} catch (final Exception e) {
			value = null;
			logger.warn("Can't set value [{}] for Field [{}]", value, fieldEntry);
			logger.warn(ExceptionUtils.getStackTrace(e));
		}
		return value;
	}

}
