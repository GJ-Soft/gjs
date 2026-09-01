package org.gjs.java.test.samples.exception;

/**
 * The Class SampleException.
 *
 * Excepción de ejemplo de la librería Gjs
 *
 * Excepción comprobada con los constructores corrientes.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class SampleException extends Exception {

    /**
     *
     */
    private static final long serialVersionUID = 1L;

    public SampleException() {
        super("Default message");
    }

    public SampleException(String message) {
        super(message);
    }

    public SampleException(String message, Throwable e) {
        super(message, e);
    }

    public SampleException(Throwable e) {
        super(e.getMessage(), e);
    }

}
