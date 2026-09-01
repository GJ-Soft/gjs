package org.gjs.java.common.supplier;

import java.util.function.Supplier;

import org.checkerframework.checker.nullness.qual.Nullable;

/**
 * The Interface Supplier.
 *
 * Interfaz de la librería Gjs
 *
 * Interfaz que debe implementar los generadores de datos aleatorios de la librería.
 *
 * @param <T>
 *            la clase que se suministra
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
// @FunctionalInterface
/**
 * The Interface GjsSupplier.
 *
 * Interfaz de la librería Gjs
 *
 * Contrato de los generadores de datos de la librería. Sobre el get() de Supplier añade el valor vacío, el nulo y las variantes en array, con su tamaño configurable.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public interface GjsSupplier<T extends @Nullable Object> extends Supplier<T> {

    /**
     * Gets the min size arrays.
     *
     * @return the min size arrays
     */
    int getMinSizeArrays();

    /**
     * Sets the min size arrays.
     *
     * @param minSizeArrays
     *            the new min size arrays
     */
    void setMinSizeArrays(int minSizeArrays);

    /**
     * Gets the max size arrays.
     *
     * @return the max size arrays
     */
    int getMaxSizeArrays();

    /**
     * Sets the max size arrays.
     *
     * @param maxSizeArrays
     *            the new max size arrays
     */
    void setMaxSizeArrays(int maxSizeArrays);

    /* (non-Javadoc)
     *
     * @see java.util.function.Supplier#get() */

    @Override
    T get();

    /**
     * Gets the nullius.
     *
     * @return the nullius
     */
    T getNullius();

    /**
     * Gets the empty.
     *
     * @return the empty
     */
    T getEmpty();

    /**
     * Gets the array.
     *
     * @return the array
     */
    T[] getArray();

    /**
     * Gets the empty array.
     *
     * @return the empty array
     */
    T[] getEmptyArray();

}
