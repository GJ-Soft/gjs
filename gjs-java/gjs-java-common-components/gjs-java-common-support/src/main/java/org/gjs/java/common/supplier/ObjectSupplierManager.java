package org.gjs.java.common.supplier;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Objects;
import java.util.Set;

import org.gjs.java.common.log.LogManager;
import org.gjs.java.common.util.LogUtils;
import org.slf4j.Logger;

/**
 * The Class ObjectSupplierManager.
 *
 * Clase de datos de la librería Gjs
 *
 * Gestor de generadores de objetos aleatorios: puede manejar tantos generadores
 * de objetos como se quiera.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class ObjectSupplierManager extends LogManager {

	/** The map object supplier. */
	private final Map<String, AbstractObjectSupplier<?>> mapObjectSupplier;

	/**
	 * Instantiates a new object supplier manager.
	 */
	public ObjectSupplierManager() {
		this(null);
	}

	/**
	 * Instantiates a new object supplier manager.
	 *
	 * @param logger the logger
	 */
	public ObjectSupplierManager(Logger logger) {
		super(logger);
		mapObjectSupplier = new HashMap<>();
	}

	/**
	 * Gets the managed classes.
	 *
	 * @return the managed classes
	 */
	public Set<String> getManagedClassNames() {
		return this.mapObjectSupplier.keySet();

	}

	/**
	 * Gets the managed classes.
	 *
	 * @return the managed classes
	 * @throws ClassNotFoundException the class not found exception
	 */
	public List<Class<?>> getManagedClasses() throws ClassNotFoundException {
		final String _METHOD_ = LogUtils.getMethodName();
		final List<Class<?>> list = new ArrayList<>();
		for (final String className : this.mapObjectSupplier.keySet()) {
			try {
				list.add(Class.forName(className));
			} catch (final ClassNotFoundException e) {
				logControlledError(_METHOD_, e);
				throw e;
			}
		}
		return list;
	}

	/**
	 * Gets the managed class.
	 *
	 * @param className the class name
	 * @return the managed class
	 * @throws ClassNotFoundException the class not found exception
	 */
	public Class<?> getManagedClass(String className) throws ClassNotFoundException {
		final String _METHOD_ = LogUtils.getMethodName();
		Class<?> res = null;
		if (this.mapObjectSupplier.containsKey(className)) {
			try {
				res = Class.forName(className);
			} catch (final ClassNotFoundException e) {
				logControlledError(_METHOD_, e);
				throw e;
			}
		}
		return res;
	}

	/**
	 * Register supplier.
	 *
	 * @param className      the class name
	 * @param objectSupplier the object supplier
	 */
	public void registerSupplier(String className, AbstractObjectSupplier<?> objectSupplier) {
		mapObjectSupplier.put(className, objectSupplier);
	}

	/**
	 * Find supplier.
	 *
	 * @param className the class name
	 * @return the abstract object supplier
	 */
	public AbstractObjectSupplier<?> findSupplier(String className) {
		return mapObjectSupplier.get(className);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.log.LogManager#setLogger(org.slf4j.Logger)
	 */

	@Override
	public void setLogger(Logger logger) {
		super.setLogger(logger);
		if (Objects.nonNull(mapObjectSupplier)) {
			for (final Entry<String, AbstractObjectSupplier<?>> objectSupplier : mapObjectSupplier.entrySet()) {
				objectSupplier.getValue().setLogger(logger);
			}
		}
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		final StringBuilder out = new StringBuilder(1024);
		out.append("ObjectSupplierManager [ ManagersRegisteredForClasses=");
		for (final String type : mapObjectSupplier.keySet()) {
			out.append(type).append("; ");
		}
		out.append(']');
		return out.toString();
	}
}
