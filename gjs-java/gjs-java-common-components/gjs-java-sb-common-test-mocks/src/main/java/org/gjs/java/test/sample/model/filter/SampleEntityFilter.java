package org.gjs.java.test.sample.model.filter;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleEntityFilter.
 *
 * Clase de datos de ejemplo de la librería Gjs
 *
 * Filtro de ejemplo para las búsquedas sobre SampleEntity: nombre, descripción y marca de activo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleEntityFilter {
    private String nombre;

    private String descripcion;

    private Boolean activo;

}
