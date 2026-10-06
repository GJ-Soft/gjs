package org.gjs.java.common.constant;

import java.math.BigInteger;

/**
 * The Class CommonConstants.
 *
 * Clase de constantes de la librería Gjs
 *
 * Constantes generales: parámetros de auditoría, respuestas por defecto, tope de las secuencias y tamaño de página.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class CommonConstants {

	public static final String PARAM_SKIP_AUDIT = "SKIP_AUDIT";
	public static final String PARAM_AUDIT_CRITICAL_TIME = "AUDIT_CRITICAL_TIME";

	/** The Constant DEFAULT_OK_RESPONSE. */
	public static final String DEFAULT_OK_RESPONSE = "OK";

	/** The Constant DEFAULT_KO_RESPONSE. */
	public static final String DEFAULT_KO_RESPONSE = "KO";

	/** The Constant JOB_ANONIMO. */
	public static final String JOB_ANONYMOUS = "Anonymous";

	/** The Constant SEQUENCE_MAX_VALUE. */
	public static final BigInteger SEQUENCE_MAX_VALUE = new BigInteger("99999999999999999999999");

	/** The Constant DEFAULT_PAGE_SIZE. */
	public static final Integer DEFAULT_PAGE_SIZE = Integer.valueOf(10);

	private CommonConstants() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

}
