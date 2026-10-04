package org.gjs.java.common.util;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.ZoneId;
import java.util.Date;

import org.junit.jupiter.api.Test;
import org.gjs.java.common.util.DateUtils;
import org.gjs.java.test.BaseClassTest;

class DateUtilsTest extends BaseClassTest<DateUtils> {

    @Test
    void testStartOfDay() {
        final SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        try {
            assertNull(DateUtils.startOfDay(null));
            final Date date = sdf.parse("2021-04-23 11:45:56");
            final Date result = DateUtils.startOfDay(date);
            final String formatted = sdf.format(result);
            assertEquals("2021-04-23 00:00:00", formatted);
        } catch (final ParseException e) {
            fail(
                    "Recibida excepcion: "
                            + e.getMessage()
            );
        }
    }

    @Test
    void testEndOfDay() {
        final SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        try {
            assertNull(DateUtils.endOfDay(null));
            final Date date = sdf.parse("2021-04-23 11:45:56");
            final Date result = DateUtils.endOfDay(date);
            final String formatted = sdf.format(result);
            assertEquals("2021-04-23 23:59:59", formatted);
        } catch (final ParseException e) {
            fail(
                    "Recibida excepcion: "
                            + e.getMessage()
            );
        }
    }

    @Test
    void testYesterdayAndTomorrow() {
        final Date yesterday = DateUtils.yesterday();
        final Date tomorrow = DateUtils.tomorrow();
        final Date now = new Date();
        assertTrue(yesterday.before(now));
        assertTrue(tomorrow.after(now));
    }

    @Test
    void testBeforeOrEqual1() {
        final Date yesterday = DateUtils.yesterday();
        final Date tomorrow = DateUtils.tomorrow();
        final Date now = new Date();
        final Date nullius = null;
        assertTrue(DateUtils.beforeOrEqual(yesterday, now));
        assertTrue(DateUtils.beforeOrEqual(yesterday, tomorrow));
        assertTrue(DateUtils.beforeOrEqual(now, tomorrow));
        assertFalse(DateUtils.beforeOrEqual(now, yesterday));
        assertFalse(DateUtils.beforeOrEqual(tomorrow, yesterday));
        assertFalse(DateUtils.beforeOrEqual(tomorrow, now));
        assertTrue(DateUtils.beforeOrEqual(DateUtils.endOfDay(now), DateUtils.startOfDay(now)));

        assertTrue(DateUtils.beforeOrEqual(now, nullius));
        assertFalse(DateUtils.beforeOrEqual(nullius, now));
        assertTrue(DateUtils.beforeOrEqual(nullius, nullius));
    }

    @Test
    void testAfterOrEqual1() {
        final Date yesterday = DateUtils.yesterday();
        final Date tomorrow = DateUtils.tomorrow();
        final Date now = new Date();
        final Date nullius = null;
        assertFalse(DateUtils.afterOrEqual(yesterday, now));
        assertFalse(DateUtils.afterOrEqual(yesterday, tomorrow));
        assertFalse(DateUtils.afterOrEqual(now, tomorrow));
        assertTrue(DateUtils.afterOrEqual(now, yesterday));
        assertTrue(DateUtils.afterOrEqual(tomorrow, yesterday));
        assertTrue(DateUtils.afterOrEqual(tomorrow, now));
        assertTrue(DateUtils.afterOrEqual(DateUtils.endOfDay(now), DateUtils.startOfDay(now)));

        assertFalse(DateUtils.afterOrEqual(now, nullius));
        assertTrue(DateUtils.afterOrEqual(nullius, now));
        assertTrue(DateUtils.afterOrEqual(nullius, nullius));
    }

    @Test
    void testBeforeOrEqual2() {
        final LocalDate yesterday = LocalDate.now(ZoneId.systemDefault()).minusDays(1);
        final LocalDate tomorrow = LocalDate.now(ZoneId.systemDefault()).plusDays(1);
        final LocalDate now = LocalDate.now(ZoneId.systemDefault());
        final LocalDate nullius = null;
        assertTrue(DateUtils.beforeOrEqual(yesterday, now));
        assertTrue(DateUtils.beforeOrEqual(yesterday, tomorrow));
        assertTrue(DateUtils.beforeOrEqual(now, tomorrow));
        assertFalse(DateUtils.beforeOrEqual(now, yesterday));
        assertFalse(DateUtils.beforeOrEqual(tomorrow, yesterday));
        assertFalse(DateUtils.beforeOrEqual(tomorrow, now));
        assertTrue(DateUtils.beforeOrEqual(now, now));

        assertTrue(DateUtils.beforeOrEqual(now, nullius));
        assertFalse(DateUtils.beforeOrEqual(nullius, now));
        assertTrue(DateUtils.beforeOrEqual(nullius, nullius));
    }

