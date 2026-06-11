package org.gjs.maven.extensions.gz;

import org.apache.maven.artifact.handler.DefaultArtifactHandler;

public class GzArtifactHandler extends DefaultArtifactHandler {

	public GzArtifactHandler() {
		super("gz");
	}

}
