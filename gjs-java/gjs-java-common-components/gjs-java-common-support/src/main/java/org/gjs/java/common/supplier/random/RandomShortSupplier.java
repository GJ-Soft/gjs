package org.gjs.java.common.supplier.random;

import java.util.Objects;

/**
 * Random Short supplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de enteros cortos aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomShortSupplier extends AbstractRandomSupplier<Short> {

    /** The max value. */
    private Short maxValue;

    /** The min value. */
    private Short minValue;

    /**
     * Instantiates a new random integer supplier.
     */
    public RandomShortSupplier() {
        this.maxValue = Short.valueOf((short) 1000000);
        this.minValue = Short.valueOf((short) 1);
    }

    /**
     * Instantiates a new random integer supplier.
     *
     * @param minValue
     *            the min value
     * @param maxValue
     *            the max value
     */
    public RandomShortSupplier(Short minValue, Short maxValue) {
        setMaxValue(maxValue);
        setMinValue(minValue);
    }

    /**
     * Gets the max value.
     *
     * @return the max value
     */
    public Short getMaxValue() {
        return maxValue;
    }

    /**
     * Sets the max value.
     *
     * @param maxValue
     *            the new max value
     */
    public void setMaxValue(Short maxValue) {
        if (Objects.nonNull(maxValue)) {
            this.maxValue = maxValue;
        }
    }

    /**
     * Gets the min value.
     *
     * @return the min value
     */
    public Short getMinValue() {
        return minValue;
    }

    /**
     * Sets the min value.
     *
     * @param minValue
     *            the new min value
     */
    public void setMinValue(Short minValue) {
        if (Objects.nonNull(minValue)) {
            this.minValue = minValue;
        }
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public Short get() {
        Short value = minValue;
        if (maxValue > minValue) {
            Short randomValue = Short.valueOf((short) random.nextInt(Short.MAX_VALUE));
            if (randomValue < 0) {
                randomValue = (short) -randomValue;
            }
            value = (short) (minValue + (randomValue % ((maxValue - minValue) + 1)));
        }
        return value;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public Short getEmpty() {
        return Short.valueOf((short) 0);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected Short[] createArray(int size) {
        return new Short[size];
    }
}
