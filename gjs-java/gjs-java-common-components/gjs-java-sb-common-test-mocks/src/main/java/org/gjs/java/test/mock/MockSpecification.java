package org.gjs.java.test.mock;

import org.springframework.data.jpa.domain.Specification;

import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Predicate;
import jakarta.persistence.criteria.Root;

/**
 * The Class MockSpecification.
 *
 * Clase de datos de la librería Gjs
 *
 * Implementa un mock de una specification JPA para cualquier clase de objetos.
 *
 * @param <E>
 *            la clase de la entidad
 * @param <F>
 *            la clase de filtrado de datos
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockSpecification<E, F> implements Specification<E> {

    /** The Constant serialVersionUID. */
    private static final long serialVersionUID = -7984377625040899124L;

    /** The filter. */
    protected transient F filter;

    /**
     * Instantiates a new mock specification.
     */
    public MockSpecification() {
    }

    /**
     * Instantiates a new mock specification.
     *
     * @param filter
     *            the filter
     */
    public MockSpecification(F filter) {
        setFilter(filter);
    }

    /**
     * Gets the filter.
     *
     * @return the filter
     */
    public F getFilter() {
        return filter;
    }

    /**
     * Sets the filter.
     *
     * @param filter
     *            the new filter
     */
    public void setFilter(F filter) {
        this.filter = filter;
    }

    /* (non-Javadoc)
     *
     * @see org.springframework.data.jpa.domain.Specification#toPredicate(jakarta.persistence.criteria.Root,
     * jakarta.persistence.criteria.CriteriaQuery, jakarta.persistence.criteria.CriteriaBuilder) */

    @Override
    public Predicate toPredicate(Root<E> root, CriteriaQuery<?> query, CriteriaBuilder criteriaBuilder) {
        return null;
    }

}
