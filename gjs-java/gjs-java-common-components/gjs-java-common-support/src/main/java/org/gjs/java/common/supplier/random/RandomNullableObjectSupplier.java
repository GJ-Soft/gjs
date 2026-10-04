package org.gjs.java.common.supplier.random;

/**
 * The Class RandomNullableObjectSupplier.
 *
 * Clase abstracta de datos de la librería Gjs
 *
 * Clase abstracta base para generadores de datos aleatorias que permitan una probabilidad de generación de un valor
 * nulo.
 *
 * @param <T>
 *            la clase de datos a generar
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class RandomNullableObjectSupplier<T> extends AbstractRandomSupplier<T> {

    /** The null probability. */
    private static final int NULL_PROBABILITY = 10;

    /** The nullable. */
    private boolean nullable = true;

    /**
     * Instantiates a new random alphanumeric string supplier.
     */
    protected RandomNullableObjectSupplier() {
    }

    /**
     * Instantiates a new random nullable object supplier.
     *
     * @param nullable
     *            the nullable
     */
    protected RandomNullableObjectSupplier(boolean nullable) {
        this.nullable = nullable;
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
     * Must be null.
     *
     * @return true, if successful
     */
    protected boolean mustBeNull() {
        return (random.nextInt(100) < NULL_PROBABILITY);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public T getEmpty() {
        return null;
    }

}
