package org.gjs.java.test.tester;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Parameter;
import java.util.Objects;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.supplier.GenericObjectSupplier;
import org.gjs.java.common.util.ConditionUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.openpojo.reflection.PojoClass;

/**
 * The Class ConstructorsTester.
 *
 * Clase de datos de la librería Gjs
 *
 * Tester de constructores.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class ConstructorsTester extends BaseMethodTester {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(ConstructorsTester.class);

	/** The Constant TEST_METHOD. */
	private static final String TEST_METHOD = "constructor";

	/**
	 * Instantiates a new constructors tester.
	 */
	public ConstructorsTester() {
		super(logger);
	}

	/**
	 * Instantiates a new constructors tester.
	 *
	 * @param stopOnError the stop on error
	 */
	public ConstructorsTester(boolean stopOnError) {
		super(logger, stopOnError);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.tester.BaseMethodTester#getTestMethod()
	 */

	@Override
	public String getTestMethod() {
		return TEST_METHOD;
	}

	/**
	 * Validate fields.
	 *
	 * @param obj the obj
	 */
	protected void validateFields(Object obj) {
		// Por defecto no hace nada
	}

	/**
	 * Validate default fields.
	 *
	 * @param obj the obj
	 */
	protected void validateDefaultFields(Object obj) {
		// Por defecto no hace nada
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.gjs.java.test.tester.BaseTester#canRun(com.openpojo.reflection.PojoClass)
	 */

	@Override
	protected boolean canRun(PojoClass pojoClass) {
		return !ConditionUtils.oneIsTrue(pojoClass.getClazz().getName().endsWith("Tester"),
				pojoClass.getClazz().getName().endsWith("Test"), isLombokBuilder(pojoClass.getClazz().getName()));
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * com.openpojo.validation.test.Tester#run(com.openpojo.reflection.PojoClass)
	 */

	@Override
	public void runTest(PojoClass pojoClass) {
		logger.info("ConstructorsTester: Class=[{}]", pojoClass.getClazz().getName());
		@SuppressWarnings("rawtypes")
		final Constructor[] allConstructors = pojoClass.getClazz().getDeclaredConstructors();
		for (final Constructor<?> constructor : allConstructors) {

			logger.info("Constructor with {}", constructor.getParameterCount());
			if (constructor.getParameterCount() > 0) {
				final boolean hasObjects = contructorHasObjects(constructor);
				final boolean hasArrays = contructorHasArrays(constructor);
				logger.info("The Constructor hasArrays={} and hasObjects={}", hasArrays, hasObjects);
				logger.info("Callig constructor with empty parameters...");
				Object[] parameters = generateEmptyParameters(constructor);
				Object obj = createInstance(constructor, parameters, pojoClass.getClazz().getName());
				affirmNotNull(String.format("Error calling constructor with empty parameters=[%s] for Class=[%s]",
						constructor.getName(), pojoClass.getClazz().getName()), obj);
				validateFields(obj);

				if (ConditionUtils.oneIsTrue(hasObjects, hasArrays)) {
					logger.info("Callig constructor with sample parameters...");
					parameters = generateSampleParameters(constructor);
					obj = createInstance(constructor, parameters, pojoClass.getClazz().getName());
					affirmNotNull(String.format("Error calling constructor with default parameters=[%s] for Class=[%s]",
							constructor.getName(), pojoClass.getClazz().getName()), obj);
					validateFields(obj);

				}
			} else {
				final Object obj = createInstance(constructor, null, pojoClass.getClazz().getName());
				affirmNotNull(String.format("Error calling default constructor for Class=[%s]", constructor.getName(),
						pojoClass.getClazz().getName()), obj);
				validateDefaultFields(obj);
			}
		}
	}

	/**
	 * Generate empty parameters.
	 *
	 * @param constructor the constructor
	 * @return the object[]
	 */
	private Object[] generateEmptyParameters(Constructor<?> constructor) {
		final Object[] parameters = new Object[constructor.getParameters().length];
		for (int i = 0; i < constructor.getParameters().length; i = i + 1) {
			final Parameter param = constructor.getParameters()[i];
			final String paramTypeName = getTypeName(param);
			logger.debug("Parametro {} de tipo {}", param.getName(), paramTypeName);
			if (PrimitiveType.isPrimitiveNative(paramTypeName)) {
				if (!param.getType().isArray()) {
					final PrimitiveType type = PrimitiveType.get(paramTypeName);
					parameters[i] = type.getDefaultValue();
				} else {
					parameters[i] = null;
				}
			} else {
				logger.info("Detectado parametro no primitivo: {}", paramTypeName);
				parameters[i] = null;
			}
		}
		return parameters;
	}

	/**
	 * Contructor has objects.
	 *
	 * @param constructor the constructor
	 * @return true, if successful
	 */
	private boolean contructorHasObjects(Constructor<?> constructor) {
		boolean hasObjects = false;
		for (int i = 0; i < constructor.getParameters().length; i = i + 1) {
			final Parameter param = constructor.getParameters()[i];
			if (!param.getType().isPrimitive()) {
				hasObjects = true;
				break;
			}
		}
		return hasObjects;
	}

	/**
	 * Contructor has arrays.
	 *
	 * @param constructor the constructor
	 * @return true, if successful
	 */
	private boolean contructorHasArrays(Constructor<?> constructor) {
		boolean hasArrays = false;
		for (int i = 0; i < constructor.getParameters().length; i = i + 1) {
			final Parameter param = constructor.getParameters()[i];
			if (param.getType().isArray()) {
				hasArrays = true;
				break;
			}
		}
		return hasArrays;
	}

	/**
	 * Generate sample parameters.
	 *
	 * @param constructor the constructor
	 * @return the object[]
	 */
	private Object[] generateSampleParameters(Constructor<?> constructor) {
		final Object[] parameters = new Object[constructor.getParameters().length];
		// TODO: Cuando haya objetos (y arrays) probar todas las combinaciones con null,
		// no null
		for (int i = 0; i < constructor.getParameters().length; i = i + 1) {
			final Parameter param = constructor.getParameters()[i];
			parameters[i] = getValue(param);
		}
		return parameters;
	}

	/**
	 * Gets the value.
	 *
	 * @param param the param
	 * @return the value
	 */
	private Object getValue(Parameter param) {
		Object value = null;
		final String paramTypeName = getTypeName(param);
		if (PrimitiveType.isPrimitiveNative(paramTypeName)) {
			value = getDefaultPrimitiveValue(param);
		} else if (PrimitiveType.isPrimitiveClass(paramTypeName)) {
			value = getDefaultPrimitiveClassValue(param);
		} else if (ManagedType.isManaged(paramTypeName)) {
			value = getDefaultManagedClassValue(param);
		} else {
			final GenericObjectSupplier supplier = new GenericObjectSupplier(paramTypeName);
			supplier.setInformAllFields(true);
			supplier.setLogger(logger);
			if (param.getType().isArray()) {
				value = supplier.getArray();
			} else {
				value = supplier.get();
			}
		}
		return value;
	}

	/**
	 * Creates the instance.
	 *
	 * @param constructor the constructor
	 * @param parameters  the parameters
	 * @param className   the class name
	 * @return the object
	 */
	private Object createInstance(Constructor<?> constructor, Object[] parameters, String className) {
		Object obj = null;
		try {
			if (Objects.nonNull(parameters)) {
				obj = constructor.newInstance(parameters);
			} else {
				obj = constructor.newInstance();
			}
		} catch (InstantiationException | IllegalAccessException | IllegalArgumentException
				| InvocationTargetException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			logger.error(String.format("Error calling constructor for Class=[%s] with parameters=[%s]", className,
					StringUtils.join(parameters, ';')), e);
		}
		return obj;
	}

	/**
	 * Checks if is lombok builder.
	 *
	 * @param className the class name
	 * @return true, if is lombok builder
	 */
	private boolean isLombokBuilder(String className) {
		return ConditionUtils.allAreTrue(className.contains("$"), className.endsWith("Builder"));
	}
}
