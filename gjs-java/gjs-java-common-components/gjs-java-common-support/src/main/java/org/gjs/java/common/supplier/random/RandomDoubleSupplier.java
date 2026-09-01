package org.gjs.java.common.supplier.random;

/**
 * Random Double supplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de reales dobles aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomDoubleSupplier extends AbstractRandomSupplier<Double> {

    /** The only positives. */
    private boolean onlyPositives;

    /**
     * Instantiates a new random double supplier.
     */
    public RandomDoubleSupplier() {
        // No hace nada
    }

    /**
     * Checks if is only positives.
     *
     * @return true, if is only positives
     */
    public boolean isOnlyPositives() {
        return onlyPositives;
    }

    /**
     * Sets the only positives.
     *
     * @param onlyPositives
     *            the new only positives
     */
    public void setOnlyPositives(boolean onlyPositives) {
        this.onlyPositives = onlyPositives;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public Double get() {
        final Double value = random.nextDouble();
        return onlyPositives ? Math.abs(value) : value;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public Double getEmpty() {
        return Double.valueOf(0.0);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected Double[] createArray(int size) {
        return new Double[size];
    }
}
