package org.gjs.java.common.supplier.random;

import org.apache.commons.lang3.RandomStringUtils;

/**
 * The Class RandomAlphanumericCharSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de carácteres aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomAlphanumericCharSupplier extends AbstractRandomSupplier<Character> {

    /**
     * Instantiates a new random alphanumeric char supplier.
     */
    public RandomAlphanumericCharSupplier() {
        // No hace nada
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public Character get() {
        return RandomStringUtils.secure().nextAlphanumeric(1).charAt(0);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public Character getEmpty() {
        return Character.valueOf('\0');
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected Character[] createArray(int size) {
        return new Character[size];
    }
}
