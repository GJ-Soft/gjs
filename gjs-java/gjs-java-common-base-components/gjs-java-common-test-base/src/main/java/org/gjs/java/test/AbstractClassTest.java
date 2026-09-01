package org.gjs.java.test;

import java.util.Objects;

import org.slf4j.LoggerFactory;

/**
 * The Class AbstractClassTest.
 *
 * Clase abstracta funcional de la librería Gjs
 *
 * Clase abstracta base para todos los test de clases de la librería Gjs
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class AbstractClassTest extends AbstractTest {

	/**
	 * Gets the clazz.
	 *
	 * @return the clazz
	 */
	protected abstract Class<?> getClazz();

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.AbstractTest#initializeLogger()
	 */

	@Override
	protected void initializeLogger() {
		logger = LoggerFactory.getLogger(this.getClass());
		logger.info("INICIO Test de la clase {}", getClassName());
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.AbstractTest#finalizeLogger()
	 */

	@Override
	protected void finalizeLogger() {
		logger.info("FIN Test de la clase {}", getClassName());
	}

	private String getClassName() {
		String res = "<Ninguna>";
		if (Objects.nonNull(getClazz())) {
			res = getClazz().getName();
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.AbstractTest#prepareTest()
	 */

	@Override
	protected void prepareTest() throws Exception {
		// Implementación por defecto: No hace falta hacer nada
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.AbstractTest#finalizeTest()
	 */

	@Override
	protected void finalizeTest() throws Exception {
		// Implementación por defecto: No hace falta hacer nada
	}

}
