package org.gjs.java.common.supplier.random;

import java.util.Objects;

/**
 * Random Integer supplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de enteros aleatorias.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomIntegerSupplier extends AbstractRandomSupplier<Integer> {

    /** The default max value. */
    private static final Integer DEFAULT_MAX_VALUE = Integer.valueOf(100000000);

    /** The default min value. */
    private static final Integer DEFAULT_MIN_VALUE = Integer.valueOf(1);

    /**
     * The max value. Starts with the default so that it is never null: the
     * setters ignore a null.
     */
    private Integer maxValue = DEFAULT_MAX_VALUE;

    /** The min value. Same as maxValue. */
    private Integer minValue = DEFAULT_MIN_VALUE;

    /**
     * Instantiates a new random integer supplier.
     */
    public RandomIntegerSupplier() {
        // No hace nada
    }

    /**
     * Instantiates a new random integer supplier.
     *
     * @param minValue
     *            the min value
     * @param maxValue
     *            the max value
     */
    public RandomIntegerSupplier(Integer minValue, Integer maxValue) {
        setMaxValue(maxValue);
        setMinValue(minValue);
    }

    /**
     * Gets the max value.
     *
     * @return the max value
     */
    public Integer getMaxValue() {
        return maxValue;
    }

    /**
     * Sets the max value.
     *
     * @param maxValue
     *            the new max value
     */
    public void setMaxValue(Integer maxValue) {
        if (Objects.nonNull(maxValue)) {
            this.maxValue = maxValue;
        }
    }

    /**
     * Gets the min value.
     *
     * @return the min value
     */
    public Integer getMinValue() {
        return minValue;
    }

    /**
     * Sets the min value.
     *
     * @param minValue
     *            the new min value
     */
    public void setMinValue(Integer minValue) {
        if (Objects.nonNull(minValue)) {
            this.minValue = minValue;
        }
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public Integer get() {
        Integer value = minValue;
        if (maxValue > minValue) {
            // In long: the width of the range does not fit in an int when it is
            // over Integer.MAX_VALUE. And floorMod instead of negating the random
            // number, which stays negative for Integer.MIN_VALUE.
            final long width = (long) maxValue - minValue + 1;
            value = (int) (minValue + Math.floorMod(random.nextLong(), width));
        }
        return value;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public Integer getEmpty() {
        return Integer.valueOf(0);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected Integer[] createArray(int size) {
        return new Integer[size];
    }
}
