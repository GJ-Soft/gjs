package org.gjs.java.common.data;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.Set;
import java.util.TreeSet;

import org.gjs.java.common.type.Matrix;
import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.StreamUtils;

/**
 * The Class SeparatedValuesDataStreamer.
 *
 * Clase de datos de la librería Gjs
 *
 * Facilita el manejo de la entrada y salida por stremers de un texto plano con
 * formato de valores separados por un separador concreto, es decir que el
 * fichero es visto como una matriz de datos, donde cada columna representa un
 * atributo y cada fila un registo.
 *
 * PENDIENTES: opciones tratar cadenas , empty as null, null as null
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class SeparatedValuesDataStreamer extends DataStreamer {

	/** The Constant DEFAULT_SEPARATOR. */
	private static final char DEFAULT_SEPARATOR = '\t';

	/** The separator. */
	private char separator;

	/** The data. */
	private Matrix<String> data;

	/** The strings columns. */
	private final Set<Integer> stringColumns = new TreeSet<>();

	/** The has header. */
	private boolean hasHeader;

	/**
	 * Instantiates a new file separated values.
	 */
	public SeparatedValuesDataStreamer() {
		this(DEFAULT_SEPARATOR);
	}

	/**
	 * Instantiates a new file separated values.
	 *
	 * @param separator the separator
	 */
	public SeparatedValuesDataStreamer(char separator) {
		this.separator = separator;
		init();
	}

	/**
	 * Instantiates a new file separated values.
	 *
	 * @param reader the reader
	 */
	public SeparatedValuesDataStreamer(InputStreamReader reader) {
		this(DEFAULT_SEPARATOR, reader);
	}

	/**
	 * Instantiates a new file separated values.
	 *
	 * @param separator the separator
	 * @param reader    the reader
	 */
	public SeparatedValuesDataStreamer(char separator, InputStreamReader reader) {
		this(separator);
		load(reader);
	}

	/**
	 * Gets the separator.
	 *
	 * @return the separator
	 */
	public char getSeparator() {
		return separator;
	}

	/**
	 * Sets the separator.
	 *
	 * @param separator the new separator
	 */
	public void setSeparator(char separator) {
		this.separator = separator;
	}

	/**
	 * Checks for header.
	 *
	 * @return true, if successful
	 */
	public boolean hasHeader() {
		return hasHeader;
	}

	/**
	 * Sets the checks for header.
	 *
	 * @param hasHeader the new checks for header
	 */
	public void setHasHeader(boolean hasHeader) {
		this.hasHeader = hasHeader;
	}

	/**
	 * Sets the string columns.
	 *
	 * @param column the new string columns
	 */
	public void setStringColumns(Integer... column) {
		stringColumns.clear();
		stringColumns.addAll(Arrays.asList(column));
	}

	/**
	 * Gets the datos.
	 *
	 * @return the datos
	 */
	public Matrix<String> getData() {
		return data;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.data.DataReader#init()
	 */

	@Override
	public void init() {
		stringColumns.clear();
		data = new Matrix<>();
		if (separator == 0) {
			separator = DEFAULT_SEPARATOR;
		}
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.files.FilePlain#loadContent(java.lang.String)
	 */

	@Override
	protected boolean loadContent(InputStreamReader reader) {
		final boolean res = true;
		try {
			StreamUtils.readData(reader, data, separator);
		} catch (final IOException ex) {
			throw new RuntimeException(ex);
		}
		return (res);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.data.DataStreamer#saveContent(java.io.OutputStreamWriter)
	 */

	@Override
	protected boolean saveContent(OutputStreamWriter writer) {
		boolean res = false;
		if (Objects.nonNull(data)) {
			try (final BufferedWriter br = new BufferedWriter(writer)) {
				for (int i = 0; i < data.rows(); i = i + 1) {
					final List<String> row = data.getRow(i);
					final boolean isHeader = ConditionUtils.allAreTrue(hasHeader, i == 0);
					br.write(makeLine(row, isHeader));
					br.newLine();
				}
				br.flush();
				res = true;
			} catch (final IOException ex) {
				throw new RuntimeException(ex);
			}
		}
		return (res);
	}

	/**
	 * Make line.
	 *
	 * @param row      the row
	 * @param isHeader the is header
	 * @return the string
	 */
	private String makeLine(List<String> row, boolean isHeader) {
		final StringBuilder line = new StringBuilder();
		boolean inicio = true;
		for (int j = 0; j < row.size(); j = j + 1) {
			String columna = row.get(j);
			if (!inicio) {
				line.append(getSeparator());
			}
			boolean isString = false;
			if (isHeader) {
				isString = true;
			} else if (columna == null) {
				columna = "null";
			} else {
				isString = stringColumns.contains(j);
			}

			if (isString) {
				line.append('\"').append(columna).append('\"');
			} else {
				line.append(columna);
			}

			inicio = false;
		}
		return line.toString();
	}
}
