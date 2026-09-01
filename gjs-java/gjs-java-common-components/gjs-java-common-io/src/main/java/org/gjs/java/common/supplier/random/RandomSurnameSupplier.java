package org.gjs.java.common.supplier.random;

import java.io.IOException;

/**
 * The Class RandomNameSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de apellidos aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomSurnameSupplier extends RandomSelectedFromFileSupplier {

    /**
     * Instantiates a new random surname supplier.
     *
     * @throws IOException
     *             Signals that an I/O exception has occurred.
     */
    public RandomSurnameSupplier() throws IOException {
        super("data/apellidos.txt");
    }

}
