package org.gjs.java.common.util;

import java.util.Objects;

import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class ExceptionUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Funciones de ayuda para el tratamiento de excepciones.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class ExceptionUtils {

	/**
	 * Clase no instanciable.
	 */
	private ExceptionUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Find cause of class.
	 *
	 * @param ex    the ex
	 * @param clazz the clazz
	 * @return the exception
	 */
	public static Exception findCauseOfClass(Exception ex, Class<?> clazz) {
		Exception cause = null;
		Throwable ex1 = ex;
		while (Objects.nonNull(ex1)) {
			if (ex1.getClass().getCanonicalName().equals(clazz.getCanonicalName())) {
				cause = (Exception) ex1;
				break;

			}
			ex1 = ex1.getCause();
		}
		return cause;
	}
}
