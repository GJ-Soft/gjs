package org.gjs.java.common.util;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertInstanceOf;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Modifier;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.test.BaseClassTest;
import org.junit.jupiter.api.Test;

class JvmUtilsTest extends BaseClassTest<JvmUtils> {

	@Test
	void testClaseNoInstanciable() throws NoSuchMethodException {
		final Constructor<JvmUtils> constructor = JvmUtils.class.getDeclaredConstructor();
		assertTrue(Modifier.isPrivate(constructor.getModifiers()));

		constructor.setAccessible(true);
		final InvocationTargetException ex = assertThrows(InvocationTargetException.class, constructor::newInstance);
		assertInstanceOf(IllegalStateException.class, ex.getCause());
		assertEquals(CommonBaseConstants.MSG_UTILITY_CLASS, ex.getCause().getMessage());
	}

	@Test
	void testJvmInfo() {
		try {
			final String info = JvmUtils.jvmInfo();
			logger.debug("jvmInfo=\n{}", info);

			assertNotNull(info);
			assertFalse(info.isBlank());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	/* El informe tiene que traer los tres bloques que promete. */
	@Test
	void testJvmInfoTraeLosBloques() {
		final String info = JvmUtils.jvmInfo();

		assertTrue(info.contains("Max heap"), "Falta el resumen de Runtime");
		assertTrue(info.contains("=== HEAP ==="), "Falta el bloque de heap");
		assertTrue(info.contains("=== NON-HEAP"), "Falta el bloque de non-heap");
	}

	/* Dos llamadas seguidas tienen que funcionar igual: no guarda estado. */
	@Test
	void testJvmInfoRepetible() {
		final String primera = JvmUtils.jvmInfo();
		final String segunda = JvmUtils.jvmInfo();

		assertNotNull(primera);
		assertNotNull(segunda);
		assertTrue(segunda.contains("=== HEAP ==="));
	}

}
