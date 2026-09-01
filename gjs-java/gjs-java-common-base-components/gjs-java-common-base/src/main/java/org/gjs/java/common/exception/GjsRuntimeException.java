package org.gjs.java.common.exception;

import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class SemillaRuntimeException.
 *
 * Excepción de la librería Gjs
 *
 * Excepción generada por las clase del módulo de utilidades Hereda de
 * RuntimeException para poder ser utilizada en funciones lambda.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class GjsRuntimeException extends RuntimeException {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = -7786700707108687537L;

	/**
	 * Instantiates a new ejemplo runtime exception.
	 */
	public GjsRuntimeException() {
		super(CommonBaseConstants.MSG_UNKNOWN_ERROR);
	}

	/**
	 * Instantiates a new ejemplo runtime exception.
	 *
	 * @param e the e
	 */
	public GjsRuntimeException(Throwable e) {
		super(e);
	}

	/**
	 * Instantiates a new ejemplo runtime exception.
	 *
	 * @param message the message
	 * @param e       the e
	 */
	public GjsRuntimeException(String message, Throwable e) {
		super(message, e);
	}

}
