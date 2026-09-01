package org.gjs.java.test.exception;

/**
 * The Class DeprecatedException.
 *
 * Excepción de la librería Gjs
 *
 * Excepción generada para avisar de que se utiliza un método deprecado.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class DeprecatedException extends RuntimeException {

    /**
     *
     */
    private static final long serialVersionUID = -4634775908373609845L;

    /**
     * Instantiates a new object supplier exception.
     *
     * @param method
     *            the method
     */
    public DeprecatedException(String method) {
        super(String.format("The method %s is deprecated", method));
    }

}
