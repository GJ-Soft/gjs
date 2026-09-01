package org.gjs.java.common.supplier.random;

import java.io.IOException;

/**
 * The Class RandomNameSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de nombres masculinos aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomMaleNameSupplier extends RandomSelectedFromFileSupplier {

    /**
     * Instantiates a new random male name supplier.
     *
     * @throws IOException
     *             Signals that an I/O exception has occurred.
     */
    public RandomMaleNameSupplier() throws IOException {
        super("data/nombresV.txt");
    }

}
