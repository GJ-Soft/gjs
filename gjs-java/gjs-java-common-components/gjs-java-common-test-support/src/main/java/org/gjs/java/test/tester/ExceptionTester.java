package org.gjs.java.test.tester;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Parameter;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.commons.lang3.ArrayUtils;
import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.util.ReflectionUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.openpojo.reflection.PojoClass;

/**
 * The Class ExceptionTester.
 *
 * Clase de datos de la librería Gjs
 *
 * Tester de excepciones.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class ExceptionTester extends BaseMethodTester {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(ExceptionTester.class);

	/** The Constant TEST_METHOD. */
	private static final String TEST_METHOD = "constructor";

	/** The special parameters. */
	private final Map<String, Object> specialParameters = new ConcurrentHashMap<>();

	/**
	 * Instantiates a new exception tester.
	 */
	public ExceptionTester() {
		super(logger);
	}

	/**
	 * Instantiates a new exception tester.
	 *
	 * @param stopOnError the stop on error
	 */
	public ExceptionTester(boolean stopOnError) {
		super(logger, stopOnError);
	}

	/**
	 * Adds the special parameter.
	 *
	 * @param className  the class name
	 * @param defaultObj the default obj
	 */
	public void addSpecialParameter(String className, Object defaultObj) {
		if (!StringUtils.isAllBlank(className)) {
			specialParameters.put(className, defaultObj);
		}
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.gjs.java.test.tester.BaseTester#canRun(com.openpojo.reflection.PojoClass)
	 */

	@Override
	protected boolean canRun(PojoClass pojoClass) {
		return ReflectionUtils.isInstanceOf(pojoClass.getClazz().getCanonicalName(),
				Throwable.class.getCanonicalName());
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * com.openpojo.validation.test.Tester#run(com.openpojo.reflection.PojoClass)
	 */

	@Override
	public void runTest(PojoClass pojoClass) {
		logger.info("ExceptionTester: Class=[{}]", pojoClass.getClazz().getName());
		@SuppressWarnings("rawtypes")
		final Constructor[] allConstructors = pojoClass.getClazz().getDeclaredConstructors();
		for (final Constructor<?> constructor : allConstructors) {
			logger.info("Constructor with {}", constructor.getParameterCount());
			Exception obj;
			if (constructor.getParameterCount() == 0) {
				obj = createInstance(constructor, null, pojoClass.getClazz().getName());
				affirmNotNull(String.format("Error calling default constructor for Class=[%s]", constructor.getName(),
						pojoClass.getClazz().getName()), obj);
			} else {
				logger.info("Constructor with {}", constructor.getParameterCount());
				final Object[] parameters = generateParameters(constructor);
				obj = createInstance(constructor, parameters, pojoClass.getClazz().getName());
				for (final Object param : parameters) {
					logger.debug("Param={} of Type={}", param, param.getClass().getCanonicalName());
				}
				affirmNotNull(String.format("Error calling constructor for Class %s with parameters [%s]",
						pojoClass.getClazz().getName(), ArrayUtils.toString(parameters)), obj);
			}
			affirmFalse(String.format("The getMessage() return null/empty string for Class=[%s]",
					pojoClass.getClazz().getName()), StringUtils.isAllBlank(obj.getMessage()));
		}
	}

	/**
	 * Creates the instance.
	 *
	 * @param constructor the constructor
	 * @param parameters  the parameters
	 * @param className   the class name
	 * @return the exception
	 */
	private Exception createInstance(Constructor<?> constructor, Object[] parameters, String className) {
		Exception obj = null;
		try {
			if (Objects.nonNull(parameters)) {
				obj = (Exception) constructor.newInstance(parameters);
			} else {
				obj = (Exception) constructor.newInstance();
			}
		} catch (InstantiationException | IllegalAccessException | IllegalArgumentException
				| InvocationTargetException e) {
			logger.error(String.format("Error calling constructor for Class %s with parameters [%s]", className,
					ArrayUtils.toString(parameters)));
			logger.error(ExceptionUtils.getStackTrace(e));
		}
		return obj;
	}

	/**
	 * Generate parameters.
	 *
	 * @param constructor the constructor
	 * @return the object[]
	 */
	// TODO: Completar para otros casos de parametros que se usan en nuestras
	// excepciones
	private Object[] generateParameters(Constructor<?> constructor) {
		final Object[] parameters = new Object[constructor.getParameters().length];
		for (int i = 0; i < constructor.getParameters().length; i = i + 1) {
			final Parameter param = constructor.getParameters()[i];
			if (!param.getType().isArray()) {
				if (specialParameters.containsKey(param.getType().getCanonicalName())) {
					parameters[i] = specialParameters.get(param.getType().getCanonicalName());
				} else if (ReflectionUtils.isInstanceOf(param.getType(), String.class.getCanonicalName())) {
					parameters[i] = "Test message";
				} else if (ReflectionUtils.isInstanceOf(param.getType(), Throwable.class.getCanonicalName())) {
					parameters[i] = new RuntimeException("Test cause");
				} else if (param.getType().isPrimitive()) {
					parameters[i] = getDefaultPrimitiveValue(param);
				} else {
					logger.warn("Detectado parametro de tipo inesperado: {}", getTypeName(param));
					parameters[i] = null;
				}
			} else {
				logger.warn("Detectado parametro de tipo array inesperado: {}", getTypeName(param));
				parameters[i] = null;
			}
		}
		return parameters;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.tester.BaseMethodTester#getTestMethod()
	 */

	@Override
	protected String getTestMethod() {
		return TEST_METHOD;
	}

}
