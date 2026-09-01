package org.gjs.java.test.mock;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Objects;
import java.util.Optional;
import java.util.function.Function;

import org.gjs.java.common.idgenerator.IdGenerator;
import org.gjs.java.common.util.ComparatorUtils;
import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.ReflectionUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.core.io.Resource;
import org.springframework.data.domain.Example;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageImpl;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.data.repository.query.FluentQuery.FetchableFluentQuery;

import jakarta.persistence.EntityNotFoundException;

/**
 * The Class MockRepository.
 *
 * Clase de datos de la librería Gjs
 *
 * Implementa un repositorio JPA de datos sencillo en memoria para cualquier
 * clase de objetos.
 *
 * @param <T>  la clase de las entidad
 * @param <PK> la clave primaria de la entidad
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockRepository<T, PK> extends MockEntityDataManager<T, PK>
		implements JpaRepository<T, PK>, JpaSpecificationExecutor<T> {

	/** The Constant logger. */
	protected static final Logger logger = LoggerFactory.getLogger(MockRepository.class);

	/** The filter. */
	private Object filter;

	/** The max id. */
	private PK maxId;

	/**
	 * Instantiates a new mock repository.
	 */
	public MockRepository() {
	}

	/**
	 * Instantiates a new mock repository.
	 *
	 * @param path the path
	 */
	public MockRepository(String path) {
		super(path);
	}

	/**
	 * Instantiates a new mock repository.
	 *
	 * @param resource the resource
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	public MockRepository(Resource resource) throws IOException {
		super(resource.getFile().getAbsolutePath());
	}

	/**
	 * Sets the filter.
	 *
	 * @param filter the new filter
	 */
	public void setFilter(Object filter) {
		this.filter = filter;
	}

	/**
	 * Autogenerate id.
	 *
	 * @return true, if successful
	 */
	protected boolean autogenerateId() {
		return false;
	}

	/**
	 * Gets the generator id.
	 *
	 * @return the generator id
	 */
	protected IdGenerator<PK> getGeneratorId() {
		return null;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.mock.MockEntityDataManager#put(java.lang.Object)
	 */

	@SuppressWarnings("unchecked")
	@Override
	protected void put(T entity) {
		super.put(entity);
		final PK id = super.getId(entity);
		if (Objects.nonNull(id) && (id instanceof Comparable)) {
			if (Objects.isNull(maxId)) {
				maxId = id;
			} else if (((Comparable<PK>) maxId).compareTo(id) < 0) {
				maxId = id;
			}
		}
	}

	/**
	 * Gets the max id.
	 *
	 * @return the max id
	 */
	protected PK getMaxId() {
		return maxId;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.repository.PagingAndSortingRepository#findAll(org.
	 * springframework.data.domain.Pageable)
	 */

	@Override
	public Page<T> findAll(Pageable pageable) {
		final List<T> list = findAll(pageable.getSort());
		final long count = count();
		final int start = (int) pageable.getOffset();
		final int end = Math.min((start + pageable.getPageSize()), list.size());
		return new PageImpl<>(list.subList(start, end), pageable, count);
	}

	/**
	 * Normalize data for save.
	 *
	 * @param entity the entity
	 */
	protected void normalizeDataForSave(T entity) {
		// Por defecto no hace nada
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.mock.MockEntityDataManager#processPK(java.lang.Object)
	 */

	@SuppressWarnings("unchecked")
	@Override
	protected PK processPK(PK id, T entity) {
		if (ConditionUtils.allAreTrue(autogenerateId(), !isValidId(id)) && !exists(id)) {
			id = getGeneratorId().generate();
			if (id instanceof Comparable) {
				if (Objects.isNull(maxId)) {
					maxId = id;
				} else {
					while (((Comparable<PK>) maxId).compareTo(id) >= 0) {
						id = getGeneratorId().generate();
					}
					maxId = id;
				}
			}
			setId(entity, id);
		}
		return id;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.repository.CrudRepository#save(S)
	 */

	@Override
	public <S extends T> S save(S entity) {
		if (Objects.isNull(entity)) {
			throw new IllegalArgumentException("entity");
		}
		normalizeDataForSave(entity);
		put(entity);
		return entity;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.repository.CrudRepository#findById(java.lang.Object)
	 */

	@Override
	public Optional<T> findById(PK id) {
		if (Objects.isNull(id)) {
			throw new IllegalArgumentException("id");
		}
		final T value = get(id);
		return Optional.ofNullable(value);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.repository.CrudRepository#existsById(java.lang.
	 * Object)
	 */

	@Override
	public boolean existsById(PK id) {
		if (Objects.isNull(id)) {
			throw new IllegalArgumentException("id");
		}
		return exists(id);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.repository.CrudRepository#count()
	 */

	@Override
	public long count() {
		return size();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.repository.CrudRepository#deleteById(java.lang.
	 * Object)
	 */

	@Override
	public void deleteById(PK id) {
		if (Objects.isNull(id)) {
			throw new IllegalArgumentException("id");
		}
		remove(id);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.repository.CrudRepository#delete(java.lang.Object)
	 */

	@Override
	public void delete(T entity) {
		if (Objects.isNull(entity)) {
			throw new IllegalArgumentException("entity");
		}
		final PK id = getId(entity);
		deleteById(id);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.repository.CrudRepository#deleteAll(java.lang.
	 * Iterable)
	 */

	@Override
	public void deleteAll(Iterable<? extends T> entities) {
		if (Objects.isNull(entities)) {
			throw new IllegalArgumentException("entities");
		}
		for (final T entity : entities) {
			if (Objects.isNull(entity)) {
				throw new IllegalArgumentException("entity");
			}
			delete(entity);
		}
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.repository.CrudRepository#deleteAll()
	 */

	@Override
	public void deleteAll() {
		removeAll();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.repository.CrudRepository#deleteAllById(java.lang.
	 * Iterable)
	 */

	@Override
	public void deleteAllById(Iterable<? extends PK> ids) {
		if (Objects.isNull(ids)) {
			throw new IllegalArgumentException("ids");
		}
		for (final PK id : ids) {
			if (Objects.isNull(id)) {
				throw new IllegalArgumentException("id");
			}
			deleteById(id);
		}
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.jpa.repository.JpaRepository#findAll()
	 */

	@Override
	public List<T> findAll() {
		return getAll();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.jpa.repository.JpaRepository#findAll(org.
	 * springframework.data.domain.Sort)
	 */

	@Override
	public List<T> findAll(Sort sort) {
		final List<T> res = findAll();
		sort(res, sort);
		return res;
	}

	/**
	 * Sort.
	 *
	 * @param <S>  the generic type
	 * @param list the list
	 * @param sort the sort
	 */
	@SuppressWarnings("unchecked")
	private <S extends T> void sort(List<S> list, Sort sort) {
		final Comparator<S> comparator = (Comparator<S>) ComparatorUtils.convert(sort, getClazz());
		list.sort(comparator);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaRepository#findAllById(java.lang.
	 * Iterable)
	 */

	@Override
	public List<T> findAllById(Iterable<PK> ids) {
		if (Objects.isNull(ids)) {
			throw new IllegalArgumentException("ids");
		}
		final List<T> res = new ArrayList<>();
		for (final PK id : ids) {
			if (Objects.isNull(id)) {
				throw new IllegalArgumentException("id");
			}
			final T entity = get(id);
			if (Objects.nonNull(entity)) {
				res.add(entity);
			}
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.jpa.repository.JpaRepository#saveAll(java.lang.
	 * Iterable)
	 */

	@SuppressWarnings("unchecked")
	@Override
	public <S extends T> List<S> saveAll(Iterable<S> entities) {
		if (Objects.isNull(entities)) {
			throw new IllegalArgumentException("entities");
		}
		final List<S> res = new ArrayList<>();
		for (final T entity : entities) {
			if (Objects.isNull(entity)) {
				throw new IllegalArgumentException("entity");
			}
			res.add((S) save(entity));
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.jpa.repository.JpaRepository#flush()
	 */

	@Override
	public void flush() {
		// Por defecto no hace nada
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.jpa.repository.JpaRepository#saveAndFlush(S)
	 */

	@Override
	public <S extends T> S saveAndFlush(S entity) {
		final S res = save(entity);
		flush();
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaRepository#saveAllAndFlush(java.
	 * lang.Iterable)
	 */

	@Override
	public <S extends T> List<S> saveAllAndFlush(Iterable<S> entities) {
		final List<S> res = new ArrayList<>();
		for (final S entity : entities) {
			res.add(save(entity));
		}
		flush();
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @deprecated (when, why, etc...)
	 *
	 * @see org.springframework.data.jpa.repository.JpaRepository#getOne(java.lang.
	 * Object)
	 */

	@Deprecated
	@Override
	public T getOne(PK id) {
		// Deprecated
		return getReferenceById(id);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @deprecated (when, why, etc...)
	 *
	 * @see org.springframework.data.jpa.repository.JpaRepository#getById(java.lang.
	 * Object)
	 */

	@Deprecated
	@Override
	public T getById(PK id) {
		// Deprecated
		return getReferenceById(id);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaRepository#getReferenceById(java.
	 * lang.Object)
	 */

	@Override
	public T getReferenceById(PK id) {
		final T res = get(id);
		if (Objects.isNull(res)) {
			throw new EntityNotFoundException();
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaSpecificationExecutor#findOne(org.
	 * springframework.data.jpa.domain. Specification)
	 */

	@Override
	public Optional<T> findOne(Specification<T> spec) {
		Optional<T> res = Optional.empty();
		final List<T> all = findAll(spec);
		if (all.size() == 1) {
			res = Optional.of(all.get(0));
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaSpecificationExecutor#findAll(org.
	 * springframework.data.jpa.domain. Specification)
	 */

	@Override
	public List<T> findAll(Specification<T> spec) {
		final List<T> res = new ArrayList<>();
		final List<T> all = getAll();
		if (spec instanceof MockSimpleSpecification) {
			setFilter(((MockSimpleSpecification<T>) spec).getFilter());
		} else if (spec instanceof MockSpecification) {
			setFilter(((MockSpecification<T, ?>) spec).getFilter());
		}

		logger.debug("Filtering {} registers with filter {}...", all.size(), filter);
		for (final T entity : all) {
			if (ReflectionUtils.meetsFilter(entity, filter)) {
				logger.debug("Added {}", entity);
				res.add(entity);
			} else {
				logger.debug("Rejected {}", entity);
			}
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaSpecificationExecutor#findAll(org.
	 * springframework.data.jpa.domain. Specification,
	 * org.springframework.data.domain.Pageable)
	 */

	@Override
	public Page<T> findAll(Specification<T> spec, Pageable pageable) {
		logger.debug("Pageable={}", pageable);
		final List<T> list = findAll(spec, pageable.getSort());
		final long count = count();
		logger.debug("Paginando {}/{} elements", list.size(), count);
		final int start = (int) pageable.getOffset();
		final int end = Math.min((start + pageable.getPageSize()), list.size());
		final Page<T> page = new PageImpl<>(list.subList(start, end), pageable, count);
		logger.debug("Pagina {}/{}", page.getNumber(), page.getContent().size());
		return page;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaSpecificationExecutor#findAll(org.
	 * springframework.data.jpa.domain. Specification,
	 * org.springframework.data.domain.Sort)
	 */

	@Override
	public List<T> findAll(Specification<T> spec, Sort sort) {
		final List<T> res = findAll(spec);
		sort(res, sort);
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaSpecificationExecutor#count(org.
	 * springframework.data.jpa.domain. Specification)
	 */

	@Override
	public long count(Specification<T> spec) {
		final List<T> res = findAll(spec);
		return res.size();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @deprecated (when, why, etc...)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaRepository#deleteInBatch(java.lang
	 * .Iterable)
	 */

	@Deprecated
	@Override
	public void deleteInBatch(Iterable<T> entities) {
		// No implementada
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.jpa.repository.JpaRepository#deleteAllInBatch()
	 */

	@Override
	public void deleteAllInBatch() {
		// No implementada
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaRepository#deleteAllByIdInBatch(
	 * java.lang.Iterable)
	 */

	@Override
	public void deleteAllByIdInBatch(Iterable<PK> ids) {
		// No implementada
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaRepository#deleteAllInBatch(java.
	 * lang.Iterable)
	 */

	@Override
	public void deleteAllInBatch(Iterable<T> entities) {
		// No implementada
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.repository.query.QueryByExampleExecutor#findOne(org.
	 * springframework.data.domain.Example)
	 */

	@Override
	public <S extends T> Optional<S> findOne(Example<S> example) {
		Optional<S> res = Optional.empty();
		final List<S> all = findAll(example);
		if (all.size() == 1) {
			res = Optional.of(all.get(0));
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.repository.query.QueryByExampleExecutor#findAll(org.
	 * springframework.data.domain.Example,
	 * org.springframework.data.domain.Pageable)
	 */

	@Override
	public <S extends T> Page<S> findAll(Example<S> example, Pageable pageable) {
		logger.debug("Pageable={}", pageable);
		final List<S> list = findAll(example, pageable.getSort());
		final long count = count();
		logger.debug("Paginando {}/{} elements", list.size(), count);
		final int start = (int) pageable.getOffset();
		final int end = Math.min((start + pageable.getPageSize()), list.size());
		final Page<S> page = new PageImpl<>(list.subList(start, end), pageable, count);
		logger.debug("Pagina {}/{}", page.getNumber(), page.getContent().size());
		return page;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.repository.query.QueryByExampleExecutor#count(org.
	 * springframework.data.domain.Example)
	 */

	@Override
	public <S extends T> long count(Example<S> example) {
		final List<S> res = findAll(example);
		return res.size();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.repository.query.QueryByExampleExecutor#exists(org.
	 * springframework.data.domain.Example)
	 */

	@Override
	public <S extends T> boolean exists(Example<S> example) {
		final List<S> res = findAll(example);
		return (!res.isEmpty());
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.jpa.repository.JpaRepository#findAll(org.
	 * springframework.data.domain.Example)
	 */

	@SuppressWarnings("unchecked")
	@Override
	public <S extends T> List<S> findAll(Example<S> example) {
		final List<S> res = new ArrayList<>();
		final List<T> all = getAll();
		for (final T entity : all) {
			if (ReflectionUtils.meetsFilter(entity, filter)) {
				res.add((S) entity);
			}
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.springframework.data.jpa.repository.JpaRepository#findAll(org.
	 * springframework.data.domain.Example, org.springframework.data.domain.Sort)
	 */

	@Override
	public <S extends T> List<S> findAll(Example<S> example, Sort sort) {
		final List<S> res = findAll(example);
		sort(res, sort);
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.repository.query.QueryByExampleExecutor#findBy(org.
	 * springframework.data.domain.Example, java.util.function.Function)
	 */

	@Override
	public <S extends T, R> R findBy(Example<S> example, Function<FetchableFluentQuery<S>, R> queryFunction) {
		return null;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.springframework.data.jpa.repository.JpaSpecificationExecutor#exists(org.
	 * springframework.data.jpa.domain. Specification)
	 */

	@Override
	public boolean exists(Specification<T> spec) {
		return Objects.nonNull(findOne(spec));
	}

	/**
	 * Checks if is valid id.
	 *
	 * @param id the id
	 * @return true, if is valid id
	 */
	private boolean isValidId(PK id) {
		boolean res = false;
		if (Objects.nonNull(id) && ((id instanceof Long) || (id instanceof Integer) || (id instanceof Short))) {
			res = (Long) id > 0;
		}
		return res;
	}

	@Override
	public Page<T> findAll(Specification<T> spec, Specification<T> countSpec, Pageable pageable) {
		return null;
	}

	@Override
	public long delete(Specification<T> spec) {
		return 0;
	}

	@Override
	public <S extends T, R> R findBy(Specification<T> spec,
			Function<? super SpecificationFluentQuery<S>, R> queryFunction) {
		return null;
	}

}
