package org.gjs.java.common.supplier.random;

import java.time.LocalDate;

/**
 * Random Date supplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de LocalDate aleatorias.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomLocalDateSupplier extends AbstractRandomSupplier<LocalDate> {

    /** The local date time supplier. */
    private final RandomLocalDateTimeSupplier localDateTimeSupplier;

    /**
     * Instantiates a new random date supplier.
     */
    public RandomLocalDateSupplier() {
        localDateTimeSupplier = new RandomLocalDateTimeSupplier();
    }

    /**
     * Instantiates a new random date supplier.
     *
     * @param dateRange
     *            the date range
     * @param onlyFuture
     *            the only future
     */
    public RandomLocalDateSupplier(int dateRange, boolean onlyFuture) {
        localDateTimeSupplier = new RandomLocalDateTimeSupplier(dateRange, onlyFuture);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public LocalDate get() {
        return localDateTimeSupplier.get().toLocalDate();
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public LocalDate getEmpty() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected LocalDate[] createArray(int size) {
        return new LocalDate[size];
    }

}
