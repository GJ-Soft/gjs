package org.gjs.java.common.type;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.sql.Timestamp;
import java.text.Collator;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.Instant;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.time.format.DateTimeParseException;
import java.util.Date;
import java.util.Locale;
import java.util.Objects;
import java.util.TimeZone;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.ConversionUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class GenericValue.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase que facilita la conversión de tipos de datos y nos permite representar un valor de cualquier tipo o clase de
 * datos.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class GenericValue implements Comparable<Object> {

    /** The Constant logger. */
    private static final Logger logger = LoggerFactory.getLogger(GenericValue.class);

    /** The Constant LOCALES. */
    private static final Locale[] LOCALES = { Locale.getDefault(), Locale.US };

    /** The value. */
    private String value;

    /**
     * Instantiates a new generic value.
     */
    public GenericValue() {
        setValue(null);
    }

    /**
     * Instantiates a new generic value.
     *
     * @param value
     *            the value
     */
    public GenericValue(boolean value) {
        setValue(Boolean.valueOf(value));
    }

    /**
     * Instantiates a new generic value.
     *
     * @param value
     *            the value
     */
    public GenericValue(short value) {
        setValue(Short.valueOf(value));
    }

    /**
     * Instantiates a new generic value.
     *
     * @param value
     *            the value
     */
    public GenericValue(int value) {
        setValue(Integer.valueOf(value));
    }

    /**
     * Instantiates a new generic value.
     *
     * @param value
     *            the value
     */
    public GenericValue(long value) {
        setValue(Long.valueOf(value));
    }

    /**
     * Instantiates a new generic value.
     *
     * @param value
     *            the value
     */
    public GenericValue(float value) {
        setValue(Float.valueOf(value));
    }

    /**
     * Instantiates a new generic value.
     *
     * @param value
     *            the value
     */
    public GenericValue(double value) {
        setValue(Double.valueOf(value));
    }

    /**
     * Instantiates a new generic value.
     *
     * @param value
     *            the value
     */
    public GenericValue(char value) {
        setValue(Character.valueOf(value));
    }

    /**
     * Instantiates a new generic value.
     *
     * @param value
     *            the value
     */
    public GenericValue(byte value) {
        // Con byte no interesa que convierta como un número o perdemos
        // el valor binario
        setValue(Character.valueOf((char) value));
    }

    /**
     * Instantiates a new generic value.
     *
     * @param value
     *            the value
     */
    public GenericValue(Object value) {
        setValue(value);
    }

    /**
     * Sets the value.
     *
     * @param value
     *            the new value
     */
    public void setValue(Object value) {
        this.value = null;
        if (Objects.nonNull(value)) {
            this.value = value.toString();
        }
    }

    /**
     * Checks if is null.
     *
     * @return true, if is null
     */
    public boolean isNull() {
        return Objects.isNull(value);
    }

    /**
     * To boolean.
     *
     * @return the boolean
     */
    public Boolean toBoolean() {
        Boolean res = null;
        if (Objects.nonNull(value)) {
            res = ConversionUtils.toBoolean(value);
        }
        return res;
    }

    /**
     * To short.
     *
     * @return the short
     */
    public Short toShort() {
        Short res = null;
        if (Objects.nonNull(value)) {
            try {
                res = Short.parseShort(value);
            } catch (final NumberFormatException ex) {
                logger.error(ex.getMessage(), ex);
            }
        }
        return res;
    }

    /**
     * To int.
     *
     * @return the integer
     */
    public Integer toInt() {
        Integer res = null;
        if (Objects.nonNull(value)) {
            try {
                res = Integer.parseInt(value);
            } catch (final NumberFormatException ex) {
                logger.error(ex.getMessage(), ex);
            }
        }
        return res;
    }

    /**
     * To long.
     *
     * @return the long
     */
    public Long toLong() {
        Long res = null;
        if (Objects.nonNull(value)) {
            try {
                res = Long.parseLong(value);
            } catch (final NumberFormatException e) {
                logger.warn(e.getMessage());
            }
        }
        return res;
    }

    /**
     * To float.
     *
     * @return the float
     */
    public Float toFloat() {
        Float res = null;
        if (Objects.nonNull(value)) {
            try {
                res = Float.parseFloat(value);
            } catch (final NumberFormatException ex) {
                logger.error(ex.getMessage(), ex);
            }
        }
        return res;
    }

    /**
     * To double.
     *
     * @return the double
     */
    public Double toDouble() {
        Double res = null;
        if (Objects.nonNull(value)) {
            try {
                res = Double.parseDouble(value);
            } catch (final NumberFormatException ex) {
                logger.error(ex.getMessage(), ex);
            }
        }
        return res;
    }

    /**
     * To char.
     *
     * @return the character
     */
    public Character toChar() {
        Character res = null;
        if (!StringUtils.isAllEmpty(value)) {
            res = Character.valueOf(value.charAt(0));
        }
        return res;
    }

    /**
     * To byte.
     *
     * @return the byte
     */
    public Byte toByte() {
        Byte res = null;
        if (Objects.nonNull(value)) {
            res = Byte.valueOf((byte) value.charAt(0));
        }
        return res;
    }

    /**
     * To big decimal.
     *
     * @return the big decimal
     */
    public BigDecimal toBigDecimal() {
        BigDecimal res = null;
        if (StringUtils.isNumeric(value)) {
            res = new BigDecimal(value);
        }
        return res;
    }

    /**
     * To big integer.
     *
     * @return the big integer
     */
    public BigInteger toBigInteger() {
        BigInteger res = null;
        if (StringUtils.isNumeric(value)) {
            res = new BigInteger(value);
        }
        return res;
    }

    /**
     * To date.
     *
     * @return the date
     */
    public Date toDate() {
        Date res = null;
        if (Objects.nonNull(value)) {
            logger.debug("Convirtiendo a Date {}", value);
            String valueNorm = value.replace('/', '-');
            final WrappedObject wrappedObject = WrappedObject.of(valueNorm);
            final String[] formats = possibleDateFormats(wrappedObject);
            valueNorm = (String) wrappedObject.get();
            if (Objects.nonNull(formats)) {
                res = parseFormats(valueNorm, formats);
            }
        }
        return res;
    }

    /**
     * Parses the formats.
     *
     * @param valueNorm
     *            the value norm
     * @param formats
     *            the formats
     * @return the date
     */
    private Date parseFormats(String valueNorm, String... formats) {
        Date res = null;
        for (final String format : formats) {
            for (final Locale locale : LOCALES) {
                try {
                    res = new SimpleDateFormat(format, locale).parse(valueNorm);
                    break;
                } catch (final ParseException e) {
                    logger.warn(e.getMessage());
                }
            }
            if (Objects.nonNull(res)) {
                break;
            }
        }
        return res;
    }

    /**
     * To local date time.
     *
     * @return the local date time
     */
    public LocalDateTime toLocalDateTime() {
        LocalDateTime res = null;
        if (StringUtils.length(value) == 29) {
            try {
                res = LocalDateTime.parse(value);
            } catch (final DateTimeParseException e) {
                logger.warn(e.getMessage());
            }
        }
        if (Objects.isNull(res)) {
            final Date date = toDate();
            if (Objects.nonNull(date)) {
                res = LocalDateTime.ofInstant(Instant.ofEpochMilli(date.getTime()), TimeZone.getDefault().toZoneId());
            }
        }
        return res;
    }

    /**
     * To local date.
     *
     * @return the local date
     */
    public LocalDate toLocalDate() {
        LocalDate res = null;
        final Date date = toDate();
        if (Objects.nonNull(date)) {
            res = Instant.ofEpochMilli(date.getTime()).atZone(ZoneId.systemDefault()).toLocalDate();
        }
        return res;
    }

    /**
     * To timestamp.
     *
     * @return the timestamp
     */
    public Timestamp toTimestamp() {
        Timestamp res = null;
        final int len = StringUtils.length(value);
        if ((len >= 27) && (len >= 29)) {
            try {
                res = Timestamp.valueOf(value);
            } catch (final IllegalArgumentException ex) {
                logger.error(ex.getMessage(), ex);
            }
        }
        if (Objects.isNull(res)) {
            final Date date = toDate();
            if (Objects.nonNull(date)) {
                res = new Timestamp(date.getTime());
            }
        }
        return res;
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#toString() */

    @Override
    public String toString() {
        return Objects.nonNull(value) ? value : "null";
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#hashCode() */

    @Override
    public int hashCode() {
        return Objects.hash(value);
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#equals(java.lang.Object) */

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (Objects.isNull(obj)) {
            return Objects.isNull(value);
        }
        return Objects.equals(toString(), obj.toString());
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Comparable#compareTo(java.lang.Object) */

    @Override
    public int compareTo(Object obj) {
        int res = 0;
        if (Objects.isNull(obj)) {
            res = Objects.nonNull(value) ? 1 : 0;
        } else if (ConditionUtils.oneIsTrue(Objects.isNull(obj.toString()), "null".equals(obj.toString()))) {
            res = Objects.nonNull(value) ? 1 : 0;
        } else if (Objects.isNull(value)) {
            res = -1;
        } else {
            res = Collator.getInstance().compare(toString(), obj.toString());
        }
        return res;
    }

    /**
     * Possible date formats.
     *
     * PENDIENTE: Habria que incluir mas posibilidades
     *
     * @param wrappedValue
     *            the value norm
     * @return the string[]
     */
    private String[] possibleDateFormats(WrappedObject wrappedValue) {
        String[] formats = null;
        String valueNorm = (String) wrappedValue.get();
        if (value.length() == 8) {
            formats = possibleDateFormats8(valueNorm.indexOf('-') >= 0);
        } else if (value.length() == 10) {
            formats = possibleDateFormats10(valueNorm.indexOf('-') <= 2);
        } else if (value.length() == 17) {
            formats = possibleDateFormats17(true);
        } else if (value.length() == 19) {
            formats = possibleDateFormats19(valueNorm.indexOf('-') <= 2);
        } else if (ConditionUtils.allAreTrue(ConditionUtils.oneIsTrue((value.length() == 28), (value.length() == 29)),
                (StringUtils.countMatches(value, " ") == 5))) {
            formats = new String[1];
            formats[0] = "EEE MMM dd HH:mm:ss zzz yyyy";
        } else if (ConditionUtils.allAreTrue((value.length() >= 21), (value.length() <= 29))) {
            if (value.length() > 23) {
                valueNorm = value.substring(0, 23);
            }
            formats = possibleDateFormats23(valueNorm.indexOf('-') <= 2);
        }
        wrappedValue.set(valueNorm);
        return formats;
    }

    /**
     * Possible date formats 8.
     *
     * @param latino
     *            the latino
     * @return the string[]
     */
    private String[] possibleDateFormats8(boolean latino) {
        String[] formats;
        formats = new String[1];
        if (latino) {
            formats[0] = "dd-MM-yy";
        } else {
            formats[0] = "yyyyMMdd";
        }
        return formats;
    }

    /**
     * Possible date formats 10.
     *
     * @param latino
     *            the latino
     * @return the string[]
     */
    private String[] possibleDateFormats10(boolean latino) {
        String[] formats;
        formats = new String[1];
        if (latino) {
            formats[0] = "dd-MM-yyyy";
        } else {
            formats[0] = "yyyy-MM-dd";
        }
        return formats;
    }

    /**
     * Possible date formats 17.
     *
     * @param latino
     *            the latino
     * @return the string[]
     */
    private String[] possibleDateFormats17(boolean latino) {
        String[] formats;
        formats = new String[2];
        if (latino) {
            formats[0] = "dd-MM-yy HH:mm:ss";
            formats[1] = "dd-MM-yy'T'HH:mm:ss";
        } else {
            formats[0] = "yy-MM-dd HH:mm:ss";
            formats[1] = "yy-MM-dd'T'HH:mm:ss";
        }
        return formats;
    }

    /**
     * Possible date formats 19.
     *
     * @param latino
     *            the latino
     * @return the string[]
     */
    private String[] possibleDateFormats19(boolean latino) {
        String[] formats;
        formats = new String[2];
        if (latino) {
            formats[0] = "dd-MM-yyyy HH:mm:ss";
            formats[1] = "dd-MM-yyyy'T'HH:mm:ss";
        } else {
            formats[0] = "yyyy-MM-dd HH:mm:ss";
            formats[1] = "yyyy-MM-dd'T'HH:mm:ss";
        }
        return formats;
    }

    /**
     * Possible date formats 23.
     *
     * @param latino
     *            the latino
     * @return the string[]
     */
    private String[] possibleDateFormats23(boolean latino) {
        String[] formats;
        formats = new String[2];
        if (latino) {
            formats[0] = "dd-MM-yyyy HH:mm:ss.SSS";
            formats[1] = "dd-MM-yyyy'T'HH:mm:ss.SSS";
        } else {
            formats[0] = "yyyy-MM-dd HH:mm:ss.SSS";
            formats[1] = "yyyy-MM-dd'T'HH:mm:ss.SSS";
        }
        return formats;
    }

}
