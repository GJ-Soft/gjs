package org.gjs.java.test;

import org.gjs.java.common.util.ConditionUtils;
import org.springframework.data.jpa.repository.JpaRepository;

/**
 * The Class SimplePKRepositoryUnitTest.
 *
 * Clase funcional de la librería Gjs
 *
 * Clase base para todos los test unitarios de repositorios JPA con clave de tipo Long de la librería Gjs
 *
 * @param <JPA>
 *            el repositorio JPA
 * @param <E>
 *            la entidad JPA
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class SimplePKRepositoryUnitTest<E, JPA extends JpaRepository<E, Long>>
        extends BaseRepositoryUnitTest<E, Long, JPA> {

    /**
     * Instantiates a new simple PK repository unit test.
     *
     * @param testClazz
     *            the test clazz
     * @param entityClazz
     *            the entity clazz
     */
    public SimplePKRepositoryUnitTest(Class<JPA> testClazz, Class<E> entityClazz) {
        super(testClazz, entityClazz, Long.class);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.AbstractRepositoryUnitTest#getImmutableId(int) */

    @Override
    protected Long getImmutableId(int index) {
        Long res = null;
        final Long[] immutableIds = getImmutableIds();
        if (ConditionUtils.allAreTrue((index >= 0), (index < immutableIds.length))) {
            res = immutableIds[index];
        }
        return res;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.AbstractRepositoryUnitTest#getNonExistentId() */

    @Override
    protected Long getNonExistentId() {
        return IDNE;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.BaseRepositoryUnitTest#isExpected(java.lang.Object) */

    @Override
    protected boolean isExpected(Long id) {
        return isIdExpected(id);
    }

}
