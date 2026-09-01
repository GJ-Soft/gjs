package org.gjs.java.common.supplier.random;

import java.util.Arrays;
import java.util.Collection;

/**
 * The Class RandomAlphanumericStringSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Selectores aleatorios de cadenas sacadas de un conjunto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomSelectedStringSupplier extends RandomSelectedObjectSupplier<String> {

    /**
     * Instantiates a new random selected string supplier.
     */
    public RandomSelectedStringSupplier() {
    }

    /**
     * Instantiates a new random selected string supplier.
     *
     * @param options
     *            the options
     */
    public RandomSelectedStringSupplier(String... options) {
        this(options, true);
    }

    /**
     * Instantiates a new random selected string supplier.
     *
     * @param options
     *            the options
     */
    public RandomSelectedStringSupplier(Collection<String> options) {
        this(options, true);
    }

    /**
     * Instantiates a new random selected string supplier.
     *
     * @param options
     *            the options
     * @param nullable
     *            the nullable
     */
    public RandomSelectedStringSupplier(String[] options, boolean nullable) {
        this(Arrays.asList(options), nullable);
    }

    /**
     * Instantiates a new random selected string supplier.
     *
     * @param options
     *            the options
     * @param nullable
     *            the nullable
     */
    public RandomSelectedStringSupplier(Collection<String> options, boolean nullable) {
        super(options, nullable);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected String[] createArray(int size) {
        return new String[size];
    }
}
