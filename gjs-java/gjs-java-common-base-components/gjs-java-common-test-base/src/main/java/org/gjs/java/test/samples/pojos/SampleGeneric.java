package org.gjs.java.test.samples.pojos;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleGeneric.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo parametrizado por el tipo de su único campo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleGeneric<PK> {

    PK generic;

}
