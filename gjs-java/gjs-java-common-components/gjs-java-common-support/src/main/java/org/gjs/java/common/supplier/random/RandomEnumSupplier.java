package org.gjs.java.common.supplier.random;

import java.util.List;

import org.apache.commons.lang3.EnumUtils;

/**
 * The Class RandomEnumSupplier.
 *
 * Clase abstracta de datos de la librería Gjs
 *
 * Clase abstracta para ser utilizada en la implementación de generadores de datos aletorios de tipo enumerado
 *
 * @param <E>
 *            la clase de enumerado
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class RandomEnumSupplier<E extends Enum<E>> extends RandomSelectedObjectSupplier<E> {

    /**
     * Instantiates a new random enum supplier.
     */
    protected RandomEnumSupplier() {
        @SuppressWarnings("unchecked")
        final List<E> options = EnumUtils.getEnumList((Class<E>) getClazz());
        super.setOptions(options);
        super.setNullable(false);
    }

    /**
     * Gets the clazz.
     *
     * @return the clazz
     */
    protected abstract Class<?> getClazz();

}
