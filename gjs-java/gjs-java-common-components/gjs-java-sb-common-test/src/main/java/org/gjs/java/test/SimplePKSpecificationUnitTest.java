package org.gjs.java.test;

import java.util.Objects;

import org.apache.commons.lang3.ArrayUtils;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class SimplePKSpecificationUnitTest.
 *
 * Clase abstracta funcional de la librería Gjs
 *
 * Clase abstracta base para todos los test unitarios de specification JPA con
 * clave de tipo Long que usen una clase especial para obtener los datos de
 * filtrado diferente de la entidad de la librería Gjs
 *
 * @param <T> el repositorio JPA
 * @param <F> el filtro
 * @param <E> la entidad JPA
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class SimplePKSpecificationUnitTest<T, F, E> extends BaseSpecificationUnitTest<T, F, E, Long> {

	/**
	 * Instantiates a new simple PK specification unit test.
	 *
	 * @param testClazz   the test clazz
	 * @param filterClazz the filter clazz
	 * @param entityClazz the entity clazz
	 */
	public SimplePKSpecificationUnitTest(Class<T> testClazz, Class<F> filterClazz, Class<E> entityClazz) {
		super(testClazz, filterClazz, entityClazz, Long.class);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.AbstractRepositoryUnitTest#getImmutableId(int)
	 */

	@Override
	protected Long getImmutableId(int index) {
		Long res = null;
		final Long[] immutableIds = getImmutableIds();
		if (ConditionUtils.allAreTrue((index >= 0), (index < immutableIds.length))) {
			res = immutableIds[index];
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.AbstractRepositoryUnitTest#getNonExistentId()
	 */

	@Override
	protected Long getNonExistentId() {
		return IDNE;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.BaseSpecificationUnitTest#isExpected(java.lang.Object)
	 */

	@Override
	protected boolean isExpected(Long id) {
		boolean res = false;
		if (Objects.nonNull(id)) {
			res = ArrayUtils.contains(getExpected(), id);
		}
		return res;
	}

}
