package org.gjs.maven.extensions.tgz;

import java.io.File;

import javax.inject.Inject;

import org.apache.maven.AbstractMavenLifecycleParticipant;
import org.apache.maven.execution.MavenSession;
import org.apache.maven.project.MavenProject;
import org.apache.maven.project.MavenProjectHelper;
import org.codehaus.plexus.logging.Logger;

public class TgzArtifactExtension extends AbstractMavenLifecycleParticipant {

	@Inject
	private Logger logger;

	@Inject
	private MavenProjectHelper projectHelper;

	@Override
	public void afterProjectsRead(MavenSession session) {

		for (MavenProject project : session.getProjects()) {

			if (!"tgz".equals(project.getPackaging())) {
				continue;
			}

			File tgz = new File(project.getBuild().getDirectory(), project.getBuild().getFinalName() + ".tgz");

			project.getArtifact().setFile(tgz);
			project.getArtifact().setArtifactHandler(new TgzArtifactHandler());

			if (logger != null) {
				logger.info("[tgz-extension] Artifact reemplazado por: " + tgz.getAbsolutePath());
			}
		}
	}
}