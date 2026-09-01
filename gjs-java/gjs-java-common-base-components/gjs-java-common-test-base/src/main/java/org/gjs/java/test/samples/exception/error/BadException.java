package org.gjs.java.test.samples.exception.error;

/**
 * The Class BadException.
 *
 * Excepción de ejemplo de la librería Gjs
 *
 * Excepción no comprobada, para las pruebas que esperan un fallo en tiempo de ejecución.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class BadException extends RuntimeException {

    /**
     *
     */
    private static final long serialVersionUID = 1L;

    public BadException(String message) {
    }

    public BadException(String message, Exception e) {
    }

}
