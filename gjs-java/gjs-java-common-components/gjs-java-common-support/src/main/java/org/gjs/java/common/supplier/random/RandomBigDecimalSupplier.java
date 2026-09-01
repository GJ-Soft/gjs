package org.gjs.java.common.supplier.random;

import java.math.BigDecimal;

/**
 * The Class RandomBigDecimalSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de BigDecimal aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomBigDecimalSupplier extends AbstractRandomSupplier<BigDecimal> {

    /** The double supplier. */
    private final RandomDoubleSupplier doubleSupplier = new RandomDoubleSupplier();

    /**
     * Instantiates a new random BigDecimal supplier.
     */
    public RandomBigDecimalSupplier() {
        // No hace nada
    }

    /**
     * Checks if is only positives.
     *
     * @return true, if is only positives
     */
    public boolean isOnlyPositives() {
        return doubleSupplier.isOnlyPositives();
    }

    /**
     * Sets the only positives.
     *
     * @param onlyPositives
     *            the new only positives
     */
    public void setOnlyPositives(boolean onlyPositives) {
        doubleSupplier.setOnlyPositives(onlyPositives);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public BigDecimal get() {
        return BigDecimal.valueOf(doubleSupplier.get());
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public BigDecimal getEmpty() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected BigDecimal[] createArray(int size) {
        return new BigDecimal[size];
    }
}
