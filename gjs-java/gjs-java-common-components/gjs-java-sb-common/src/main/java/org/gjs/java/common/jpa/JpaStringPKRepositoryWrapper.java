package org.gjs.java.common.jpa;

import org.springframework.data.jpa.repository.JpaRepository;

import lombok.Getter;

/**
 * The Class JpaStringPKRepositoryWrapper.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase que permite recubrir un repositorio JPA de una entidad con clave primaria de tipo Long.
 *
 * @param <T>
 *            la entidad JPA
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
public class JpaStringPKRepositoryWrapper<T> extends JpaRepositoryWrapper<T, String> {

    /**
     * Instantiates a new jpa simple PK repository wrapper.
     *
     * @param entity
     *            the entity
     * @param repository
     *            the repository
     */
    public JpaStringPKRepositoryWrapper(Class<T> entity, JpaRepository<T, String> repository) {
        super(entity, String.class, repository);
    }

    /**
     * Instantiates a new jpa simple PK repository wrapper.
     *
     * @param entity
     *            the entity
     * @param repository
     *            the repository
     * @param dataFile
     *            the data file
     */
    public JpaStringPKRepositoryWrapper(Class<T> entity, JpaRepository<T, String> repository, String dataFile) {
        super(entity, String.class, repository, dataFile);
    }

}
