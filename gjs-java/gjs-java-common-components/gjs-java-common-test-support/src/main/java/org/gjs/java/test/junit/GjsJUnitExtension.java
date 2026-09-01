package org.gjs.java.test.junit;

import java.util.MissingResourceException;
import java.util.ResourceBundle;

import org.gjs.java.common.supplier.ObjectSupplierManager;
import org.gjs.java.common.util.ClazzUtils;
import org.gjs.java.test.supplier.testinggame.TestingGamesSingleton;
import org.junit.jupiter.api.extension.BeforeAllCallback;
import org.junit.jupiter.api.extension.ExtensionContext;
import org.mockito.junit.jupiter.MockitoExtension;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class SemillaJUnitExtension.
 *
 * Clase de la librería Gjs.
 *
 * Extensión de Junit que permite cargar automáticamente los
 * ObjectSupplierManager que proveen de juegos de pruebas aleatorios que se
 * indiquen en el fichero testinggames.properties.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class GjsJUnitExtension extends MockitoExtension implements BeforeAllCallback, AutoCloseable {

	/** The Constant PROPERTIES_FILE. */
	private static final String PROPERTIES_FILE = "testinggames";

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(GjsJUnitExtension.class);

	/** The started. */
	private static boolean started;

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.junit.jupiter.api.extension.BeforeAllCallback#beforeAll(org.junit.jupiter
	 * .api.extension.ExtensionContext)
	 */

	@Override
	public void beforeAll(ExtensionContext context) {
		if (!started) {
			started = true;
			try {
				final ResourceBundle rb = ResourceBundle.getBundle(PROPERTIES_FILE);
				for (final String testinggame : rb.keySet()) {
					final ObjectSupplierManager objestSupplierManager = (ObjectSupplierManager) ClazzUtils
							.createInstance(rb.getString(testinggame), logger);
					logger.debug("Adding testing game {} : {}", testinggame, objestSupplierManager);
					TestingGamesSingleton.getInstance().addTestingGamne(testinggame, objestSupplierManager);
				}
			} catch (final MissingResourceException e) {
				// Do nothing
			}
		}
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.junit.jupiter.api.extension.ExtensionContext.Store.CloseableResource#
	 * close()
	 */

	@Override
	public void close() {
		TestingGamesSingleton.getInstance().clear();
	}
}
