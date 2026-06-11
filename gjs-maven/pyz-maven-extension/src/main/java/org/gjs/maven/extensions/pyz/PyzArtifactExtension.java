package org.gjs.maven.extensions.pyz;

import java.io.File;

import javax.inject.Inject;

import org.apache.maven.AbstractMavenLifecycleParticipant;
import org.apache.maven.execution.MavenSession;
import org.apache.maven.project.MavenProject;
import org.apache.maven.project.MavenProjectHelper;
import org.codehaus.plexus.logging.Logger;

public class PyzArtifactExtension extends AbstractMavenLifecycleParticipant {

	@Inject
	private Logger logger;

	@Inject
	private MavenProjectHelper projectHelper;

	@Override
	public void afterProjectsRead(MavenSession session) {

		for (MavenProject project : session.getProjects()) {

			if (!"pyz".equals(project.getPackaging())) {
				continue;
			}

			File pyz = new File(project.getBuild().getDirectory(), project.getBuild().getFinalName() + ".pyz");

			project.getArtifact().setFile(pyz);
			project.getArtifact().setArtifactHandler(new PyzArtifactHandler());

			if (logger != null) {
				logger.info("[pyz-extension] Artifact reemplazado por: " + pyz.getAbsolutePath());
			}
		}
	}
}