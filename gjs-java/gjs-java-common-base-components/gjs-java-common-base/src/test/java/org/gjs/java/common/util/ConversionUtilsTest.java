package org.gjs.java.common.util;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.math.BigDecimal;
import java.sql.Timestamp;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Date;
import java.util.Objects;
import java.util.Properties;

import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.exception.GjsException;
import org.gjs.java.common.test.utils.AssertionUtils;
import org.gjs.java.common.util.ConversionUtils;
import org.gjs.java.test.BaseClassTest;
import org.gjs.java.test.samples.pojos.SamplePojo;
import org.junit.jupiter.api.Test;

class ConversionUtilsTest extends BaseClassTest<ConversionUtils> {

	@Test
	void testToBoolean() {
		assertFalse(ConversionUtils.toBoolean(null));
		assertFalse(ConversionUtils.toBoolean(""));
		assertFalse(ConversionUtils.toBoolean("aye"));
		assertFalse(ConversionUtils.toBoolean("false"));
		assertTrue(ConversionUtils.toBoolean("true"));
		assertTrue(ConversionUtils.toBoolean("cierto"));
		assertTrue(ConversionUtils.toBoolean("1"));
		assertFalse(ConversionUtils.toBoolean("falso"));
		assertFalse(ConversionUtils.toBoolean("0"));
		assertTrue(ConversionUtils.toBoolean("tRuE"));
		assertTrue(ConversionUtils.toBoolean("CIERTO"));
	}

