package org.gjs.java.test.tester;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.gjs.java.test.BaseUnitTest;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.openpojo.reflection.PojoClass;
import com.openpojo.reflection.impl.PojoClassFactory;

class BaseFieldTesterTest extends BaseUnitTest<BaseFieldTester> {

	private static final Logger loggerDePrueba = LoggerFactory.getLogger(BaseFieldTesterTest.class);

	/** Concreta minima: BaseFieldTester solo deja abstracto el runTest. */
	private static class TesterDePrueba extends BaseFieldTester {

		private int vueltas;

		TesterDePrueba() {
			super(loggerDePrueba, "Prueba");
		}

		TesterDePrueba(boolean stopOnError) {
			super(loggerDePrueba, "Prueba", stopOnError);
		}

		@Override
		protected void runTest(PojoClass pojoClass) {
			beginClass(pojoClass.getName(), pojoClass.getPojoFields().size());
			for (int i = 0; i < pojoClass.getPojoFields().size(); i = i + 1) {
				fieldProcessed();
			}
			endClass();
			vueltas = vueltas + 1;
		}
	}

	/* canRun no filtra nada: acepta cualquier clase. */
	@Test
	void testCanRunAceptaTodo() {
		final TesterDePrueba tester = new TesterDePrueba();

		assertTrue(tester.canRun(PojoClassFactory.getPojoClass(String.class)));
		assertTrue(tester.canRun(PojoClassFactory.getPojoClass(BaseFieldTesterTest.class)));
	}

	@Test
	void testStopOnError() {
		assertTrue(new TesterDePrueba(true).isStopOnError());
	}

	/* El ciclo begin/fieldProcessed/end no debe reventar ni con clases sin campos. */
	@Test
	void testCicloCompleto() {
		final TesterDePrueba tester = new TesterDePrueba();

		assertDoesNotThrow(() -> tester.run(PojoClassFactory.getPojoClass(TesterDePrueba.class)));
		assertDoesNotThrow(() -> tester.run(PojoClassFactory.getPojoClass(Object.class)));
		assertTrue(tester.vueltas >= 1);
	}

}
