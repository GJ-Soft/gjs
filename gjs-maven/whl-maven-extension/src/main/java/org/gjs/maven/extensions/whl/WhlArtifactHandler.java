package org.gjs.maven.extensions.whl;

import org.apache.maven.artifact.handler.DefaultArtifactHandler;

/**
 * The Class WhlArtifactHandler.
 *
 * Clase funcional de la librería Gjs
 *
 * ArtifactHandler del empaquetado whl: registra whl como extensión del artefacto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class WhlArtifactHandler extends DefaultArtifactHandler {

	public WhlArtifactHandler() {
		super("whl");
	}

}
