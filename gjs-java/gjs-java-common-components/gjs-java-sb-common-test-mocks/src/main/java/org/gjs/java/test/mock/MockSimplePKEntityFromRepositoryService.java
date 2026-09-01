package org.gjs.java.test.mock;

import java.util.Objects;

/**
 * The Class MockSimplePKEntityFromRepositoryService.
 *
 * Clase de la libreria Gjs Implementa un repositorio JPA de datos sencillo en memoria para cualquier clase de
 * objetos.
 *
 * @param <DTO>
 *            the generic type
 * @param <E>
 *            the element type
 * @param <FDTO>
 *            the generic type
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class MockSimplePKEntityFromRepositoryService<DTO, E, FDTO>
        extends MockEntityFromRepositoryService<DTO, Long, E, Long, FDTO> {

    /** The mock repository. */
    protected MockEntityDataManager<E, Long> mockRepository;

    /**
     * Instantiates a new mock simple PK entity from repository service.
     */
    public MockSimplePKEntityFromRepositoryService() {
    }

    /**
     * Instantiates a new mock simple PK entity from repository service.
     *
     * @param mockRepository
     *            the mock repository
     */
    public MockSimplePKEntityFromRepositoryService(MockEntityDataManager<E, Long> mockRepository) {
        this.mockRepository = mockRepository;
        if (Objects.nonNull(mockRepository)) {
            for (final E entity : mockRepository.getAll()) {
                super.put(entityToDto(entity));
            }
        }
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.mock.MockEntityDataManager#getPKClazz() */

    @Override
    protected Class<?> getPKClazz() {
        return Long.class;
    }

}
