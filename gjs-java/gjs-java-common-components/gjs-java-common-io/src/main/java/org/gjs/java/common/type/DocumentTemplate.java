package org.gjs.java.common.type;

import java.io.IOException;

import org.gjs.java.common.util.ResourceUtils;

/**
 * The Class DocumentTemplate.
 *
 * Clase de datos de la librería Gjs
 *
 * Produce un texto de salida a partir de una plantilla por sustitución de
 * parámetros. En la plantilla las variables deben indicarse mediante el formato
 * ${variable}.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class DocumentTemplate extends StringTemplate {

	/**
	 * Instantiates a new document template.
	 *
	 * @param templatePath the template path
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	public DocumentTemplate(String templatePath) throws IOException {
		super(ResourceUtils.getResourceAsString(templatePath));
	}

	/**
	 * Generate document.
	 *
	 * Por compatibilidad con la versión anterior.
	 *
	 * @return the string
	 */
	public String generateDocument() {
		return generate();
	}
}
