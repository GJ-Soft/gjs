package org.gjs.java.test;

import static org.junit.jupiter.api.Assertions.fail;

import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.gjs.java.test.junit.GjsJUnitExtension;
import org.gjs.java.test.supplier.testinggame.TestingGamesSingleton;
import org.junit.jupiter.api.extension.ExtendWith;

/**
 * The Class AbstractUnitTest.
 *
 * Clase abstracta funcional de la librería Gjs
 *
 * Clase abstracta base para todos los test unitarios de la librería Gjs
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@ExtendWith(GjsJUnitExtension.class)
public abstract class AbstractUnitTest extends AbstractClassTest {

	/** The line sep. */
	protected static String lineSep = System.lineSeparator();

	/** The file sep. */
	protected static String fileSep = FileSystems.getDefault().getSeparator();

	/** The current dir. */
	protected Path currentDir;

	/** The results dir. */
	protected Path resultsDir;

	/**
	 * Initialize.
	 *
	 * @throws Exception the exception
	 */
	protected void initialize() throws Exception {
		logger.debug("Empty initialize: maybe you should overwrite it?");
	}

	/**
	 * Prepare Test.
	 */
	@Override
	protected void prepareTest() {
		TestingGamesSingleton.getInstance().setLogger(logger);
		try {
			currentDir = Paths.get("").resolve("target/test-classes");
			resultsDir = currentDir.resolve("results");
			logger.debug("Directorio de ejecucion : {}", currentDir.toFile().getAbsolutePath());
			logger.debug("Directorio de resultados: {}", resultsDir.toFile().getAbsolutePath());
			if (!resultsDir.toFile().exists()) {
				resultsDir.toFile().mkdirs();
			}
			initialize();
		} catch (final Exception e) {
			logger.error("Error inicializando los datos para el test", e);
			fail("Error inicializando los datos para el test");
		}
	}

}