    @Test
    void testAfterOrEqual2() {
        final LocalDate yesterday = LocalDate.now(ZoneId.systemDefault()).minusDays(1);
        final LocalDate tomorrow = LocalDate.now(ZoneId.systemDefault()).plusDays(1);
        final LocalDate now = LocalDate.now(ZoneId.systemDefault());
        final LocalDate nullius = null;
        assertFalse(DateUtils.afterOrEqual(yesterday, now));
        assertFalse(DateUtils.afterOrEqual(yesterday, tomorrow));
        assertFalse(DateUtils.afterOrEqual(now, tomorrow));
        assertTrue(DateUtils.afterOrEqual(now, yesterday));
        assertTrue(DateUtils.afterOrEqual(tomorrow, yesterday));
        assertTrue(DateUtils.afterOrEqual(tomorrow, now));
        assertTrue(DateUtils.afterOrEqual(now, now));

        assertFalse(DateUtils.afterOrEqual(now, nullius));
        assertTrue(DateUtils.afterOrEqual(nullius, now));
        assertTrue(DateUtils.afterOrEqual(nullius, nullius));
    }

    @Test
    void testDaysBetween1() {
        final Date yesterday = DateUtils.yesterday();
        try {
            Thread.sleep(10);
        } catch (final InterruptedException e) {
        }
        final Date now = new Date();
        try {
            Thread.sleep(10);
        } catch (final InterruptedException e) {
        }
        final Date tomorrow = DateUtils.tomorrow();
        assertEquals(0, DateUtils.daysBetween(null, null));
        assertEquals(Long.MAX_VALUE, DateUtils.daysBetween(null, now));
        assertEquals(Long.MIN_VALUE, DateUtils.daysBetween(now, null));
        assertEquals(1, DateUtils.daysBetween(now, tomorrow));
        assertEquals(-1, DateUtils.daysBetween(now, yesterday));
        assertEquals(2, DateUtils.daysBetween(yesterday, tomorrow));
        assertEquals(-2, DateUtils.daysBetween(tomorrow, yesterday));
        final Date date1 = DateUtils.relativeToToday(-11);
        final Date date2 = DateUtils.relativeToToday(7);
        logger.info("Date1={}", date1);
        logger.info("Date2={}", date2);
        assertEquals(18, DateUtils.daysBetween(date1, date2));
    }

    @Test
    void testDaysBetween2() throws ParseException {
        final SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        // Winter date
        final Date dateW1 = sdf.parse("2024-01-15");
        final Date dateW2 = sdf.parse("2024-01-25");
        final Date dateW3 = sdf.parse("2024-03-25");
        // Summer date
        final Date dateS1 = sdf.parse("2024-04-15");
        final Date dateS2 = sdf.parse("2024-04-25");
        final Date dateS3 = sdf.parse("2024-04-04");
        logger.info("DateW1={}", dateW1);
        logger.info("DateW2={}", dateW2);
        logger.info("DateW3={}", dateW2);
        logger.info("DateS1={}", dateS1);
        logger.info("DateS2={}", dateS2);
        logger.info("DateS3={}", dateS3);
        assertEquals(10, DateUtils.daysBetween(dateW1, dateW2));
        assertEquals(10, DateUtils.daysBetween(dateS1, dateS2));
        assertEquals(10, DateUtils.daysBetween(dateW3, dateS3));
    }

    @Test
    void testIsValidEndDate1() {
        final Date nullDate = null;
        final Date yesterday = DateUtils.yesterday();
        final Date tomorrow = DateUtils.tomorrow();
        final Date now = new Date();
        assertTrue(DateUtils.isValidEndDate(nullDate));
        assertFalse(DateUtils.isValidEndDate(yesterday));
        assertTrue(DateUtils.isValidEndDate(now));
        assertTrue(DateUtils.isValidEndDate(tomorrow));
    }

    @Test
    void testIsValidEndDate2() {
        final LocalDate nullDate = null;
        final LocalDate now = LocalDate.now(ZoneId.systemDefault());
        final LocalDate yesterday = now.minusDays(1);
        final LocalDate tomorrow = now.plusDays(1);
        assertTrue(DateUtils.isValidEndDate(nullDate));
        assertFalse(DateUtils.isValidEndDate(yesterday));
        assertTrue(DateUtils.isValidEndDate(now));
        assertTrue(DateUtils.isValidEndDate(tomorrow));
    }

