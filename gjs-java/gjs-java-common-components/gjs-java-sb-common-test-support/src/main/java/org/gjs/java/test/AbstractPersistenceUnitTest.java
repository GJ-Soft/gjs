package org.gjs.java.test;

import org.springframework.test.annotation.Rollback;
import org.springframework.transaction.annotation.Transactional;

import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;

/**
 * The Class AbstractPersistenceUnitTest.
 *
 * Clase abstracta funcional de la librería Gjs
 *
 * Clase abstracta base para todos los test unitarios de clases que necesiten datos de un repositorio JPA de la librería
 * Gjs
 *
 * @param <T>
 *            el repositorio JPA
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Transactional
@Rollback
public abstract class AbstractPersistenceUnitTest<T> extends AbstractDataObjectUnitTest<T> {

    /** The entity manager. */
    @PersistenceContext
    protected EntityManager entityManager;

    /**
     * Instantiates a new abstract persistence unit test.
     */
    public AbstractPersistenceUnitTest() {
    }

    /**
     * Instantiates a new abstract persistence unit test.
     *
     * @param testClazz
     *            the test clazz
     */
    public AbstractPersistenceUnitTest(Class<T> testClazz) {
        super(testClazz);
    }

}
