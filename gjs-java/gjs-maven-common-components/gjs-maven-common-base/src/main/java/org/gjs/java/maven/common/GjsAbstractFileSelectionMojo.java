package org.gjs.java.maven.common;

import java.util.List;

import org.apache.maven.plugins.annotations.Parameter;
import org.codehaus.plexus.util.DirectoryScanner;

/**
 * The Class GjsAbstractFileSelectionMojo.
 *
 * Base para los goals que trabajan sobre un conjunto de ficheros del proyecto. Resuelve la seleccion antes de ejecutar
 * el goal y la deja en {@link #includedFiles}, de modo que la subclase solo tiene que recorrerla.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class GjsAbstractFileSelectionMojo extends GjsAbstractMojo {

	/** Patrones de los ficheros a incluir. Si no se indica ninguno, se incluyen todos. */
	@Parameter
	protected List<String> includes;

	/** Patrones de los ficheros a excluir, ademas de las exclusiones por defecto del DirectoryScanner. */
	@Parameter
	protected List<String> excludes;

	/** Si el nombre del directorio base debe encabezar la ruta de cada fichero. */
	@Parameter(defaultValue = "true")
	protected boolean includeBaseDirectory;

	/** Rutas de los ficheros seleccionados, relativas al directorio base. */
	protected String[] includedFiles;

	/**
	 * Resuelve la seleccion de ficheros sobre el directorio base.
	 *
	 * @throws Exception cualquier fallo en la preparacion, incluido el de la clase padre
	 */
	@Override
	protected void additionalInitializations() throws Exception {
		super.additionalInitializations();

		DirectoryScanner scanner = new DirectoryScanner();
		scanner.setBasedir(baseDirectory);

		if (includes != null && !includes.isEmpty()) {
			scanner.setIncludes(includes.toArray(new String[0]));
		} else {
			scanner.setIncludes(new String[] { "**/**" });
		}

		if (excludes != null && !excludes.isEmpty()) {
			scanner.setExcludes(excludes.toArray(new String[0]));
		}

		scanner.addDefaultExcludes();
		scanner.scan();

		includedFiles = scanner.getIncludedFiles();
	}

}
