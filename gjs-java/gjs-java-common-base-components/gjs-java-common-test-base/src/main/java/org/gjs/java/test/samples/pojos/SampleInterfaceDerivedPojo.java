package org.gjs.java.test.samples.pojos;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleInterfaceDerivedPojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo derivado de SampleInterfacePojo: hereda de una clase que a su vez implementa interfaz.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleInterfaceDerivedPojo extends SampleInterfacePojo {

    private boolean activo;
    private char codigo;

}