	@Test
	void testToNativeArray1() {
		try {
			Byte[] values = null;
			byte[] array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Byte[0];
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Byte[4];
			values[0] = Byte.valueOf((byte) 27);
			values[1] = Byte.valueOf((byte) 0);
			values[2] = null;
			values[3] = Byte.valueOf((byte) 147);
			array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(values.length, array.length);
			for (final byte element : array) {
				assertNotNull(element);
			}
			assertEquals((byte) 27, array[0]);
			assertEquals((byte) 0, array[1]);
			assertEquals((byte) 0, array[2]);
			assertEquals((byte) 147, array[3]);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToNativeArray2() {
		try {
			Long[] values = null;
			long[] array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Long[0];
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Long[4];
			values[0] = Long.valueOf(27);
			values[1] = Long.valueOf(0);
			values[2] = null;
			values[3] = Long.valueOf(147);
			array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(values.length, array.length);
			for (final long element : array) {
				assertNotNull(element);
			}
			assertEquals(27, array[0]);
			assertEquals(0, array[1]);
			assertEquals(0, array[2]);
			assertEquals(147, array[3]);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToNativeArray3() {
		try {
			Integer[] values = null;
			int[] array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Integer[0];
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Integer[4];
			values[0] = Integer.valueOf(27);
			values[1] = Integer.valueOf(0);
			values[2] = null;
			values[3] = Integer.valueOf(147);
			array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(values.length, array.length);
			for (final int element : array) {
				assertNotNull(element);
			}
			assertEquals(27, array[0]);
			assertEquals(0, array[1]);
			assertEquals(0, array[2]);
			assertEquals(147, array[3]);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToNativeArray4() {
		try {
			Short[] values = null;
			short[] array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Short[0];
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Short[4];
			values[0] = Short.valueOf((short) 27);
			values[1] = Short.valueOf((short) 0);
			values[2] = null;
			values[3] = Short.valueOf((short) 147);
			array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(values.length, array.length);
			for (final short element : array) {
				assertNotNull(element);
			}
			assertEquals((short) 27, array[0]);
			assertEquals((short) 0, array[1]);
			assertEquals((short) 0, array[2]);
			assertEquals((short) 147, array[3]);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToNativeArray5() {
		try {
			Float[] values = null;
			float[] array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Float[0];
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Float[4];
			values[0] = Float.valueOf(27);
			values[1] = Float.valueOf(0);
			values[2] = null;
			values[3] = Float.valueOf(147);
			array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(values.length, array.length);
			for (final float element : array) {
				assertNotNull(element);
			}
			assertEquals(27, array[0]);
			assertEquals(0, array[1]);
			assertEquals(0, array[2]);
			assertEquals(147, array[3]);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToNativeArray6() {
		try {
			Double[] values = null;
			double[] array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Double[0];
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Double[4];
			values[0] = Double.valueOf(27);
			values[1] = Double.valueOf(0);
			values[2] = null;
			values[3] = Double.valueOf(147);
			array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(values.length, array.length);
			for (final double element : array) {
				assertNotNull(element);
			}
			assertEquals(27, array[0]);
			assertEquals(0, array[1]);
			assertEquals(0, array[2]);
			assertEquals(147, array[3]);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToNativeArray7() {
		try {
			Character[] values = null;
			char[] array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Character[0];
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Character[4];
			values[0] = Character.valueOf((char) 27);
			values[1] = Character.valueOf((char) 0);
			values[2] = null;
			values[3] = Character.valueOf((char) 147);
			array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(values.length, array.length);
			for (final char element : array) {
				assertNotNull(element);
			}
			assertEquals((char) 27, array[0]);
			assertEquals((char) 0, array[1]);
			assertEquals((char) 0, array[2]);
			assertEquals((char) 147, array[3]);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToNativeArray8() {
		try {
			Boolean[] values = null;
			boolean[] array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Boolean[0];
			assertNotNull(array);
			assertEquals(0, array.length);
			values = new Boolean[4];
			values[0] = Boolean.TRUE;
			values[1] = Boolean.FALSE;
			values[2] = null;
			values[3] = Boolean.TRUE;
			array = ConversionUtils.toNativeArray(values);
			assertNotNull(array);
			assertEquals(values.length, array.length);
			for (final boolean element : array) {
				assertNotNull(element);
			}
			assertEquals(true, array[0]);
			assertEquals(false, array[1]);
			assertEquals(false, array[2]);
			assertEquals(true, array[3]);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToPrimitiveValue() {
		try {
			String value = null;
			Object primitiveValue = ConversionUtils.toPrimitiveValue(PrimitiveType.INTEGER.getName(), value);
			assertNull(primitiveValue);

			value = "0";
			primitiveValue = ConversionUtils.toPrimitiveValue(PrimitiveType.INTEGER.getName(), value);
			assertNotNull(primitiveValue);
			assertTrue(primitiveValue instanceof Integer);
			assertEquals(0, ((Integer) primitiveValue).intValue());
			primitiveValue = ConversionUtils.toPrimitiveValue(PrimitiveType.CHAR.getName(), value);
			assertNotNull(primitiveValue);
			assertTrue(primitiveValue instanceof Character);
			assertEquals('0', ((Character) primitiveValue).charValue());
			primitiveValue = ConversionUtils.toPrimitiveValue(PrimitiveType.BOOLEAN.getName(), value);
			assertNotNull(primitiveValue);
			assertTrue(primitiveValue instanceof Boolean);
			assertEquals(false, ((Boolean) primitiveValue).booleanValue());
			primitiveValue = ConversionUtils.toPrimitiveValue(PrimitiveType.BYTE.getName(), value);
			assertNotNull(primitiveValue);
			assertTrue(primitiveValue instanceof Byte);
			assertEquals(48, ((Byte) primitiveValue).byteValue());
			primitiveValue = ConversionUtils.toPrimitiveValue(PrimitiveType.SHORT.getName(), value);
			assertNotNull(primitiveValue);
			assertTrue(primitiveValue instanceof Short);
			assertEquals(0, ((Short) primitiveValue).shortValue());
			primitiveValue = ConversionUtils.toPrimitiveValue(PrimitiveType.LONG.getName(), value);
			assertNotNull(primitiveValue);
			assertTrue(primitiveValue instanceof Long);
			assertEquals(0, ((Long) primitiveValue).longValue());
			primitiveValue = ConversionUtils.toPrimitiveValue(PrimitiveType.FLOAT.getName(), value);
			assertNotNull(primitiveValue);
			assertTrue(primitiveValue instanceof Float);
			assertEquals(0, ((Float) primitiveValue).floatValue());
			primitiveValue = ConversionUtils.toPrimitiveValue(PrimitiveType.DOUBLE.getName(), value);
			assertNotNull(primitiveValue);
			assertTrue(primitiveValue instanceof Double);
			assertEquals(0, ((Double) primitiveValue).doubleValue());

			primitiveValue = ConversionUtils.toPrimitiveValue("java.util.Date", value);
			assertNull(primitiveValue);

			value = "";
			primitiveValue = ConversionUtils.toPrimitiveValue(PrimitiveType.INTEGER.getName(), value);
			assertNull(primitiveValue);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToManagedValue1() throws ParseException {
		try {
			String value = null;
			Object managedValue = ConversionUtils.toManagedValue(ManagedType.STRING.getClassName(), value);
			assertNull(managedValue);

			value = "Test";
			managedValue = ConversionUtils.toManagedValue(ManagedType.STRING.getClassName(), value);
			assertNotNull(managedValue);
			assertTrue(managedValue instanceof String);
			assertEquals("Test", managedValue);

			managedValue = ConversionUtils.toManagedValue(ManagedType.BIGDECIMAL.getClassName(), value);
			assertNull(managedValue);
			value = "0";
			managedValue = ConversionUtils.toManagedValue(ManagedType.BIGDECIMAL.getClassName(), value);
			assertNotNull(managedValue);
			assertTrue(managedValue instanceof BigDecimal);
			assertEquals(BigDecimal.ZERO, managedValue);

			managedValue = ConversionUtils.toManagedValue(ManagedType.DATE.getClassName(), value);
			assertNull(managedValue);
			value = "20121221";
			managedValue = ConversionUtils.toManagedValue(ManagedType.DATE.getClassName(), value);
			assertNotNull(managedValue);
			assertTrue(managedValue instanceof Date);
			AssertionUtils.assertSameDay(new SimpleDateFormat("yyyyMMdd").parse(value),
					(Date) managedValue);

			value = "test";
			managedValue = ConversionUtils.toManagedValue(ManagedType.LOCALDATETIME.getClassName(), value);
			assertNull(managedValue);
			value = "2024-01-05T10:14:11.479960100";
			managedValue = ConversionUtils.toManagedValue(ManagedType.LOCALDATETIME.getClassName(), value);
			assertNotNull(managedValue);
			assertTrue(managedValue instanceof LocalDateTime);
			AssertionUtils.assertSameSecond(
					new SimpleDateFormat("yyyy-MM-dd'T'hh:mm:ss").parse("2024-01-05T10:14:11"),
					Date.from(((LocalDateTime) managedValue).atZone(ZoneId.systemDefault()).toInstant()));

			value = "test";
			managedValue = ConversionUtils.toManagedValue(ManagedType.LOCALDATE.getClassName(), value);
			assertNull(managedValue);
			value = "2024-01-05T10:14:11.479960100";
			managedValue = ConversionUtils.toManagedValue(ManagedType.LOCALDATE.getClassName(), value);
			assertNotNull(managedValue);
			assertTrue(managedValue instanceof LocalDate);
			AssertionUtils.assertSameSecond(
					new SimpleDateFormat("yyyy-MM-dd").parse("2024-01-05"),
					Date.from(((LocalDate) managedValue).atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));
			value = "11/02/23";
			managedValue = ConversionUtils.toManagedValue(ManagedType.LOCALDATE.getClassName(), value);
			assertNotNull(managedValue);
			assertTrue(managedValue instanceof LocalDate);
			AssertionUtils.assertSameSecond(
					new SimpleDateFormat("yyyy-MM-dd").parse("2023-02-11"),
					Date.from(((LocalDate) managedValue).atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));

			value = "test";
			managedValue = ConversionUtils.toManagedValue(ManagedType.TIMESTAMP.getClassName(), value);
			assertNull(managedValue);
			value = "2024-01-05 10:14:29.8536693";
			managedValue = ConversionUtils.toManagedValue(ManagedType.TIMESTAMP.getClassName(), value);
			assertNotNull(managedValue);
			assertTrue(managedValue instanceof Timestamp);
			AssertionUtils.assertSameSecond(
					new SimpleDateFormat("yyyy-MM-dd hh:mm:ss").parse("2024-01-05 10:14:29"),
					new Date(((Timestamp) managedValue).getTime()));

			managedValue = ConversionUtils.toManagedValue("java.math.BigInteger", value);
			assertNull(managedValue);

			value = "";
			managedValue = ConversionUtils.toManagedValue(ManagedType.BIGDECIMAL.getClassName(), value);
			assertNull(managedValue);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToManagedValue2() throws ParseException {
		try {

			final String value = "11/02/23";
			final Object managedValue = ConversionUtils.toManagedValue(ManagedType.LOCALDATE.getClassName(), value);
			assertNotNull(managedValue);
			assertTrue(managedValue instanceof LocalDate);
			AssertionUtils.assertSameDay(new SimpleDateFormat("yy-MM-dd").parse("23-02-11"),
					Date.from(((LocalDate) managedValue).atStartOfDay().atZone(ZoneId.systemDefault()).toInstant()));

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToObjectValue() {
		try {
			String value = null;
			Object objectValue = ConversionUtils.toObjectValue(PrimitiveType.INTEGER.getName(), value);
			assertNull(objectValue);

			value = "0";
			objectValue = ConversionUtils.toObjectValue(PrimitiveType.INTEGER.getName(), value);
			assertNotNull(objectValue);
			assertTrue(objectValue instanceof Integer);
			assertEquals(0, objectValue);

			objectValue = ConversionUtils.toObjectValue(ManagedType.BIGDECIMAL.getClassName(), value);
			assertNotNull(objectValue);
			assertTrue(objectValue instanceof BigDecimal);
			assertEquals(BigDecimal.ZERO, objectValue);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testConvertValue() {
		try {
			Object value = null;
			Object objectValue = ConversionUtils.convertValue(PrimitiveType.INTEGER.getName(), false, value);
			assertNull(objectValue);

			value = "0";
			objectValue = ConversionUtils.convertValue(ManagedType.STRING.getClassName(), false, value);
			assertNotNull(objectValue);
			assertTrue(objectValue instanceof String);
			assertEquals("0", objectValue);

			objectValue = ConversionUtils.convertValue(PrimitiveType.INTEGER.getName(), false, value);
			assertNotNull(objectValue);
			assertTrue(objectValue instanceof Integer);
			assertEquals(0, objectValue);

			objectValue = ConversionUtils.convertValue(ManagedType.BIGDECIMAL.getClassName(), false, value);
			assertNotNull(objectValue);
			assertTrue(objectValue instanceof BigDecimal);
			assertEquals(BigDecimal.ZERO, objectValue);

			objectValue = ConversionUtils.convertValue(PrimitiveType.BYTE.getName(), true, value);
			assertNotNull(objectValue);
			assertTrue(objectValue instanceof byte[]);
			assertEquals(1, ((byte[]) objectValue).length);

			objectValue = ConversionUtils.convertValue(PrimitiveType.LONG.getName(), true, value);
			assertNull(objectValue);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testToString1() {
		Object obj = null;
		String res = ConversionUtils.toString(obj);
		assertNotNull(res);
		assertEquals("null", res);
		assertEquals(Objects.toString(obj, "null"), res);
		assertEquals(Objects.toString(obj), res);
		obj = "Aye";
		res = ConversionUtils.toString(obj);
		assertNotNull(res);
		assertEquals("Aye", res);
		assertEquals(Objects.toString(obj, "null"), res);
		assertEquals(Objects.toString(obj), res);
		obj = Long.valueOf(1);
		res = ConversionUtils.toString(obj);
		assertNotNull(res);
		assertEquals("1", res);
		assertEquals(Objects.toString(obj, "null"), res);
		assertEquals(Objects.toString(obj), res);
	}

	@Test
	void testToString2() {
		Properties prop = null;
		String res = ConversionUtils.toString(prop);
		assertNotNull(res);
		logger.info("Prop={}", res);
		assertEquals("null", res);
		prop = new Properties();
		res = ConversionUtils.toString(prop);
		assertNotNull(res);
		logger.info("Prop={}", res);
		assertEquals("", res);
		prop.put("Prop", "Value");
		res = ConversionUtils.toString(prop);
		assertNotNull(res);
		logger.info("Prop={}", res);
		assertEquals("Prop=Value;", res);
	}

	@Test
	void testToString3() {
		Object obj = null;
		String string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("null", string);
		obj = Long.valueOf(0);
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("0", string);
		obj = "test";
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("test", string);
		obj = new SamplePojo(1, "test");
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("SamplePojo [id=1, nombre=test]", string);
		obj = SamplePojo.class;
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("class org.gjs.java.test.samples.pojos.SamplePojo", string);
		obj = new int[0];
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("[]", string);
		obj = new short[0];
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("[]", string);
		obj = new long[0];
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("[]", string);
		obj = new float[0];
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("[]", string);
		obj = new double[0];
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("[]", string);
		obj = new byte[0];
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("[]", string);
		obj = new char[0];
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("[]", string);
		obj = new boolean[0];
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("[]", string);
		obj = new SamplePojo[0];
		string = ConversionUtils.toString(obj);
		assertNotNull(string);
		assertEquals("[]", string);
	}

	@Test
	void testToString4() {
		Object[] obj = null;
		String res = ConversionUtils.toString(obj);
		assertNotNull(res);
		assertEquals("null", res);
		assertEquals(Objects.toString(obj, "null"), res);
		assertEquals(Objects.toString(obj), res);
		obj = new String[] { "Aye", "Yuk" };
		res = ConversionUtils.toString(obj);
		assertNotNull(res);
		assertEquals("[Aye, Yuk]", res);
		// assertNotEquals(Objects.toString(obj, "null"), res);
		// assertEquals(Objects.toString(obj), res);
		obj = new Long[] { Long.valueOf(1), Long.valueOf(2) };
		res = ConversionUtils.toString(obj);
		assertNotNull(res);
		assertEquals("[1, 2]", res);
		// assertEquals(Objects.toString(obj, "null"), res);
		// assertEquals(Objects.toString(obj), res);
	}

	@Test
	void testLongValue1() {
		final Long value1 = Long.valueOf(7);
		final Long value2 = null;
		assertEquals(0, ConversionUtils.longValue(value2));
		assertEquals(7, ConversionUtils.longValue(value1));
	}

	@Test
	void testIntValue1() {
		final Integer value1 = Integer.valueOf(7);
		final Integer value2 = null;
		assertEquals(0, ConversionUtils.intValue(value2));
		assertEquals(7, ConversionUtils.intValue(value1));
	}

	@Test
	void testIntValue2() {
		final Short value1 = Short.valueOf((short) 7);
		final Short value2 = null;
		assertEquals(0, ConversionUtils.intValue(value2));
		assertEquals(7, ConversionUtils.intValue(value1));
	}

	@Test
	void testLongValue2() {
		final String value1 = "7";
		final String value2 = "-1";
		try {
			assertEquals(-1, ConversionUtils.longValue(value2));
			assertEquals(7, ConversionUtils.longValue(value1));
		} catch (final Exception e) {
			fail("Se ha producido una excepcion");
		}
	}

	@Test
	void testLongValue_Exception1() {
		final String value1 = "x";
		try {
			ConversionUtils.longValue(value1);
			fail("Se esperaba uns excepcion");
		} catch (final GjsException e) {

		} catch (final Exception e) {
			fail("Se ha producido una excepcion inesperada");
		}
	}

	@Test
	void testLongValue_Exception2() {
		final String value1 = null;
		try {
			ConversionUtils.longValue(value1);
			fail("Se esperaba uns excepcion");
		} catch (final GjsException e) {

		} catch (final Exception e) {
			fail("Se ha producido una excepcion inesperada");
		}
	}

	@Test
	void testPositiveLongValue1() {
		final String value1 = "7";
		final String value2 = "0";
		try {
			assertEquals(0, ConversionUtils.unsignedLongValue(value2));
			assertEquals(7, ConversionUtils.unsignedLongValue(value1));
		} catch (final Exception e) {
			fail("Se ha producido una excepcion");
		}
	}

	@Test
	void testPositiveLongValue_Exception1() {
		final String value1 = "x-1";
		try {
			ConversionUtils.unsignedLongValue(value1);
			fail("Se esperaba uns excepcion");
		} catch (final GjsException e) {

		} catch (final Exception e) {
			fail("Se ha producido una excepcion inesperada");
		}
	}

	@Test
	void testPositiveLongValue_Exception2() {
		final String value1 = null;
		try {
			ConversionUtils.unsignedLongValue(value1);
			fail("Se esperaba uns excepcion");
		} catch (final GjsException e) {

		} catch (final Exception e) {
			fail("Se ha producido una excepcion inesperada");
		}
	}

	@Test
	void testBooleanValue() {
		assertFalse(ConversionUtils.booleanValue(null));
		assertFalse(ConversionUtils.booleanValue(""));
		assertFalse(ConversionUtils.booleanValue("xxxx"));
		assertFalse(ConversionUtils.booleanValue("No"));
		assertTrue(ConversionUtils.booleanValue(" Si"));
		assertTrue(ConversionUtils.booleanValue("1"));
		assertTrue(ConversionUtils.booleanValue("YEs"));
		assertTrue(ConversionUtils.booleanValue("true"));
		assertFalse(ConversionUtils.booleanValue("0"));
		assertFalse(ConversionUtils.booleanValue("false "));
	}

	@Test
	void testAssignValue() {
		final Long idNull = null;
		final Long id1 = Long.valueOf(1);
		final Long idDef = Long.valueOf(0);
		Long id = ConversionUtils.assignValue(id1, idDef);
		assertNotNull(id);
		assertEquals(id1, id);
		id = ConversionUtils.assignValue(idNull, idDef);
		assertNotNull(id);
		assertEquals(idDef, id);
	}

}
