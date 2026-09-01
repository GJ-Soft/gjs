package org.gjs.java.common.supplier.random;

import org.gjs.java.common.enums.Sexo;

/**
 * The Class RandomSexSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de sexo aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomSexSupplier extends RandomEnumSupplier<Sexo> {

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.RandomEnumSupplier#getClazz() */

    @Override
    protected Class<?> getClazz() {
        return Sexo.class;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected Sexo[] createArray(int size) {
        return new Sexo[size];
    }

}
