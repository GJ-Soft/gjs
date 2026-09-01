package org.gjs.java.test.samples.exception;

import org.gjs.java.test.samples.pojos.SamplePojo;

/**
 * The Class SampleWithSpecialsException.
 *
 * Excepción de ejemplo de la librería Gjs
 *
 * Excepción comprobada cuyo constructor por defecto ya trae mensaje, para las pruebas que no admiten un mensaje nulo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class SampleWithSpecialsException extends Exception {

    /**
     *
     */
    private static final long serialVersionUID = 1L;

    public SampleWithSpecialsException() {
        super("Default message");
    }

    public SampleWithSpecialsException(String message) {
        super(message);
    }

    public SampleWithSpecialsException(String message, Throwable e) {
        super(message, e);
    }

    public SampleWithSpecialsException(Throwable e) {
        super(e.getMessage(), e);
    }

    public SampleWithSpecialsException(SamplePojo sample) {
        super(String.format("Sample error for the object %s", (sample != null) ? sample.getNombre() : "<unknown>"));
    }

}
