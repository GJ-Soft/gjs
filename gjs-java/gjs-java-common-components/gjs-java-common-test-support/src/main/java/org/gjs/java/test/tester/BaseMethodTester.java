package org.gjs.java.test.tester;

import java.lang.reflect.Parameter;

import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.util.ClazzUtils;
import org.gjs.java.common.util.ReflectionUtils;
import org.slf4j.Logger;

import com.openpojo.reflection.PojoClass;

/**
 * The Class BaseMethodTester.
 *
 * Clase abstracta de datos de la librería Gjs
 *
 * Clase abstracta base para implementar tester customizados sobre métodos.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class BaseMethodTester extends BaseTester {

	/**
	 * Instantiates a new base method tester.
	 *
	 * @param logger the getLogger()
	 */
	protected BaseMethodTester(Logger logger) {
		setLogger(logger);
	}

	/**
	 * Instantiates a new base method tester.
	 *
	 * @param logger      the getLogger()
	 * @param stopOnError the stop on error
	 */
	protected BaseMethodTester(Logger logger, boolean stopOnError) {
		super(stopOnError);
		setLogger(logger);
	}

	/**
	 * Gets the test method.
	 *
	 * @return the test method
	 */
	protected abstract String getTestMethod();

	/**
	 * Checks for method.
	 *
	 * @param pojoClass the pojo class
	 * @return true, if successful
	 */
	protected boolean hasMethod(PojoClass pojoClass) {
		return ReflectionUtils.hasMethod(pojoClass.getClazz(), getTestMethod());
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.gjs.java.test.tester.BaseTester#canRun(com.openpojo.reflection.PojoClass)
	 */

	@Override
	protected boolean canRun(PojoClass pojoClass) {
		return hasMethod(pojoClass);
	}

	/**
	 * Gets the default primitive value.
	 *
	 * @param param the param
	 * @return the default primitive value
	 */
	protected Object getDefaultPrimitiveValue(Parameter param) {
		Object res = null;
		final String paramTypeName = getTypeName(param);
		final PrimitiveType type = PrimitiveType.get(paramTypeName);
		if (!param.getType().isArray()) {
			res = type.getDefaultValue();
			getLogger().info("Creado objeto primitivo: {}", paramTypeName);
		} else {
			res = type.getDefaultArray();
			getLogger().info("Creado array de objeto primitivo: {}", paramTypeName);
		}
		return res;
	}

	/**
	 * Gets the type name.
	 *
	 * @param param the param
	 * @return the type name
	 */
	protected String getTypeName(Parameter param) {
		return param.getType().getCanonicalName().replace("[]", "");
	}

	/**
	 * Gets the default primitive class value.
	 *
	 * @param param the param
	 * @return the default primitive class value
	 */
	protected Object getDefaultPrimitiveClassValue(Parameter param) {
		Object res = null;
		final String paramTypeName = getTypeName(param);
		final PrimitiveType type = PrimitiveType.getFromClass(paramTypeName);
		if (!param.getType().isArray()) {
			res = type.getDefaultObject();
			getLogger().info("Creado objeto clase primitiva: {}", paramTypeName);
		} else {
			res = ClazzUtils.createArrayInstance(paramTypeName, getLogger());
			getLogger().info("Creado array de objeto clase primitiva: {}", paramTypeName);
		}
		return res;
	}

	/**
	 * Gets the default managed class value.
	 *
	 * @param param the param
	 * @return the default managed class value
	 */
	protected Object getDefaultManagedClassValue(Parameter param) {
		Object res = null;
		final String paramTypeName = getTypeName(param);
		final ManagedType type = ManagedType.get(paramTypeName);
		if (!param.getType().isArray()) {
			res = type.getDefaultObject();
			getLogger().info("Creado objeto clase manajada: {}", paramTypeName);
		} else {
			res = ClazzUtils.createArrayInstance(paramTypeName, getLogger());
			getLogger().info("Creado array de objeto clase manejada: {}", paramTypeName);
		}
		return res;
	}

	/**
	 * Gets the default object value.
	 *
	 * @param param the param
	 * @return the default object value
	 */
	protected Object getDefaultObjectValue(Parameter param) {
		Object res = null;
		final String paramTypeName = getTypeName(param);
		if (!param.getType().isArray()) {
			res = ClazzUtils.createInstance(paramTypeName, getLogger());
			getLogger().info("Creado objeto no primitivo: {}", paramTypeName);
		} else {
			res = ClazzUtils.createArrayInstance(paramTypeName, getLogger());
			getLogger().info("Creado array de objeto no primitivo: {}", paramTypeName);
		}
		return res;
	}

}
