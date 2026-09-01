package org.gjs.java.common.data;

import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import org.apache.commons.collections4.CollectionUtils;
import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class SheetDataStreamer.
 *
 * Clase de datos de la librería Gjs
 *
 * Facilita el manejo de la entrada y salida por stremers de un texto plano como
 * una hoja de cálculo, incorporando una primera fila de nombres de columnas al
 * formato de valores separados por un separador concreto.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class SheetDataStreamer extends SeparatedValuesDataStreamer {

	/** The column names. */
	private List<String> columnNames;

	/**
	 * Instantiates a new file sheet.
	 */
	public SheetDataStreamer() {
		super.setHasHeader(true);
	}

	/**
	 * Instantiates a new file sheet.
	 *
	 * @param separator the separator
	 */
	public SheetDataStreamer(char separator) {
		super(separator);
		super.setHasHeader(true);
	}

	/**
	 * Instantiates a new sheet data reader.
	 *
	 * @param reader the reader
	 */
	public SheetDataStreamer(InputStreamReader reader) {
		super(reader);
		super.setHasHeader(true);
	}

	/**
	 * Instantiates a new sheet data reader.
	 *
	 * @param separator the separator
	 * @param reader    the reader
	 */
	public SheetDataStreamer(char separator, InputStreamReader reader) {
		super(separator, reader);
		super.setHasHeader(true);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.files.SeparatedValuesDataReader#init()
	 */

	@Override
	public void init() {
		super.init();
		columnNames = new ArrayList<>();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see
	 * org.gjs.java.files.SeparatedValuesDataReader#loadContent(java.lang.String)
	 */

	@Override
	protected boolean loadContent(InputStreamReader reader) {
		boolean res = super.loadContent(reader);
		if (super.getData().rows() > 0) {
			columnNames = super.getData().getRow(0);
			normalizeHeader();
		} else {
			res = false;
		}
		return (res);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.files.SeparatedValuesDataReader#isValid()
	 */

	/**
	 * Checks if is valid.
	 *
	 * @return true, if is valid
	 */
	public boolean isValid() {
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
		return Integer.max(super.getData().rows() - 1, 0);
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
		return super.getData().getRow(row + 1);
	}

	/**
	 * Gets the value.
	 *
	 * @param row    the row
	 * @param column the column
	 * @return the value
	 */
	public String getValue(int row, int column) {
		return super.getData().getValue(row + 1, column);
	}

	/**
	 * Sets the row.
	 *
	 * @param row    the row
	 * @param values the values
	 */
	public void setRow(int row, List<String> values) {
		if (!CollectionUtils.isEmpty(values)) {
			super.getData().setRow(row + 1, new ArrayList<>(values));
		}
	}

	/**
	 * Sets the row.
	 *
	 * @param row    the row
	 * @param values the values
	 */
	public void setRow(int row, String... values) {
		super.getData().setRow(row + 1, values);
	}

	/**
	 * Adds the row.
	 *
	 * @param values the values
	 */
	public void addRow(List<String> values) {
		if (CollectionUtils.isEmpty(values)) {
			super.getData().addRow();
		} else {
			super.getData().addRow(new ArrayList<>(values));
		}
	}

	/**
	 * Adds the row.
	 *
	 * @param values the values
	 */
	public void addRow(String... values) {
		super.getData().addRow(values);
	}

	/**
	 * Sets the value.
	 *
	 * @param row    the row
	 * @param column the column
	 * @param value  the value
	 */
	public void setValue(int row, int column, String value) {
		super.getData().setValue(row + 1, column, value);
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
	 * Sets the column name.
	 *
	 * @param column the column
	 * @param name   the name
	 */
	public void setColumnName(int column, String name) {
		if (ConditionUtils.allAreTrue(validColumn(column), !StringUtils.isAllBlank(name), !StringUtils.isBlank(name))) {
			columnNames.set(column, name.trim());
			super.getData().getRow(0).set(column, name);
		}
	}

	/**
	 * Adds the column name.
	 *
	 * @param name the name
	 */
	public void addColumnName(String name) {
		if (ConditionUtils.allAreTrue(rows() == 0, !StringUtils.isAllBlank(name), !StringUtils.isBlank(name))) {
			columnNames.add(name.trim());
			if (super.getData().rows() == 0) {
				super.getData().addRow(name.trim());
			} else {
				super.getData().getRow(0).add(name.trim());
			}
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
