package org.gjs.java.common.test.utils;

import java.math.BigInteger;
import java.util.Collection;
import java.util.Date;
import java.util.Iterator;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.TimeUnit;
import java.util.regex.Pattern;

import org.apache.commons.lang3.ObjectUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.util.CalculusUtils;
import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.ConversionUtils;
import org.opentest4j.AssertionFailedError;
import org.slf4j.Logger;

/**
 * The Class AssertionUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Algunas assertions customizadas para utilizar en los test automatizados.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class AssertionUtils {

	/** The Constant EPSILON_FLOAT. */
	private static final float EPSILON_FLOAT = CalculusUtils.epsilonFloat();

	/** The Constant EPSILON_DOUBLE. */
	private static final double EPSILON_DOUBLE = CalculusUtils.epsilonDouble();

	/** The Constant ASSERTION_WARNIG_MESSAGE_FORMAT. */
	private static final String ASSERTION_WARNIG_MESSAGE_FORMAT = "%s: Expected=%s; Actual=%s";

	/** The Constant ASSERTION_COLLECTION_MESSAGE_FORMAT. */
	private static final String ASSERTION_COLLECTION_MESSAGE_FORMAT = "%s: %s";

	/** The Constant ASSERTION_DIFFERENT_ITEM_FORMAT. */
	private static final String ASSERTION_DIFFERENT_ITEM_FORMAT = "Item %s: Expected=%s; Actual=%s";

	/** The Constant ASSERTION_DIFFERENT_KEY_FORMAT. */
	private static final String ASSERTION_DIFFERENT_KEY_FORMAT = "Key %s: Expected=%s; Actual=%s";

	/** The Constant ASSERTION_PATTERN_NOT_MATCHES. */
	private static final String ASSERTION_PATTERN_NOT_MATCHES = "Value %s not macthes pattern %s";

	/**
	 * Clase no instanciable.
	 */
	private AssertionUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Assert matches.
	 *
	 * @param pattern the pattern
	 * @param value   the value
	 */
	public static void assertMatches(String pattern, String value) {
		boolean res = false;
		if (ConditionUtils.allAreTrue(Objects.nonNull(pattern), Objects.nonNull(value))) {
			res = Pattern.compile(pattern).matcher(value).matches();
		}
		org.junit.jupiter.api.Assertions.assertTrue(res, String.format(ASSERTION_PATTERN_NOT_MATCHES, value, pattern));
	}

	/**
	 * Assert equals numeric.
	 *
	 * @param expected the expected
	 * @param actual   the actual
	 */
	public static void assertEqualsNumeric(float expected, float actual) {
		org.junit.jupiter.api.Assertions.assertTrue(Math.abs(expected - actual) < EPSILON_FLOAT);
	}

	/**
	 * Assert equals numeric.
	 *
	 * @param expected the expected
	 * @param actual   the actual
	 */
	public static void assertEqualsNumeric(double expected, double actual) {
		org.junit.jupiter.api.Assertions.assertTrue(Math.abs(expected - actual) < EPSILON_DOUBLE);
	}

	/**
	 * Assert equals int.
	 *
	 * @param expected the expected
	 * @param actual   the actual
	 */
	public static void assertEqualsInt(BigInteger expected, BigInteger actual) {
		if (ObjectUtils.anyNull(expected, actual)) {
			throw new AssertionFailedError("Null value");
		}
		org.junit.jupiter.api.Assertions.assertTrue(expected.equals(actual));
	}

	/**
	 * Assert equals as warning.
	 *
	 * @param expected the expected
	 * @param actual   the actual
	 * @param message  the message
	 * @param logger   the logger
	 */
	public static void assertEqualsAsWarning(Object expected, Object actual, String message, Logger logger) {
		try {
			org.junit.jupiter.api.Assertions.assertEquals(expected, actual, message);
		} catch (final AssertionFailedError e) {
			if (Objects.nonNull(logger)) {
				logger.warn(String.format(ASSERTION_WARNIG_MESSAGE_FORMAT, message, expected, actual));
			}
		}

	}

	/**
	 * Assert same day.
	 *
	 * @param expected the expected
	 * @param actual   the actual
	 */
	public static void assertSameDay(Date expected, Date actual) {
		assertEqualsDate(expected, actual, TimeUnit.DAYS);
	}

	/**
	 * Assert same hour.
	 *
	 * @param expected the expected
	 * @param actual   the actual
	 */
	public static void assertSameHour(Date expected, Date actual) {
		assertEqualsDate(expected, actual, TimeUnit.HOURS);
	}

	/**
	 * Assert same second.
	 *
	 * @param expected the expected
	 * @param actual   the actual
	 */
	public static void assertSameSecond(Date expected, Date actual) {
		assertEqualsDate(expected, actual, TimeUnit.SECONDS);
	}

	/**
	 * Assert equals.
	 *
	 * @param expected the expected
	 * @param actual   the actual
	 * @param message  the message
	 */
	public static void assertCollectionEquals(Collection<?> expected, Collection<?> actual, String message) {
		org.junit.jupiter.api.Assertions.assertEquals(Objects.isNull(expected), Objects.isNull(actual),
				String.format(ASSERTION_COLLECTION_MESSAGE_FORMAT, message, "One is null and the other not"));
		if (ConditionUtils.allAreTrue(Objects.nonNull(expected), Objects.nonNull(actual))) {
			org.junit.jupiter.api.Assertions.assertEquals(expected.size(), actual.size(),
					String.format(ASSERTION_COLLECTION_MESSAGE_FORMAT, message, "Different size"));

			final Iterator<?> iteratorExpected = expected.iterator();
			final Iterator<?> iteratorActual = actual.iterator();
			int i = 0;
			while (iteratorExpected.hasNext() && iteratorActual.hasNext()) {
				final Object itemExpected = iteratorExpected.next();
				final Object itemActual = iteratorActual.next();
				org.junit.jupiter.api.Assertions.assertEquals(itemExpected, itemActual,
						String.format(ASSERTION_COLLECTION_MESSAGE_FORMAT, message,
								String.format(ASSERTION_DIFFERENT_ITEM_FORMAT, i, itemExpected, itemActual)));
				i = i + 1;
			}
		}
	}

	/**
	 * Assert collection equals.
	 *
	 * @param expected the expected
	 * @param actual   the actual
	 * @param message  the message
	 */
	public static void assertCollectionEquals(Map<?, ?> expected, Map<?, ?> actual, String message) {
		org.junit.jupiter.api.Assertions.assertEquals(Objects.isNull(expected), Objects.isNull(actual),
				String.format(ASSERTION_COLLECTION_MESSAGE_FORMAT, message, "One is null and the other not"));
		if (ConditionUtils.allAreTrue(Objects.nonNull(expected), Objects.nonNull(actual))) {
			org.junit.jupiter.api.Assertions.assertEquals(expected.size(), actual.size(),
					String.format(ASSERTION_COLLECTION_MESSAGE_FORMAT, message, "Different size"));

			final Iterator<?> iteratorExpected = expected.keySet().iterator();
			final Iterator<?> iteratorActual = actual.keySet().iterator();
			int i = 0;
			while (iteratorExpected.hasNext() && iteratorActual.hasNext()) {
				final Object keyExpected = iteratorExpected.next();
				final Object keyActual = iteratorActual.next();
				org.junit.jupiter.api.Assertions.assertEquals(keyExpected, keyActual,
						String.format(ASSERTION_COLLECTION_MESSAGE_FORMAT, message,
								String.format(ASSERTION_DIFFERENT_KEY_FORMAT, i, keyExpected, keyActual)));

				final Object itemExpected = expected.get(keyExpected);
				final Object itemActual = actual.get(keyActual);
				org.junit.jupiter.api.Assertions.assertEquals(itemExpected, itemActual,
						String.format(ASSERTION_COLLECTION_MESSAGE_FORMAT, message,
								String.format(ASSERTION_DIFFERENT_ITEM_FORMAT, i, itemExpected, itemActual)));
				i = i + 1;
			}
		}
	}

	/**
	 * Assert equals date.
	 *
	 * @param expected the expected
	 * @param actual   the actual
	 * @param timeUnit the time unit
	 */
	private static void assertEqualsDate(Date expected, Date actual, TimeUnit timeUnit) {
		if (ConditionUtils.allAreTrue(Objects.nonNull(expected), Objects.nonNull(actual))) {
			final long diffInMillies = actual.getTime() - expected.getTime();
			org.junit.jupiter.api.Assertions.assertEquals(0, timeUnit.convert(diffInMillies, TimeUnit.MILLISECONDS));
		} else if (Objects.isNull(expected)) {
			org.junit.jupiter.api.Assertions.assertNull(actual);
		} else {
			org.junit.jupiter.api.Assertions.fail(formatValues(expected, actual));
		}
	}

	/**
	 * Format values.
	 *
	 * @param expected the expected
	 * @param actual   the actual
	 * @return the string
	 */
	private static String formatValues(Object expected, Object actual) {
		final String expectedString = ConversionUtils.toString(expected);
		final String actualString = ConversionUtils.toString(actual);
		if (expectedString.equals(actualString)) {
			return String.format("expected: %s but was: %s", formatClassAndValue(expected, expectedString),
					formatClassAndValue(actual, actualString));
		}
		return String.format("expected: <%s> but was: <%s>", expectedString, actualString);
	}

	/**
	 * Format class and value.
	 *
	 * @param value       the value
	 * @param valueString the value string
	 * @return the string
	 */
	private static String formatClassAndValue(Object value, String valueString) {
		final String classAndHash = getClassName(value) + toHash(value);
		// if it's a class, there's no need to repeat the class name contained in the
		// valueString.
		return (value instanceof Class ? String.format("<%s>", classAndHash)
				: String.format("%s<%s>", classAndHash, valueString));
	}

	/**
	 * Gets the class name.
	 *
	 * @param obj the obj
	 * @return the class name
	 */
	private static String getClassName(Object obj) {
		return (Objects.isNull(obj) ? "null"
				: obj instanceof Class ? ((Class<?>) obj).getCanonicalName() : obj.getClass().getName());
	}

	/**
	 * To hash.
	 *
	 * @param obj the obj
	 * @return the string
	 */
	private static String toHash(Object obj) {
		return (Objects.isNull(obj) ? "" : String.format("@%s", Integer.toHexString(System.identityHashCode(obj))));
	}

}
