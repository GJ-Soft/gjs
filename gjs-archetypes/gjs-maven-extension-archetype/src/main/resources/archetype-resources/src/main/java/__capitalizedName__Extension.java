#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $infoGroup = $groupId)
#set( $infoArtifact = $artifactId)
#set( $infoVersion = $version)
package ${package};

import javax.inject.Inject;

import org.apache.maven.AbstractMavenLifecycleParticipant;
import org.apache.maven.artifact.handler.DefaultArtifactHandler;
import org.apache.maven.execution.MavenExecutionRequest;
import org.apache.maven.execution.MavenSession;
import org.apache.maven.project.MavenProject;
import org.apache.maven.project.MavenProjectHelper;
import org.codehaus.plexus.logging.Logger;


public class ${capitalizedName}Extension extends AbstractMavenLifecycleParticipant {

	@Inject
	private Logger logger;

	@Inject
	private MavenProjectHelper projectHelper;

	@Override
	public void afterProjectsRead( MavenSession session ) {

		MavenExecutionRequest request = session.getRequest();
		//TODO
	}
	
		@Override
	public void afterSessionEnd( MavenSession session ) {

		MavenExecutionRequest request = session.getRequest();
		//TODO
	}

}