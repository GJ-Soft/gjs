package org.gjs.java.test.samples.pojos;

import java.util.List;
import java.util.Map;
import java.util.Set;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleCollectionsPojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo con una lista, un conjunto y un mapa.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleCollectionsPojo {

    private List<Long> ids;
    private Set<String> nombres;
    private Map<String, SamplePojo> objetos;

    public SampleCollectionsPojo() {
    }

}
