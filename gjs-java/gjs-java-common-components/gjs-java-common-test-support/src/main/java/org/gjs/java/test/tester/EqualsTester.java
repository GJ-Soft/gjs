package org.gjs.java.test.tester;

import org.gjs.java.common.supplier.GenericObjectSupplier;
import org.gjs.java.common.util.ReflectionUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.openpojo.reflection.PojoClass;

/**
 * The Class EqualsTester.
 *
 * Clase de datos de la librería Gjs
 *
 * Tester de métodos equals.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class EqualsTester extends BaseMethodTester {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(EqualsTester.class);

	/** The Constant TEST_METHOD. */
	private static final String TEST_METHOD = "equals";

	/**
	 * Instantiates a new equals tester.
	 */
	public EqualsTester() {
		super(logger);
	}

	/**
	 * Instantiates a new equals tester.
	 *
	 * @param stopOnError the stop on error
	 */
	public EqualsTester(boolean stopOnError) {
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
		logger.info("EqualsTester: Class={}", className);
		final GenericObjectSupplier supplier = new GenericObjectSupplier(className);
		supplier.setInformAllFields(true);
		supplier.setLogger(logger);
		final Object instance1 = supplier.get();
		final Object instance2 = supplier.get();
		final Object instanceEq = instance1;
		final Object instanceClon = ReflectionUtils.clone(instance1);
		final Object other = supplier.getNullius();
		final Object nullObj = null;
		// logger.debug("** EQUALS INSTANCE1={}", instance1);
		// logger.debug("** EQUALS INSTANCE2={}", instance2);
		// logger.debug("** EQUALS INSTANCECLON={}", instanceClon);
		affirmFalse(String.format(
				"Class=[%s] not dispatching 'equals()' different random generated objects. Object1=[%s]. Object2=[%s]",
				className, instance1, instance2), instance1.equals(instance2));
		affirmTrue(String.format("Class=[%s] not dispatching 'equals()' same object", className),
				instance1.equals(instance1));
		affirmTrue(String.format("Class=[%s] not dispatching 'equals()' same object", className),
				instance1.equals(instanceEq));
		affirmTrue(String.format("Class=[%s] not dispatching 'equals()' cloned object. Object=[%s]. Clon=[%s]",
				className, instance1, instanceClon), instance1.equals(instanceClon));
		affirmFalse(String.format("Class=[%s] not dispatching 'equals()' empty object", className),
				instance1.equals(other));
		affirmFalse(String.format("Class=[%s] not dispatching 'equals()' null object", className),
				instance1.equals(nullObj));

		final Object instanceEmpty = supplier.getEmpty();
		final Object instanceEmptyEq = instanceEmpty;
		final Object instanceEmptyClon = ReflectionUtils.clone(instanceEmpty);
		// logger.debug("** EQUALS INSTANCEEMPTY={}", instanceEmpty);
		// logger.debug("** EQUALS INSTANCEEMPTYCLON={}", instanceEmptyClon);
		affirmTrue(String.format("Class=[%s] not dispatching 'equals()' same empty object", className),
				instanceEmpty.equals(instanceEmptyEq));
		affirmTrue(String.format("Class=[%s] not dispatching 'equals()' empty cloned object", className),
				instanceEmpty.equals(instanceEmptyClon));
		affirmFalse(String.format(
				"Class=[%s] not dispatching 'equals()' empty and random generated objects. Object=[%s]. Empty=[%s]",
				className, instance1, instanceEmpty), instanceEmpty.equals(instance1));
	}

}
