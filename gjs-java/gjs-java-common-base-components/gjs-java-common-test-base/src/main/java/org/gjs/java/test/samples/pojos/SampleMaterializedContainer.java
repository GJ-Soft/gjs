package org.gjs.java.test.samples.pojos;

import java.util.Date;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleMaterializedContainer.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo que contiene una SampleMaterialized2, para las pruebas sobre genéricos ya materializados.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleMaterializedContainer {

    SampleMaterialized2 materialized;
    Date inicio;

    @Override
    public String toString() {
        return "SampleMaterializedContainer [materialized=" + materialized + ", inicio=" + inicio + "]";
    }

}
