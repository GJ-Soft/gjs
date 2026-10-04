package org.gjs.java.common.supplier.random;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.sql.Timestamp;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Arrays;
import java.util.Collection;
import java.util.Date;
import java.util.Set;
import java.util.TreeSet;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.exception.ExceptionUtils;
import org.apache.commons.lang3.tuple.Pair;
import org.gjs.java.common.enums.Sexo;
import org.gjs.java.common.supplier.GjsSupplier;
import org.gjs.java.common.supplier.random.AbstractRandomSupplier;
import org.gjs.java.common.supplier.random.RandomAlphanumericCharSupplier;
import org.gjs.java.common.supplier.random.RandomAlphanumericStringSupplier;
import org.gjs.java.common.supplier.random.RandomBigDecimalSupplier;
import org.gjs.java.common.supplier.random.RandomBigIntegerSupplier;
import org.gjs.java.common.supplier.random.RandomBooleanSupplier;
import org.gjs.java.common.supplier.random.RandomBytesSupplier;
import org.gjs.java.common.supplier.random.RandomDateSupplier;
import org.gjs.java.common.supplier.random.RandomDniStringSupplier;
import org.gjs.java.common.supplier.random.RandomDoubleSupplier;
import org.gjs.java.common.supplier.random.RandomEnumSupplier;
import org.gjs.java.common.supplier.random.RandomExceptionSupplier;
import org.gjs.java.common.supplier.random.RandomFloatSupplier;
import org.gjs.java.common.supplier.random.RandomIntegerSupplier;
import org.gjs.java.common.supplier.random.RandomLocalDateSupplier;
import org.gjs.java.common.supplier.random.RandomLocalDateTimeSupplier;
import org.gjs.java.common.supplier.random.RandomLongSupplier;
import org.gjs.java.common.supplier.random.RandomNullableObjectSupplier;
import org.gjs.java.common.supplier.random.RandomNieStringSupplier;
import org.gjs.java.common.supplier.random.RandomNifStringSupplier;
import org.gjs.java.common.supplier.random.RandomNumericStringSupplier;
import org.gjs.java.common.supplier.random.RandomPairOfDateSupplier;
import org.gjs.java.common.supplier.random.RandomSelectedObjectSupplier;
import org.gjs.java.common.supplier.random.RandomSelectedStringSupplier;
import org.gjs.java.common.supplier.random.RandomSexSupplier;
import org.gjs.java.common.supplier.random.RandomShortSupplier;
import org.gjs.java.common.supplier.random.RandomTimestampSupplier;
import org.gjs.java.common.util.AdministrativeUtils;
import org.gjs.java.test.AbstractClassTest;
import org.junit.jupiter.api.Test;

class RandomSuppliersSupportTest extends AbstractClassTest {

	@Override
	protected Class<?> getClazz() {
		return AbstractRandomSupplier.class;
	}

