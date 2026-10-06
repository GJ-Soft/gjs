package org.gjs.java.common.type;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.sql.Timestamp;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import org.junit.jupiter.api.Test;
import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.test.utils.AssertionUtils;
import org.gjs.java.common.type.GenericValue;
import org.gjs.java.test.BaseClassTest;

class GenericValueTest extends BaseClassTest<GenericValue> {

    @Test
    void testGenericValue1() {
        final GenericValue value = new GenericValue();
        logger.info("Object={}", value.toString());
        assertNull(value.getValue());
        assertNotNull(value.toString());
        assertEquals("null", value.toString());
        assertNull(value.toShort());
        assertNull(value.toInt());
        assertNull(value.toLong());
        assertNull(value.toFloat());
        assertNull(value.toDouble());
        assertNull(value.toBigDecimal());
        assertNull(value.toBigInteger());
        assertNull(value.toBoolean());
        assertNull(value.toByte());
        assertNull(value.toDate());
        assertNull(value.toChar());
        assertNull(value.toLocalDate());
        assertNull(value.toLocalDateTime());
        assertNull(value.toTimestamp());

        value.setValue(null);
        logger.info("Object={}", value.toString());
        assertNull(value.getValue());
        assertTrue(value.isNull());
        assertEquals("null", value.toString());

        value.setValue((long) 1);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertEquals("1", value.getValue());
        assertEquals("1", value.toString());
        assertNotNull(value.toLong());
        assertEquals(1, value.toLong().longValue());
        assertNotNull(value.toShort());
        assertEquals(1, value.toShort().shortValue());
        assertNotNull(value.toInt());
        assertEquals(1, value.toInt().intValue());
        assertNotNull(value.toFloat());
        assertEquals(1, value.toFloat().floatValue());
        assertNotNull(value.toDouble());
        assertEquals(1, value.toDouble().doubleValue());
        assertNotNull(value.toBoolean());
        assertEquals(true, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertEquals('1', value.toChar().charValue());
        assertNotNull(value.toByte());
        assertEquals(49, value.toByte().byteValue());
    }

    @Test
    void testGenericValue2() {
        final GenericValue value = new GenericValue((char) 1);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertEquals("\1", value.getValue());
        assertEquals("\1", value.toString());
        assertNull(value.toShort());
        assertNull(value.toInt());
        assertNull(value.toLong());
        assertNull(value.toFloat());
        assertNull(value.toDouble());
        assertNotNull(value.toBoolean());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertEquals((char) 1, value.toChar().charValue());
        assertNotNull(value.toByte());
        assertEquals(1, value.toByte().byteValue());
    }

    @Test
    void testGenericValue3() {
        final GenericValue value = new GenericValue(true);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertEquals("true", value.getValue());
        assertEquals("true", value.toString());
        assertNull(value.toShort());
        assertNull(value.toInt());
        assertNull(value.toLong());
        assertNull(value.toFloat());
        assertNull(value.toDouble());
        assertNotNull(value.toBoolean());
        assertEquals(true, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertEquals('t', value.toChar().charValue());
        assertNotNull(value.toByte());
        assertEquals(116, value.toByte().byteValue());
    }

    @Test
    void testGenericValue4() {
        final GenericValue value = new GenericValue((short) -1);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertEquals("-1", value.getValue());
        assertEquals("-1", value.toString());
        assertNotNull(value.toLong());
        assertEquals(-1, value.toLong().longValue());
        assertNotNull(value.toShort());
        assertEquals(-1, value.toShort().shortValue());
        assertNotNull(value.toInt());
        assertEquals(-1, value.toInt().intValue());
        assertNotNull(value.toFloat());
        assertEquals(-1, value.toFloat().floatValue());
        assertNotNull(value.toDouble());
        assertEquals(-1, value.toDouble().doubleValue());
        assertNotNull(value.toBoolean());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertEquals('-', value.toChar().charValue());
        assertNotNull(value.toByte());
        assertEquals(45, value.toByte().byteValue());
    }

    @Test
    void testGenericValue5() {
        final GenericValue value = new GenericValue(24);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertEquals("24", value.getValue());
        assertEquals("24", value.toString());
        assertNotNull(value.toLong());
        assertEquals(24, value.toLong().longValue());
        assertNotNull(value.toShort());
        assertEquals(24, value.toShort().shortValue());
        assertNotNull(value.toInt());
        assertEquals(24, value.toInt().intValue());
        assertNotNull(value.toFloat());
        assertEquals(24, value.toFloat().floatValue());
        assertNotNull(value.toDouble());
        assertEquals(24, value.toDouble().doubleValue());
        assertNotNull(value.toBoolean());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertEquals('2', value.toChar().charValue());
        assertNotNull(value.toByte());
        assertEquals(50, value.toByte().byteValue());
    }

    @Test
    void testGenericValue6() {
        final GenericValue value = new GenericValue((long) 108);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertEquals("108", value.getValue());
        assertEquals("108", value.toString());
        assertNotNull(value.toLong());
        assertEquals(108, value.toLong().longValue());
        assertNotNull(value.toShort());
        assertEquals(108, value.toShort().shortValue());
        assertNotNull(value.toInt());
        assertEquals(108, value.toInt().intValue());
        assertNotNull(value.toFloat());
        assertEquals(108, value.toFloat().floatValue());
        assertNotNull(value.toDouble());
        assertEquals(108, value.toDouble().doubleValue());
        assertNotNull(value.toBoolean());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertEquals('1', value.toChar().charValue());
        assertNotNull(value.toByte());
        assertEquals(49, value.toByte().byteValue());
    }

    @Test
    void testGenericValue7() {
        final GenericValue value = new GenericValue((float) -1.01);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertEquals("-1.01", value.getValue());
        assertEquals("-1.01", value.toString());
        assertNull(value.toLong());
        assertNull(value.toShort());
        assertNull(value.toInt());
        assertNotNull(value.toFloat());
        AssertionUtils.assertEqualsNumeric((float) -1.01, value.toFloat().floatValue());
        assertNotNull(value.toDouble());
        assertEquals(-1.01, value.toDouble().doubleValue());
        assertNotNull(value.toBoolean());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertEquals('-', value.toChar().charValue());
        assertNotNull(value.toByte());
        assertEquals(45, value.toByte().byteValue());
    }

    @Test
    void testGenericValue8() {
        final GenericValue value = new GenericValue(821.0100541);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertEquals("821.0100541", value.getValue());
        assertEquals("821.0100541", value.toString());
        assertNull(value.toLong());
        assertNull(value.toShort());
        assertNull(value.toInt());
        assertNotNull(value.toFloat());
        AssertionUtils.assertEqualsNumeric((float) 821.0100541,
                value.toFloat().floatValue());
        assertNotNull(value.toDouble());
        assertEquals(821.0100541, value.toDouble().doubleValue());
        assertNotNull(value.toBoolean());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertEquals('8', value.toChar().charValue());
        assertNotNull(value.toByte());
        assertEquals(56, value.toByte().byteValue());
    }

    @Test
    void testGenericValue9() {
        final GenericValue value = new GenericValue((byte) 1);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertEquals("\1", value.getValue());
        assertEquals("\1", value.toString());
        assertNull(value.toShort());
        assertNull(value.toInt());
        assertNull(value.toLong());
        assertNull(value.toFloat());
        assertNull(value.toDouble());
        assertNotNull(value.toBoolean());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertEquals((char) 1, value.toChar().charValue());
        assertNotNull(value.toByte());
        assertEquals(1, value.toByte().byteValue());
    }

    @SuppressWarnings({ "nls", "unlikely-arg-type" })
    @Test
    void testGenericValue10() {
        final GenericValue value0 = new GenericValue();
        final GenericValue value1 = new GenericValue("1");
        final GenericValue value2 = new GenericValue(1);
        final GenericValue value3 = new GenericValue(1.0);
        logger.info("Object0={} Hash={}", value0.toString(), value0.hashCode());
        logger.info("Object1={} Hash={}", value1.toString(), value1.hashCode());
        logger.info("Object2={} Hash={}", value2.toString(), value2.hashCode());
        logger.info("Object3={} Hash={}", value3.toString(), value3.hashCode());
        assertFalse(value1.equals(null));
        assertFalse(value1.equals("null"));
        assertFalse(value1.equals(value0));
        assertTrue(value0.equals(value0));
        assertTrue(value1.equals(value1));
        assertTrue(value1.equals(value2));
        assertFalse(value1.equals(value3));
        assertTrue(value0.equals(null));
        assertTrue(value0.equals("null"));
        assertNotNull(value0.hashCode());
        assertNotNull(value1.hashCode());
        assertNotNull(value2.hashCode());
        assertNotNull(value3.hashCode());
    }

    @Test
    void testGenericValue11() {
        final GenericValue value0 = new GenericValue();
        final GenericValue value1 = new GenericValue("1");
        final GenericValue value2 = new GenericValue(1);
        final GenericValue value3 = new GenericValue(1.0);
        logger.info("Object0={} Hash={}", value0.toString(), value0.hashCode());
        logger.info("Object1={} Hash={}", value1.toString(), value1.hashCode());
        logger.info("Object2={} Hash={}", value2.toString(), value2.hashCode());
        logger.info("Object3={} Hash={}", value3.toString(), value3.hashCode());
        assertEquals(1, value1.compareTo(null));
        assertEquals(0, value0.compareTo(null));
        assertEquals(1, value1.compareTo(value0));
        assertEquals(-1, value0.compareTo(value1));
        assertEquals(0, value1.compareTo(value1));
        assertEquals(0, value1.compareTo(value2));
        assertEquals(1, value3.compareTo(value1));
        assertEquals(-1, value1.compareTo(value3));
        assertEquals(-1, value1.compareTo("2"));
        assertEquals(-1, value1.compareTo("2"));
        assertEquals(0, value1.compareTo("1"));
        assertEquals(0, value0.compareTo("null"));
    }

    @Test
    void testGenericValue12() {
        final List<GenericValue> list = new ArrayList<>();
        list.add(new GenericValue());
        list.add(new GenericValue("1"));
        list.add(new GenericValue(1));
        list.add(new GenericValue(1.0));
        for (final GenericValue value1 : list) {
            for (final GenericValue value2 : list) {
                logger.info("Value1={}", value1);
                logger.info("value2={}", value2);
                assertEquals(value1.compareTo(value2), -value2.compareTo(value1));
                assertEquals(value1.equals(value2), value2.equals(value1));
                assertEquals(value1.equals(value2), (value1.compareTo(value2) == 0));
            }
        }
    }

    @Test
    void testGenericValue13() {
        final GenericValue value = new GenericValue(BigDecimal.ONE);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertEquals("1", value.getValue());
        assertEquals("1", value.toString());
        assertNotNull(value.toShort());
        assertNotNull(value.toInt());
        assertNotNull(value.toLong());
        assertNotNull(value.toFloat());
        assertNotNull(value.toDouble());
        assertNotNull(value.toBoolean());
        assertNotNull(value.toBigDecimal());
        assertNotNull(value.toBigInteger());
        assertNull(value.toDate());
        assertNull(value.toLocalDateTime());
        assertNull(value.toLocalDate());
        assertNull(value.toTimestamp());
        assertEquals(BigDecimal.ONE, value.toBigDecimal());
        assertEquals(BigInteger.ONE, value.toBigInteger());
        assertEquals(1, value.toShort().shortValue());
        assertEquals(1, value.toInt().intValue());
        assertEquals(1, value.toLong().longValue());
        assertEquals(1, value.toFloat().floatValue());
        assertEquals(1, value.toDouble().doubleValue());
        assertEquals(true, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertEquals('1', value.toChar().charValue());
        assertNotNull(value.toByte());
        assertEquals(49, value.toByte().byteValue());
    }

    @Test
    void testGenericValue14() {
        final Date date = new Date();
        final GenericValue value = new GenericValue(date);
        logger.info("Object={}", value.toString());
        logger.info("Length={}", value.toString().length());
        logger.info("Date={}", date);
        logger.info("Object={}", value.toDate());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertNotNull("1", value.getValue());
        assertNotNull("1", value.toString());
        assertNull(value.toShort());
        assertNull(value.toInt());
        assertNull(value.toLong());
        assertNull(value.toFloat());
        assertNull(value.toDouble());
        assertNotNull(value.toBoolean());
        assertNull(value.toBigDecimal());
        assertNull(value.toBigInteger());
        assertNotNull(value.toDate());
        assertNotNull(value.toLocalDateTime());
        assertNotNull(value.toLocalDate());
        assertNotNull(value.toTimestamp());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertNotNull(value.toByte());
        AssertionUtils.assertSameSecond(date, value.toDate());
        AssertionUtils.assertSameSecond(date,
                Date.from(value.toLocalDateTime().atZone(ZoneId.systemDefault()).toInstant()));
        AssertionUtils.assertSameSecond(date, new Date(value.toTimestamp().getTime()));
        AssertionUtils.assertSameDay(date,
                Date.from(value.toLocalDate().atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));
    }

    @Test
    void testGenericValue15() {
        final LocalDateTime date = (LocalDateTime) ManagedType.LOCALDATETIME.getDefaultObject();
        final GenericValue value = new GenericValue(date);
        logger.info("Date={}", date);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertNotNull("1", value.getValue());
        assertNotNull("1", value.toString());
        assertNull(value.toShort());
        assertNull(value.toInt());
        assertNull(value.toLong());
        assertNull(value.toFloat());
        assertNull(value.toDouble());
        assertNotNull(value.toBoolean());
        assertNull(value.toBigDecimal());
        assertNotNull(value.toDate());
        assertNotNull(value.toLocalDateTime());
        assertNotNull(value.toLocalDate());
        assertNotNull(value.toTimestamp());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertNotNull(value.toByte());
        AssertionUtils.assertSameSecond(Date.from(date.atZone(ZoneId.systemDefault()).toInstant()), value.toDate());
        AssertionUtils.assertSameSecond(
                Date.from(date.atZone(ZoneId.systemDefault()).toInstant()),
                Date.from(value.toLocalDateTime().atZone(ZoneId.systemDefault()).toInstant()));
        AssertionUtils.assertSameSecond(
                Date.from(date.atZone(ZoneId.systemDefault()).toInstant()), new Date(value.toTimestamp().getTime()));
        AssertionUtils.assertSameDay(
                Date.from(date.atZone(ZoneId.systemDefault()).toInstant()),
                Date.from(value.toLocalDate().atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));
    }

    @Test
    void testGenericValue16() {
        final Timestamp date = (Timestamp) ManagedType.TIMESTAMP.getDefaultObject();
        final GenericValue value = new GenericValue(date);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertNotNull("1", value.getValue());
        assertNotNull("1", value.toString());
        assertNull(value.toShort());
        assertNull(value.toInt());
        assertNull(value.toLong());
        assertNull(value.toFloat());
        assertNull(value.toDouble());
        assertNotNull(value.toBoolean());
        assertNull(value.toBigDecimal());
        assertNotNull(value.toDate());
        assertNotNull(value.toLocalDateTime());
        assertNotNull(value.toLocalDate());
        assertNotNull(value.toTimestamp());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertNotNull(value.toByte());
        AssertionUtils.assertSameSecond(new Date(date.getTime()), value.toDate());
        AssertionUtils.assertSameSecond(new Date(date.getTime()),
                Date.from(value.toLocalDateTime().atZone(ZoneId.systemDefault()).toInstant()));
        AssertionUtils.assertSameSecond(new Date(date.getTime()),
                new Date(value.toTimestamp().getTime()));
        AssertionUtils.assertSameDay(new Date(date.getTime()),
                Date.from(value.toLocalDate().atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));
    }

    @Test
    void testGenericValue17() throws ParseException {
        final String formatted = "20240101";
        final Date date = new SimpleDateFormat("yyyyMMdd").parse(formatted);
        final GenericValue value = new GenericValue(formatted);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertNotNull("1", value.getValue());
        assertNotNull("1", value.toString());
        assertNull(value.toShort());
        assertNotNull(value.toInt());
        assertNotNull(value.toLong());
        assertNotNull(value.toFloat());
        assertNotNull(value.toDouble());
        assertNotNull(value.toBoolean());
        assertNotNull(value.toBigDecimal());
        assertNotNull(value.toDate());
        assertNotNull(value.toLocalDateTime());
        assertNotNull(value.toLocalDate());
        assertNotNull(value.toTimestamp());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertNotNull(value.toByte());
        AssertionUtils.assertSameSecond(date, value.toDate());
        AssertionUtils.assertSameSecond(date,
                Date.from(value.toLocalDateTime().atZone(ZoneId.systemDefault()).toInstant()));
        AssertionUtils.assertSameSecond(date, new Date(value.toTimestamp().getTime()));
        AssertionUtils.assertSameDay(date,
                Date.from(value.toLocalDate().atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));
    }

    @Test
    void testGenericValue18() throws ParseException {
        final String formatted = "12-06-25T10:00:00";
        final Date date = new SimpleDateFormat("dd-MM-yy'T'hh:mm:ss").parse(formatted);
        final GenericValue value = new GenericValue(formatted);
        logger.info("Object={}", value.toString());
        assertNotNull(value.getValue());
        assertFalse(value.isNull());
        assertNotNull("1", value.getValue());
        assertNotNull("1", value.toString());
        assertNull(value.toShort());
        assertNull(value.toInt());
        assertNull(value.toLong());
        assertNull(value.toFloat());
        assertNull(value.toDouble());
        assertNotNull(value.toBoolean());
        assertNull(value.toBigDecimal());
        assertNotNull(value.toDate());
        assertNotNull(value.toLocalDateTime());
        assertNotNull(value.toLocalDate());
        assertNotNull(value.toTimestamp());
        assertEquals(false, value.toBoolean().booleanValue());
        assertNotNull(value.toChar());
        assertNotNull(value.toByte());
        AssertionUtils.assertSameSecond(date, value.toDate());
        AssertionUtils.assertSameSecond(date,
                Date.from(value.toLocalDateTime().atZone(ZoneId.systemDefault()).toInstant()));
        AssertionUtils.assertSameSecond(date, new Date(value.toTimestamp().getTime()));
        AssertionUtils.assertSameDay(date,
                Date.from(value.toLocalDate().atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));
    }

    /*
     * Regresión: la comprobación de longitud era (len >= 27) && (len >= 29), así que
     * sólo pasaba por Timestamp.valueOf la forma con los nueve decimales; el resto
     * caía en toDate() y perdía la fracción de segundo.
     */
    @Test
    void testToTimestampKeepsFraction() {
        assertEquals(Timestamp.valueOf("2024-01-15 10:30:45.123"),
                new GenericValue("2024-01-15 10:30:45.123").toTimestamp());
        assertEquals(123000000, new GenericValue("2024-01-15 10:30:45.123").toTimestamp().getNanos());
        assertEquals(Timestamp.valueOf("2024-01-15 10:30:45"), new GenericValue("2024-01-15 10:30:45").toTimestamp());
        assertEquals(Timestamp.valueOf("2024-01-15 10:30:45.123456789"),
                new GenericValue("2024-01-15 10:30:45.123456789").toTimestamp());
    }

}
