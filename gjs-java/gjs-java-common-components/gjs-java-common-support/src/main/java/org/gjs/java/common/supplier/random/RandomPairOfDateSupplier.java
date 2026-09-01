package org.gjs.java.common.supplier.random;

import java.lang.reflect.Array;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Calendar;
import java.util.Date;

import org.apache.commons.lang3.tuple.ImmutablePair;
import org.apache.commons.lang3.tuple.Pair;

/**
 * Random Date supplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de rangos de fecha aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomPairOfDateSupplier extends AbstractRandomSupplier<Pair<Date, Date>> {

    /** The Constant DEFAULT_DATE_RANGE. */
    public static final int DEFAULT_DATE_RANGE = 50;

    /** The date range. */
    private int dateRange;

    /** The range supplier. */
    private final RandomIntegerSupplier rangeSupplier;

    /**
     * Instantiates a new random pair of date supplier.
     */
    public RandomPairOfDateSupplier() {
        this(DEFAULT_DATE_RANGE);
    }

    /**
     * Instantiates a new random pair of date supplier.
     *
     * @param dateRange
     *            the date range
     */
    public RandomPairOfDateSupplier(int dateRange) {
        this.dateRange = Integer.max(dateRange, 0);
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
     * Gets the date.
     *
     * @param dayStart
     *            the relative day starting interval
     * @param dayEnd
     *            the relative day ending interval
     * @return the date
     */
    private Date getDate(int dayStart, int dayEnd) {
        rangeSupplier.setMinValue(Integer.valueOf(dayStart));
        rangeSupplier.setMaxValue(Integer.valueOf(dayEnd));
        final Calendar cal = Calendar.getInstance();
        cal.add(Calendar.DATE, rangeSupplier.get());
        final LocalDateTime ldt = LocalDateTime.ofInstant(cal.getTime().toInstant(), ZoneId.systemDefault());
        return Date.from(ldt.atZone(ZoneId.systemDefault()).toInstant());
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.testinggame.suppliers.Supplier#get() */

    @Override
    public Pair<Date, Date> get() {
        return new ImmutablePair<>(getDate(-dateRange, -1), getDate(0, dateRange));
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.Supplier#getEmpty() */

    @Override
    public Pair<Date, Date> getEmpty() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @SuppressWarnings("unchecked")
    @Override
    protected Pair<Date, Date>[] createArray(int size) {
        return (Pair<Date, Date>[]) Array.newInstance(ImmutablePair.class, size);
    }

}
