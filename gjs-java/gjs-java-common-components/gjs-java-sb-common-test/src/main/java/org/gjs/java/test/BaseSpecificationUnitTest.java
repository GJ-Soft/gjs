package org.gjs.java.test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.util.List;
import java.util.Objects;
import java.util.function.Function;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.util.ClazzUtils;
import org.gjs.java.common.util.ReflectionUtils;
import org.junit.jupiter.api.Test;
import org.opentest4j.AssertionFailedError;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;

/**
 * The Class BaseSpecificationUnitTest.
 *
 * Clase abstracta funcional de la librería Gjs
 *
 * Clase abstracta base para todos los test unitarios de specification JPA que
 * usen una clase especial para obtener los datos de filtrado diferente de la
 * entidad de la librería Gjs
 *
 * @param <T>  el repositorio JPA
 * @param <F>  el filtro
 * @param <E>  la entidad JPA
 * @param <PK> la clave primaria de la entidad JPA
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class BaseSpecificationUnitTest<T, F, E, PK> extends AbstractRepositoryUnitTest<T, E, PK> {

	/** The filter clazz. */
	private final Class<F> filterClazz;

	/**
	 * Instantiates a new base specification unit test.
	 *
	 * @param testClazz   the test clazz
	 * @param filterClazz the filter clazz
	 * @param entityClazz the entity clazz
	 * @param pkClazz     the pk clazz
	 */
	protected BaseSpecificationUnitTest(Class<T> testClazz, Class<F> filterClazz, Class<E> entityClazz,
			Class<PK> pkClazz) {
		super(testClazz, entityClazz, pkClazz);
		this.filterClazz = filterClazz;
	}

	/**
	 * Gets the new instance function.
	 *
	 * @return the new instance function
	 */
	protected abstract Function<F, Specification<E>> getNewInstanceFunction();

	/**
	 * Gets the test filters.
	 *
	 * @return the test filters
	 */
	protected abstract List<F> getTestFilters();

	/**
	 * Gets the test expected results.
	 *
	 * @return the test expected results
	 */
	protected abstract List<Long> getTestExpectedResults();

	/**
	 * Validators test result.
	 *
	 * @param testCase the test case
	 * @param element  the element
	 * @return true, if successful
	 */
	protected abstract boolean validatorsTestResult(int testCase, E element);

	/**
	 * Gets the specification executor.
	 *
	 * @return the specification executor
	 */
	@SuppressWarnings("unchecked")
	protected JpaSpecificationExecutor<E> getSpecificationExecutor() {
		return (JpaSpecificationExecutor<E>) getRepository();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.gjs.java.test.AbstractRepositoryUnitTest#isExpected(java.lang.Object)
	 */

	@Override
	protected boolean isExpected(PK id) {
		boolean res = false;
		if (Objects.nonNull(id)) {
			res = true;
		}
		return res;
	}

	/**
	 * Valid element data count.
	 *
	 * @return the long
	 */
	@Override
	protected long validElementDataCount() {
		return initialDataCount;
	}

	/**
	 * Test new instance null.
	 */
	@SuppressWarnings("unchecked")
	@Test
	public void testNewInstanceNull() {
		try {
			final Specification<E> specification = getNewInstanceFunction().apply(null);
			assertNotNull(specification);
			final List<E> list = getSpecificationExecutor().findAll(specification);
			assertNotNull(list);
			logger.debug("Retrieved {} elements", list.size());
			for (final E element : list) {
				logger.debug("Element={}", element);
			}
			assertEquals(validElementDataCount(), list.size(), "Wrong number of elements returned");
			for (final E element : list) {
				assertNotNull(element);
				logger.debug("Element={}", element);
				final PK id = (PK) ReflectionUtils.getId(element, getEntityClazz(), getPKClazz());
				assertNotNull(id, "Retrieved id cannot be null");
				logger.info("**** {}", id);
				logger.info("**** {}", isExpected(id));
				assertTrue(isExpected(id), String.format("Element id=%s not expected", id));
			}
		} catch (final AssertionFailedError e) {
			throw e;
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Recibida excepcion");
		}
	}

	/**
	 * Test new instance empty.
	 */
	@SuppressWarnings("unchecked")
	@Test
	public void testNewInstanceEmpty() {
		try {
			final F filter = (F) ClazzUtils.createInstance(filterClazz.getCanonicalName(), logger);
			final Specification<E> specification = getNewInstanceFunction().apply(filter);
			assertNotNull(specification);
			final List<E> list = getSpecificationExecutor().findAll(specification);
			assertNotNull(list);
			logger.debug("Retrieved {} elements", list.size());
			assertEquals(validElementDataCount(), list.size(), "Wrong number of elements returned");
			for (final E element : list) {
				assertNotNull(element);
				logger.debug("Element={}", element);
				final PK id = (PK) ReflectionUtils.getId(element, getEntityClazz(), getPKClazz());
				assertTrue(isExpected(id), String.format("Element id=%s not expected", id));
			}
		} catch (final AssertionFailedError e) {
			throw e;
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Recibida excepcion");
		}
	}

	/**
	 * Test new instance general.
	 */
	@Test
	public void testNewInstanceGeneral() {
		try {
			logger.info("Filters to try: {}", getTestFilters().size());
			for (int i = 0; i < getTestFilters().size(); i = i + 1) {
				final F filter = getTestFilters().get(i);
				logger.info("{}) Filter={}", i, filter);
				final Specification<E> specification = getNewInstanceFunction().apply(filter);
				final List<E> list = getSpecificationExecutor().findAll(specification);
				assertNotNull(list);
				logger.info("{}) Results={}", i, list.size());
				for (int j = 0; j < list.size(); j = j + 1) {
					final E element = list.get(j);
					logger.debug("Element {} ={}", j, element);
				}
				assertEquals(getTestExpectedResults().get(i), list.size(),
						String.format("Wrong number of elements returned for case %s", i));
				for (final E element : list) {
					assertNotNull(element);
					assertTrue(validatorsTestResult(i, element),
							String.format("Element %s not expected for case %s", element, i));
				}
			}
		} catch (final AssertionFailedError e) {
			throw e;
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Recibida excepcion");
		}
	}

}
