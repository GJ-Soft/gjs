package org.gjs.java.test.mock;

import java.io.IOException;

import org.springframework.core.io.Resource;

/**
 * The Class MockSimplePKEntityService.
 *
 * Clase de datos de la librería Gjs
 *
 * Implementa un servicio de datos sencillo en memoria para cualquier clase de objetos cuya clave primaria sea un Long.
 *
 * @param <T>
 *            la clase de las entidad
 * @param <F>
 *            la clase de filtrado de datos
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockSimplePKEntityService<T, F> extends MockEntityService<T, Long, F> {

    /**
     * Instantiates a new mock simple PK entity service.
     */
    public MockSimplePKEntityService() {
    }

    /**
     * Instantiates a new mock simple PK entity service.
     *
     * @param path
     *            the path
     */
    public MockSimplePKEntityService(String path) {
        super(path);
    }

    /**
     * Instantiates a new mock simple PK entity service.
     *
     * @param resource
     *            the resource
     * @throws IOException
     *             Signals that an I/O exception has occurred.
     */
    public MockSimplePKEntityService(Resource resource) throws IOException {
        super(resource.getFile().getAbsolutePath());
    }

}
