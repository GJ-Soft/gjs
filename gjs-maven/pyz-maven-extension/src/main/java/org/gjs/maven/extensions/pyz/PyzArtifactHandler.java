package org.gjs.maven.extensions.pyz;

import org.apache.maven.artifact.handler.DefaultArtifactHandler;

/**
 * The Class PyzArtifactHandler.
 *
 * Clase funcional de la librería Gjs
 *
 * ArtifactHandler del empaquetado pyz: registra pyz como extensión del artefacto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class PyzArtifactHandler extends DefaultArtifactHandler {

	public PyzArtifactHandler() {
		super("pyz");
	}

}
