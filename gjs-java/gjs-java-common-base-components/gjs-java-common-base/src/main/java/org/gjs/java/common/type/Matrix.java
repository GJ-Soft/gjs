package org.gjs.java.common.type;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class Matrix.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase parametrizada para almacenar una matriz de datos de cualquier tipo.
 *
 * @param <T>
 *            la clase de objetos
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class Matrix<T> {

    /** The values. */
    private final List<ArrayList<T>> values;

    /**
     * Instantiates a new matrix.
     */
    public Matrix() {
        values = new ArrayList<>();
    }

    /**
     * Rows.
     *
     * @return the int
     */
    public int rows() {
        return (values.size());
    }

    /**
     * Columns.
     *
     * @param row
     *            the row
     * @return the int
     */
    public int columns(int row) {
        int res = 0;
        if (ConditionUtils.allAreTrue((row >= 0), (row < values.size()))) {
            res = values.get(row).size();
        }
        return (res);
    }

    /**
     * Gets the row.
     *
     * @param row
     *            the row
     * @return the row
     */
    public List<T> getRow(int row) {
        List<T> rowValues = null;
        if (ConditionUtils.allAreTrue((row >= 0), (row < this.values.size()))) {
            rowValues = this.values.get(row);
        }
        return (rowValues);
    }

    /**
     * Gets the value.
     *
     * @param row
     *            the row
     * @param column
     *            the column
     * @return the value
     */
    public T getValue(int row, int column) {
        T value = null;
        if (ConditionUtils.allAreTrue((row >= 0), (row < values.size()))) {
            final List<T> rowValues = this.values.get(row);
            if ((column >= 0) && (column < rowValues.size())) {
                value = rowValues.get(column);
            }
        }
        return (value);

    }

    /**
     * Adds the row.
     *
     * @param values
     *            the values
     */
    public void addRow(List<T> values) {
        if (Objects.nonNull(values)) {
            this.values.add(new ArrayList<>(values));
        }
    }

    /**
     * Sets the row.
     *
     * @param row
     *            the row
     * @param values
     *            the values
     */
    @SuppressWarnings("unchecked")
    public void setRow(int row, T... values) {
        final ArrayList<T> rowData = new ArrayList<>();
        if (Objects.nonNull(values)) {
            rowData.addAll(Arrays.asList(values));
        }
        setRow(row, rowData);
    }

    /**
     * Sets the row.
     *
     * @param row
     *            the row
     * @param values
     *            the values
     */
    public void setRow(int row, List<T> values) {
        if (ConditionUtils.allAreTrue((row >= 0), Objects.nonNull(values))) {
            while (this.values.size() <= row) {
                this.values.add(new ArrayList<>());
            }
            this.values.set(row, new ArrayList<>(values));
        }
    }

    /**
     * Adds the row.
     *
     * @param values
     *            the values
     */
    @SuppressWarnings("unchecked")
    public void addRow(T... values) {
        final ArrayList<T> row = new ArrayList<>();
        if (Objects.nonNull(values)) {
            row.addAll(Arrays.asList(values));
        }
        this.values.add(row);
    }

    /**
     * Sets the value.
     *
     * @param row
     *            the row
     * @param column
     *            the column
     * @param value
     *            the value
     */
    public void setValue(int row, int column, T value) {
        if (ConditionUtils.allAreTrue((row >= 0), (column >= 0))) {
            while (this.values.size() <= row) {
                this.values.add(new ArrayList<>());
            }
            final List<T> rowValues = this.values.get(row);
            while (rowValues.size() <= column) {
                rowValues.add(null);
            }
            rowValues.set(column, value);
        }
    }

    /**
     * Removes the row.
     *
     * @param row
     *            the row
     */
    public void removeRow(int row) {
        if (ConditionUtils.allAreTrue((row >= 0), (row < this.values.size()))) {
            this.values.remove(row);
        }
    }

    /**
     * Clear.
     */
    public void clear() {
        values.clear();
    }

}
