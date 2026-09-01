package org.gjs.java.common.supplier.random;

import java.util.Objects;

/**
 * Random Long supplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de enteros aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomLongSupplier extends AbstractRandomSupplier<Long> {

    /** The max value. */
    private Long maxValue;

    /** The min value. */
    private Long minValue;

    /**
     * Instantiates a new random long supplier.
     */
    public RandomLongSupplier() {
        this.maxValue = Long.valueOf(1000000000);
        this.minValue = Long.valueOf(1);
    }

    /**
     * Instantiates a new random long supplier.
     *
     * @param minValue
     *            the min value
     * @param maxValue
     *            the max value
     */
    public RandomLongSupplier(Long minValue, Long maxValue) {
        setMaxValue(maxValue);
        setMinValue(minValue);
    }

    /**
     * Gets the max value.
     *
     * @return the max value
     */
    public Long getMaxValue() {
        return maxValue;
    }

    /**
     * Sets the max value.
     *
     * @param maxValue
     *            the new max value
     */
    public void setMaxValue(Long maxValue) {
        if (Objects.nonNull(maxValue)) {
            this.maxValue = maxValue;
        }
    }

    /**
     * Gets the min value.
     *
     * @return the min value
     */
    public Long getMinValue() {
        return minValue;
    }

    /**
     * Sets the min value.
     *
     * @param minValue
     *            the new min value
     */
    public void setMinValue(Long minValue) {
        if (Objects.nonNull(minValue)) {
            this.minValue = minValue;
        }
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public Long get() {
        Long value = minValue;
        if (maxValue > minValue) {
            Long randomValue = random.nextLong();
            if (randomValue < 0) {
                randomValue = -randomValue;
            }
            value = minValue + (randomValue % ((maxValue - minValue) + 1));
        }
        return value;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public Long getEmpty() {
        return Long.valueOf(0);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected Long[] createArray(int size) {
        return new Long[size];
    }

}
