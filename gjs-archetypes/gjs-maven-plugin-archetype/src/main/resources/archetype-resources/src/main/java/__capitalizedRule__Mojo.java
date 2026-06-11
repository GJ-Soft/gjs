#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $capitalizedRule = $rule.substring(0,1).toUpperCase() + $rule.substring(1))
#set( $upperPhase = $phase.toUpperCase())
#set( $infoGroup = $groupId)
#set( $infoArtifact = $artifactId)
#set( $infoVersion = $version)
package ${package};

import java.util.List;

import org.apache.maven.plugins.annotations.LifecyclePhase;
import org.apache.maven.plugins.annotations.Mojo;
import org.apache.maven.plugins.annotations.ResolutionScope;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.plugin.logging.Log;
import org.gjs.java.maven.common.GjsAbstractMojo;

/**
 * This goal executes the defined enforcer-rules once per module.
 */
@Mojo( name = "${rule}",
        defaultPhase = LifecyclePhase.${upperPhase},
        threadSafe = true)
public class ${capitalizedRule}Mojo extends GjsAbstractMojo {
 
 
    /** Flag to easily skip all checks. */
    @Parameter(property = "${shortName}.skip", defaultValue = "false")
    private boolean skip = false;

    /**
     * Flag to fail the build if at least one check fails.
     */
    @Parameter(property = "${shortName}.fail", defaultValue = "true")
    private boolean fail = true;

	@Override
	protected String getGoalName() {
		return "${rule}";
	}

	@Override
	protected boolean getSkip() {
		return skip;
	}

	@Override
	protected boolean getFail() {
		return fail;
	}

	@Override
	protected void goalExecution(Log log, List<String> arg0) {
		// TODO Auto-generated method stub		
	}




}
