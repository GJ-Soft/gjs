package org.gjs.java.test;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.TestInstance.Lifecycle;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class AbstractTest.
 *
 * Clase abstracta funcional de la librería Gjs
 *
 * Clase abstracta base para todos los test de la librería Gjs
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@TestInstance(Lifecycle.PER_CLASS)
public abstract class AbstractTest {

	/** The logger. */
	protected Logger logger;

	/**
	 * Prepare test.
	 */
	protected abstract void prepareTest() throws Exception;

	/**
	 * Finalize test.
	 */
	protected abstract void finalizeTest() throws Exception;

	/**
	 * Initialize logger.
	 */
	protected void initializeLogger() {
		logger = LoggerFactory.getLogger(getClass());
		logger.info("INICIO Test unitario {}", getClass().getName());
	}

	/**
	 * Finalize logger.
	 */
	protected void finalizeLogger() {
		logger.info("FIN Test unitario {}", getClass().getName());
	}

	/**
	 * Before all.
	 */
	@BeforeAll
	protected void beforeAll() throws Exception {
		initializeLogger();
		prepareTest();
	}

	/**
	 * After all.
	 */
	@AfterAll
	protected void afterAll() throws Exception {
		finalizeTest();
		finalizeLogger();
	}

}
