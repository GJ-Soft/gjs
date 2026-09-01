package org.gjs.java.common.supplier.random;

/**
 * The Class RandomAlphanumericStringSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de DNI aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomDniStringSupplier extends RandomNumericStringSupplier {

    /** The dni length for generated strings. */
    private static final int DNI_LENGTH = 8;

    /**
     * Instantiates a new random dni string supplier.
     */
    public RandomDniStringSupplier() {
        super(DNI_LENGTH, false, true);
    }

}
