package org.gjs.java.common.util;

import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class CalculusUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Algunas funciones de ayuda para cálculos numéricos. En concreto, el cálculo
 * de los EPSILON de la máquina virtual para diferentes tipos numéricos.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class CalculusUtils {

	private CalculusUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Epsilon float.
	 *
	 * @return the float
	 */
	public static float epsilonFloat() {
		return Math.ulp(1.0f);
	}

	/**
	 * Epsilon double.
	 *
	 * @return the double
	 */
	public static double epsilonDouble() {
		return Math.ulp(1.0);
	}

}
