package org.gjs.java.test;

import org.gjs.java.test.mock.MockModelDataManager;

/**
 * The Class BaseDataServiceUnitTest.
 *
 * Clase abtracta funcional de la librería Gjs
 *
 * Clase base genérica para implementar los tests unitarios de los servicios de la librería Gjs
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 * @param <T>
 *            clase a testear
 * @param <D>
 *            clase mock de la base de datos
 */
public abstract class BaseDataServiceUnitTest<T, D extends MockModelDataManager> extends AbstractDataObjectUnitTest<T> {

    /** The mock database. */
    // Mocks
    protected D mockDatabase;

    /**
     * Instantiates a new abstract data object unit test.
     */
    protected BaseDataServiceUnitTest() {
    }

    /**
     * Instantiates a new abstract data object unit test.
     *
     * @param testClazz
     *            the test clazz
     */
    protected BaseDataServiceUnitTest(Class<T> testClazz) {
        super(testClazz);
    }

    /**
     * Creates the mock database.
     *
     * @return the d
     * @throws Exception
     *             the exception
     */
    protected abstract D createMockDatabase() throws Exception;

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.AbstractDataObjectUnitTest#loadTestData() */

    @Override
    protected long loadTestData() throws Exception {
        mockDatabase = createMockDatabase();
        return getExpected().length;
    }

}
