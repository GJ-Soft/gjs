#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $capitalizedExtension = $extension.substring(0,1).toUpperCase() + $extension.substring(1))
#set( $infoGroup = $groupId)
#set( $infoArtifact = $artifactId)
#set( $infoVersion = $version)
package ${package};

import java.io.File;

import javax.inject.Inject;

import org.apache.maven.AbstractMavenLifecycleParticipant;
import org.apache.maven.artifact.handler.DefaultArtifactHandler;
import org.apache.maven.execution.MavenSession;
import org.apache.maven.project.MavenProject;
import org.apache.maven.project.MavenProjectHelper;
import org.codehaus.plexus.logging.Logger;


public class ${capitalizedExtension}ArtifactExtension extends AbstractMavenLifecycleParticipant {

	@Inject
	private Logger logger;

	@Inject
	private MavenProjectHelper projectHelper;

	@Override
	public void afterProjectsRead(MavenSession session) {

		for (MavenProject project : session.getProjects()) {

			if (!"${extension}".equals(project.getPackaging())) {
				continue;
			}

			File file = new File(project.getBuild().getDirectory(),
					 project.getBuild().getFinalName() + ".${extension}");

			project.getArtifact().setFile(file);
			project.getArtifact().setArtifactHandler(new DefaultArtifactHandler("${extension}"));

			if (logger != null) {
				logger.info("[${capitalizedExtension}ArtifactExtension] Artifact reemplazado por: " + file.getAbsolutePath());
			}
		}
	}
}