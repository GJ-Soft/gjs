package org.gjs.java.maven.common;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.List;

import org.apache.maven.plugin.logging.Log;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.io.TempDir;

class GjsAbstractFileSelectionMojoTest {

	private static class SeleccionDePrueba extends GjsAbstractFileSelectionMojo {

		@Override
		protected boolean getSkip() {
			return false;
		}

		@Override
		protected boolean getFail() {
			return true;
		}

		@Override
		protected String getGoalName() {
			return "seleccion-de-prueba";
		}

		@Override
		protected void goalExecution(Log log, List<String> errorMessages) {
			// La seleccion la hace additionalInitializations; aqui no hay nada que hacer.
		}
	}

	private SeleccionDePrueba mojoSobre(Path raiz) {
		final SeleccionDePrueba mojo = new SeleccionDePrueba();
		mojo.baseDirectory = raiz.toFile();
		return mojo;
	}

	private List<String> seleccionados(SeleccionDePrueba mojo) {
		return Arrays.stream(mojo.includedFiles).map(f -> f.replace(File.separatorChar, '/')).sorted().toList();
	}

	private void crear(Path raiz, String ruta) throws IOException {
		final Path destino = raiz.resolve(ruta);
		Files.createDirectories(destino.getParent());
		Files.writeString(destino, "contenido");
	}

	@Test
	void testSinPatronesSeleccionaTodo(@TempDir Path raiz) throws IOException {
		crear(raiz, "uno.txt");
		crear(raiz, "dos.dat");
		crear(raiz, "sub/tres.txt");

		final SeleccionDePrueba mojo = mojoSobre(raiz);
		assertDoesNotThrow(mojo::execute);

		assertEquals(List.of("dos.dat", "sub/tres.txt", "uno.txt"), seleccionados(mojo));
	}

	@Test
	void testIncludes(@TempDir Path raiz) throws IOException {
		crear(raiz, "uno.txt");
		crear(raiz, "dos.dat");
		crear(raiz, "sub/tres.txt");

		final SeleccionDePrueba mojo = mojoSobre(raiz);
		mojo.includes = List.of("**/*.txt");
		assertDoesNotThrow(mojo::execute);

		assertEquals(List.of("sub/tres.txt", "uno.txt"), seleccionados(mojo));
	}

	@Test
	void testExcludes(@TempDir Path raiz) throws IOException {
		crear(raiz, "uno.txt");
		crear(raiz, "dos.dat");
		crear(raiz, "sub/tres.txt");

		final SeleccionDePrueba mojo = mojoSobre(raiz);
		mojo.excludes = List.of("sub/**");
		assertDoesNotThrow(mojo::execute);

		assertEquals(List.of("dos.dat", "uno.txt"), seleccionados(mojo));
	}

	/* addDefaultExcludes deja fuera los directorios de control de versiones. */
	@Test
	void testExclusionesPorDefecto(@TempDir Path raiz) throws IOException {
		crear(raiz, "uno.txt");
		crear(raiz, ".git/config");

		final SeleccionDePrueba mojo = mojoSobre(raiz);
		assertDoesNotThrow(mojo::execute);

		final List<String> seleccion = seleccionados(mojo);
		assertTrue(seleccion.contains("uno.txt"));
		assertFalse(seleccion.stream().anyMatch(f -> f.startsWith(".git/")));
	}

}
