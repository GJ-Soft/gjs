package org.gjs.java.test;

import java.lang.reflect.ParameterizedType;
import java.util.Objects;

/**
 * The Class BaseUnitTest.
 *
 * Clase funcional de la librería Gjs
 *
 * Clase base genérica para implementar los tests unitarios de una clase representada por el tipo genérico T. En caso de
 * multiherencia la clase objeto del test unitario siempre debe ser la primera clase dentro de los tipos genericos
 * parametrizados, o bien pasársele al constructor.
 *
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 * @param <T>
 *            clase a testear
 */
public class BaseUnitTest<T> extends AbstractUnitTest {

    /** The test clazz. */
    private final Class<T> testClazz;

    /**
     * Instantiates a new base unit test.
     */
    @SuppressWarnings("unchecked")
    public BaseUnitTest() {
        testClazz = (Class<T>) ((ParameterizedType) getClass().getGenericSuperclass()).getActualTypeArguments()[0];
    }

    /**
     * Instantiates a new base unit test.
     *
     * @param testClazz
     *            the test clazz
     */
    public BaseUnitTest(Class<T> testClazz) {
        this.testClazz = testClazz;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.AbstractUnitTest#getClazz() */

    @Override
    protected Class<?> getClazz() {
        return testClazz;
    }

    /**
     * Checks if is valid.
     *
     * @return true, if is valid
     */
    public boolean isValid() {
        return Objects.nonNull(testClazz);
    }
}
