package org.gjs.java.maven.common;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.apache.maven.execution.MavenSession;
import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecution;
import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.logging.Log;
import org.apache.maven.plugins.annotations.Parameter;
import org.apache.maven.project.MavenProject;
import org.gjs.java.maven.exception.GjsMavenException;

/**
 * The Class GjsAbstractMojo.
 */
public abstract class GjsAbstractMojo extends AbstractMojo {

	/** MojoExecution needed by the ExpressionEvaluator. */
	@Parameter(defaultValue = "${mojoExecution}", readonly = true, required = true)
	protected MojoExecution mojoExecution;

	/** The MavenSession. */
	@Parameter(defaultValue = "${session}", readonly = true, required = true)
	protected MavenSession session;

	/** POM. */
	@Parameter(defaultValue = "${project}", readonly = true, required = true)
	protected MavenProject project;

	@Parameter(defaultValue = "${project.basedir}", required = true)
	protected File baseDirectory;

	@Parameter(defaultValue = "${project.build.directory}", required = true)
	protected File outputDirectory;

	@Parameter(defaultValue = "${project.build.finalName}", required = true)
	protected String finalName;

	/** Flag to easily getSkip() all checks. */
	protected abstract boolean getSkip();

	/**
	 * Flag to getFail() the build if at least one check fails.
	 */
	protected abstract boolean getFail();

	/**
	 * Gets the goal name.
	 *
	 * @return the goal name
	 */
	protected abstract String getGoalName();

	/**
	 * Goal execution.
	 *
	 * @param log           the log
	 *
	 * @param errorMessages the error messages
	 */
	protected abstract void goalExecution(Log log, List<String> errorMessages) throws Throwable;

	protected void additionalInitializations() {
	}

	/**
	 * Execute.
	 *
	 * @throws MojoExecutionException the mojo execution exception
	 */
	@Override
	public void execute() throws MojoExecutionException {
		Log log = this.getLog();

		if (getSkip()) {
			log.info(String.format("Skipping %s execution.", getGoalName()));
			return;
		}

		// create my helper
		// PluginParameterExpressionEvaluator evaluator = new
		// PluginParameterExpressionEvaluator(session, mojoExecution);

		additionalInitializations();

		List<String> errorMessages = new ArrayList<>();
		log.info(String.format("Executing %s.", getGoalName()));
		try {
			goalExecution(log, errorMessages);
		} catch (Throwable e) {
			String goalMessage = createGoalMessage(e);
			errorMessages.add(goalMessage);
		}
		if (errorMessages.isEmpty()) {
			log.info(String.format("%s executed ok.", getGoalName()));
		} else {
			log.info(String.format("%s executed with errors.", getGoalName()));
			if (getFail()) {
				throw new GjsMavenException(
						System.lineSeparator() + String.join(System.lineSeparator(), errorMessages));
			} else {
				errorMessages.forEach(log::warn);
			}
		}
	}

	/**
	 * Creates the goal message.
	 *
	 * @param e the e
	 * @return the string
	 */
	protected String createGoalMessage(Throwable e) {
		StringBuilder result = new StringBuilder();
		result.append("Goal ").append(getGoalName()).append(": ");
		if (e.getMessage() != null) {
			result.append(" with message:").append(System.lineSeparator()).append(e.getMessage());
		} else {
			result.append(" without a message");
		}
		return result.toString();
	}

}
