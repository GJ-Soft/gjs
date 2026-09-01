package org.gjs.java.common.data;

/**
 * The Interface DataExtractor.
 *
 * Interfaz de la librería Gjs
 *
 * Interfaz que debe implementar los extractores de datos singulares de una clase de objetos concreta para integrarse en
 * el sistema automatizado de importación y exportación de datos de Semilla.
 *
 * @param <T>
 *            la clase de datos del extractor
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public interface DataExtractor<T> {

    /**
     * Columns.
     *
     * @return the int
     */
    int columns();

    /**
     * Gets the column name.
     *
     * @param column
     *            the column
     * @return the column name
     */
    String getColumnName(int column);

    /**
     * Gets the column value.
     *
     * @param obj
     *            the obj
     * @param column
     *            the column
     * @return the column value
     */
    String getColumnValue(T obj, int column);

    /**
     * Gets the column value.
     *
     * @param obj
     *            the obj
     * @param columnName
     *            the column name
     * @return the column value
     */
    String getColumnValue(T obj, String columnName);

}
