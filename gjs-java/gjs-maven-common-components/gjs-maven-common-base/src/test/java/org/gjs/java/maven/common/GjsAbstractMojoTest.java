package org.gjs.java.maven.common;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.List;

import org.apache.maven.plugin.logging.Log;
import org.gjs.java.maven.exception.GjsMavenException;
import org.junit.jupiter.api.Test;

class GjsAbstractMojoTest {

	/** Mojo de usar y tirar: se le dice que debe hacer y anota si llego a ejecutarse. */
	private static class MojoDePrueba extends GjsAbstractMojo {

		private boolean skip;
		private boolean fail = true;
		private boolean ejecutado;
		private String errorAAnotar;
		private Exception fallaEnGoal;
		private Exception fallaEnInicializacion;

		@Override
		protected boolean getSkip() {
			return skip;
		}

		@Override
		protected boolean getFail() {
			return fail;
		}

		@Override
		protected String getGoalName() {
			return "goal-de-prueba";
		}

		@Override
		protected void additionalInitializations() throws Exception {
			if (fallaEnInicializacion != null) {
				throw fallaEnInicializacion;
			}
		}

		@Override
		protected void goalExecution(Log log, List<String> errorMessages) throws Exception {
			ejecutado = true;
			if (errorAAnotar != null) {
				errorMessages.add(errorAAnotar);
			}
			if (fallaEnGoal != null) {
				throw fallaEnGoal;
			}
		}
	}

	@Test
	void testSkipNoEjecutaElGoal() {
		final MojoDePrueba mojo = new MojoDePrueba();
		mojo.skip = true;

		assertDoesNotThrow(mojo::execute);
		assertFalse(mojo.ejecutado);
	}

	@Test
	void testGoalCorrecto() {
		final MojoDePrueba mojo = new MojoDePrueba();

		assertDoesNotThrow(mojo::execute);
		assertTrue(mojo.ejecutado);
	}

	@Test
	void testErrorAnotadoConFail() {
		final MojoDePrueba mojo = new MojoDePrueba();
		mojo.errorAAnotar = "algo no cuadra";

		final GjsMavenException ex = assertThrows(GjsMavenException.class, mojo::execute);
		assertTrue(ex.getMessage().contains("algo no cuadra"));
		// Nadie lanzo nada: el error lo anoto el propio goal, asi que no hay causa.
		assertNull(ex.getCause());
	}

	@Test
	void testErrorAnotadoSinFail() {
		final MojoDePrueba mojo = new MojoDePrueba();
		mojo.errorAAnotar = "algo no cuadra";
		mojo.fail = false;

		assertDoesNotThrow(mojo::execute);
	}

	/* La excepcion del goal tiene que viajar como causa, o se pierde la traza. */
	@Test
	void testExcepcionDelGoalLlevaCausa() {
		final MojoDePrueba mojo = new MojoDePrueba();
		mojo.fallaEnGoal = new IllegalStateException("reventon");

		final GjsMavenException ex = assertThrows(GjsMavenException.class, mojo::execute);
		assertSame(mojo.fallaEnGoal, ex.getCause());
		assertTrue(ex.getMessage().contains("reventon"));
	}

	/* Sin mensaje, al menos que se sepa de que excepcion se trata. */
	@Test
	void testExcepcionSinMensajeIdentificaLaClase() {
		final MojoDePrueba mojo = new MojoDePrueba();
		mojo.fallaEnGoal = new NullPointerException();

		final GjsMavenException ex = assertThrows(GjsMavenException.class, mojo::execute);
		assertTrue(ex.getMessage().contains("java.lang.NullPointerException"));
		assertTrue(ex.getMessage().contains("goal-de-prueba"));
	}

	/*
	 * Lo que falle preparando el terreno tiene que pasar por el mismo control que lo que falle en el goal: respetar
	 * getFail() y no escaparse crudo.
	 */
	@Test
	void testFalloEnInicializacionSinFail() {
		final MojoDePrueba mojo = new MojoDePrueba();
		mojo.fallaEnInicializacion = new IllegalStateException("no existe el directorio base");
		mojo.fail = false;

		assertDoesNotThrow(mojo::execute);
		assertFalse(mojo.ejecutado);
	}

	@Test
	void testFalloEnInicializacionConFail() {
		final MojoDePrueba mojo = new MojoDePrueba();
		mojo.fallaEnInicializacion = new IllegalStateException("no existe el directorio base");

		final GjsMavenException ex = assertThrows(GjsMavenException.class, mojo::execute);
		assertSame(mojo.fallaEnInicializacion, ex.getCause());
		assertFalse(mojo.ejecutado);
	}

}
