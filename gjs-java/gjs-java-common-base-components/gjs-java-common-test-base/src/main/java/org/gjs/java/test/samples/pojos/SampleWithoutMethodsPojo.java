package org.gjs.java.test.samples.pojos;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleWithoutMethodsPojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo sin accesores: solo campos.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleWithoutMethodsPojo {

    private long id;
    private String nombre;

    public SampleWithoutMethodsPojo() {
    }

}
