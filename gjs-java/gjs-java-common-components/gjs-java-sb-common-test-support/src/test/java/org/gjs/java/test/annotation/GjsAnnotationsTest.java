package org.gjs.java.test.annotation;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

import java.lang.annotation.Annotation;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.lang.reflect.AnnotatedElement;
import java.lang.reflect.Method;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ConditionEvaluationResult;
import org.junit.jupiter.api.extension.ExecutionCondition;
import org.junit.jupiter.api.extension.ExtensionContext;

class GjsAnnotationsTest {

	private static final String PROPIEDAD = "gjs.test.propiedad";

	private static final List<Class<? extends Annotation>> TODAS = List.of(GjsDatabaseTest.class, GjsITTest.class,
			GjsEnvironmentVarValueTest.class, GjsJavaVersionTest.class, GjsPropertyValueTest.class);

	/* Metodos anotados solo para leerles la anotacion. No los descubre JUnit: la clase no es @Nested. */
	private static class Diana {

		@GjsPropertyValueTest(named = PROPIEDAD, matches = "valor")
		void propiedadQueCasa() {
			// solo interesa su anotacion
		}

		@GjsPropertyValueTest(named = PROPIEDAD, matches = "otro")
		void propiedadQueNoCasa() {
			// solo interesa su anotacion
		}

		@GjsPropertyValueTest(named = "gjs.test.inexistente", matches = ".*")
		void propiedadInexistente() {
			// solo interesa su anotacion
		}

		@GjsEnvironmentVarValueTest(named = "PATH", matches = ".+")
		void variableQueExiste() {
			// solo interesa su anotacion
		}

		@GjsEnvironmentVarValueTest(named = "GJS_VARIABLE_INEXISTENTE", matches = ".*")
		void variableInexistente() {
			// solo interesa su anotacion
		}

		@GjsJavaVersionTest(minVersion = 8)
		void desdeJava8() {
			// solo interesa su anotacion
		}

		@GjsJavaVersionTest(minVersion = 99)
		void desdeJava99() {
			// solo interesa su anotacion
		}

		@GjsJavaVersionTest(maxVersion = 8)
		void hastaJava8() {
			// solo interesa su anotacion
		}

		@GjsJavaVersionTest
		void sinLimites() {
			// solo interesa su anotacion
		}
	}

	private ConditionEvaluationResult evaluar(ExecutionCondition condicion, String metodo)
			throws NoSuchMethodException {
		final Method elemento = Diana.class.getDeclaredMethod(metodo);
		final ExtensionContext contexto = mock(ExtensionContext.class);
		when(contexto.getElement()).thenReturn(Optional.<AnnotatedElement>of(elemento));
		return condicion.evaluateExecutionCondition(contexto);
	}

	/*
	 * Sin retencion RUNTIME JUnit no las ve, y el metodo anotado no se ejecuta ni se salta: no existe como test. Es la
	 * comprobacion que sostiene a todas las demas.
	 */
	@Test
	void testRetencionEnTiempoDeEjecucion() {
		for (final Class<? extends Annotation> anotacion : TODAS) {
			final Retention retencion = anotacion.getAnnotation(Retention.class);
			assertNotNull(retencion, anotacion.getSimpleName() + " no declara @Retention");
			assertEquals(RetentionPolicy.RUNTIME, retencion.value(), anotacion.getSimpleName());
		}
	}

	@Test
	void testTodasDeclaranTarget() {
		for (final Class<? extends Annotation> anotacion : TODAS) {
			assertNotNull(anotacion.getAnnotation(Target.class), anotacion.getSimpleName() + " no declara @Target");
		}
	}

	/* Las de Spring anotan la clase de test; las de JUnit, el metodo. */
	@Test
	void testDondeSeAplicaCadaUna() {
		assertTrue(destinos(GjsITTest.class).contains(ElementType.TYPE));
		assertTrue(destinos(GjsDatabaseTest.class).contains(ElementType.TYPE));

		assertTrue(destinos(GjsJavaVersionTest.class).contains(ElementType.METHOD));
		assertTrue(destinos(GjsPropertyValueTest.class).contains(ElementType.METHOD));
		assertTrue(destinos(GjsEnvironmentVarValueTest.class).contains(ElementType.METHOD));
	}

	/* Las tres de JUnit son @Test por si mismas. */
	@Test
	void testLasDeJUnitSonTest() {
		assertTrue(GjsJavaVersionTest.class.isAnnotationPresent(Test.class));
		assertTrue(GjsPropertyValueTest.class.isAnnotationPresent(Test.class));
		assertTrue(GjsEnvironmentVarValueTest.class.isAnnotationPresent(Test.class));
	}

	@Test
	void testPropiedadDeSistema() throws NoSuchMethodException {
		final ExecutionCondition condicion = new GjsPropertyValueTest.Condicion();
		System.setProperty(PROPIEDAD, "valor");
		try {
			assertFalse(evaluar(condicion, "propiedadQueCasa").isDisabled());
			assertTrue(evaluar(condicion, "propiedadQueNoCasa").isDisabled());
			assertTrue(evaluar(condicion, "propiedadInexistente").isDisabled());
		} finally {
			System.clearProperty(PROPIEDAD);
		}
	}

	/*
	 * PATH existe en Windows y en Unix, y getenv no distingue mayusculas en Windows, asi que sirve de variable segura
	 * para el caso positivo.
	 */
	@Test
	void testVariableDeEntorno() throws NoSuchMethodException {
		final ExecutionCondition condicion = new GjsEnvironmentVarValueTest.Condicion();

		assertFalse(evaluar(condicion, "variableQueExiste").isDisabled());
		assertTrue(evaluar(condicion, "variableInexistente").isDisabled());
	}

	@Test
	void testVersionDeJava() throws NoSuchMethodException {
		final ExecutionCondition condicion = new GjsJavaVersionTest.Condicion();

		assertFalse(evaluar(condicion, "desdeJava8").isDisabled());
		assertTrue(evaluar(condicion, "desdeJava99").isDisabled());
		assertTrue(evaluar(condicion, "hastaJava8").isDisabled());
		assertFalse(evaluar(condicion, "sinLimites").isDisabled());
	}

	/* Sin la anotacion, la condicion no debe estorbar. */
	@Test
	void testSinAnotacionNoDeshabilita() {
		final ExtensionContext vacio = mock(ExtensionContext.class);
		when(vacio.getElement()).thenReturn(Optional.empty());

		assertFalse(new GjsPropertyValueTest.Condicion().evaluateExecutionCondition(vacio).isDisabled());
		assertFalse(new GjsEnvironmentVarValueTest.Condicion().evaluateExecutionCondition(vacio).isDisabled());
		assertFalse(new GjsJavaVersionTest.Condicion().evaluateExecutionCondition(vacio).isDisabled());
	}

	private List<ElementType> destinos(Class<? extends Annotation> anotacion) {
		return Arrays.asList(anotacion.getAnnotation(Target.class).value());
	}

}