    @Test
    void testIsValidDateRange1() {
        final Date nullDate = null;
        final Date yesterday = DateUtils.yesterday();
        final Date tomorrow = DateUtils.tomorrow();
        final Date now = new Date();
        assertTrue(DateUtils.isValidDateRange(nullDate, nullDate));
        assertTrue(DateUtils.isValidDateRange(nullDate, tomorrow));
        assertTrue(DateUtils.isValidDateRange(yesterday, nullDate));
        assertTrue(DateUtils.isValidDateRange(now, nullDate));
        assertTrue(DateUtils.isValidDateRange(nullDate, now));
        assertFalse(DateUtils.isValidDateRange(nullDate, yesterday));
        assertFalse(DateUtils.isValidDateRange(yesterday, yesterday));
        assertTrue(DateUtils.isValidDateRange(yesterday, now));
        assertTrue(DateUtils.isValidDateRange(yesterday, tomorrow));
        assertFalse(DateUtils.isValidDateRange(tomorrow, yesterday));
    }

    @Test
    void testIsValidDateRange2() {
        final LocalDate nullDate = null;
        final LocalDate now = LocalDate.now(ZoneId.systemDefault());
        final LocalDate yesterday = now.minusDays(1);
        final LocalDate tomorrow = now.plusDays(1);
        assertTrue(DateUtils.isValidDateRange(nullDate, nullDate));
        assertTrue(DateUtils.isValidDateRange(nullDate, tomorrow));
        assertTrue(DateUtils.isValidDateRange(yesterday, nullDate));
        assertTrue(DateUtils.isValidDateRange(now, nullDate));
        assertTrue(DateUtils.isValidDateRange(nullDate, now));
        assertFalse(DateUtils.isValidDateRange(nullDate, yesterday));
        assertFalse(DateUtils.isValidDateRange(yesterday, yesterday));
        assertTrue(DateUtils.isValidDateRange(yesterday, now));
        assertTrue(DateUtils.isValidDateRange(yesterday, tomorrow));
        assertFalse(DateUtils.isValidDateRange(tomorrow, yesterday));
    }

    @Test
    void testBefore() {
        final Date yesterday = DateUtils.yesterday();
        final Date tomorrow = DateUtils.tomorrow();
        final Date now = new Date();
        final Date future = null;
        assertTrue(DateUtils.before(yesterday, now));
        assertTrue(DateUtils.before(yesterday, tomorrow));
        assertTrue(DateUtils.before(now, tomorrow));
        assertFalse(DateUtils.before(now, yesterday));
        assertFalse(DateUtils.before(tomorrow, yesterday));
        assertFalse(DateUtils.before(tomorrow, now));
        assertFalse(DateUtils.before(DateUtils.startOfDay(now), DateUtils.endOfDay(now)));
        assertTrue(DateUtils.before(yesterday, future));
        assertTrue(DateUtils.before(now, future));
        assertTrue(DateUtils.before(tomorrow, future));
        assertFalse(DateUtils.before(future, future));
        assertFalse(DateUtils.before(future, yesterday));
        assertFalse(DateUtils.before(future, now));
        assertFalse(DateUtils.before(future, tomorrow));
    }

    @Test
    void testAfter() {
        final Date yesterday = DateUtils.yesterday();
        final Date tomorrow = DateUtils.tomorrow();
        final Date now = new Date();
        final Date future = null;
        assertFalse(DateUtils.after(yesterday, now));
        assertFalse(DateUtils.after(yesterday, tomorrow));
        assertFalse(DateUtils.after(now, tomorrow));
        assertTrue(DateUtils.after(now, yesterday));
        assertTrue(DateUtils.after(tomorrow, yesterday));
        assertTrue(DateUtils.after(tomorrow, now));
        assertFalse(DateUtils.after(DateUtils.endOfDay(now), DateUtils.startOfDay(now)));
        assertFalse(DateUtils.after(yesterday, future));
        assertFalse(DateUtils.after(now, future));
        assertFalse(DateUtils.after(tomorrow, future));
        assertFalse(DateUtils.after(future, future));
        assertTrue(DateUtils.after(future, yesterday));
        assertTrue(DateUtils.after(future, now));
        assertTrue(DateUtils.after(future, tomorrow));
    }

}
