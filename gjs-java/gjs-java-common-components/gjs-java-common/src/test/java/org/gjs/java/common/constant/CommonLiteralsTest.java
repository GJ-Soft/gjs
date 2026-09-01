package org.gjs.java.common.constant;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertInstanceOf;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Modifier;

import org.gjs.java.test.BaseUnitTest;
import org.junit.jupiter.api.Test;

class CommonLiteralsTest extends BaseUnitTest<CommonLiterals> {

	@Test
	void testClaseNoInstanciable() throws NoSuchMethodException {
		final Constructor<CommonLiterals> constructor = CommonLiterals.class.getDeclaredConstructor();
		assertTrue(Modifier.isPrivate(constructor.getModifiers()));

		constructor.setAccessible(true);
		final InvocationTargetException ex = assertThrows(InvocationTargetException.class, constructor::newInstance);
		assertInstanceOf(IllegalStateException.class, ex.getCause());
		assertEquals(CommonBaseConstants.MSG_UTILITY_CLASS, ex.getCause().getMessage());
	}

	@Test
	void testLiterales() {
		assertEquals("audit.critical.time.warning", CommonLiterals.LIT_CRITICAL_TIME_WARNING);
		assertEquals("audit.time.warning", CommonLiterals.LIT_TIME_WARNING);
	}

}
