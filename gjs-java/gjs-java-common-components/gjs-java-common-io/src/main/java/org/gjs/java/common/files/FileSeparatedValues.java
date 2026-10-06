package org.gjs.java.common.files;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Path;
import java.util.List;
import java.util.Objects;

import org.gjs.java.common.type.Matrix;
import org.gjs.java.common.util.StreamUtils;

// opciones tratar cadenas , empty as null, null as null

/**
 * The Class FileSeparatedValues.
 *
 * Clase de datos de la librería Gjs
 *
 * Facilita el manejo un fichero de texto plano con formato de valores separados
 * por un separador concreto, es decir que el fichero es visto como una matriz
 * de datos, donde cada columna representa un atributo y cada fila un registo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class FileSeparatedValues extends FilePlain {

	/** The Constant DEFAULT_SEPARATOR. */
	private static final char DEFAULT_SEPARATOR = '\t';

	/** The separator. */
	private char separator;

	/** The data. */
	private Matrix<String> data;

	/**
	 * Instantiates a new file separated values.
	 */
	public FileSeparatedValues() {
		this(DEFAULT_SEPARATOR);
	}

	/**
	 * Instantiates a new file separated values.
	 *
	 * @param separator the separator
	 */
	public FileSeparatedValues(char separator) {
		this.separator = separator;
	}

	/**
	 * Instantiates a new file separated values.
	 *
	 * @param path the path
	 */
	public FileSeparatedValues(String path) {
		this(DEFAULT_SEPARATOR, path);
	}

	/**
	 * Instantiates a new file separated values.
	 *
	 * @param directory the directory
	 * @param name      the name
	 */
	public FileSeparatedValues(String directory, String name) {
		this(DEFAULT_SEPARATOR, directory, name);
	}

	/**
	 * Instantiates a new file separated values.
	 *
	 * @param separator the separator
	 * @param path      the path
	 */
	public FileSeparatedValues(char separator, String path) {
		this(separator);
		load(path);
	}

	/**
	 * Instantiates a new file separated values.
	 *
	 * @param separator the separator
	 * @param directory the directory
	 * @param name      the name
	 */
	public FileSeparatedValues(char separator, String directory, String name) {
		this(separator);
		load(directory, name);
	}

	/**
	 * Instantiates a new file separated values.
	 *
	 * @param file the file
	 */
	public FileSeparatedValues(File file) {
		this(DEFAULT_SEPARATOR, file);
	}

	/**
	 * Instantiates a new file separated values.
	 *
	 * @param separator the separator
	 * @param file      the file
	 */
	public FileSeparatedValues(char separator, File file) {
		this(separator);
		String absolutePath = null;
		if (Objects.nonNull(file)) {
			absolutePath = file.getAbsolutePath();
		}
		load(absolutePath);
	}

	/**
	 * Instantiates a new file lines.
	 *
	 * @param path the path
	 */
	public FileSeparatedValues(Path path) {
		this(DEFAULT_SEPARATOR, path);
	}

	/**
	 * Instantiates a new file separated values.
	 *
	 * @param separator the separator
	 * @param path      the path
	 */
	public FileSeparatedValues(char separator, Path path) {
		this(separator);
		String absolutePath = null;
		if (Objects.nonNull(path)) {
			absolutePath = path.toFile().getAbsolutePath();
		}
		load(absolutePath);
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
	 * Gets the datos.
	 *
	 * @return the datos
	 */
	public Matrix<String> getDatos() {
		return data;
	}

	/**
	 * Sets the datos.
	 *
	 * @param datos the new datos
	 */
	public void setDatos(Matrix<String> datos) {
		this.data = datos;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.files.FilePlain#init()
	 */

	@Override
	public void init() {
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
	protected boolean loadContent(String path) {
		final boolean res = true;
		init();
		try {
			StreamUtils.readData(new FileReader(path), data, separator);
		} catch (final IOException ex) {
			throw new RuntimeException(ex);
		}
		return (res);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.files.FilePlain#saveContent(java.lang.String)
	 */

	@Override
	protected boolean saveContent(String path) {
		boolean res = false;
		if (Objects.nonNull(data)) {
			try (final BufferedWriter br = new BufferedWriter(new FileWriter(path))) {
				for (int i = 0; i < data.rows(); i = i + 1) {
					final List<String> row = data.getRow(i);
					br.write(makeLine(row));
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
	 * @param row the row
	 * @return the string
	 */
	private String makeLine(List<String> row) {
		final StringBuilder line = new StringBuilder();
		boolean inicio = true;
		for (final String columna : row) {
			if (!inicio) {
				line.append(getSeparator());
			}
			line.append(Objects.requireNonNullElse(columna, "null"));
			inicio = false;
		}
		return line.toString();
	}

	@Override
	protected boolean isValidContent() {
		return Objects.nonNull(data);
	}
}
