package org.gjs.java.common.supplier;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertInstanceOf;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.test.BaseClassTest;
import org.gjs.java.test.samples.pojos.SamplePojo;
import org.junit.jupiter.api.Test;

class GenericObjectSupplierTest extends BaseClassTest<GenericObjectSupplier> {

	private static final String CLASE = "org.gjs.java.test.samples.pojos.SamplePojo";

	/* El constructor deja puestos informAllFields e informCollections; es lo unico que anade sobre su clase padre. */
	@Test
	void testConstructor() {
		final GenericObjectSupplier supplier = new GenericObjectSupplier(CLASE);

		assertEquals(CLASE, supplier.getClassName());
		assertTrue(supplier.isInformAllFields());
		assertTrue(supplier.isInformCollections());
	}

	@Test
	void testGet() {
		try {
			final GenericObjectSupplier supplier = new GenericObjectSupplier(CLASE);

			final Object obj = supplier.get();
			assertNotNull(obj);
			assertInstanceOf(SamplePojo.class, obj);

			// getEmpty no devuelve null: devuelve una instancia con los campos en blanco.
			final SamplePojo vacio = assertInstanceOf(SamplePojo.class, supplier.getEmpty());
			assertEquals(0L, vacio.getId());
			assertEquals("", vacio.getNombre());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testArrays() {
		try {
			final GenericObjectSupplier supplier = new GenericObjectSupplier(CLASE);

			Object[] array = supplier.getEmptyArray();
			assertNotNull(array);
			assertEquals(0, array.length);

			array = supplier.getArray();
			assertNotNull(array);
			assertTrue(array.length >= supplier.getMinSizeArrays());
			assertTrue(array.length <= supplier.getMaxSizeArrays());
			for (final Object element : array) {
				assertInstanceOf(SamplePojo.class, element);
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	/* Con una clase que no existe no revienta: devuelve null. */
	@Test
	void testClaseInexistente() {
		try {
			final GenericObjectSupplier supplier = new GenericObjectSupplier("no.existe.NingunaClase");

			assertEquals("no.existe.NingunaClase", supplier.getClassName());
			assertNull(supplier.get());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

}
