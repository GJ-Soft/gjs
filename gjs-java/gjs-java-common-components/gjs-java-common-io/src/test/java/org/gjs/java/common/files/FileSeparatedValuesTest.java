package org.gjs.java.common.files;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.type.Matrix;
import org.gjs.java.test.BaseUnitTest;
import org.junit.jupiter.api.Test;

public class FileSeparatedValuesTest extends BaseUnitTest<FileSeparatedValues> {

	@Test
	void testFileSeparatedValues1() {
		try {
			final Path filePath = currentDir.resolve("data/ejemplo.csv");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileSeparatedValues file = new FileSeparatedValues(',', filePath.toAbsolutePath().toString());
			assertNotNull(file.getDirectory());
			assertNotNull(file.getName());
			assertNotNull(file.getPath());
			assertTrue(file.isValid());
			logger.info("Directory: {}", file.getDirectory());
			logger.info("Name     : {}", file.getName());
			logger.info("Path     : {}", file.getPath());
			assertNotNull(file.getSeparator());
			assertEquals(',', file.getSeparator());
			assertNotNull(file.getDatos());
			assertEquals(4, file.getDatos().rows());

			final String[][] EXPECTED = { { "valor1", "1", "0.25", "true", "AB C" },
					{ "valor2", "2", "", "false", null }, { "valor3,4", "3", "-2.01", "true", "" },
					{ "valor4", "4", "1.1", "false", "abc" } };

			for (int i = 0; i < file.getDatos().rows(); i = i + 1) {
				final List<String> row = file.getDatos().getRow(i);
				assertNotNull(row);
				assertEquals(5, file.getDatos().columns(i));
				for (int j = 0; j < file.getDatos().columns(i); j = j + 1) {
					assertEquals(EXPECTED[i][j], file.getDatos().getValue(i, j));
				}
			}

			file.clear();
			assertEquals(0, file.getDatos().rows());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileSeparatedValues2() {
		try {
			final Path filePath = currentDir.resolve("data/vacio.txt");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileSeparatedValues file = new FileSeparatedValues(',', filePath.toAbsolutePath().toString());
			assertNotNull(file.getDirectory());
			assertNotNull(file.getName());
			assertNotNull(file.getPath());
			assertTrue(file.isValid());
			logger.info("Directory: {}", file.getDirectory());
			logger.info("Name     : {}", file.getName());
			logger.info("Path     : {}", file.getPath());
			assertNotNull(file.getSeparator());
			assertEquals(',', file.getSeparator());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileSeparatedValues3() {
		try {
			final Path filePath = currentDir.resolve("data/ejemploSheet1.csv");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileSeparatedValues file = new FileSeparatedValues(',', filePath.toAbsolutePath().toString());
			assertNotNull(file.getDirectory());
			assertNotNull(file.getName());
			assertNotNull(file.getPath());
			assertTrue(file.isValid());
			logger.info("Directory: {}", file.getDirectory());
			logger.info("Name     : {}", file.getName());
			logger.info("Path     : {}", file.getPath());
			assertNotNull(file.getDatos());
			assertEquals(5, file.getDatos().rows());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileSeparatedValues4() {
		try {
			final Path filePath = currentDir.resolve("data/ejemplo.csv");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileSeparatedValues file = new FileSeparatedValues();
			assertNull(file.getDirectory());
			assertNull(file.getName());
			assertNull(file.getPath());
			assertFalse(file.isValid());
			assertNotNull(file.getSeparator());
			assertEquals('\t', file.getSeparator());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());
			file.setSeparator(',');
			file.load(filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			assertNotNull(file.getDirectory());
			assertNotNull(file.getName());
			assertNotNull(file.getPath());
			logger.info("Directory: {}", file.getDirectory());
			logger.info("Name     : {}", file.getName());
			logger.info("Path     : {}", file.getPath());
			assertTrue(file.isValid());
			assertNotNull(file.getSeparator());
			assertEquals(',', file.getSeparator());
			assertNotNull(file.getDatos());
			assertEquals(4, file.getDatos().rows());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileSeparatedValues5() {
		try {
			final Path filePath = currentDir.resolve("data/ejemplo.csv");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileSeparatedValues file1 = new FileSeparatedValues(
					filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileSeparatedValues file2 = new FileSeparatedValues(
					filePath.toAbsolutePath().getParent().toString().replace("\\", "\\\\"),
					filePath.toAbsolutePath().getFileName().toString());
			assertNotNull(file1.getDirectory());
			assertNotNull(file1.getName());
			assertNotNull(file1.getPath());
			assertNotNull(file2.getDirectory());
			assertNotNull(file2.getName());
			assertNotNull(file2.getPath());
			assertEquals(file2.getDirectory(), file1.getDirectory());
			assertEquals(file2.getName(), file2.getName());
			assertEquals(file2.getPath(), file2.getPath());
			assertNotNull(file1.getSeparator());
			assertNotNull(file2.getSeparator());
			assertEquals(file2.getSeparator(), file1.getSeparator());
			assertNotNull(file1.getDatos());
			assertNotNull(file2.getDatos());
			assertEquals(file2.getDatos().rows(), file1.getDatos().rows());
			assertTrue(file1.isValid());
			assertTrue(file2.isValid());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileSeparatedValues6() {
		try {
			final Path filePath = currentDir.resolve("data/ejemplo.csv");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileSeparatedValues file = new FileSeparatedValues();
			assertNull(file.getDirectory());
			assertNull(file.getName());
			assertNull(file.getPath());
			assertFalse(file.isValid());
			assertNotNull(file.getSeparator());
			assertEquals('\t', file.getSeparator());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());
			file.setSeparator(',');
			file.load(filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			assertNotNull(file.getDirectory());
			assertNotNull(file.getName());
			assertNotNull(file.getPath());
			assertTrue(file.isValid());
			logger.info("Directory: {}", file.getDirectory());
			logger.info("Name     : {}", file.getName());
			logger.info("Path     : {}", file.getPath());
			assertNotNull(file.getSeparator());
			assertEquals(',', file.getSeparator());
			assertNotNull(file.getDatos());
			assertEquals(4, file.getDatos().rows());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileSeparatedValues7() {
		try {
			final Path filePath = currentDir.resolve("data/nuevoX.csv");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
            Files.deleteIfExists(filePath);
			final FileSeparatedValues file = new FileSeparatedValues(filePath.toFile());
			assertNotNull(file.getDirectory());
			assertNotNull(file.getName());
			assertNotNull(file.getPath());
			logger.info("Directory: {}", file.getDirectory());
			logger.info("Name     : {}", file.getName());
			logger.info("Path     : {}", file.getPath());
			assertTrue(file.isValid());
			assertFalse(file.exists());
			assertNotNull(file.getSeparator());
			assertEquals('\t', file.getSeparator());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());

			final Matrix<String> datos = new Matrix<>();
			file.setDatos(datos);
			assertTrue(file.isValid());
			assertFalse(file.exists());
			assertEquals(0, file.getDatos().rows());

			datos.addRow("Line1", "Value1");
			datos.addRow("Line2", "Value2");
			file.setDatos(datos);
			assertTrue(file.isValid());
			assertFalse(file.exists());
			assertEquals(2, file.getDatos().rows());

			assertTrue(file.save());
			assertTrue(file.isValid());
			assertTrue(file.exists());

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileSeparatedValues8() {
		try {
			final Path filePath = currentDir.resolve("data/ejemplo.csv");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			FileSeparatedValues file = new FileSeparatedValues(filePath);
			assertNotNull(file.getDirectory());
			assertNotNull(file.getName());
			assertNotNull(file.getPath());
			assertTrue(file.isValid());
			logger.info("Directory: {}", file.getDirectory());
			logger.info("Name     : {}", file.getName());
			logger.info("Path     : {}", file.getPath());
			assertNotNull(file.getSeparator());
			assertEquals('\t', file.getSeparator());
			assertNotNull(file.getDatos());
			assertEquals(4, file.getDatos().rows());

			file = new FileSeparatedValues(',', filePath);
			assertNotNull(file.getDirectory());
			assertNotNull(file.getName());
			assertNotNull(file.getPath());
			assertTrue(file.isValid());
			logger.info("Directory: {}", file.getDirectory());
			logger.info("Name     : {}", file.getName());
			logger.info("Path     : {}", file.getPath());
			assertNotNull(file.getSeparator());
			assertEquals(',', file.getSeparator());
			assertNotNull(file.getDatos());
			assertEquals(4, file.getDatos().rows());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	/*
	 * Regresión: una columna nula lanzaba NullPointerException al guardar
	 * (Objects.requireNonNull); se escribe "null", como en SeparatedValuesDataStreamer.
	 */
	@Test
	void testFileSeparatedValuesNullColumn() throws Exception {
		final Path filePath = currentDir.resolve("data/nuloX.csv");
		Files.deleteIfExists(filePath);
		final FileSeparatedValues file = new FileSeparatedValues(filePath.toFile());
		final Matrix<String> datos = new Matrix<>();
		datos.addRow("Line1", null);
		file.setDatos(datos);
		assertTrue(file.save());
		assertEquals("Line1\tnull", Files.readAllLines(filePath).get(0));
		Files.deleteIfExists(filePath);
	}

}
