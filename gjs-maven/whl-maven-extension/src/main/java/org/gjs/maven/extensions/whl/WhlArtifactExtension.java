package org.gjs.maven.extensions.whl;

import java.io.File;

import javax.inject.Inject;

import org.apache.maven.AbstractMavenLifecycleParticipant;
import org.apache.maven.execution.MavenSession;
import org.apache.maven.project.MavenProject;
import org.apache.maven.project.MavenProjectHelper;
import org.codehaus.plexus.logging.Logger;

/**
 * The Class WhlArtifactExtension.
 *
 * Clase funcional de la librería Gjs
 *
 * Participante del ciclo de vida de Maven para el empaquetado whl: apunta el artefacto del proyecto al fichero generado en target y le asigna su ArtifactHandler.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class WhlArtifactExtension extends AbstractMavenLifecycleParticipant {

	@Inject
	private Logger logger;

	@Inject
	private MavenProjectHelper projectHelper;

	@Override
	public void afterProjectsRead(MavenSession session) {

		for (MavenProject project : session.getProjects()) {

			if (!"whl".equals(project.getPackaging())) {
				continue;
			}

			String artifactId = project.getArtifactId().replace('-', '_');
			String version = project.getVersion().replace("-SNAPSHOT", ".dev0").replace("-RC.", "rc").replace("-", ".");

			String whlName = artifactId + "-" + version + "-py3-none-any";
			File whl = new File(project.getBuild().getDirectory(), whlName + ".whl");

			project.getArtifact().setFile(whl);
			project.getArtifact().setArtifactHandler(new WhlArtifactHandler());

			if (logger != null) {
				logger.info("[whl-extension] Artifact reemplazado por: " + whl.getAbsolutePath());
			}
		}
	}
}