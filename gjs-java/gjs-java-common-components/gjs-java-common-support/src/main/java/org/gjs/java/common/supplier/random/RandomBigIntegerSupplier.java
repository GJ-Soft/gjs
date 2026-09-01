package org.gjs.java.common.supplier.random;

import java.math.BigInteger;

/**
 * The Class RandomBigIntegerSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de BigInteger aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomBigIntegerSupplier extends AbstractRandomSupplier<BigInteger> {

    /** The double supplier. */
    private final RandomLongSupplier longSupplier = new RandomLongSupplier();

    /**
     * Instantiates a new random BigInteger supplier.
     */
    public RandomBigIntegerSupplier() {
        // No hace nada
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public BigInteger get() {
        return BigInteger.valueOf(longSupplier.get());
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public BigInteger getEmpty() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected BigInteger[] createArray(int size) {
        return new BigInteger[size];
    }
}
