package org.gjs.java.common.supplier.random;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Calendar;
import java.util.Date;

/**
 * Random Date supplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de Date aleatorias.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomDateSupplier extends AbstractRandomSupplier<Date> {

    /** The Constant DEFAULT_DATE_RANGE. */
    public static final int DEFAULT_DATE_RANGE = 50;

    /** The date range. */
    private int dateRange;

    /** The only future. */
    private boolean onlyFuture;

    /** The range supplier. */
    private final RandomIntegerSupplier rangeSupplier;

    /**
     * Instantiates a new random date supplier.
     */
    public RandomDateSupplier() {
        this(DEFAULT_DATE_RANGE, false);
    }

    /**
     * Instantiates a new random date supplier.
     *
     * @param dateRange
     *            the date range
     * @param onlyFuture
     *            the only future
     */
    public RandomDateSupplier(int dateRange, boolean onlyFuture) {
        this.dateRange = Integer.max(dateRange, 0);
        this.onlyFuture = onlyFuture;
        rangeSupplier = new RandomIntegerSupplier(Integer.valueOf(-this.dateRange), Integer.valueOf(this.dateRange));
    }

    /**
     * Gets the date range.
     *
     * @return the date range
     */
    public int getDateRange() {
        return dateRange;
    }

    /**
     * Sets the date range.
     *
     * @param dateRange
     *            the new date range
     */
    public void setDateRange(int dateRange) {
        this.dateRange = dateRange;
    }

    /**
     * Checks if is only future.
     *
     * @return true, if is only future
     */
    public boolean isOnlyFuture() {
        return onlyFuture;
    }

    /**
     * Sets the only future.
     *
     * @param onlyFuture
     *            the new only future
     */
    public void setOnlyFuture(boolean onlyFuture) {
        this.onlyFuture = onlyFuture;
    }

    /**
     * Gets the date.
     *
     * @param daysBefore
     *            the days before
     * @param daysAfter
     *            the days after
     * @return the date
     */
    private Date getDate(int daysBefore, int daysAfter) {
        rangeSupplier.setMinValue(Integer.valueOf(-daysBefore));
        rangeSupplier.setMaxValue(Integer.valueOf(daysAfter));
        final Calendar cal = Calendar.getInstance();
        cal.add(Calendar.DATE, rangeSupplier.get());
        final LocalDateTime ldt = LocalDateTime.ofInstant(cal.getTime().toInstant(), ZoneId.systemDefault());
        return Date.from(ldt.atZone(ZoneId.systemDefault()).toInstant());
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public Date get() {
        return getDate(onlyFuture ? 0 : dateRange, dateRange);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public Date getEmpty() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected Date[] createArray(int size) {
        return new Date[size];
    }

}
