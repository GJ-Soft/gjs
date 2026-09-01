package org.gjs.maven.extensions.tgz;

import org.apache.maven.artifact.handler.DefaultArtifactHandler;

/**
 * The Class TgzArtifactHandler.
 *
 * Clase funcional de la librería Gjs
 *
 * ArtifactHandler del empaquetado tgz: registra tgz como extensión del artefacto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class TgzArtifactHandler extends DefaultArtifactHandler {

	public TgzArtifactHandler() {
		super("tgz");
	}

}
