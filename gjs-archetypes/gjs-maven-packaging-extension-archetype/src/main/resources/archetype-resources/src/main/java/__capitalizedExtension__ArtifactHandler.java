#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $capitalizedExtension = $extension.substring(0,1).toUpperCase() + $extension.substring(1))
#set( $infoGroup = $groupId)
#set( $infoArtifact = $artifactId)
#set( $infoVersion = $version)
package ${package};

import org.apache.maven.artifact.handler.DefaultArtifactHandler;

public class ${capitalizedExtension}ArtifactHandler extends DefaultArtifactHandler {

	public ${capitalizedExtension}ArtifactHandler() {
		super("${extension}");
	}

}
