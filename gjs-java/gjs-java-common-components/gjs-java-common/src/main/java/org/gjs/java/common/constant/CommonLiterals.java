package org.gjs.java.common.constant;

/**
 * The Class CommonLiterals.
 *
 * Clase de constantes de la librería Gjs
 *
 * Claves de los literales con los que la auditoría avisa de los tiempos.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class CommonLiterals {

	public static final String LIT_CRITICAL_TIME_WARNING = "audit.critical.time.warning";

	public static final String LIT_TIME_WARNING = "audit.time.warning";

	private CommonLiterals() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

}
