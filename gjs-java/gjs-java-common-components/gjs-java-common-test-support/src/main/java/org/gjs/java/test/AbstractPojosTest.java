package org.gjs.java.test;

import java.util.Arrays;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;
import java.util.concurrent.ConcurrentHashMap;

import javax.naming.spi.ObjectFactory;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.test.tester.CompareToTester;
import org.gjs.java.test.tester.ConstructorsTester;
import org.gjs.java.test.tester.DefaultGetterTester;
import org.gjs.java.test.tester.DefaultSetterTester;
import org.gjs.java.test.tester.EqualsAndCompareToTester;
import org.gjs.java.test.tester.EqualsTester;
import org.gjs.java.test.tester.HashCodeTester;
import org.gjs.java.test.tester.ToStringTester;
import org.gjs.java.test.types.Testers;
import org.slf4j.Logger;

import com.openpojo.reflection.PojoClassFilter;
import com.openpojo.validation.Validator;
import com.openpojo.validation.ValidatorBuilder;
import com.openpojo.validation.rule.impl.GetterMustExistRule;
import com.openpojo.validation.rule.impl.SetterMustExistRule;

/**
 * The Class AbstractPojosTest.
 *
 * Clase abstracta funcional de la librería Gjs
 *
 * Clase abstracta base para todos los test unitarios Pojos de la librería
 * Gjs
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class AbstractPojosTest {

	/** The map special testers. */
	private final Map<String, Testers> mapSpecialTesters = new ConcurrentHashMap<>();

	/** The stop on error. */
	private final boolean stopOnError;

	/**
	 * Instantiates a new abstract pojos test.
	 */
	protected AbstractPojosTest() {
		stopOnError = true;
	}

	/**
	 * Instantiates a new abstract pojos test.
	 *
	 * @param stopOnError the stop on e163 rror
	 */
	protected AbstractPojosTest(boolean stopOnError) {
		this.stopOnError = stopOnError;
	}

	/**
	 * Checks if is stop on error.
	 *
	 * @return true, if is stop on error
	 */
	protected boolean isStopOnError() {
		return this.stopOnError;
	}

	/**
	 * Gets the logger.
	 *
	 * @return logger
	 */
	protected abstract Logger getLogger();

	/**
	 * Gets the pojo package.
	 *
	 * @return package to test
	 */
	protected abstract String getPojoPackage();

	/**
	 * Test pojo classes.
	 */
	protected void testPojoClasses() {
		testPojoClasses(new String[0]);
	}

	/**
	 * Test pojo classes.
	 *
	 * @param exclude the exclude
	 */
	protected void testPojoClasses(String... exclude) {
		getLogger().info("Pojo's Test: Package {}", getPojoPackage());
		getLogger().info("Pojo's Test: stopOnError={}", stopOnError);
		final Set<String> setExclude = new TreeSet<>(Arrays.asList(exclude));
		setExclude.addAll(mapSpecialTesters.keySet());
		try {
			testPojoStructureAndBehavior(setExclude);
		} catch (final NullPointerException e) {
			// Se relanza tal cual: el catch de Exception de abajo la convertiria en un aviso.
			throw e;
		} catch (final Exception e) {
			getLogger().warn(ExceptionUtils.getStackTrace(e));
		}
		testPojoStructureAndBehaviorSpecials(exclude);
	}

	/**
	 * Adds the special class testers.
	 *
	 * @param className the class name
	 * @param testers   the testers
	 */
	protected void addSpecialClassTesters(String className, Testers testers) {
		mapSpecialTesters.put(className, testers);
	}

	/**
	 * Test pojo structure and behavior.
	 *
	 * @param excludeClazz the exclude clazz
	 */
	private void testPojoStructureAndBehavior(Set<String> excludeClazz) {
		final Validator validator = ValidatorBuilder.create()
				// Add Rules
				// .with(new GetterMustExistRule()).with(new SetterMustExistRule())
				// Add Testers
				.with(new DefaultSetterTester(stopOnError)).with(new DefaultGetterTester(stopOnError))
				.with(new ToStringTester(stopOnError)).with(new HashCodeTester(stopOnError))
				.with(new EqualsTester(stopOnError)).with(new CompareToTester(stopOnError))
				.with(new EqualsAndCompareToTester(stopOnError)).with(new ConstructorsTester(stopOnError)).build();

		final PojoClassFilter[] filters = new PojoClassFilter[] { pc -> !pc.getClazz().getSimpleName().endsWith("_"),
				pc -> !pc.getClazz().isAssignableFrom(ObjectFactory.class),
				pc -> !pc.getClazz().getSimpleName().endsWith("Test"), pc -> !pc.isNestedClass(),
				pc -> !pc.isAbstract(), pc -> !pc.isInterface(), pc -> !pc.isStatic(),
				pc -> !excludeClazz.contains(pc.getClazz().getSimpleName()) };
		validator.validate(getPojoPackage(), filters);
	}

	/**
	 * Test pojo structure and behavior.
	 *
	 * @param exclude the exclude
	 */
	private void testPojoStructureAndBehaviorSpecials(String... exclude) {
		// TODO: Completar la customizacion de todos los tipos de tester y/o
		// generalizxar a cualquier conjunto de testers
		for (final Map.Entry<String, Testers> entry : mapSpecialTesters.entrySet()) {
			final String className = entry.getKey();
			getLogger().info("Special test for {}", className);
			final Testers testers = entry.getValue();
			final Validator validator = ValidatorBuilder.create()
					// Add Rules
					.with(new GetterMustExistRule()).with(new SetterMustExistRule())
					// Add Testers
					.with(testers.getSetterTester()).with(new DefaultGetterTester(stopOnError))
					.with(new ToStringTester(stopOnError)).with(new HashCodeTester(stopOnError))
					.with(new EqualsTester()).with(new CompareToTester(stopOnError))
					.with(new EqualsAndCompareToTester(stopOnError)).with(new ConstructorsTester(stopOnError)).build();

			final Set<String> excludeClazz = new TreeSet<>(Arrays.asList(exclude));
			final PojoClassFilter[] filters = new PojoClassFilter[] {
					pc -> !pc.getClazz().getSimpleName().endsWith("_"),
					pc -> !pc.getClazz().getSimpleName().endsWith("Factory"),
					pc -> pc.getClazz().getSimpleName().equals(className),
					pc -> !pc.getClazz().getSimpleName().endsWith("Test"), pc -> !pc.isNestedClass(),
					pc -> !pc.isAbstract(), pc -> !pc.isInterface(), pc -> !pc.isStatic(),
					pc -> !excludeClazz.contains(pc.getClazz().getSimpleName()) };
			validator.validate(getPojoPackage(), filters);
		}
	}

}
