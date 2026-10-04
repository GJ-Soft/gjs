package org.gjs.java.test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.fail;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.apache.commons.collections4.CollectionUtils;
import org.gjs.java.test.util.PojoUtils;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.TestInstance;
import org.junit.jupiter.api.TestInstance.Lifecycle;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.junit.jupiter.MockitoExtension;
import org.slf4j.Logger;

import com.openpojo.validation.test.Tester;

/**
 * The Class AbstractPackageTest.
 *
 * Clase abstracta funcional de la librería Gjs
 *
 * Clase abstracta base para todos los test unitarios que se apliquen a todas
 * las clases de un un paquete concreto de la librería Gjs
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@TestInstance(Lifecycle.PER_CLASS)
@ExtendWith(MockitoExtension.class)
public abstract class AbstractPackageTest {

	/** The testers. */
	protected final List<Tester> testers;

	/**
	 * Instantiates a new abstract package test.
	 *
	 * @param testers the testers
	 */
	protected AbstractPackageTest(Tester... testers) {
		this.testers = new ArrayList<>();
		Collections.addAll(this.testers, testers);
	}

	/**
	 * Gets the logger.
	 *
	 * @return the logger
	 */
	protected abstract Logger getLogger();

	/**
	 * Gets the package.
	 *
	 * @return the package
	 */
	protected abstract String getPackage();

	/**
	 * Initialize.
	 *
	 * @throws Exception the exception
	 */
	protected void initialize() throws Exception {
		getLogger().debug("Empty initialize: maybe you should overwrite it?");
	}

	/**
	 * Before all.
	 */
	@BeforeAll
	protected void beforeAll() {
		assertNotNull(getPackage(), "Debe implementar correctamente la function getPackage()");
		assertFalse(CollectionUtils.isEmpty(testers), "Debe incluir algun tester");
		try {
			getLogger().info("INICIO Test del paquete {}", getPackage());
			initialize();
		} catch (final Exception e) {
			getLogger().error("Error inicializando los datos para el test", e);
			fail("Error inicializando los datos para el test");
		}
	}

	/**
	 * After all.
	 */
	@AfterAll
	protected void afterAll() {
		getLogger().info("FIN Test del paquete {}", getPackage());
	}

	/**
	 * Test classes.
	 */
	public void testClasses() {
		PojoUtils.testPojo(testers, getPackage());
	}

}
