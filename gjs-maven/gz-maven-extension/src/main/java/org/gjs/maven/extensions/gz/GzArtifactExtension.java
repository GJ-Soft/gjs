package org.gjs.maven.extensions.gz;

import java.io.File;

import javax.inject.Inject;

import org.apache.maven.AbstractMavenLifecycleParticipant;
import org.apache.maven.execution.MavenSession;
import org.apache.maven.project.MavenProject;
import org.apache.maven.project.MavenProjectHelper;
import org.codehaus.plexus.logging.Logger;

public class GzArtifactExtension extends AbstractMavenLifecycleParticipant {

	@Inject
	private Logger logger;

	@Inject
	private MavenProjectHelper projectHelper;

	@Override
	public void afterProjectsRead(MavenSession session) {

		for (MavenProject project : session.getProjects()) {

			if (!"gz".equals(project.getPackaging())) {
				continue;
			}

			File gz = new File(project.getBuild().getDirectory(), project.getBuild().getFinalName() + ".gz");

			project.getArtifact().setFile(gz);
			project.getArtifact().setArtifactHandler(new GzArtifactHandler());

			if (logger != null) {
				logger.info("[gz-extension] Artifact reemplazado por: " + gz.getAbsolutePath());
			}
		}
	}
}