package org.gjs.java.common.supplier.random;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;
import java.util.Objects;

import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class RandomNullableObjectSupplier.
 *
 * Clase abstracta de datos de la librería Gjs
 *
 * Clase abstracta base para selectores aleatorios de valores sacados de un conjunto.
 *
 * @param <T>
 *            la clase de datos a generar
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class RandomSelectedObjectSupplier<T> extends RandomNullableObjectSupplier<T> {

    /** The options. */
    private List<T> options;

    /** The index supplier. */
    private RandomIntegerSupplier indexSupplier;

    /**
     * Instantiates a new random selected object supplier.
     */
    protected RandomSelectedObjectSupplier() {
        this.options = new ArrayList<>();
        indexSupplier = new RandomIntegerSupplier(Integer.valueOf(0), Integer.valueOf(-1));
    }

    /**
     * Instantiates a new random selected object supplier.
     *
     * @param options
     *            the options
     */
    @SafeVarargs
    protected RandomSelectedObjectSupplier(T... options) {
        this(options, true);
    }

    /**
     * Instantiates a new random selected object supplier.
     *
     * @param options
     *            the options
     */
    protected RandomSelectedObjectSupplier(Collection<T> options) {
        this(options, true);
    }

    /**
     * Instantiates a new random selected object supplier.
     *
     * @param options
     *            the options
     * @param nullable
     *            the nullable
     */
    protected RandomSelectedObjectSupplier(T[] options, boolean nullable) {
        this(Arrays.asList(options), nullable);
    }

    /**
     * Instantiates a new random selected object supplier.
     *
     * @param options
     *            the options
     * @param nullable
     *            the nullable
     */
    protected RandomSelectedObjectSupplier(Collection<T> options, boolean nullable) {
        super(nullable);
        this.options = new ArrayList<>();
        indexSupplier = new RandomIntegerSupplier(Integer.valueOf(0), Integer.valueOf(0));
        setOptions(options);
    }

    /**
     * Sets the options.
     *
     * @param options
     *            the new options
     */
    @SuppressWarnings("unchecked")
    protected void setOptions(T... options) {
        setOptions(Arrays.asList(options));
    }

    /**
     * Sets the options.
     *
     * @param options
     *            the new options
     */
    protected void setOptions(Collection<T> options) {
        this.options.clear();
        if (Objects.nonNull(options)) {
            this.options.addAll(options);
            indexSupplier.setMaxValue(this.options.size() - 1);
        } else {
            indexSupplier.setMaxValue(-1);
        }
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#get() */

    @Override
    public T get() {
        if (ConditionUtils.oneIsTrue(ConditionUtils.allAreTrue(isNullable(), mustBeNull()), options.isEmpty())) {
            return null;
        }
        final int index = indexSupplier.get();
        return options.get(index);
    }

}
