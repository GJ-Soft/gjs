package org.gjs.java.common.files;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Objects;

import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.StreamUtils;

/**
 * The Class FileLines.
 *
 * Clase de datos de la librería Gjs
 *
 * Facilita el manejo un fichero de texto plano como una secuencia de líneas de
 * texto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class FileLines extends FilePlain implements Iterable<String> {

	/** The lines. */
	private List<String> lines;

	/** The pos. */
	private int pos = -1;

	/**
	 * Instantiates a new file lines.
	 */
	public FileLines() {
	}

	/**
	 * Instantiates a new file lines.
	 *
	 * @param path the path
	 */
	public FileLines(String path) {
		super(path);
	}

	/**
	 * Instantiates a new file lines.
	 *
	 * @param diretory the diretory
	 * @param name     the name
	 */
	public FileLines(String diretory, String name) {
		super(diretory, name);
	}

	/**
	 * Instantiates a new file lines.
	 *
	 * @param file the file
	 */
	public FileLines(File file) {
		super(file);
	}

	/**
	 * Instantiates a new file lines.
	 *
	 * @param path the path
	 */
	public FileLines(Path path) {
		super(path);
	}

	/**
	 * Gets the lines.
	 *
	 * @return the lines
	 */
	public List<String> getLines() {
		return lines;
	}

	/**
	 * Sets the lines.
	 *
	 * @param lineas the new lines
	 */
	public void setLines(List<String> lineas) {
		this.lines = lineas;
	}

	/**
	 * Count.
	 *
	 * @return the int
	 */
	public int count() {
		int res = 0;
		if (Objects.nonNull(lines)) {
			res = lines.size();
		}
		return res;
	}

	/**
	 * Begin.
	 */
	public void begin() {
		pos = 0;
	}

	/**
	 * End.
	 */
	public void end() {
		pos = count() - 1;
	}

	/**
	 * Next.
	 */
	public void next() {
		if (pos < count()) {
			pos = pos + 1;
		}
	}

	/**
	 * Previous.
	 */
	public void previous() {
		if (pos >= 0) {
			pos = pos - 1;
		}
	}

	/**
	 * Gets the current.
	 *
	 * @return the current
	 */
	public String getCurrent() {
		String res = null;
		if (validPos(pos)) {
			res = lines.get(pos);
		}
		return (res);
	}

	/**
	 * Sets the current.
	 *
	 * @param line the new current
	 */
	public void setCurrent(String line) {
		if (validPos(pos)) {
			lines.set(pos, line);
		}
	}

	/**
	 * Insert.
	 *
	 * @param line the line
	 */
	public void insert(String line) {
		if (pos >= 0) {
			if (pos < count()) {
				lines.add(pos, line);
				pos = pos + 1;
			} else if (pos == lines.size()) {
				lines.add(line);
				pos = pos + 1;
			}
		}
	}

	/**
	 * Removes the.
	 */
	public void remove() {
		if (validPos(pos)) {
			lines.remove(pos);
			if (pos > count()) {
				pos = count() - 1;
			}
		}
	}

	/**
	 * Eof.
	 *
	 * @return true, if successful
	 */
	public boolean eof() {
		boolean res = (count() == 0);
		if (!res) {
			res = (pos == count());
		}
		return res;
	}

	/**
	 * Bof.
	 *
	 * @return true, if successful
	 */
	public boolean bof() {
		return (pos == -1);
	}

	/**
	 * Find.
	 *
	 * @param texto the texto
	 * @return true, if successful
	 */
	public boolean find(String texto) {
		pos = -1;
		return (findNext(texto));
	}

	/**
	 * Find next.
	 *
	 * @param texto the texto
	 * @return true, if successful
	 */
	public boolean findNext(String texto) {
		boolean enc = false;
		next();
		while (ConditionUtils.allAreTrue((pos < count()), !enc, !eof())) {
			enc = getCurrent().contains(texto);
			if (!enc) {
				next();
			}
		}
		return enc;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.files.FilePlain#init()
	 */

	/**
	 * Inits the.
	 */
	@Override
	protected void init() {
		lines = new ArrayList<>();
		pos = -1;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.files.FilePlain#loadContent(java.lang.String)
	 */

	/**
	 * Load content.
	 *
	 * @param path the path
	 * @return true, if successful
	 */
	@Override
	protected boolean loadContent(String path) {
		final boolean res = true;
		lines = new ArrayList<>();
		try {
			StreamUtils.readLines(new FileReader(path), lines);
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

	/**
	 * Save content.
	 *
	 * @param path the path
	 * @return true, if successful
	 */
	@Override
	protected boolean saveContent(String path) {
		boolean res = false;
		try (final BufferedWriter br = new BufferedWriter(new FileWriter(path))) {
			for (final String line : lines) {
				br.write(line);
				br.newLine();
			}
			br.flush();
			res = true;
		} catch (final IOException ex) {
			throw new RuntimeException(ex);
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
		return Objects.nonNull(lines);
	}

	/**
	 * Valid pos.
	 *
	 * @param pos the pos
	 * @return true, if successful
	 */
	private boolean validPos(int pos) {
		return ConditionUtils.allAreTrue((pos >= 0), (pos < count()));
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Iterable#iterator()
	 */

	/**
	 * Iterator.
	 *
	 * @return the iterator
	 */
	@Override
	public Iterator<String> iterator() {
		Iterator<String> iterator = null;
		if (Objects.nonNull(lines)) {
			iterator = lines.iterator();
		}
		return iterator;
	}
}
