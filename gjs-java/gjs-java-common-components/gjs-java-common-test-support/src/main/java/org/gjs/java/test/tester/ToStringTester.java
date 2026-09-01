package org.gjs.java.test.tester;

import java.util.Objects;

import org.gjs.java.common.supplier.GenericObjectSupplier;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.openpojo.reflection.PojoClass;

/**
 * The Class ToStringTester.
 *
 * Clase de datos de la librería Gjs
 *
 * Tester de métodos toString.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class ToStringTester extends BaseMethodTester {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(ToStringTester.class);

	/** The Constant TEST_METHOD. */
	private static final String TEST_METHOD = "toString";

	/**
	 * Instantiates a new to string tester.
	 */
	public ToStringTester() {
		super(logger);
	}

	/**
	 * Instantiates a new to string tester.
	 *
	 * @param stopOnError the stop on error
	 */
	public ToStringTester(boolean stopOnError) {
		super(logger, stopOnError);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.tester.BaseMethodTester#getTestMethod()
	 */

	@Override
	public String getTestMethod() {
		return TEST_METHOD;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * com.openpojo.validation.test.Tester#run(com.openpojo.reflection.PojoClass)
	 */

	@Override
	public void runTest(PojoClass pojoClass) {
		final String className = pojoClass.getClazz().getCanonicalName();
		logger.debug("ToStringTester: Class={}", className);
		final GenericObjectSupplier supplier = new GenericObjectSupplier(className);
		supplier.setInformAllFields(true);
		supplier.setLogger(logger);
		final Object instance = supplier.get();
		if (Objects.nonNull(instance)) {
			affirmNotNull("Expected toString random object", instance.toString());
		}
		final Object instanceEmpty = supplier.getEmpty();
		if (Objects.nonNull(instanceEmpty)) {
			affirmNotNull("Expected toString empty object (1)", instanceEmpty.toString());
		}
		final Object instanceNull = supplier.getNullius();
		if (Objects.nonNull(instanceNull)) {
			affirmNotNull("Expected toString empty object (2)", instanceNull.toString());
		}
	}
}
