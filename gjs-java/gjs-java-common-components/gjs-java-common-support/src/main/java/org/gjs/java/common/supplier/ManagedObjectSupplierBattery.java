package org.gjs.java.common.supplier;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.sql.Timestamp;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Date;

import org.gjs.java.common.supplier.random.RandomAlphanumericStringSupplier;
import org.gjs.java.common.supplier.random.RandomBigDecimalSupplier;
import org.gjs.java.common.supplier.random.RandomBigIntegerSupplier;
import org.gjs.java.common.supplier.random.RandomDateSupplier;
import org.gjs.java.common.supplier.random.RandomExceptionSupplier;
import org.gjs.java.common.supplier.random.RandomLocalDateSupplier;
import org.gjs.java.common.supplier.random.RandomLocalDateTimeSupplier;
import org.gjs.java.common.supplier.random.RandomTimestampSupplier;

/**
 * The Class ManagedObjectSupplierBattery.
 *
 * Clase de datos de la librería Gjs
 *
 * Generador de objetos aleatorios para todos las clases de datos incluidas en el enumerado ManagedType de tipos
 * gestionados.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class ManagedObjectSupplierBattery {

    /** The string supplier. */
    private final GjsSupplier<String> stringSupplier = new RandomAlphanumericStringSupplier(50, false, false);

    /** The big decimal supplier. */
    private final GjsSupplier<BigDecimal> bigDecimalSupplier = new RandomBigDecimalSupplier();

    /** The big integer supplier. */
    private final GjsSupplier<BigInteger> bigIntegerSupplier = new RandomBigIntegerSupplier();

    /** The date supplier. */
    private final GjsSupplier<Date> dateSupplier = new RandomDateSupplier();

    /** The localDateTime supplier. */
    private final GjsSupplier<LocalDateTime> localDateTimeSupplier = new RandomLocalDateTimeSupplier();

    /** The localDate supplier. */
    private final GjsSupplier<LocalDate> localDateSupplier = new RandomLocalDateSupplier();

    /** The timestamp supplier. */
    private final GjsSupplier<Timestamp> timestampSupplier = new RandomTimestampSupplier();

    /** The exception supplier. */
    private final GjsSupplier<Exception> exceptionSupplier = new RandomExceptionSupplier();

    /**
     * Random string.
     *
     * @return random value
     */
    public String randomString() {
        return stringSupplier.get();
    }

    /**
     * Random date.
     *
     * @return random value
     */
    public Date randomDate() {
        return dateSupplier.get();
    }

    /**
     * Random LocalDateTime.
     *
     * @return random value
     */
    public LocalDateTime randomLocalDateTime() {
        return localDateTimeSupplier.get();
    }

    /**
     * Random LocalDate.
     *
     * @return random value
     */
    public LocalDate randomLocalDate() {
        return localDateSupplier.get();
    }

    /**
     * Random Timestamp.
     *
     * @return random value
     */
    public Timestamp randomTimestamp() {
        return timestampSupplier.get();
    }

    /**
     * Random big decimal.
     *
     * @return random value
     */
    public BigDecimal randomBigDecimal() {
        return bigDecimalSupplier.get();
    }

    /**
     * Random big integer.
     *
     * @return random value
     */
    public BigInteger randomBigInteger() {
        return bigIntegerSupplier.get();
    }

    /**
     * Random exception.
     *
     * @return random value
     */
    public Exception randomException() {
        return exceptionSupplier.get();
    }

    /**
     * Random string.
     *
     * @return random value
     */
    public String emptyString() {
        return stringSupplier.getEmpty();
    }

    /**
     * Random date.
     *
     * @return random value
     */
    public Date emptyDate() {
        return dateSupplier.getEmpty();
    }

    /**
     * Empty local date time.
     *
     * @return the local date time
     */
    public LocalDateTime emptyLocalDateTime() {
        return localDateTimeSupplier.getEmpty();
    }

    /**
     * Empty local date.
     *
     * @return the local date
     */
    public LocalDate emptyLocalDate() {
        return localDateSupplier.getEmpty();
    }

    /**
     * Empty Timestamp.
     *
     * @return random value
     */
    public Timestamp emptyTimestamp() {
        return timestampSupplier.getEmpty();
    }

    /**
     * Empty big decimal.
     *
     * @return random value
     */
    public BigDecimal emptyBigDecimal() {
        return bigDecimalSupplier.getEmpty();
    }

    /**
     * Empty big integer.
     *
     * @return random value
     */
    public BigInteger emptyBigInteger() {
        return bigIntegerSupplier.getEmpty();
    }

    /**
     * Empty exception.
     *
     * @return random value
     */
    public Exception emptyException() {
        return exceptionSupplier.getEmpty();
    }

    /**
     * Random Array string.
     *
     * @return randomArray value
     */
    public String[] randomArrayString() {
        return stringSupplier.getArray();
    }

    /**
     * Random Array date.
     *
     * @return randomArray value
     */
    public Date[] randomArrayDate() {
        return dateSupplier.getArray();
    }

    /**
     * Random array local date time.
     *
     * @return the local date time[]
     */
    public LocalDateTime[] randomArrayLocalDateTime() {
        return localDateTimeSupplier.getArray();
    }

    /**
     * Random array local date.
     *
     * @return the local date[]
     */
    public LocalDate[] randomArrayLocalDate() {
        return localDateSupplier.getArray();
    }

    /**
     * Random Array timestamp.
     *
     * @return randomArray value
     */
    public Timestamp[] randomArrayTimestamp() {
        return timestampSupplier.getArray();
    }

    /**
     * Random Array big decimal.
     *
     * @return randomArray value
     */
    public BigDecimal[] randomArrayBigDecimal() {
        return bigDecimalSupplier.getArray();
    }

    /**
     * Random Array big integer.
     *
     * @return randomArray value
     */
    public BigInteger[] randomArrayBigInteger() {
        return bigIntegerSupplier.getArray();
    }

    /**
     * Random Array exception.
     *
     * @return randomArray value
     */
    public Exception[] randomArrayException() {
        return exceptionSupplier.getArray();
    }

    /**
     * Empty Array string.
     *
     * @return randomArray value
     */
    public String[] emptyArrayString() {
        return stringSupplier.getEmptyArray();
    }

    /**
     * Empty Array date.
     *
     * @return randomArray value
     */
    public Date[] emptyArrayDate() {
        return dateSupplier.getEmptyArray();
    }

    /**
     * Empty array local date time.
     *
     * @return the local date time[]
     */
    public LocalDateTime[] emptyArrayLocalDateTime() {
        return localDateTimeSupplier.getEmptyArray();
    }

    /**
     * Empty array local date.
     *
     * @return the local date[]
     */
    public LocalDate[] emptyArrayLocalDate() {
        return localDateSupplier.getEmptyArray();
    }

    /**
     * Empty Array timestamp.
     *
     * @return randomArray value
     */
    public Timestamp[] emptyArrayTimestamp() {
        return timestampSupplier.getEmptyArray();
    }

    /**
     * Empty Array big decimal.
     *
     * @return randomArray value
     */
    public BigDecimal[] emptyArrayBigDecimal() {
        return bigDecimalSupplier.getEmptyArray();
    }

    /**
     * Empty Array big integer.
     *
     * @return randomArray value
     */
    public BigInteger[] emptyArrayBigInteger() {
        return bigIntegerSupplier.getEmptyArray();
    }

    /**
     * Empty Array exception.
     *
     * @return randomArray value
     */
    public Exception[] emptyArrayException() {
        return exceptionSupplier.getEmptyArray();
    }

}
