package org.gjs.java.common.files;

import java.io.File;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import org.apache.commons.collections4.CollectionUtils;
import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class FileSheet.
 *
 * Clase de datos de la librería Gjs
 *
 * Facilita el manejo un fichero de texto plano como una hoja de cálculo,
 * incorporando una primera fila de nombres de columnas al formato de valores
 * separados por un separador concreto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class FileSheet extends FileSeparatedValues {

	/** The column names. */
	private List<String> columnNames;

	/**
	 * Instantiates a new file sheet.
	 */
	public FileSheet() {
	}

	/**
	 * Instantiates a new file sheet.
	 *
	 * @param separator the separator
	 */
	public FileSheet(char separator) {
		super(separator);
	}

	/**
	 * Instantiates a new file sheet.
	 *
	 * @param path the path
	 */
	public FileSheet(String path) {
		super(path);
	}

	/**
	 * Instantiates a new file sheet.
	 *
	 * @param directory the directory
	 * @param name      the name
	 */
	public FileSheet(String directory, String name) {
		super(directory, name);
	}

	/**
	 * Instantiates a new file sheet.
	 *
	 * @param separator the separator
	 * @param path      the path
	 */
	public FileSheet(char separator, String path) {
		super(separator, path);
	}

	/**
	 * Instantiates a new file sheet.
	 *
	 * @param separator the separator
	 * @param directory the directory
	 * @param name      the name
	 */
	public FileSheet(char separator, String directory, String name) {
		super(separator, directory, name);
	}

	/**
	 * Instantiates a new file sheet.
	 *
	 * @param file the file
	 */
	public FileSheet(File file) {
		super(file);
	}

	/**
	 * Instantiates a new file sheet.
	 *
	 * @param separator the separator
	 * @param file      the file
	 */
	public FileSheet(char separator, File file) {
		super(separator, file);
	}

	/**
	 * Instantiates a new file sheet.
	 *
	 * @param path the path
	 */
	public FileSheet(Path path) {
		super(path);
	}

	/**
	 * Instantiates a new file sheet.
	 *
	 * @param separator the separator
	 * @param path      the path
	 */
	public FileSheet(char separator, Path path) {
		super(separator, path);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.files.FileSeparatedValues#init()
	 */

	/**
	 * Inits the.
	 */
	@Override
	public void init() {
		super.init();
		columnNames = new ArrayList<>();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.files.FileSeparatedValues#loadContent(java.lang.String)
	 */

	/**
	 * Load content.
	 *
	 * @param path the path
	 * @return true, if successful
	 */
	@Override
	protected boolean loadContent(String path) {
		boolean res = super.loadContent(path);
		if (super.getDatos().rows() > 0) {
			columnNames = super.getDatos().getRow(0);
			normalizeHeader();
		} else {
			res = false;
		}
		return (res);
	}

	/**
	 * Checks if is valid content.
	 *
	 * @return true, if is valid content
	 */
	@Override
	protected boolean isValidContent() {
		boolean res = false;
		if (!CollectionUtils.isEmpty(columnNames)) {
			res = true;
			for (final String name : columnNames) {
				if (StringUtils.isAllBlank(name)) {
					res = false;
					break;
				}
			}
			if (res) {
				for (int i = 0; i < rows(); i = i + 1) {
					if (getRow(i).size() != columns()) {
						res = false;
						break;
					}
				}
			}
		}
		return res;
	}

	/**
	 * Rows.
	 *
	 * @return the int
	 */
	public int rows() {
		return Integer.max(super.getDatos().rows() - 1, 0);
	}

	/**
	 * Columns.
	 *
	 * @return the int
	 */
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

	/**
	 * Gets the row.
	 *
	 * @param row the row
	 * @return the row
	 */
	public List<String> getRow(int row) {
		return super.getDatos().getRow(row + 1);
	}

	/**
	 * Gets the value.
	 *
	 * @param row    the row
	 * @param column the column
	 * @return the value
	 */
	public String getValue(int row, int column) {
		return super.getDatos().getValue(row + 1, column);
	}

	/**
	 * Gets the column name.
	 *
	 * @param column the column
	 * @return the column name
	 */
	public String getColumnName(int column) {
		String name = null;
		if (validColumn(column)) {
			name = columnNames.get(column);
		}
		return name;
	}

	/**
	 * Sets the column names.
	 *
	 * @param names the new column names
	 */
	public void setColumnNames(List<String> names) {
		if (ConditionUtils.allAreTrue((rows() == 0), Objects.nonNull(names))) {
			super.getDatos().clear();
			super.getDatos().addRow(names);
			columnNames = super.getDatos().getRow(0);
			normalizeHeader();
		}
	}

	/**
	 * Sets the column names.
	 *
	 * @param names the new column names
	 */
	public void setColumnNames(String... names) {
		if (rows() == 0) {
			super.getDatos().clear();
			super.getDatos().addRow(names);
			columnNames = super.getDatos().getRow(0);
			normalizeHeader();
		}
	}

	/**
	 * Adds the row.
	 *
	 * @param values the values
	 */
	public void addRow(List<String> values) {
		if (Objects.nonNull(values) && (values.size() == columns())) {
			super.getDatos().addRow(values);
		}
	}

	/**
	 * Adds the row.
	 *
	 * @param values the values
	 */
	public void addRow(String... values) {
		if (Objects.nonNull(values) && (values.length == columns())) {
			super.getDatos().addRow(values);
		}
	}

	/**
	 * Sets the value.
	 *
	 * @param row    the row
	 * @param column the column
	 * @param value  the value
	 */
	public void setValue(int row, int column, String value) {
		if (validCoordinates(row, column)) {
			super.getDatos().setValue(row + 1, column, value);
		}
	}

	/**
	 * Sets the row.
	 *
	 * @param row    the row
	 * @param values the values
	 */
	public void setRow(int row, List<String> values) {
		if (Objects.nonNull(values) && (values.size() == columns())) {
			super.getDatos().setRow(row, values);
		}
	}

	/**
	 * Sets the row.
	 *
	 * @param row    the row
	 * @param values the values
	 */
	public void setRow(int row, String... values) {
		if (Objects.nonNull(values) && (values.length == columns())) {
			super.getDatos().setRow(row, values);
		}
	}

	/**
	 * Sets the column name.
	 *
	 * @param column the column
	 * @param name   the name
	 */
	public void setColumnName(int column, String name) {
		if (ConditionUtils.allAreTrue(!StringUtils.isAllBlank(name), (column < columns()))) {
			super.getDatos().setValue(0, column, name);
		}
	}

	/**
	 * Clear data.
	 */
	public void clearData() {
		while (super.getDatos().rows() > 1) {
			super.getDatos().removeRow(super.getDatos().rows() - 1);
		}
	}

	/**
	 * Valid column.
	 *
	 * @param column the column
	 * @return true, if successful
	 */
	private boolean validColumn(int column) {
		return ConditionUtils.allAreTrue((column >= 0), (column < columnNames.size()));
	}

	/**
	 * Valid coordinates.
	 *
	 * @param row    the row
	 * @param column the column
	 * @return true, if successful
	 */
	private boolean validCoordinates(int row, int column) {
		return ConditionUtils.allAreTrue((row < rows()), (column < columns()));
	}

	/**
	 * Normalize header.
	 */
	private void normalizeHeader() {
		for (int i = 0; i < columnNames.size(); i = i + 1) {
			if (Objects.nonNull(columnNames.get(i))) {
				columnNames.set(i, columnNames.get(i).trim());
			}
		}

	}
}
