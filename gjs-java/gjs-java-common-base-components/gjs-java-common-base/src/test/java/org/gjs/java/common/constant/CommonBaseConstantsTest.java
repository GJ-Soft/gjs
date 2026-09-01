package org.gjs.java.common.constant;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertInstanceOf;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Modifier;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import org.gjs.java.test.BaseClassTest;
import org.junit.jupiter.api.Test;

class CommonBaseConstantsTest extends BaseClassTest<CommonBaseConstants> {

	@Test
	void testClaseNoInstanciable() throws NoSuchMethodException {
		final Constructor<CommonBaseConstants> constructor = CommonBaseConstants.class.getDeclaredConstructor();
		assertTrue(Modifier.isPrivate(constructor.getModifiers()));

		constructor.setAccessible(true);
		final InvocationTargetException ex = assertThrows(InvocationTargetException.class, constructor::newInstance);
		assertInstanceOf(IllegalStateException.class, ex.getCause());
		assertEquals(CommonBaseConstants.MSG_UTILITY_CLASS, ex.getCause().getMessage());
	}

	@Test
	void testLocalePorDefecto() {
		assertNotNull(CommonBaseConstants.DEFAULT_LOCALE);
		assertEquals("es", CommonBaseConstants.DEFAULT_LOCALE.getLanguage());
		assertEquals("ES", CommonBaseConstants.DEFAULT_LOCALE.getCountry());
	}

	@Test
	void testFormatosDeFecha() {
		final LocalDateTime momento = LocalDateTime.of(2026, 8, 27, 14, 5, 9, 123000000);

		assertEquals("2026-08-27", formatear(CommonBaseConstants.DATE_OUTPUT_FORMAT, momento));
		assertEquals("2026-08-27T14:05:09", formatear(CommonBaseConstants.DATETIME_OUTPUT_FORMAT, momento));
		assertEquals("2026-08-27T14:05:09.123", formatear(CommonBaseConstants.TIMESTAMP_OUTPUT_FORMAT, momento));
		assertEquals("27/08/2026 14:05:09", formatear(CommonBaseConstants.SIMPLE_DATETIME_FORMAT, momento));
	}

	@Test
	void testMarcadores() {
		assertEquals("NUL", CommonBaseConstants.NULL_VALUE);
		assertEquals("XXX", CommonBaseConstants.INFORMED_VALUE);
		assertNotNull(CommonBaseConstants.MSG_UNKNOWN_ERROR);
		assertNotNull(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	private String formatear(String patron, LocalDateTime momento) {
		return DateTimeFormatter.ofPattern(patron).format(momento);
	}

}
