package org.gjs.java.common.supplier;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.test.BaseClassTest;
import org.junit.jupiter.api.Test;

class PrimitiveObjectSupplierBatteryTest extends BaseClassTest<PrimitiveObjectSupplierBattery> {

	private final PrimitiveObjectSupplierBattery bateria = new PrimitiveObjectSupplierBattery();

	@Test
	void testRandom() {
		try {
			assertNotNull(bateria.randomLong());
			assertNotNull(bateria.randomInt());
			assertNotNull(bateria.randomShort());
			assertNotNull(bateria.randomBoolean());
			assertNotNull(bateria.randomFloat());
			assertNotNull(bateria.randomDouble());
			assertNotNull(bateria.randomChar());
			assertNotNull(bateria.randomBytes());
			assertNotNull(bateria.randomByte());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	/* Los suppliers de int y short se construyen acotados al rango 0-1000. */
	@Test
	void testRangosAcotados() {
		for (int i = 0; i < 100; i = i + 1) {
			final Integer entero = bateria.randomInt();
			assertTrue(entero >= 0 && entero <= 1000, String.format("randomInt devolvio %s", entero));

			final Short corto = bateria.randomShort();
			assertTrue(corto >= 0 && corto <= 1000, String.format("randomShort devolvio %s", corto));
		}
	}

	/* Aqui "vacio" es el valor cero del tipo, no null. */
	@Test
	void testEmpty() {
		assertEquals(Long.valueOf(0), bateria.emptyLong());
		assertEquals(Integer.valueOf(0), bateria.emptyInt());
		assertEquals(Short.valueOf((short) 0), bateria.emptyShort());
		assertEquals(Boolean.FALSE, bateria.emptyBoolean());
		assertEquals(Float.valueOf(0), bateria.emptyFloat());
		assertEquals(Double.valueOf(0), bateria.emptyDouble());
		assertEquals(Character.valueOf('\0'), bateria.emptyChar());
		assertEquals(Byte.valueOf((byte) 0), bateria.emptyByte());
		assertEquals(0, bateria.emptyBytes().length);
	}

	@Test
	void testArraysVacios() {
		assertEquals(0, bateria.emptyArrayLong().length);
		assertEquals(0, bateria.emptyArrayInt().length);
		assertEquals(0, bateria.emptyArrayShort().length);
		assertEquals(0, bateria.emptyArrayBoolean().length);
		assertEquals(0, bateria.emptyArrayFloat().length);
		assertEquals(0, bateria.emptyArrayDouble().length);
		assertEquals(0, bateria.emptyArrayChar().length);
		assertEquals(0, bateria.emptyArrayBytes().length);
	}

	@Test
	void testArraysConDatos() {
		try {
			comprobarArray(bateria.randomArrayLong());
			comprobarArray(bateria.randomArrayInt());
			comprobarArray(bateria.randomArrayShort());
			comprobarArray(bateria.randomArrayBoolean());
			comprobarArray(bateria.randomArrayFloat());
			comprobarArray(bateria.randomArrayDouble());
			comprobarArray(bateria.randomArrayChar());
			comprobarArray(bateria.randomArrayBytes());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	/* No se exige un tamano minimo: lo fija getMinSizeArrays y podria ser cero. */
	private void comprobarArray(Object[] array) {
		assertNotNull(array);
		for (final Object element : array) {
			assertNotNull(element);
		}
	}

}
