package org.gjs.java.common.files;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.nio.file.Path;
import java.util.ArrayList;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.type.DataObject;
import org.gjs.java.common.util.ConversionUtils;
import org.gjs.java.test.BaseUnitTest;
import org.junit.jupiter.api.Test;

public class FileObjectsTest extends BaseUnitTest<FileObjects> {

	@Test
	void testFileObjects1() {
		try {
			final Path filePath = currentDir.resolve("data/rol.csv");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileObjects file = new FileObjects(',', filePath.toAbsolutePath().toString());
			logger.debug("Attriutes={}", file.attributes());
			logger.debug("Columns={}", file.columns());
			logger.debug("Count={}", file.count());
			logger.debug("Rows={}", file.rows());
			assertTrue(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(7, file.getColumnNames().size());
			assertEquals(file.columns(), file.getColumnNames().size());
			assertEquals(file.attributes(), file.getColumnNames().size());

			final String[] ATTRIBUTES_EXPECTED1 = { "id", "aplicacionId", "nombre", "descripcion", "fechaAlta",
					"fechaBaja", "activo" };

			final String[][] EXPECTED1 = { { "4", "1", "prueba_jlm", "Rol prueba", "06/11/23", "null", "1" },
					{ "5", "1", "SUPERADMINISTRADOR", "Superadministrador de semilla.", "06/11/23", "null", "1" },
					{ "6", "1", "PRUEBA_JLM", "PRUEBA_JLM descripción", "15/12/23", "null", "1" },
					{ "1", "1", "ADM_SEMILLA2", "Administrador de semilla.", "06/11/23", "null", "1" },
					{ "2", "1", "CON_SEMILLA2", "Consulta semilla.", "06/11/23", "null", "1" },
					{ "3", "1", "ANONIMO2",
							"Rol provisional para los usuarios que se autentican sin estar registrados en el sistema.",
							"06/11/23", "null", "1" } };

			final String[][] EXPECTED2 = { { "4", "1", "prueba_jlm", "Rol prueba", "06/11/23", "null", "1" },
					{ "5", "1", "SUPERADMINISTRADOR", "Superadministrador de semilla.", "06/11/23", "null", "1" },
					{ "6", "1", "PRUEBA_JLM", "PRUEBA_JLM descripción", "15/12/23", "15/01/24", "1" },
					{ "null", "null", "null", "null", "null", "null", "null" },
					{ "2", "1", "CON_SEMILLA2", "Consulta semilla.", "06/11/23", "null", "1" },
					{ "3", "1", "ANONIMO2",
							"Rol provisional para los usuarios que se autentican sin estar registrados en el sistema.",
							"06/11/23", "null", "1" },
					{ "9", "1", "ROL_X", "Rol de test", "01/01/2024", "null", "1" } };

			for (int i = 0; i < file.attributes(); i = i + 1) {
				final String attribute = file.getAttribute(i);
				assertNotNull(attribute);
				assertEquals(ATTRIBUTES_EXPECTED1[i], attribute);
			}

			assertEquals(6, file.rows());
			assertEquals(file.rows(), file.count());
			assertNotNull(file.getObjects());
			assertEquals(file.count(), file.getObjects().size());

			for (int i = 0; i < file.count(); i = i + 1) {
				final DataObject data = file.getObject(i);
				assertNotNull(data);
				assertEquals(file.attributes(), data.getFields().size());
				for (int j = 0; j < file.attributes(); j = j + 1) {
					if ("null".equals(EXPECTED1[i][j])) {
						assertNull(data.getValue(file.getAttribute(j)));
					} else {
						assertEquals(EXPECTED1[i][j], data.getValue(file.getAttribute(j)),
								String.format("Object=%s Attribute=%s(%s): Value error", i, file.getAttribute(j), j));
					}
				}
			}

			file.setColumnName(0, "");
			file.setColumnName(2, "CAMBIADO");
			for (int i = 0; i < file.attributes(); i = i + 1) {
				final String attribute = file.getAttribute(i);
				assertNotNull(attribute);
				assertEquals(ATTRIBUTES_EXPECTED1[i], attribute);
			}

			file.setValue(1, 0, "CAMBIADO");
			file.setValue(2, 1, null);
			file.setRow(3, "a", "b", "c");

			assertEquals(6, file.rows());
			assertEquals(file.rows(), file.count());
			assertNotNull(file.getObjects());
			assertEquals(file.count(), file.getObjects().size());

			for (int i = 0; i < file.count(); i = i + 1) {
				final DataObject data = file.getObject(i);
				assertNotNull(data);
				assertEquals(file.attributes(), data.getFields().size());
				for (int j = 0; j < file.attributes(); j = j + 1) {
					if ("null".equals(EXPECTED1[i][j])) {
						assertNull(data.getValue(file.getAttribute(j)));
					} else {
						assertEquals(EXPECTED1[i][j], data.getValue(file.getAttribute(j)),
								String.format("Object=%s Attribute=%s(%s): Value error", i, file.getAttribute(j), j));
					}
				}
			}

			DataObject data = file.getObject(2);
			assertNotNull(data);
			data.setValue(file.getAttribute(5), "15/01/24");

			data = new DataObject();
			file.setObject(3, data);
			assertEquals(6, file.count());
			DataObject dataRec = file.getObject(3);
			assertNotEquals(data, dataRec);
			for (int j = 0; j < file.attributes(); j = j + 1) {
				data.setValue(file.getAttribute(j), null);
			}
			file.setObject(3, data);
			assertEquals(6, file.count());
			dataRec = file.getObject(3);
			assertEquals(data, dataRec);

			data = new DataObject();
			data.setValue("id", "9");
			data.setValue("aplicacionId", "1");
			data.setValue("nombre", "ROL_X");
			data.setValue("descripcion", "Rol de test");
			data.setValue("fechaAlta", "01/01/2024");
			data.setValue("fechaBaja", null);
			data.setValue("activo", "1");
			file.addObject(data);
			assertEquals(7, file.count());
			dataRec = file.getObject(6);
			assertEquals(data, dataRec);
			for (int i = 0; i < file.count(); i = i + 1) {
				data = file.getObject(i);
				assertNotNull(data);
				assertEquals(file.attributes(), data.getFields().size());
				for (int j = 0; j < file.attributes(); j = j + 1) {
					if ("null".equals(EXPECTED2[i][j])) {
						assertNull(data.getValue(file.getAttribute(j)));
					} else {
						assertEquals(EXPECTED2[i][j], data.getValue(file.getAttribute(j)),
								String.format("Object=%s Attribute=%s(%s): Value error", i, file.getAttribute(j), j));
					}
				}
			}

			file.clearData();
			assertEquals(0, file.count());
			assertEquals(7, file.columns());
			assertNull(file.getObject(0));
			data = file.addObject();
			assertNotNull(data);
			assertEquals(1, file.count());
			for (int j = 0; j < file.attributes(); j = j + 1) {
				assertNull(data.getValue(file.getAttribute(j)));
			}

			file.clear();
			assertEquals(0, file.rows());
			assertEquals(0, file.columns());
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.getColumnNames().size());
			assertNull(file.getObject(0));
			data = file.addObject();
			assertNull(data);
			assertEquals(0, file.count());

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileObjects2() {
		try {
			final Path filePath = currentDir.resolve("data/rolVacio.csv");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileObjects file = new FileObjects(',', filePath.toAbsolutePath().toString());
			assertTrue(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(7, file.attributes());
			assertNotNull(file.getObjects());
			assertEquals(0, file.count());

			file.setColumnName(0, "");
			file.setColumnName(2, "CAMBIADO");
			assertTrue(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(7, file.attributes());
			assertNotNull(file.getObjects());
			assertEquals(0, file.count());
			assertEquals("id", file.getAttribute(0));
			assertEquals("cambiado", file.getAttribute(2));

			file.setColumnNames("Column1", "Column2");
			assertTrue(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(2, file.attributes());
			assertNotNull(file.getObjects());
			assertEquals(0, file.count());
			assertEquals("column1", file.getAttribute(0));
			assertEquals("column2", file.getAttribute(1));

			file.clearData();
			assertEquals(0, file.count());
			assertEquals(2, file.attributes());

			file.clear();
			assertEquals(0, file.count());
			assertEquals(0, file.attributes());

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileObjects3() {
		try {
			final Path filePath = currentDir.resolve("data/vacio.txt");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileObjects file = new FileObjects(',', filePath.toAbsolutePath().toString());
			assertFalse(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.attributes());
			assertNotNull(file.getObjects());
			assertEquals(0, file.count());

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileObjects4() {
		try {
			final FileObjects file = new FileObjects();
			assertFalse(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.columns());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());
			assertEquals(0, file.rows());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileObjects5() {
		try {
			final FileObjects file = new FileObjects(',');
			assertFalse(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.columns());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());
			assertEquals(0, file.rows());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileObjects6() {
		try {
			final Path filePath = currentDir.resolve("data/vacio.txt");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileObjects file = new FileObjects(filePath.toFile().toString());
			assertFalse(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.columns());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());
			assertEquals(0, file.rows());

			ArrayList<String> columns = null;
			file.setColumnNames(columns);
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.columns());
			columns = new ArrayList<>();
			file.setColumnNames(columns);
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.columns());
			columns.add("Col1");
			columns.add("Col2");
			file.setColumnNames(columns);
			assertNotNull(file.getColumnNames());
			assertEquals(2, file.columns());
			assertEquals(0, file.rows());

			file.addRow("Val1", "Val2");
			assertEquals(0, file.rows());

			final ArrayList<String> row = new ArrayList<>();
			row.add("Val1");
			row.add("Val2");
			file.addRow(row);
			assertEquals(0, file.rows());

			file.setRow(0, "Val1", "Val2");
			assertEquals(0, file.rows());
			file.setRow(0, row);
			assertEquals(0, file.rows());

			file.setValue(0, 0, "Val1");
			assertEquals(0, file.rows());
			assertNull(file.getValue(0, 0));

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileObjects7() {
		try {
			final Path filePath = currentDir.resolve("data/vacio.txt");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileObjects file = new FileObjects(filePath.toFile().getParent(), filePath.toFile().getName());
			assertFalse(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.columns());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());
			assertEquals(0, file.rows());

			file.setColumnNames();
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.columns());

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileObjects8() {
		try {
			final Path filePath = currentDir.resolve("data/vacio.txt");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileObjects file = new FileObjects(filePath.toFile());
			assertFalse(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.columns());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());
			assertEquals(0, file.rows());

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileObjects9() {
		try {
			final Path filePath = currentDir.resolve("data/vacio.txt");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileObjects file = new FileObjects(',', filePath.toFile());
			assertFalse(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.columns());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());
			assertEquals(0, file.rows());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileObjects10() {
		try {
			final Path filePath = currentDir.resolve("data/vacio.txt");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			FileObjects file = new FileObjects(filePath);
			assertFalse(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.columns());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());
			assertEquals(0, file.rows());
			assertNotNull(file.getSeparator());
			assertEquals('\t', file.getSeparator());

			file = new FileObjects(',', filePath);
			assertFalse(file.isValid());
			assertNotNull(file.getColumnNames());
			assertEquals(0, file.columns());
			assertNotNull(file.getDatos());
			assertEquals(0, file.getDatos().rows());
			assertEquals(0, file.rows());
			assertNotNull(file.getSeparator());
			assertEquals(',', file.getSeparator());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	@Test
	void testFileObjects11() {
		try {
			final Path filePath = currentDir.resolve("data/ejemplo2.csv");
			logger.info("{}", filePath.toAbsolutePath().toString().replace("\\", "\\\\"));
			final FileObjects file = new FileObjects(',', filePath.toAbsolutePath().toString());
			logger.debug("Attriutes={}", file.attributes());
			logger.debug("Columns={}", file.columns());
			logger.debug("Count={}", file.count());
			logger.debug("Rows={}", file.rows());
			assertTrue(file.isValid());
			assertNotNull(file.getColumnNames());
			// assertEquals(7, file.getColumnNames().size());
			// assertEquals(file.columns(), file.getColumnNames().size());
			// assertEquals(file.attributes(), file.getColumnNames().size());
			for (final Object obj : file.getObjects()) {
				logger.info(ConversionUtils.toString(obj));
			}
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Se ha producido un error");
		}
	}

	/**
	 * Regresion: addObject(null) evaluaba value.numFields() como argumento de
	 * ConditionUtils.oneIsTrue y daba NullPointerException. Un nulo no se anade.
	 */
	@Test
	void testAddObjectNulo() {
		final FileObjects file = new FileObjects();
		final int filas = file.rows();
		file.addObject(null);
		assertEquals(filas, file.rows());
	}

}
