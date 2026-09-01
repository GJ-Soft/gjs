package org.gjs.java.test.samples.pojos;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleMaterialized1.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Materialización de SampleGeneric con Long como parámetro.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleMaterialized1 extends SampleGeneric<Long> {

    String texto;

    @Override
    public String toString() {
        return "SampleMaterialized1 [texto=" + texto + ", generic=" + generic + "]";
    }

}
