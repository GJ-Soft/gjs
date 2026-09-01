package org.gjs.java.test.mock;

import java.util.Objects;

/**
 * The Class MockDatabaseSingleton.
 *
 * Clase singleton de la librería Gjs.
 *
 * Clase singleton pensada como proveedor global de una base de datos moqueada configurable para test.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockDatabaseSingleton extends MockModelDataManager {

    /** The instance. */
    private static MockDatabaseSingleton instance;

    /**
     * Instantiates a new mock database singleton.
     */
    public MockDatabaseSingleton() {
        // No hace nada
    }

    /**
     * Gets the single instance of MockDatabaseSingleton.
     *
     * @return single instance of MockDatabaseSingleton
     */
    public static MockDatabaseSingleton getInstance() {
        if (Objects.isNull(instance)) {
            instance = new MockDatabaseSingleton();
        }
        return instance;
    }

}
