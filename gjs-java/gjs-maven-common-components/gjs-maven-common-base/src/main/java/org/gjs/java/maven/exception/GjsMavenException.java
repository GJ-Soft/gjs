package org.gjs.java.maven.exception;

import org.apache.maven.plugin.MojoExecutionException;

/**
 * The Class GjsMavenException.
 *
 * Excepcion de la libreria Gjs para los goals de Maven. Al extender MojoExecutionException, Maven la trata como un
 * fallo de ejecucion del plugin y no como un error interno.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class GjsMavenException extends MojoExecutionException {

	/**
	 * 
	 */
	private static final long serialVersionUID = 2776641976527303225L;

	/**
	 * Instantiates a new gjs maven exception.
	 *
	 * @param message the message
	 */
	public GjsMavenException(String message) {
		super(message);
	}

	/**
	 * Instantiates a new gjs maven exception.
	 *
	 * @param message the message
	 * @param cause   the cause
	 */
	public GjsMavenException(String message, Throwable cause) {
		super(message, cause);
	}

	/**
	 * Instantiates a new gjs maven exception.
	 *
	 * @param cause the cause
	 */
	public GjsMavenException(Throwable cause) {
		super(cause);
	}

}
