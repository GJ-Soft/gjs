package org.gjs.java.test.mock;

import java.io.IOException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.util.CollectionUtils;
import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.IdUtils;
import org.gjs.java.common.util.ReflectionUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.support.MutableSortDefinition;
import org.springframework.beans.support.PagedListHolder;
import org.springframework.beans.support.SortDefinition;
import org.springframework.core.io.Resource;

/**
 * The Class MockEntityService.
 *
 * Clase de datos de la librería Gjs
 *
 * Implementa un servicio de datos sencillo en memoria para cualquier clase de objetos.
 *
 * @param <T>
 *            la clase de la entidad
 * @param <PK>
 *            la clave primaria de la entidad
 * @param <F>
 *            la clase de filtrado de datos
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockEntityService<T, PK, F> extends MockEntityDataManager<T, PK> {

    /** The Constant logger. */
    protected static final Logger logger = LoggerFactory.getLogger(MockEntityService.class);

    /**
     * Instantiates a new mock entity service.
     */
    public MockEntityService() {
    }

    /**
     * Instantiates a new mock entity service.
     *
     * @param path
     *            the path
     */
    public MockEntityService(String path) {
        super(path);
    }

    /**
     * Instantiates a new mock entity service.
     *
     * @param resource
     *            the resource
     * @throws IOException
     *             Signals that an I/O exception has occurred.
     */
    public MockEntityService(Resource resource) throws IOException {
        super(resource.getFile().getAbsolutePath());
    }

    /**
     * Checks if is logical delete.
     *
     * @return true, if is logical delete
     */
    protected boolean isLogicalDelete() {
        return false;
    }

    /**
     * Fill fields for insert.
     *
     * @param dto
     *            the dto
     */
    protected void fillFieldsForInsert(T dto) {
        // Por defecto no hace nada
    }

    /**
     * Fill fields for update.
     *
     * @param dto
     *            the dto
     */
    protected void fillFieldsForUpdate(T dto) {
        // Por defecto no hace nada
    }

    /**
     * Update for logical delete.
     *
     * @param dto
     *            the dto
     */
    protected void updateForLogicalDelete(T dto) {
        // Por defecto no hace nada
    }

    /**
     * Find.
     *
     * @param id
     *            the id
     * @return the t
     */
    public T find(PK id) {
        return super.get(id);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.mock.MockEntityDataManager#exists(java.lang.Object) */

    @Override
    public boolean exists(PK id) {
        return super.exists(id);
    }

    /**
     * Save.
     *
     * @param dto
     *            the dto
     * @return the t
     */
    @SuppressWarnings("unchecked")
    public T save(T dto) {
        logger.warn("PKCLASS={}", pkClazz.getCanonicalName());
        final PK id = getId(dto);
        logger.debug("Intento de insercion de objeto con ID={}", id);
        if (PrimitiveType.LONG.isSameClassType(pkClazz.getCanonicalName())) {
            final Long longId = (Long) id;
            if (!IdUtils.isValid(longId)) {
                Long idVal = Long.valueOf(1);
                while (exists((PK) idVal)) {
                    idVal = idVal + 1;
                }
                logger.debug("Asignado ID={} al objeto", idVal);
                setId(dto, (PK) idVal);
            }
        }
        fillFieldsForInsert(dto);
        logger.debug("Intertando objeto con ID={}", getId(dto));
        put(dto);
        logger.debug("Insertado objeto({}). Totales={}", getClazz().getCanonicalName(), size());
        return dto;
    }

    /**
     * Update.
     *
     * @param dto
     *            the dto
     * @return the t
     */
    public T update(T dto) {
        final PK id = getId(dto);
        if (exists(id)) {
            fillFieldsForUpdate(dto);
            put(dto);
        }
        return dto;
    }

    /**
     * Delete.
     *
     * @param id
     *            the id
     */
    public void delete(PK id) {
        remove(id);
    }

    /**
     * Delete.
     *
     * @param id
     *            the id
     * @param reason
     *            the reason
     * @return the t
     */
    public T delete(PK id, String reason) {
        logger.debug("deleting id={}", id);
        T dto = find(id);
        if (Objects.nonNull(dto)) {
            if (isLogicalDelete()) {
                logger.debug("logical deleting dto={}", dto);
                updateForLogicalDelete(dto);
                dto = update(dto);
            } else {
                logger.debug("physical deleting dto={}", dto);
                remove(id);
            }
        }
        return dto;
    }

    /**
     * Count.
     *
     * @return the long
     */
    public long count() {
        return size();
    }

    /**
     * Count.
     *
     * @param filter
     *            the filter
     * @return the long
     */
    public long count(F filter) {
        final List<T> listFiltered = filter(filter);
        return listFiltered.size();
    }

    /**
     * Find all.
     *
     * @return the list
     */
    public List<T> findAll() {
        return getAll();
    }

    /**
     * Find activas.
     *
     * @return the list
     */
    public List<T> findActivas() {
        return findAll();
    }

    /**
     * Filter.
     *
     * @param pageNumber
     *            the page number
     * @param pageSize
     *            the page size
     * @param order
     *            the order
     * @param asc
     *            the asc
     * @param filter
     *            the filter
     * @return the list
     */
    public List<T> filter(Integer pageNumber, Integer pageSize, String order, Integer asc, F filter) {
        final List<T> listFiltered = filter(filter);
        final SortDefinition sort = new MutableSortDefinition(order, false, (asc == 1));
        final PagedListHolder<T> page = new PagedListHolder<>(listFiltered, sort);
        page.setPageSize(pageSize);
        page.setPage(pageNumber);
        return page.getPageList();
    }

    /**
     * Filter.
     *
     * @param order
     *            the order
     * @param asc
     *            the asc
     * @param filter
     *            the filter
     * @return the list
     */
    public List<T> filter(String order, Integer asc, F filter) {
        final List<T> listFiltered = filter(filter);
        final SortDefinition sort = new MutableSortDefinition(order, false, (asc == 1));
        final PagedListHolder<T> page = new PagedListHolder<>(listFiltered, sort);
        page.setPageSize(listFiltered.size());
        page.setPage(0);
        return page.getPageList();
    }

    /**
     * Filter.
     *
     * @param filter
     *            the filter
     * @return the list
     */
    protected List<T> filter(F filter) {
        final List<T> listData = getAll();
        logger.debug("Filtering {} values whith filter {}", listData.size(), filter);
        final List<T> listIncluded = new ArrayList<>();
        for (final T data : listData) {
            if (Objects.nonNull(filter)) {
                final List<Method> gettersFilter = ReflectionUtils.getAllGetters(filter.getClass());
                final List<Method> getters = ReflectionUtils.getAllGetters(getClazz());
                logger.debug("Try to filter Dto={}", data);
                if (includeObject(data, filter, getters, gettersFilter)) {
                    logger.debug("Included!");
                    listIncluded.add(data);
                }
            } else {
                listIncluded.add(data);
            }
        }
        logger.debug("Filtered {} values", listIncluded.size());
        return listIncluded;

    }

    /**
     * Include object.
     *
     * @param data
     *            the data
     * @param filter
     *            the filter
     * @param getters
     *            the getters
     * @param gettersFilter
     *            the getters filter
     * @return true, if successful
     */
    protected boolean includeObject(T data, F filter, List<Method> getters, List<Method> gettersFilter) {
        boolean include = true;
        for (final Method getterFilter : gettersFilter) {
            if (!ConditionUtils.oneIsTrue("getId".equals(getterFilter.getName()),
                    CollectionUtils.isCollection(getterFilter.getReturnType()))) {

                final Method getterValue = findGetter(getterFilter, getters);
                if (Objects.nonNull(getterValue)) {
                    final Object filterValue = ReflectionUtils.getFieldValue(filter, getterFilter);
                    if (Objects.nonNull(filterValue)) {
                        final Object objValue = ReflectionUtils.getFieldValue(data, getterValue);
                        if (!Objects.equals(objValue, filterValue)) {
                            logger.debug("Values are different {}/{}", filterValue, objValue);
                            include = false;
                            break;
                        }
                    }
                }
            }
        }
        return include;
    }

    /**
     * Find getter.
     *
     * @param getterFilter
     *            the getter filter
     * @param getters
     *            the getters
     * @return the method
     */
    private Method findGetter(Method getterFilter, List<Method> getters) {
        Method getterValue = null;
        for (final Method getter : getters) {
            if (getterFilter.getName().equals(getter.getName())) {
                getterValue = getter;
                break;
            }
        }
        return getterValue;
    }
}
