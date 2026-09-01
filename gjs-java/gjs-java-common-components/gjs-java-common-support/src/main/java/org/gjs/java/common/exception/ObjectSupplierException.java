package org.gjs.java.common.exception;

/**
 * The Class ObjectSupplierException.
 *
 * Excepción de la librería Gjs
 *
 * Excepción generada por los ObjectSupplier cuando fallan al intentar generar un objeto aleatorio.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class ObjectSupplierException extends RuntimeException {

    /** The Constant serialVersionUID. */
    private static final long serialVersionUID = -4225619350455794258L;

    /**
     * Instantiates a new object supplier exception.
     *
     * @param message
     *            the message
     */
    public ObjectSupplierException(String message) {
        super(message);
    }

    /**
     * Instantiates a new object supplier exception.
     *
     * @param message
     *            the message
     * @param e
     *            the e
     */
    public ObjectSupplierException(String message, Exception e) {
        super(message, e);
    }

}
