package org.gjs.java.common.files;

import java.io.File;
import java.nio.file.FileSystems;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Objects;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.exception.ExceptionUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class FilePlain.
 *
 * Clase de datos de la librería Gjs
 *
 * Facilita el manejo un fichero de texto plano.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class FilePlain {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(FilePlain.class);

	/** The file path. */
	private String filePath;

	/**
	 * Instantiates a new file plain.
	 */
	public FilePlain() {
		newFile();
	}

	/**
	 * Instantiates a new file plain.
	 *
	 * @param path the path
	 */
	public FilePlain(String path) {
		load(path);
	}

	/**
	 * Instantiates a new file plain.
	 *
	 * @param directory the directory
	 * @param file      the file
	 */
	public FilePlain(String directory, String file) {
		load(directory, file);
	}

	/**
	 * Instantiates a new file plain.
	 *
	 * @param file the file
	 */
	public FilePlain(File file) {
		load(file);
	}

	/**
	 * Instantiates a new file plain.
	 *
	 * @param path the path
	 */
	public FilePlain(Path path) {
		File file = null;
		if (Objects.nonNull(path)) {
			file = path.toFile();
		}
		load(file);
	}

	/**
	 * Gets the path.
	 *
	 * @return the path
	 */
	public String getPath() {
		return filePath;
	}

	/**
	 * Sets the path.
	 *
	 * @param path the new path
	 */
	public void setPath(String path) {
		if (StringUtils.isAllBlank(path)) {
			throw new RuntimeException(String.format("Not a valid path: %s", path));
		}
		try {
			final Path pathObj = Path.of(path).toAbsolutePath();
			this.filePath = pathObj.toFile().getAbsolutePath();
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			throw new RuntimeException(String.format("Not a valid path: %s", path));
		}
	}

	/**
	 * Gets the directory.
	 *
	 * @return the directory
	 */
	public String getDirectory() {
		String res = null;
		if (!StringUtils.isAllBlank(filePath)) {
			Path path = Path.of(filePath);
			while (!path.toFile().isDirectory()) {
				path = path.getParent();
			}
			res = path.toFile().getPath();
		}
		return res;
	}

	/**
	 * Gets the name.
	 *
	 * @return the name
	 */
	public String getName() {
		String res = null;
		if (!StringUtils.isAllBlank(filePath)) {
			final Path path = Path.of(filePath);
			res = path.toFile().getName();
		}
		return res;
	}

	/**
	 * Inits the.
	 */
	protected abstract void init();

	/**
	 * Load content.
	 *
	 * @param path the path
	 * @return true, if successful
	 */
	protected abstract boolean loadContent(String path);

	/**
	 * Save content.
	 *
	 * @param path the path
	 * @return true, if successful
	 */
	protected abstract boolean saveContent(String path);

	/**
	 * Checks if is valid content.
	 *
	 * @return true, if is valid content
	 */
	protected abstract boolean isValidContent();

	/**
	 * Checks if is valid.
	 *
	 * @return true, if is valid
	 */
	public boolean isValid() {
		boolean res = false;
		try {
			Paths.get(filePath);
			res = isValidContent();
		} catch (InvalidPathException | NullPointerException e) {
			logger.warn(e.getMessage());
		}
		return res;
	}

	/**
	 * Exists.
	 *
	 * @return true, if successful
	 */
	public boolean exists() {
		boolean res = false;
		if (!StringUtils.isAllBlank(filePath)) {
			final Path pathObj = Path.of(filePath).toAbsolutePath();
			res = pathObj.toFile().isFile();
		}
		return res;
	}

	/**
	 * Load.
	 *
	 * @param directory the directory
	 * @param file      the file
	 * @return true, if successful
	 */
	public boolean load(String directory, String file) {
		return load(String.format("%s%s%s", directory, FileSystems.getDefault().getSeparator(), file));
	}

	/**
	 * Load.
	 *
	 * @param file the file
	 * @return true, if successful
	 */
	public boolean load(File file) {
		String absolutePath = null;
		if (Objects.nonNull(file)) {
			absolutePath = file.getAbsolutePath();
		}
		return load(absolutePath);
	}

	/**
	 * Load.
	 *
	 * @param path the path
	 * @return true, if successful
	 */
	public boolean load(String path) {
		setPath(path);
		return (load());
	}

	/**
	 * Load.
	 *
	 * @return true, if successful
	 */
	public boolean load() {
		boolean res = false;
		final Path path = Path.of(filePath);
		if (path.toFile().isFile()) {
			res = loadContent(filePath);
		}
		return (res);
	}

	/**
	 * New file.
	 */
	public void newFile() {
		init();
	}

	/**
	 * Save.
	 *
	 * @return true, if successful
	 */
	public boolean save() {
		boolean res = false;
		if (!StringUtils.isAllBlank(filePath)) {
			res = saveContent(filePath);
		}
		return (res);
	}

	/**
	 * Save.
	 *
	 * @param path the path
	 * @return true, if successful
	 */
	public boolean save(String path) {
		setPath(path);
		return (save());
	}

	/**
	 * Clear.
	 */
	public void clear() {
		init();
	}

}
