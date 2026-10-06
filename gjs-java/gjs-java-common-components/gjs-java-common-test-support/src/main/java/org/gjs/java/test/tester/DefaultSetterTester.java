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
 * The Class DefaultSetterTester.
 *
 * Clase de datos de la librería Gjs
 *
 * Tester de métodos setter.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class DefaultSetterTester extends BaseFieldTester {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(DefaultSetterTester.class);

	/**
	 * Instantiates a new default setter tester.
	 */
	public DefaultSetterTester() {
		super(logger, "Setter");
	}

	/**
	 * Instantiates a new default setter tester.
	 *
	 * @param stopOnError the stop on error
	 */
	public DefaultSetterTester(boolean stopOnError) {
		super(logger, "Setter", stopOnError);
	}

	/**
	 * Expected value.
	 *
	 * @param fieldName   the field name
	 * @param settedValue the setted value
	 * @return the object
	 */
	protected Object expectedValue(String fieldName, Object settedValue) {
		return settedValue;
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
			if (fieldEntry.hasSetter()) {
				Object value;
				try {
					value = RandomFactory.getRandomValue(fieldEntry);
				} catch (final Exception e) {
					value = null;
					logger.warn("Can't generate a value for Field [{}]", fieldEntry);
					logger.warn(ExceptionUtils.getStackTrace(e));
				}

				final boolean esContenedor = fieldEntry.isParameterized() || fieldEntry.isArray();

				SameInstanceIdentityHandlerStub.registerIdentityHandlerStubForValue(value);
				if (logger.isDebugEnabled()) {
					logger.debug("Testing Field [{}] with value [{}]", fieldEntry, safeToString(value));
				}

				try {
					fieldEntry.invokeSetter(classInstance, value);
					final Object expected = expectedValue(fieldEntry.getName(), value);
					// NOTA: Con los array y colecciones hay implementacións que permiten nulos pero
					// a veces se fuerza el contenedor vacio.
					if (!esContenedor || Objects.nonNull(value)) {
						final Object obtained = fieldEntry.get(classInstance);
						affirmEquals(String.format(
								"Class=[%s]: Setter test failed, non equal value for field=[%s] : expected=%s; obtained=%s",
								className, fieldEntry.getName(), expected, obtained), expected, obtained);
					}
					fieldProcessed();
					SameInstanceIdentityHandlerStub.unregisterIdentityHandlerStubForValue(value);
				} catch (final Exception e) {
					value = null;
					logger.warn("Can't set value [{}] for Field [{}]", value, fieldEntry);
					logger.warn(ExceptionUtils.getStackTrace(e));
				}

			} else {
				logger.debug("Field [{}] has no setter skipping", fieldEntry.getName());
			}
			endClass();
		}

	}
}
