package org.gjs.java.common.supplier.random;

import org.apache.commons.lang3.RandomStringUtils;
import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class RandomAlphanumericStringSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de cadenas aleatorias.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomAlphanumericStringSupplier extends RandomNullableObjectSupplier<String> {

    /** The default length for generated strings. */
    public static final int DEFAULT_STRING_LENGTH = 50;

    /** The max length. */
    private int maxLength = DEFAULT_STRING_LENGTH;

    /** The constant length. */
    private boolean constantLength;

    /**
     * Instantiates a new random alphanumeric string supplier.
     */
    public RandomAlphanumericStringSupplier() {
    }

    /**
     * Instantiates a new random alphanumeric string supplier.
     *
     * @param maxLength
     *            the max length
     * @param nullable
     *            the nullable
     * @param constantLength
     *            the constant length
     */
    public RandomAlphanumericStringSupplier(int maxLength, boolean nullable, boolean constantLength) {
        super(nullable);
        this.maxLength = maxLength;
        this.constantLength = constantLength;
    }

    /**
     * Gets the max length.
     *
     * @return the max length
     */
    public int getMaxLength() {
        return maxLength;
    }

    /**
     * Sets the max length.
     *
     * @param maxLength
     *            the new max length
     */
    public void setMaxLength(int maxLength) {
        this.maxLength = maxLength;
    }

    /**
     * Checks if is constant length.
     *
     * @return true, if is constant length
     */
    public boolean isConstantLength() {
        return constantLength;
    }

    /**
     * Sets the constant length.
     *
     * @param constantLength
     *            the new constant length
     */
    public void setConstantLength(boolean constantLength) {
        this.constantLength = constantLength;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public String get() {
        if (ConditionUtils.allAreTrue(isNullable(), mustBeNull())) {
            return null;
        }
        final int minLengthDefault = isNullable() ? 0 : 1;
        final int minLength = constantLength ? maxLength : minLengthDefault;
        final RandomIntegerSupplier lengthSupplier = new RandomIntegerSupplier(Integer.valueOf(minLength),
                Integer.valueOf(maxLength));
        final int size = lengthSupplier.get();
        return RandomStringUtils.secure().nextAlphanumeric(size);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.RandomNullableObjectSupplier#getEmpty() */

    @Override
    public String getEmpty() {
        return isNullable() ? null : (constantLength ? StringUtils.repeat(' ', maxLength) : "");
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected String[] createArray(int size) {
        return new String[size];
    }
}
