package org.gjs.java.common.jpa;

import java.util.Map;
import java.util.Map.Entry;

import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.type.DataObject;
import org.slf4j.LoggerFactory;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.CrudRepository;
import org.springframework.util.CollectionUtils;

import lombok.Getter;

/**
 * Class JpaRepositoryWrapper.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase que permite recubrir un repositorio JPA.
 *
 * @param <T>  la entidad JPA
 * @param <ID> la clase de la clave primaria de la entidad
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class JpaRepositoryWrapper<T, ID> extends BaseRepositoryWrapper<T, ID> {

	/** The repository. */
	protected JpaRepository<T, ID> repository;

	/** The jpa dependencies. */
	@Getter
	protected Map<String, JpaRepositoryWrapper<?, ?>> jpaDependencies;

	/**
	 * Instantiates a new jpa repository wrapper.
	 *
	 * @param entity     the entity
	 * @param pk         the pk
	 * @param repository the repository
	 */
	public JpaRepositoryWrapper(Class<T> entity, Class<ID> pk, JpaRepository<T, ID> repository) {
		super(entity, pk, LoggerFactory.getLogger(CrudRepositoryWrapper.class));
		this.repository = repository;
	}

	/**
	 * Instantiates a new jpa repository wrapper.
	 *
	 * @param entity     the entity
	 * @param pk         the pk
	 * @param repository the repository
	 * @param dataFile   the data file
	 */
	public JpaRepositoryWrapper(Class<T> entity, Class<ID> pk, JpaRepository<T, ID> repository, String dataFile) {
		super(entity, pk, dataFile, LoggerFactory.getLogger(CrudRepositoryWrapper.class));
		this.repository = repository;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.jpa.BaseRepositoryWrapper#getRepository()
	 */

	@Override
	public CrudRepository<T, ID> getRepository() {
		return repository;
	}

	/**
	 * Sets the jpa dependencies.
	 *
	 * @param dependencies the dependencies
	 */
	public void setJpaDependencies(Map<String, JpaRepositoryWrapper<?, ?>> dependencies) {
		this.jpaDependencies = dependencies;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.jpa.BaseRepositoryWrapper#postLoadCsvTasks()
	 */

	@Override
	protected void postLoadCsvTasks() {
		repository.flush();
	}

	/**
	 * Load dependencies.
	 */
	@Override
	protected void loadDependencies() {
		if (!CollectionUtils.isEmpty(jpaDependencies)) {
			logger.debug("Loading dependencies (Total={})", jpaDependencies.size());
			for (final Entry<String, JpaRepositoryWrapper<?, ?>> entry : jpaDependencies.entrySet()) {
				final String field = entry.getKey();
				final JpaRepositoryWrapper<?, ?> dependency = entry.getValue();
				logger.debug("Loading dependencies for field {} of type {}", field, dependency.getClass());
				if (dependency.getRepository().count() == 0) {
					dependency.loadCsv();
				}
			}
		}
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.gjs.java.test.jpa.BaseRepositoryWrapper#isFieldToTranslate(java.lang.
	 * String)
	 */

	@Override
	protected boolean isFieldToTranslate(String field) {
		boolean translate = true;
		if (!CollectionUtils.isEmpty(jpaDependencies)) {
			translate = !jpaDependencies.containsKey(field);
		}
		return translate;
	}

	/**
	 * Resolve dependecies.
	 *
	 * @param dataObj the data obj
	 * @param obj     the obj
	 */
	@Override
	protected void resolveDependecies(DataObject dataObj, T obj) {
		if (!CollectionUtils.isEmpty(jpaDependencies)) {
			logger.debug("Completing dependency objects...");
			for (final Entry<String, JpaRepositoryWrapper<?, ?>> entry : jpaDependencies.entrySet()) {
				final String field = entry.getKey();
				final JpaRepositoryWrapper<?, ?> dependency = entry.getValue();
				if (PrimitiveType.LONG.isSameClassType(dependency.getPk().getCanonicalName())) {
					@SuppressWarnings("unchecked")
					final JpaRepositoryWrapper<?, Long> simpleDependency = (JpaRepositoryWrapper<?, Long>) dependency;
					logger.debug("Find dependency for field {} of type {}", field, dependency.getEntity());
					assignDependencyFieldByLongId(dataObj, obj, field, simpleDependency);
				} else if (ManagedType.STRING.isSameType(dependency.getPk().getCanonicalName())) {
					@SuppressWarnings("unchecked")
					final JpaRepositoryWrapper<?, String> simpleDependency = (JpaRepositoryWrapper<?, String>) dependency;
					logger.debug("Find dependency for field {} of type {}", field, dependency.getEntity());
					assignDependencyFieldByStringId(dataObj, obj, field, simpleDependency);
				} else {
					logger.warn("Functionality not implemented for repositories with PK={}",
							dependency.getPk().getCanonicalName());
				}
			}
		}
	}

}
