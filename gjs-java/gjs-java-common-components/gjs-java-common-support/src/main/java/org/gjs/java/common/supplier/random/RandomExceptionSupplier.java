package org.gjs.java.common.supplier.random;

import org.gjs.java.common.supplier.GjsSupplier;

/**
 * Random Exception supplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de excepciones aleatorias.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomExceptionSupplier extends AbstractRandomSupplier<Exception> {

    /** The string supplier. */
    private final GjsSupplier<String> stringSupplier;

    /**
     * Instantiates a new random date supplier.
     */
    public RandomExceptionSupplier() {
        stringSupplier = new RandomAlphanumericStringSupplier(128, false, false);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public Exception get() {
        return new Exception(stringSupplier.get());
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public Exception getEmpty() {
        return new Exception();
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected Exception[] createArray(int size) {
        return new Exception[size];
    }

}
