package org.gjs.java.common.supplier;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.fail;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.test.BaseClassTest;
import org.junit.jupiter.api.Test;

class ManagedObjectSupplierBatteryTest extends BaseClassTest<ManagedObjectSupplierBattery> {

	private final ManagedObjectSupplierBattery bateria = new ManagedObjectSupplierBattery();

	@Test
	void testRandom() {
		try {
			assertNotNull(bateria.randomString());
			assertNotNull(bateria.randomDate());
			assertNotNull(bateria.randomLocalDateTime());
			assertNotNull(bateria.randomLocalDate());
			assertNotNull(bateria.randomTimestamp());
			assertNotNull(bateria.randomBigDecimal());
			assertNotNull(bateria.randomBigInteger());
			assertNotNull(bateria.randomException());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	/*
	 * "Vacio" no es sinonimo de null: cada supplier decide. Las fechas y los numeros
	 * grandes dan null, la cadena da "" y la excepcion una instancia recien hecha.
	 */
	@Test
	void testEmpty() {
		assertEquals("", bateria.emptyString());
		assertNotNull(bateria.emptyException());
		assertNull(bateria.emptyDate());
		assertNull(bateria.emptyLocalDateTime());
		assertNull(bateria.emptyLocalDate());
		assertNull(bateria.emptyTimestamp());
		assertNull(bateria.emptyBigDecimal());
		assertNull(bateria.emptyBigInteger());
	}

	@Test
	void testArraysVacios() {
		assertEquals(0, bateria.emptyArrayString().length);
		assertEquals(0, bateria.emptyArrayDate().length);
		assertEquals(0, bateria.emptyArrayLocalDateTime().length);
		assertEquals(0, bateria.emptyArrayLocalDate().length);
		assertEquals(0, bateria.emptyArrayTimestamp().length);
		assertEquals(0, bateria.emptyArrayBigDecimal().length);
		assertEquals(0, bateria.emptyArrayBigInteger().length);
		assertEquals(0, bateria.emptyArrayException().length);
	}

	@Test
	void testArraysConDatos() {
		try {
			comprobarArray(bateria.randomArrayString());
			comprobarArray(bateria.randomArrayDate());
			comprobarArray(bateria.randomArrayLocalDateTime());
			comprobarArray(bateria.randomArrayLocalDate());
			comprobarArray(bateria.randomArrayTimestamp());
			comprobarArray(bateria.randomArrayBigDecimal());
			comprobarArray(bateria.randomArrayBigInteger());
			comprobarArray(bateria.randomArrayException());
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
