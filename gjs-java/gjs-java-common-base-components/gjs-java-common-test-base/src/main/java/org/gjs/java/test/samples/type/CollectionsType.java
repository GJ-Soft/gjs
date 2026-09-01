package org.gjs.java.test.samples.type;

import java.math.BigDecimal;
import java.util.List;
import java.util.Map;
import java.util.Set;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class CollectionsType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo con colecciones y mapas de distintos contenidos.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class CollectionsType {
    private List<Integer> coiVal;
    private Set<Long> colVal;
    private Map<Character, Double> mocdVal;
    private List<BigDecimal> cdecVal;

    public CollectionsType() {
    }
}
