package org.gjs.java.common.supplier.random;

import org.apache.commons.lang3.RandomStringUtils;
import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class RandomNumericStringSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de cadenas numéricas aleatorias.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomNumericStringSupplier extends RandomAlphanumericStringSupplier {

    /**
     * Instantiates a new random numeric string supplier.
     */
    public RandomNumericStringSupplier() {
    }

    /**
     * Instantiates a new random numeric string supplier.
     *
     * @param maxLength
     *            the max length
     * @param nullable
     *            the nullable
     * @param constantLength
     *            the constant length
     */
    public RandomNumericStringSupplier(int maxLength, boolean nullable, boolean constantLength) {
        super(maxLength, nullable, constantLength);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.RandomAlphanumericStringSupplier#get() */

    @Override
    public String get() {
        if (ConditionUtils.allAreTrue(isNullable(), mustBeNull())) {
            return null;
        }
        final int minLength = isConstantLength() ? getMaxLength() : 0;
        final RandomIntegerSupplier lengthSupplier = new RandomIntegerSupplier(Integer.valueOf(minLength),
                Integer.valueOf(getMaxLength()));
        return RandomStringUtils.secure().nextNumeric(lengthSupplier.get());
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.RandomAlphanumericStringSupplier#getEmpty() */

    @Override
    public String getEmpty() {
        return isNullable() ? null : (isConstantLength() ? StringUtils.repeat('0', getMaxLength()) : "");
    }
}
