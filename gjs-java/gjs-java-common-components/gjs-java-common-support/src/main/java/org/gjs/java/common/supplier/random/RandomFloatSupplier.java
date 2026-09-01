package org.gjs.java.common.supplier.random;

/**
 * Random Float supplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de reales aleatorias.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomFloatSupplier extends AbstractRandomSupplier<Float> {

    /** The only positives. */
    private boolean onlyPositives;

    /**
     * Instantiates a new random float supplier.
     */
    public RandomFloatSupplier() {
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
    public Float get() {
        final Float value = random.nextFloat();
        return onlyPositives ? Math.abs(value) : value;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public Float getEmpty() {
        return Float.valueOf((float) 0.0);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected Float[] createArray(int size) {
        return new Float[size];
    }
}
