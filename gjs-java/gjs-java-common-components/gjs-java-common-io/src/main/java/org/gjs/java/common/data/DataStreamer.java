package org.gjs.java.common.data;

import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.Objects;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class DataReader.
 *
 * Clase abstracta de datos de la librería Gjs
 *
 * Clase abstracta que facilita el trabajo con una pareja
 * InputStreamWriter/OutputStreamWriter para propiciar la entrada y salida
 * general de datos
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public abstract class DataStreamer {

	/** The Constant logger. */
	protected Logger logger;

	/**
	 * Instantiates a new reader plain.
	 */
	protected DataStreamer() {
		logger = LoggerFactory.getLogger(getClass());
	}

	/**
	 * Load.
	 *
	 * @param reader the reader
	 * @return true, if successful
	 */
	public boolean load(InputStreamReader reader) {
		boolean res = false;
		if (Objects.nonNull(reader)) {
			init();
			res = loadContent(reader);
		}
		return res;
	}

	/**
	 * Save.
	 *
	 * @param writer the writer
	 * @return true, if successful
	 */
	public boolean save(OutputStreamWriter writer) {
		boolean res = false;
		if (Objects.nonNull(writer)) {
			res = saveContent(writer);
		}
		return (res);
	}

	/**
	 * Clear.
	 */
	public void clear() {
		init();
	}

	/**
	 * Inits the.
	 */
	protected abstract void init();

	/**
	 * Load.
	 *
	 * @param reader the reader
	 * @return true, if successful
	 */
	protected abstract boolean loadContent(InputStreamReader reader);

	/**
	 * Save content.
	 *
	 * @param writer the writer
	 * @return true, if successful
	 */
	protected abstract boolean saveContent(OutputStreamWriter writer);

}
