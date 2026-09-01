package org.gjs.java.common.exception;

/**
 * The Class ObjectClonerException.
 *
 * Excepción de la librería Gjs
 *
 * Excepción generada por las utilidades de clonación de objetos utilizadas para la automatización de test de la
 * librería Gjs.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class ObjectClonerException extends RuntimeException {

    /** The Constant serialVersionUID. */
    private static final long serialVersionUID = -4225619350455794258L;

    /**
     * Instantiates a new object cloner exception.
     *
     * @param message
     *            the message
     */
    public ObjectClonerException(String message) {
        super(message);
    }

    /**
     * Instantiates a new object cloner exception.
     *
     * @param message
     *            the message
     * @param e
     *            the e
     */
    public ObjectClonerException(String message, Exception e) {
        super(message, e);
    }

}
