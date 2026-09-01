package org.gjs.java.common.exception;

import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class GjsException.
 *
 * Excepción de la librería Gjs
 *
 * Clase básica que heredan todas las excepciones de Semilla.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class GjsException extends Exception {

	/**
	 *
	 */
	private static final long serialVersionUID = 2182396048438886381L;

	/**
	 * Constructor de la clase.
	 *
	 */
	public GjsException() {
		super(CommonBaseConstants.MSG_UNKNOWN_ERROR);
	}

	/**
	 * Constructor de la clase.
	 *
	 * @param message El mensaje de detalle para la excepción.
	 */
	public GjsException(String message) {
		super(message);
	}

	/**
	 * Constructor de la clase.
	 *
	 * @param cause La causa de la excepción.
	 */
	public GjsException(Throwable cause) {
		super(cause);
	}

	/**
	 * Constructor de la clase.
	 *
	 * @param message El mensaje de detalle para la excepción.
	 * @param cause   La causa de la excepción.
	 */
	public GjsException(String message, Throwable cause) {
		super(message, cause);
	}

	/**
	 * Constructor de la clase.
	 *
	 * @param message            El mensaje de detalle para la excepción.
	 * @param cause              La causa de la excepción.
	 * @param enableSuppression  Si la supresión está habilitada o no.
	 * @param writableStackTrace Si el stack trace debe ser editable o no.
	 */
	public GjsException(String message, Throwable cause, boolean enableSuppression, boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
	}

}
