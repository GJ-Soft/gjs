package org.gjs.java.test.tester;

import java.util.ArrayList;
import java.util.List;

import org.gjs.java.common.supplier.GenericObjectSupplier;
import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.ReflectionUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.openpojo.reflection.PojoClass;

/**
 * The Class EqualsTester.
 *
 * Clase de datos de la librería Gjs
 *
 * Tester de coherencia de los métodos equals y compareTo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class EqualsAndCompareToTester extends BaseMethodTester {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(EqualsAndCompareToTester.class);

	/** The Constant NUM_OBJECTS. */
	private static final int NUM_OBJECTS = 15;

	/** The Constant TEST_METHOD_EQUALS. */
	private static final String TEST_METHOD_EQUALS = "equals";

	/** The Constant TEST_METHOD. */
	private static final String TEST_METHOD = "compareTo";

	/**
	 * Instantiates a new equals and compare to tester.
	 */
	public EqualsAndCompareToTester() {
		super(logger);
	}

	/**
	 * Instantiates a new equals and compare to tester.
	 *
	 * @param stopOnError the stop on error
	 */
	public EqualsAndCompareToTester(boolean stopOnError) {
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
	 * org.gjs.java.test.tester.BaseTester#canRun(com.openpojo.reflection.PojoClass)
	 */

	@Override
	protected boolean canRun(PojoClass pojoClass) {
		return ConditionUtils.allAreTrue(super.canRun(pojoClass),
				ReflectionUtils.hasMethod(pojoClass.getClazz(), TEST_METHOD_EQUALS));
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
		logger.info("EqualsAndCompareTester: Class={}", className);
		final GenericObjectSupplier supplier = new GenericObjectSupplier(className);
		supplier.setInformAllFields(true);
		supplier.setLogger(logger);
		Object instance1 = supplier.get();
		if (instance1 instanceof Comparable) {
			final List<Object> instances = new ArrayList<>();
			instances.add(instance1);
			for (int i = 0; i < NUM_OBJECTS - 1; i = i + 1) {
				instances.add(supplier.get());
			}
			for (int i = 0; i < NUM_OBJECTS; i = i + 1) {
				instance1 = instances.get(i);
				@SuppressWarnings("unchecked")
				final Comparable<Object> comparable = ((Comparable<Object>) instance1);
				for (int j = 0; j < NUM_OBJECTS; j = j + 1) {
					final Object instance2 = instances.get(j);
					if (instance1.equals(instance2)) {
						affirmTrue(String.format(
								"Class=[%s] 'equals()' not match 'compareTo() compareTo of %s and %s must be 0",
								className, instance1, instance2), comparable.compareTo(instance2) == 0);
					} else {
						affirmFalse(String.format(
								"Class=[%s] 'equals()' not match 'compareTo() compareTo of %s and %s must be different of 0",
								className, instance1, instance2), comparable.compareTo(instance2) == 0);
					}
				}
			}
		}
	}

}
