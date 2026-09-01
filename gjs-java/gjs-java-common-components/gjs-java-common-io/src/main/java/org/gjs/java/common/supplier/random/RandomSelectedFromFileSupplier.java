package org.gjs.java.common.supplier.random;

import java.io.File;
import java.io.IOException;
import java.util.List;

import org.gjs.java.common.files.FileLines;
import org.gjs.java.common.util.ResourceUtils;

/**
 * The Class RandomSelectedFromFileSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Selector aleatorio de valores importados de un fichero.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomSelectedFromFileSupplier extends RandomSelectedStringSupplier {

	/**
	 * Instantiates a new random selected from file supplier.
	 *
	 * @param txtFile the txt file
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	public RandomSelectedFromFileSupplier(String txtFile) throws IOException {
		final File resource = ResourceUtils.getFileResource(txtFile);
		final FileLines file = new FileLines(resource);
		final List<String> options = file.getLines();
		setOptions(options);
		setNullable(false);
	}

}
