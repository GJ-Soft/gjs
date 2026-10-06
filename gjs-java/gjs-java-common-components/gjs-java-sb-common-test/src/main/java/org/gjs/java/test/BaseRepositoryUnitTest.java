package org.gjs.java.test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.List;
import java.util.Objects;
import java.util.Optional;

import org.gjs.java.common.util.ReflectionUtils;
import org.junit.jupiter.api.Test;
import org.springframework.data.jpa.repository.JpaRepository;

/**
 * The Class BaseRepositoryUnitTest.
 *
 * Clase funcional de la librería Gjs
 *
 * Clase base para todos los test unitarios de repositorios JPA de la librería
 * Gjs
 *
 * @param <JPA> el repositorio JPA
 * @param <E>   la entidad JPA
 * @param <PK>  la clave primaria de la entidad JPA
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class BaseRepositoryUnitTest<E, PK, JPA extends JpaRepository<E, PK>>
		extends AbstractRepositoryUnitTest<JPA, E, PK> {

	/**
	 * Instantiates a new base repository unit test.
	 *
	 * @param testClazz   the test clazz
	 * @param entityClazz the entity clazz
	 * @param pkClazz     the pk clazz
	 */
	protected BaseRepositoryUnitTest(Class<JPA> testClazz, Class<E> entityClazz, Class<PK> pkClazz) {
		super(testClazz, entityClazz, pkClazz);
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
	 * Test find by id.
	 */
	@Test
	protected void testFindById() {
		Optional<E> res = getRepository().findById(getNonExistentId());
		assertNotNull(res);
		assertFalse(res.isPresent());
		res = getRepository().findById(getImmutableId(0));
		assertNotNull(res);
		assertTrue(res.isPresent());
		assertEquals(getImmutableId(0), ReflectionUtils.getId(res.get(), getEntityClazz(), getPKClazz()));
	}

	/**
	 * Validate find all result.
	 *
	 * @param pos    the pos
	 * @param entity the entity
	 * @return true, if successful
	 */
	protected boolean validateFindAllResult(int pos, E entity) {
		return true;
	}

	/**
	 * Test find all.
	 */
	@Test
	public void testFindAll() {
		logger.info("FindAll expected results={}", validElementDataCount());
		final List<E> list = getRepository().findAll();
		assertNotNull(list);
		logger.info("FindAll return {} Results", list.size());
		for (final E entity : list) {
			logger.info("{}", entity);
		}
		assertEquals(validElementDataCount(), list.size());
		for (int i = 0; i < list.size(); i = i + 1) {
			final E entity = list.get(i);
			assertNotNull(entity);
			assertTrue(validateFindAllResult(i, entity),
					String.format("Not expected in position %s register %s", String.valueOf(i), entity));
		}
	}

	/**
	 * Test count.
	 */
	@Test
	public void testCount() {
		logger.info("Count expected results={}", validElementDataCount());
		final long count = getRepository().count();
		logger.info("Count return {} Results", count);
		assertEquals(validElementDataCount(), count);
	}

}