	@Test
	void testRandomAlphanumericCharSupplier() {
		try {
			final GjsSupplier<Character> supplier = new RandomAlphanumericCharSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			assertNotNull(supplier.get());
			assertNotNull(supplier.getEmpty());

			assertEquals(1, supplier.getMinSizeArrays());
			assertEquals(5, supplier.getMaxSizeArrays());

			Character[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Character element : array) {
				assertNotNull(element);
			}

			supplier.setMinSizeArrays(-1);
			supplier.setMaxSizeArrays(0);
			assertEquals(1, supplier.getMinSizeArrays());
			assertEquals(5, supplier.getMaxSizeArrays());

			supplier.setMinSizeArrays(2);
			supplier.setMaxSizeArrays(2);
			assertEquals(2, supplier.getMinSizeArrays());
			assertEquals(2, supplier.getMaxSizeArrays());
			array = supplier.getArray();
			assertNotNull(array);
			assertEquals(2, array.length);
			for (final Character element : array) {
				assertNotNull(element);
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomAlphanumericStringSupplier() {
		try {
			final RandomAlphanumericStringSupplier supplier = new RandomAlphanumericStringSupplier(10, false, false);
			logger.info("Test {}", supplier.getClass().getName());
			assertEquals(10, supplier.getMaxLength());
			assertFalse(supplier.isConstantLength());
			assertFalse(supplier.isNullable());

			supplier.setNullable(true);
			String empty = supplier.getEmpty();
			assertNull(empty);
			supplier.setNullable(false);
			supplier.setConstantLength(false);
			empty = supplier.getEmpty();
			assertNotNull(empty);
			assertEquals(0, empty.length());
			supplier.setConstantLength(true);
			empty = supplier.getEmpty();
			assertNotNull(empty);
			assertEquals(supplier.getMaxLength(), empty.length());
			assertEquals(StringUtils.repeat(' ', supplier.getMaxLength()), empty);
			supplier.setConstantLength(false);

			supplier.setNullable(false);
			for (int i = 0; i < 100; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				logger.info("Cadena={}", value);
				assertTrue(value.length() >= 0);
				assertTrue(value.length() <= 10);
			}
			supplier.setConstantLength(true);
			assertTrue(supplier.isConstantLength());
			for (int i = 0; i < 10; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				assertEquals(10, value.length());
			}
			supplier.setMaxLength(8);
			supplier.setConstantLength(false);
			supplier.setNullable(true);
			assertEquals(8, supplier.getMaxLength());
			assertFalse(supplier.isConstantLength());
			assertTrue(supplier.isNullable());
			for (int i = 0; i < 10; i = i + 1) {
				final String value = supplier.get();
				if (value != null) {
					assertTrue(value.length() >= 0);
					assertTrue(value.length() <= 8);
				}
			}

			String[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			supplier.setNullable(false);
			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final String element : array) {
				assertNotNull(element);
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomBooleanSupplier() {
		try {
			final GjsSupplier<Boolean> supplier = new RandomBooleanSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			assertNotNull(supplier.get());
			assertNotNull(supplier.getEmpty());

			Boolean[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Boolean element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomDateSupplier() {
		try {
			GjsSupplier<Date> supplier = new RandomDateSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			assertNotNull(supplier.get());
			assertNull(supplier.getEmpty());

			supplier = new RandomDateSupplier(10000, false);
			final Set<Date> set = new TreeSet<>();
			for (int i = 0; i < 10; i = i + 1) {
				final Date date = supplier.get();
				assertNotNull(date);
				logger.debug("Date={}", date);
				assertFalse(set.contains(date));
				set.add(date);
			}

			Date[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Date element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomDoubleSupplier() {
		try {
			final RandomDoubleSupplier supplier = new RandomDoubleSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			Double value = supplier.get();
			assertNotNull(value);
			supplier.setOnlyPositives(true);
			assertTrue(supplier.isOnlyPositives());
			for (int i = 0; i < 5; i = i + 1) {
				value = supplier.get();
				assertNotNull(value);
				assertTrue(value >= 0.0);
			}
			assertNotNull(supplier.getEmpty());

			Double[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Double element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomFloatSupplier() {
		try {
			final RandomFloatSupplier supplier = new RandomFloatSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			Float value = supplier.get();
			assertNotNull(value);
			supplier.setOnlyPositives(true);
			assertTrue(supplier.isOnlyPositives());
			for (int i = 0; i < 5; i = i + 1) {
				value = supplier.get();
				assertNotNull(value);
				assertTrue(value >= 0.0);
			}
			assertNotNull(supplier.getEmpty());

			Float[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Float element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomIntegerSupplier() {
		try {
			final RandomIntegerSupplier supplier = new RandomIntegerSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			supplier.setMinValue(Integer.valueOf(1));
			supplier.setMaxValue(Integer.valueOf(10));
			assertEquals(Integer.valueOf(1), supplier.getMinValue());
			assertEquals(Integer.valueOf(10), supplier.getMaxValue());
			for (int i = 0; i < 10; i = i + 1) {
				final Integer value = supplier.get();
				assertNotNull(value);
				assertTrue(value >= Integer.valueOf(1));
				assertTrue(value <= Integer.valueOf(10));
			}
			assertNotNull(supplier.getEmpty());

			Integer[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Integer element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomShortSupplier() {
		try {
			final RandomShortSupplier supplier = new RandomShortSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			supplier.setMinValue(Short.valueOf((short) 1));
			supplier.setMaxValue(Short.valueOf((short) 10));
			assertEquals(Short.valueOf((short) 1), supplier.getMinValue());
			assertEquals(Short.valueOf((short) 10), supplier.getMaxValue());
			for (int i = 0; i < 10; i = i + 1) {
				final Short value = supplier.get();
				assertNotNull(value);
				assertTrue(value >= Short.valueOf((short) 1));
				assertTrue(value <= Short.valueOf((short) 10));
			}
			assertNotNull(supplier.getEmpty());

			Short[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Short element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomLongSupplier() {
		try {
			final RandomLongSupplier supplier = new RandomLongSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			supplier.setMinValue(Long.valueOf(1));
			supplier.setMaxValue(Long.valueOf(10));
			assertEquals(Long.valueOf(1), supplier.getMinValue());
			assertEquals(Long.valueOf(10), supplier.getMaxValue());
			for (int i = 0; i < 10; i = i + 1) {
				final Long value = supplier.get();
				assertNotNull(value);
				assertTrue(value >= Long.valueOf(1));
				assertTrue(value <= Long.valueOf(10));
			}
			assertNotNull(supplier.getEmpty());

			Long[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Long element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomBigDecimalSupplier() {
		try {
			final RandomBigDecimalSupplier supplier = new RandomBigDecimalSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			assertFalse(supplier.isOnlyPositives());
			BigDecimal value = supplier.get();
			assertNotNull(value);
			supplier.setOnlyPositives(true);
			assertTrue(supplier.isOnlyPositives());
			for (int i = 0; i < 5; i = i + 1) {
				value = supplier.get();
				assertNotNull(value);
				assertTrue(value.compareTo(BigDecimal.ZERO) >= 0);
			}
			assertNull(supplier.getEmpty());

			BigDecimal[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final BigDecimal element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomBigIntegerSupplier() {
		try {
			final RandomBigIntegerSupplier supplier = new RandomBigIntegerSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			BigInteger value = supplier.get();
			assertNotNull(value);
			for (int i = 0; i < 5; i = i + 1) {
				value = supplier.get();
				assertNotNull(value);
			}
			assertNull(supplier.getEmpty());

			BigInteger[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final BigInteger element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomBytesSupplier() {
		try {
			final RandomBytesSupplier supplier = new RandomBytesSupplier(10, false, false);
			logger.info("Test {}", supplier.getClass().getName());
			assertEquals(10, supplier.getMaxLength());
			assertFalse(supplier.isConstantLength());
			assertFalse(supplier.isNullable());

			final Byte[] empty = supplier.getEmpty();
			assertNotNull(empty);
			assertEquals(0, empty.length);

			for (int i = 0; i < 10; i = i + 1) {
				final Byte[] value = supplier.get();
				assertNotNull(value);
				assertTrue(value.length >= 0);
				assertTrue(value.length <= 10);
			}
			supplier.setConstantLength(true);
			assertTrue(supplier.isConstantLength());
			for (int i = 0; i < 10; i = i + 1) {
				final Byte[] value = supplier.get();
				assertNotNull(value);
				assertEquals(10, value.length);
			}
			supplier.setMaxLength(8);
			supplier.setConstantLength(false);
			supplier.setNullable(true);
			assertEquals(8, supplier.getMaxLength());
			assertFalse(supplier.isConstantLength());
			assertTrue(supplier.isNullable());
			for (int i = 0; i < 10; i = i + 1) {
				final Byte[] value = supplier.get();
				if (value != null) {
					assertTrue(value.length >= 0);
					assertTrue(value.length <= 8);
				}
			}

			Byte[][] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Byte[] element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomPairOfDateSupplier() {
		try {
			final RandomPairOfDateSupplier supplier = new RandomPairOfDateSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			assertNull(supplier.getEmpty());
			Pair<Date, Date> value = supplier.get();
			assertNotNull(value);
			assertNotNull(value.getKey());
			assertNotNull(value.getValue());
			assertTrue(value.getKey().before(value.getValue()));
			supplier.setDateRange(10);
			assertEquals(10, supplier.getDateRange());
			for (int i = 0; i < 10; i = i + 1) {
				value = supplier.get();
				assertNotNull(value);
				assertNotNull(value.getKey());
				assertNotNull(value.getValue());
				assertTrue(value.getKey().before(value.getValue()));
			}

			Pair<Date, Date>[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Pair<Date, Date> element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomNumericStringSupplier() {
		try {
			final RandomNumericStringSupplier supplier = new RandomNumericStringSupplier(10, false, false);
			logger.info("Test {}", supplier.getClass().getName());
			assertEquals(10, supplier.getMaxLength());
			assertFalse(supplier.isConstantLength());
			assertFalse(supplier.isNullable());

			supplier.setNullable(true);
			String empty = supplier.getEmpty();
			assertNull(empty);
			supplier.setNullable(false);
			supplier.setConstantLength(false);
			empty = supplier.getEmpty();
			assertNotNull(empty);
			assertEquals(0, empty.length());
			supplier.setConstantLength(true);
			empty = supplier.getEmpty();
			assertNotNull(empty);
			assertEquals(supplier.getMaxLength(), empty.length());
			assertEquals(StringUtils.repeat('0', supplier.getMaxLength()), empty);
			supplier.setConstantLength(false);

			supplier.setNullable(false);
			for (int i = 0; i < 10; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				assertTrue(value.length() >= 0);
				assertTrue(value.length() <= 10);
				for (int j = 0; j < value.length(); j = j + 1) {
					assertTrue(Character.isDigit(value.charAt(j)));
				}
			}
			supplier.setConstantLength(true);
			assertTrue(supplier.isConstantLength());
			for (int i = 0; i < 10; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				assertEquals(10, value.length());
				for (int j = 0; j < value.length(); j = j + 1) {
					assertTrue(Character.isDigit(value.charAt(j)));
				}
			}
			supplier.setMaxLength(8);
			supplier.setConstantLength(false);
			supplier.setNullable(true);
			assertEquals(8, supplier.getMaxLength());
			assertFalse(supplier.isConstantLength());
			assertTrue(supplier.isNullable());
			for (int i = 0; i < 10; i = i + 1) {
				final String value = supplier.get();
				if (value != null) {
					assertTrue(value.length() >= 0);
					assertTrue(value.length() <= 8);
					for (int j = 0; j < value.length(); j = j + 1) {
						assertTrue(Character.isDigit(value.charAt(j)));
					}
				}
			}

			String[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			supplier.setNullable(false);
			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final String element : array) {
				assertNotNull(element);
				for (int j = 0; j < element.length(); j = j + 1) {
					assertTrue(Character.isDigit(element.charAt(j)));
				}
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testMinMaxValues() {
		try {
			final RandomIntegerSupplier supplier = new RandomIntegerSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			final int min = 1;
			final int max = 2;
			supplier.setMinValue(Integer.valueOf(min));
			supplier.setMaxValue(Integer.valueOf(max));
			boolean minGenerated = false;
			boolean maxGenerated = false;
			for (int i = 0; i < 20; i = i + 1) {
				final Integer value = supplier.get();
				assertNotNull(value);
				logger.info("VALOR={}", value);
				if (!minGenerated) {
					minGenerated = (value.intValue() == min);
				}
				if (!maxGenerated) {
					maxGenerated = (value.intValue() == max);
				}
			}
			assertTrue(minGenerated);
			assertTrue(maxGenerated);
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomSelectedStringSupplier1() {
		final String[] options = { "Cadena1", "Cadena2", "Cadena3", "Cadena4" };
		final Set<String> setOptions = new TreeSet<>(Arrays.asList(options));
		try {

			RandomSelectedStringSupplier supplier = new RandomSelectedStringSupplier(options);
			for (int i = 0; i < 20; i = i + 1) {
				final String value = supplier.get();
				if (value != null) {
					assertTrue(setOptions.contains(value));
				}
			}
			supplier = new RandomSelectedStringSupplier(setOptions, false);
			for (int i = 0; i < 20; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				assertTrue(setOptions.contains(value));
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomSelectedStringSupplier2() {
		Set<String> setOptions = new TreeSet<>();
		try {

			RandomSelectedStringSupplier supplier = new RandomSelectedStringSupplier(setOptions, true);
			supplier = new RandomSelectedStringSupplier(setOptions, true);
			for (int i = 0; i < 20; i = i + 1) {
				final String value = supplier.get();
				assertNull(value);
			}

			setOptions = null;
			supplier = new RandomSelectedStringSupplier(setOptions, false);
			for (int i = 0; i < 20; i = i + 1) {
				final String value = supplier.get();
				assertNull(value);
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomDniStringSupplier() {
		try {
			final RandomDniStringSupplier supplier = new RandomDniStringSupplier();
			for (int i = 0; i < 10; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				assertEquals(8, value.length());
				assertTrue(StringUtils.isNumeric(value));
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomNifStringSupplier() {
		try {
			final RandomNifStringSupplier supplier = new RandomNifStringSupplier();
			for (int i = 0; i < 10; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				assertEquals(9, value.length());
				assertTrue(AdministrativeUtils.validateNif(value));
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomNieStringSupplier() {
		try {
			final RandomNieStringSupplier supplier = new RandomNieStringSupplier();
			for (int i = 0; i < 10; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				assertEquals(9, value.length());
				assertTrue(AdministrativeUtils.validateNie(value));
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	private enum Prueba {
		OPCION1, OPCION2, OPCION3
	}

	@Test
	void testRandomEnumSupplier() {
		try {
			final RandomEnumSupplier<Prueba> supplier = new RandomEnumSupplier<>() {

				@Override
				protected Class<?> getClazz() {
					return Prueba.class;
				}

				@Override
				protected Prueba[] createArray(int size) {
					return new Prueba[size];
				}

			};

			for (int i = 0; i < 20; i = i + 1) {
				final Prueba value = supplier.get();
				assertNotNull(value);
				logger.debug("Valor generado={}", value);
				assertTrue(value instanceof Prueba);
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomSexSupplier() {
		try {
			final RandomSexSupplier supplier = new RandomSexSupplier();
			int vcount = 0;
			int hcount = 0;
			for (int i = 0; i < 100; i = i + 1) {
				final Sexo value = supplier.get();
				assertNotNull(value);
				if (Sexo.HEMBRA.equals(value)) {
					hcount = hcount + 1;
				} else {
					vcount = vcount + 1;
				}
			}
			logger.debug("PORCENTAJE DE {}={}%", Sexo.VARON, vcount);
			logger.debug("PORCENTAJE DE {}={}%", Sexo.HEMBRA, hcount);

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomExceptionSupplier() {
		try {
			final GjsSupplier<Exception> supplier = new RandomExceptionSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			assertNotNull(supplier.get());
			assertNotNull(supplier.getEmpty());

			Exception[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Exception element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomLocalDateSupplier() {
		try {
			GjsSupplier<LocalDate> supplier = new RandomLocalDateSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			assertNotNull(supplier.get());
			assertNull(supplier.getEmpty());

			supplier = new RandomLocalDateSupplier(10000, false);
			final Set<LocalDate> set = new TreeSet<>();
			for (int i = 0; i < 20; i = i + 1) {
				final LocalDate value = supplier.get();
				assertNotNull(value);
				logger.debug("LocalDate={}", value);
				set.add(value);
			}
			// Aqui la precision es el dia, no el milisegundo, asi que dos tiradas
			// pueden coincidir de verdad. Se exige variedad, no unicidad.
			assertTrue(set.size() > 1);

			LocalDate[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final LocalDate element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomLocalDateTimeSupplier() {
		try {
			GjsSupplier<LocalDateTime> supplier = new RandomLocalDateTimeSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			assertNotNull(supplier.get());
			assertNull(supplier.getEmpty());

			supplier = new RandomLocalDateTimeSupplier(10000, false);
			final Set<LocalDateTime> set = new TreeSet<>();
			for (int i = 0; i < 10; i = i + 1) {
				final LocalDateTime value = supplier.get();
				assertNotNull(value);
				logger.debug("LocalDateTime={}", value);
				assertFalse(set.contains(value));
				set.add(value);
			}

			LocalDateTime[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final LocalDateTime element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomTimestampSupplier() {
		try {
			GjsSupplier<Timestamp> supplier = new RandomTimestampSupplier();
			logger.info("Test {}", supplier.getClass().getName());
			assertNotNull(supplier.get());
			assertNull(supplier.getEmpty());

			supplier = new RandomTimestampSupplier(10000, false);
			final Set<Timestamp> set = new TreeSet<>();
			for (int i = 0; i < 10; i = i + 1) {
				final Timestamp value = supplier.get();
				assertNotNull(value);
				logger.debug("Timestamp={}", value);
				assertFalse(set.contains(value));
				set.add(value);
			}

			Timestamp[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Timestamp element : array) {
				assertNotNull(element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomNullableObjectSupplier() {
		try {
			logger.info("Test {}", RandomNullableObjectSupplier.class.getName());
			final NullableDePrueba supplier = new NullableDePrueba();
			assertTrue(supplier.isNullable());
			assertNull(supplier.getEmpty());
			assertFalse(new NullableDePrueba(false).isNullable());

			supplier.setNullable(false);
			assertFalse(supplier.isNullable());
			for (int i = 0; i < 100; i = i + 1) {
				assertNotNull(supplier.get());
			}

			// mustBeNull tira a un 10 %. Sobre 10000 intentos tiene que salir de las
			// dos maneras, y la proporcion caer holgadamente dentro del 5-15 %.
			supplier.setNullable(true);
			int nulos = 0;
			for (int i = 0; i < 10000; i = i + 1) {
				if (supplier.get() == null) {
					nulos = nulos + 1;
				}
			}
			logger.debug("Nulos={} de 10000", nulos);
			assertTrue(nulos > 500, String.format("Salieron %s nulos de 10000", nulos));
			assertTrue(nulos < 1500, String.format("Salieron %s nulos de 10000", nulos));
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomSelectedObjectSupplier() {
		final Set<String> opciones = new TreeSet<>(Arrays.asList("uno", "dos", "tres"));
		try {
			logger.info("Test {}", RandomSelectedObjectSupplier.class.getName());
			SeleccionDePrueba supplier = new SeleccionDePrueba(opciones, false);
			for (int i = 0; i < 20; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				assertTrue(opciones.contains(value));
			}

			// Sin opciones devuelve null aunque no sea nullable.
			supplier = new SeleccionDePrueba(new TreeSet<>(), false);
			for (int i = 0; i < 20; i = i + 1) {
				assertNull(supplier.get());
			}

			// Y con la coleccion a null, igual.
			final Set<String> ninguna = null;
			supplier = new SeleccionDePrueba(ninguna, false);
			for (int i = 0; i < 20; i = i + 1) {
				assertNull(supplier.get());
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	/** Concreta minima para poder probar la logica de RandomNullableObjectSupplier. */
	private static class NullableDePrueba extends RandomNullableObjectSupplier<String> {

		NullableDePrueba() {
			super();
		}

		NullableDePrueba(boolean nullable) {
			super(nullable);
		}

		@Override
		public String get() {
			return isNullable() && mustBeNull() ? null : "valor";
		}

		@Override
		protected String[] createArray(int size) {
			return new String[size];
		}
	}

	/** Concreta minima para poder probar la logica de RandomSelectedObjectSupplier. */
	private static class SeleccionDePrueba extends RandomSelectedObjectSupplier<String> {

		SeleccionDePrueba(Collection<String> options, boolean nullable) {
			super(options, nullable);
		}

		@Override
		protected String[] createArray(int size) {
			return new String[size];
		}
	}

	/**
	 * Regresion: el constructor con limites nulos los dejaba a null y get() daba
	 * NullPointerException. Ahora se quedan los valores por defecto.
	 */
	@Test
	void testRandomIntegerSupplierLimitesNulos() {
		final RandomIntegerSupplier supplier = new RandomIntegerSupplier(null, null);
		assertEquals(Integer.valueOf(1), supplier.getMinValue());
		assertEquals(Integer.valueOf(100000000), supplier.getMaxValue());
		for (int i = 0; i < 1000; i = i + 1) {
			final int value = supplier.get();
			assertTrue((value >= 1) && (value <= 100000000), "fuera de rango: " + value);
		}
	}

	/**
	 * Regresion: con un rango mas ancho que Integer.MAX_VALUE la anchura se
	 * desbordaba, y salian valores fuera de los limites.
	 */
	@Test
	void testRandomIntegerSupplierRangoCompleto() {
		final RandomIntegerSupplier supplier = new RandomIntegerSupplier(Integer.MIN_VALUE, Integer.MAX_VALUE);
		boolean negativo = false;
		boolean positivo = false;
		for (int i = 0; i < 1000; i = i + 1) {
			final int value = supplier.get();
			negativo = negativo || (value < 0);
			positivo = positivo || (value > 0);
		}
		assertTrue(negativo && positivo, "con todo el rango deberian salir negativos y positivos");
	}

	@Test
	void testRandomIntegerSupplierLimitesIncluidos() {
		final RandomIntegerSupplier supplier = new RandomIntegerSupplier(3, 4);
		final Set<Integer> vistos = new TreeSet<>();
		for (int i = 0; i < 1000; i = i + 1) {
			vistos.add(supplier.get());
		}
		assertEquals(Set.of(3, 4), vistos);
	}

}
