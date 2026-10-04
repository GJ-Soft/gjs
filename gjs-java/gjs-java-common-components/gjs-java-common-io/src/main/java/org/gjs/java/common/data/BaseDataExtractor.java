package org.gjs.java.common.data;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.util.ConditionUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class BaseDataExtractor.
 *
 * Clase abstracta de datos de la librería Gjs
 *
 * Clase abstracta usada como base para implementar un extractor de datos
 * singular.
 *
 * @param <T> la clase de datos del extractor
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public abstract class BaseDataExtractor<T> implements DataExtractor<T> {

	/** The Constant logger. */
	protected Logger logger;

	/** The column names. */
	private final List<String> columnNames;

	/**
	 * Instantiates a new base data extractor.
	 */
	protected BaseDataExtractor() {
		logger = LoggerFactory.getLogger(getClass());
		columnNames = new ArrayList<>();
	}

	/**
	 * Instantiates a new base data extractor.
	 *
	 * @param columnName the column name
	 */
	protected BaseDataExtractor(String... columnName) {
		logger = LoggerFactory.getLogger(getClass());
		columnNames = Arrays.asList(columnName);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.data.DataExtractor#columns()
	 */

	@Override
	public int columns() {
		return columnNames.size();
	}

	/**
	 * Gets the column names.
	 *
	 * @return the column names
	 */
	public List<String> getColumnNames() {
		return columnNames;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.data.DataExtractor#getColumnName(int)
	 */

	@Override
	public String getColumnName(int column) {
		String name = null;
		if (validColumn(column)) {
			name = columnNames.get(column);
		}
		return name;
	}

	/**
	 * Sets the column name.
	 *
	 * @param column the column
	 * @param name   the name
	 */
	public void setColumnName(int column, String name) {
		if (ConditionUtils.allAreTrue(validColumn(column), !StringUtils.isAllBlank(name), !StringUtils.isBlank(name))) {
			columnNames.set(column, name.trim());
		}
	}

	/**
	 * Adds the column name.
	 *
	 * @param name the name
	 */
	public void addColumnName(String name) {
		if (ConditionUtils.allAreTrue(!StringUtils.isAllBlank(name), !StringUtils.isBlank(name))) {
			columnNames.add(name.trim());
		}
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.data.DataExtractor#getColumnValue(java.lang.Object,
	 * java.lang.String)
	 */

	@Override
	public String getColumnValue(T obj, String columnName) {
		String value = null;
		if (!StringUtils.isAllBlank(columnName)) {
			int column = -1;
			boolean found = false;
			while (ConditionUtils.allAreTrue((column < columnNames.size() - 1), !found)) {
				column = column + 1;
				found = columnNames.get(column).equals(columnName);
			}
			if (found) {
				value = getColumnValue(obj, column);
			}
		}
		return value;
	}

	/**
	 * Valid column.
	 *
	 * @param column the column
	 * @return true, if successful
	 */
	protected boolean validColumn(int column) {
		return ConditionUtils.allAreTrue((column >= 0), (column < columns()));
	}

}
