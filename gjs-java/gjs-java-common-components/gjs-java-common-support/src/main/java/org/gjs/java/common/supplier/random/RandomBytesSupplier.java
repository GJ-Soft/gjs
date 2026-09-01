package org.gjs.java.common.supplier.random;

import org.apache.commons.lang3.ArrayUtils;

/**
 * The Class RandomBytesSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de secueancias de bytes aleatorias.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomBytesSupplier extends AbstractRandomSupplier<Byte[]> {

    /** The default length for generated strings. */
    public static final int DEFAULT_STRING_LENGTH = 50;

    /** The max length. */
    private int maxLength = DEFAULT_STRING_LENGTH;

    /** The nullable. */
    private boolean nullable = true;

    /** The constant length. */
    private boolean constantLength;

    /**
     * Instantiates a new random bytes supplier.
     */
    public RandomBytesSupplier() {
    }

    /**
     * Instantiates a new random bytes supplier.
     *
     * @param maxLength
     *            the max length
     * @param nullable
     *            the nullable
     * @param constantLength
     *            the constant length
     */
    public RandomBytesSupplier(int maxLength, boolean nullable, boolean constantLength) {
        this.maxLength = maxLength;
        this.nullable = nullable;
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
     * Checks if is nullable.
     *
     * @return true, if is nullable
     */
    public boolean isNullable() {
        return nullable;
    }

    /**
     * Sets the nullable.
     *
     * @param nullable
     *            the new nullable
     */
    public void setNullable(boolean nullable) {
        this.nullable = nullable;
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
    public Byte[] get() {
        final int minLength = constantLength ? maxLength : (nullable ? 0 : 1);

        final RandomIntegerSupplier lengthSupplier =
                new RandomIntegerSupplier(Integer.valueOf(minLength), Integer.valueOf(maxLength));
        final byte[] value = new byte[lengthSupplier.get()];
        random.nextBytes(value);
        return ArrayUtils.toObject(value);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public Byte[] getEmpty() {
        return new Byte[0];
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected Byte[][] createArray(int size) {
        return new Byte[size][0];
    }
}
