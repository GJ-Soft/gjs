package org.gjs.java.test;

import static org.junit.jupiter.api.Assertions.fail;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class AbstractPojosTestTest extends BaseUnitTest<AbstractPojosTest> {

	private class PojosTest extends AbstractPojosTest {

		private final Logger logger = LoggerFactory.getLogger(PojosTest.class);

		@Override
		protected Logger getLogger() {
			return logger;
		}

		/**
		 * Paquete inexistente a proposito: lo que se comprueba aqui es que
		 * AbstractPojosTest aguanta un paquete sin clases que validar, no las clases
		 * en si. De eso se ocupan Pojos1Test y Pojos2Test sobre el paquete real.
		 *
		 * @return paquete vacio
		 */
		@Override
		protected String getPojoPackage() {
			return "org.gjs.java.test.samples.vacio";
		}

		public void test() {
			super.testPojoClasses();
		}
	}

	@Test
	void testAbstractPojosTest() {
		try {
			final PojosTest pojosTests = new PojosTest();
			pojosTests.test();
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

}
