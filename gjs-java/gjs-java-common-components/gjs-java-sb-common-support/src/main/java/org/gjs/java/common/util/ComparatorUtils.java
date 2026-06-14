package org.gjs.java.common.util;

import java.lang.reflect.InvocationTargetException;
import java.util.Comparator;
import java.util.Iterator;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.BeansException;
import org.springframework.data.domain.Sort;

/**
 * The Class ComparatorUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Rutinas para crear Comparator<> genéricos a partir de un Sort u Order dado.
 *
 * --------------------------------------------------------------------------------------------------------------------
 *
 *
 *
 *
 *
 *
 *
 * Gj Software
 * 2025
 * 
 *
 * 
 * 
 * --------------------------------------------------------------------------------------------------------------------
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class ComparatorUtils {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(ComparatorUtils.class);

	/*
	 * PropertyDescriptor). This solution doesn't handle sorting by deeper fields
	 * (eg. Person.Address.Street) Null values aren't correctly handled. Use
	 * Comparator.nullsFirst or nullsLast.
	 */

	/**
	 * Clase no instanciable.
	 */
	private ComparatorUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Convert.
	 *
	 * @param <T>  the generic type
	 * @param sort the sort
	 * @param type the type
	 * @return the comparator
	 */
	public static <T> Comparator<T> convert(Sort sort, Class<T> type) {
		final Iterator<Sort.Order> orderIterator = sort.iterator();
		final Sort.Order order = orderIterator.next();

		Comparator<T> comparator = convert(order, type);
		while (orderIterator.hasNext()) {
			comparator = comparator.thenComparing(convert(orderIterator.next(), type));
		}
		return comparator;
	}

	/**
	 * Convert.
	 *
	 * @param <T>   the generic type
	 * @param order the order
	 * @param type  the type
	 * @return the comparator
	 */
	private static <T> Comparator<T> convert(Sort.Order order, Class<T> type) {
		@SuppressWarnings({ "unchecked", "rawtypes" })
		final Comparator<T> comparator = Comparator.comparing((T entity) -> {
			try {
				return (Comparable) org.springframework.beans.BeanUtils.getPropertyDescriptor(type, order.getProperty())
						.getReadMethod().invoke(entity);
			} catch (BeansException | IllegalAccessException | IllegalArgumentException | InvocationTargetException e) {
				logger.warn(ExceptionUtils.getStackTrace(e));
			}
			return null;
		});
		if (order.isDescending()) {
			return comparator.reversed();
		}
		return comparator;
	}
}
