package org.gjs.java.test.tester;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.lang.reflect.Parameter;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.test.BaseUnitTest;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.openpojo.reflection.PojoClass;
import com.openpojo.reflection.impl.PojoClassFactory;

class BaseMethodTesterTest extends BaseUnitTest<BaseMethodTester> {

	private static final Logger loggerDePrueba = LoggerFactory.getLogger(BaseMethodTesterTest.class);

	/** Clase de usar y tirar sobre la que mirar metodos y parametros. */
	public static class Diana {

		public void conPrimitivo(int valor) {
			// solo interesa su firma
		}

		public void conArrayPrimitivo(int[] valores) {
			// solo interesa su firma
		}

		public void conObjeto(String texto) {
			// solo interesa su firma
		}
	}

	/** Concreta minima: BaseMethodTester deja abstractos getTestMethod y runTest. */
	private static class TesterDePrueba extends BaseMethodTester {

		private final String metodo;

		TesterDePrueba(String metodo) {
			super(loggerDePrueba);
			this.metodo = metodo;
		}

		@Override
		protected String getTestMethod() {
			return metodo;
		}

		@Override
		protected void runTest(PojoClass pojoClass) {
			// no hace falta para lo que se prueba aqui
		}
	}

	private Parameter primerParametro(String metodo, Class<?> tipo) throws NoSuchMethodException {
		return Diana.class.getMethod(metodo, tipo).getParameters()[0];
	}

	/* canRun se apoya en hasMethod: solo corre sobre las clases que tienen el metodo. */
	@Test
	void testCanRunSiguesAHasMethod() {
		final TesterDePrueba conMetodo = new TesterDePrueba("conObjeto");
		final TesterDePrueba sinMetodo = new TesterDePrueba("metodoQueNoExiste");
		final PojoClass diana = PojoClassFactory.getPojoClass(Diana.class);

		assertTrue(conMetodo.hasMethod(diana));
		assertTrue(conMetodo.canRun(diana));

		assertFalse(sinMetodo.hasMethod(diana));
		assertFalse(sinMetodo.canRun(diana));
	}

	/* getTypeName quita los corchetes, de modo que un array y su tipo dan lo mismo. */
	@Test
	void testGetTypeName() {
		try {
			final TesterDePrueba tester = new TesterDePrueba("conPrimitivo");

			assertEquals("int", tester.getTypeName(primerParametro("conPrimitivo", int.class)));
			assertEquals("int", tester.getTypeName(primerParametro("conArrayPrimitivo", int[].class)));
			assertEquals("java.lang.String", tester.getTypeName(primerParametro("conObjeto", String.class)));
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	/* Para un primitivo suelto devuelve su valor por defecto; para un array, un array. */
	@Test
	void testGetDefaultPrimitiveValue() {
		try {
			final TesterDePrueba tester = new TesterDePrueba("conPrimitivo");

			final Object valor = tester.getDefaultPrimitiveValue(primerParametro("conPrimitivo", int.class));
			assertNotNull(valor);

			final Object array = tester.getDefaultPrimitiveValue(primerParametro("conArrayPrimitivo", int[].class));
			assertNotNull(array);
			assertTrue(array.getClass().isArray(), "Para un parametro array esperaba un array");
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

}
