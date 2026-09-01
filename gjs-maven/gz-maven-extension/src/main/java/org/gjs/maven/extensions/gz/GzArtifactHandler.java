package org.gjs.maven.extensions.gz;

import org.apache.maven.artifact.handler.DefaultArtifactHandler;

/**
 * The Class GzArtifactHandler.
 *
 * Clase funcional de la librería Gjs
 *
 * ArtifactHandler del empaquetado gz: registra gz como extensión del artefacto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class GzArtifactHandler extends DefaultArtifactHandler {

	public GzArtifactHandler() {
		super("gz");
	}

}
