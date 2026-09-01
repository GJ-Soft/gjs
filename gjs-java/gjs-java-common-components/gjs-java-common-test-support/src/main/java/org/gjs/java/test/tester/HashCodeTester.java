package org.gjs.java.test.tester;

import org.gjs.java.common.supplier.GenericObjectSupplier;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.openpojo.reflection.PojoClass;

/**
 * The Class HashCodeTester.
 *
 * Clase de datos de la librería Gjs
 *
 * Tester de métodos hashCode.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class HashCodeTester extends BaseMethodTester {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(HashCodeTester.class);

	/** The Constant TEST_METHOD. */
	private static final String TEST_METHOD = "hashCode";

	/**
	 * Instantiates a new hash code tester.
	 */
	public HashCodeTester() {
		super(logger);
	}

	/**
	 * Instantiates a new hash code tester.
	 *
	 * @param stopOnError the stop on error
	 */
	public HashCodeTester(boolean stopOnError) {
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
		logger.info("HashCodeTester: Class={}", className);
		final GenericObjectSupplier supplier = new GenericObjectSupplier(className);
		supplier.setInformAllFields(true);
		supplier.setLogger(logger);
		final Object instance = supplier.get();
		final Object instanceEmpty = supplier.getEmpty();
		final Object instanceNull = supplier.getNullius();
		int value = instance.hashCode();
		affirmTrue(String.format("Class=[%s] 'hashCode()' random object (object=%s; value=%s)", className, instance,
				value), value != 0);
		value = instanceEmpty.hashCode();
		affirmTrue(String.format("Class=[%s] 'hashCode()' empty object (1) (object=%s; value=%s)", className,
				instanceEmpty, value), value != 0);
		value = instanceNull.hashCode();
		affirmTrue(String.format("Class=[%s] 'hashCode()' empty object (2) (object=%s; value=%s)", className,
				instanceNull, value), value != 0);

	}
}
