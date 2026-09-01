package org.gjs.java.test.samples.pojos;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleMaterialized2.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Materialización de SampleGeneric con SamplePojo como parámetro.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleMaterialized2 extends SampleGeneric<SamplePojo> {

    String texto;

    @Override
    public String toString() {
        return "SampleMaterialized2 [texto=" + texto + ", generic=" + generic + "]";
    }

}
