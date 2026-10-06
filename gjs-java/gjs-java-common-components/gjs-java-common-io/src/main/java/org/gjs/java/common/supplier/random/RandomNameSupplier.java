package org.gjs.java.common.supplier.random;

import java.io.IOException;

import org.gjs.java.common.enums.Sexo;

/**
 * The Class RandomNameSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de nombres aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomNameSupplier extends RandomAlphanumericStringSupplier {

    /** The sex supplier. */
    private final RandomSexSupplier sexSupplier;

    /** The male name supplier. */
    private final RandomMaleNameSupplier maleNameSupplier;

    /** The female name supplier. */
    private final RandomFemaleNameSupplier femaleNameSupplier;

    /**
     * Instantiates a new random name supplier.
     *
     * @throws IOException
     *             Signals that an I/O exception has occurred.
     */
    public RandomNameSupplier() throws IOException {
        super(50, false, false);
        sexSupplier = new RandomSexSupplier();
        maleNameSupplier = new RandomMaleNameSupplier();
        femaleNameSupplier = new RandomFemaleNameSupplier();
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.RandomAlphanumericStringSupplier#get() */

    @Override
    public String get() {
        final Sexo sexo = sexSupplier.get();
        if (Sexo.VARON.equals(sexo)) {
            return maleNameSupplier.get();
        }
        return femaleNameSupplier.get();
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.RandomAlphanumericStringSupplier#getEmpty() */

    @Override
    public String getEmpty() {
        return null;
    }

}
