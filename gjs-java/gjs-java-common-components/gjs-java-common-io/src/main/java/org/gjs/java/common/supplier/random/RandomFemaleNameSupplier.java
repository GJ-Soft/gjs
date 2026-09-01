package org.gjs.java.common.supplier.random;

import java.io.IOException;

/**
 * The Class RandomNameSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de nombres femeninos aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomFemaleNameSupplier extends RandomSelectedFromFileSupplier {

    /**
     * Instantiates a new random female name supplier.
     *
     * @throws IOException
     *             Signals that an I/O exception has occurred.
     */
    public RandomFemaleNameSupplier() throws IOException {
        super("data/nombresH.txt");
    }

}
