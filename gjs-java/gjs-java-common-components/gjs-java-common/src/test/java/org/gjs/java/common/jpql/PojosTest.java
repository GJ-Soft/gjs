package org.gjs.java.common.jpql;

import org.gjs.java.test.AbstractPojosTest;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 *
 */
class PojosTest extends AbstractPojosTest {

	private static final Logger logger = LoggerFactory.getLogger(PojosTest.class);

	/**
	 * @return logger
	 */
	@Override
	protected Logger getLogger() {
		return logger;
	}

	/**
	 * @return package to test
	 */
	@Override
	protected String getPojoPackage() {
		return getClass().getPackage().getName();
	}

	/**
	 *
	 */
	@Test
	void testPojos() {
		testPojoClasses();
	}

}
