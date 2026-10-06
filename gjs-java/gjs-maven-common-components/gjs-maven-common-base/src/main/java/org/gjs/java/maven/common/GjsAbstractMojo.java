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
 *
 * Base de los goals de la libreria Gjs. Recoge los errores del goal, decide entre fallar el build o avisar segun
 * getFail(), y deja a la subclase solo lo suyo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
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
	 *
	 * @throws Exception cualquier fallo del goal; se recoge en execute() y se trata segun getFail()
	 */
	protected abstract void goalExecution(Log log, List<String> errorMessages) throws Exception;

	/**
	 * Preparativos previos al goal. Se ejecuta dentro del control de errores de execute(), asi que lo que falle aqui se
	 * trata igual que lo que falle en el propio goal.
	 *
	 * @throws Exception cualquier fallo en la preparacion
	 */
	protected void additionalInitializations() throws Exception {
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

		List<String> errorMessages = new ArrayList<>();
		Exception cause = null;
		log.info(String.format("Executing %s.", getGoalName()));
		try {
			additionalInitializations();
			goalExecution(log, errorMessages);
		} catch (Exception e) {
			cause = e;
			errorMessages.add(createGoalMessage(e));
		}
		if (errorMessages.isEmpty()) {
			log.info(String.format("%s executed ok.", getGoalName()));
		} else {
			log.info(String.format("%s executed with errors.", getGoalName()));
			if (getFail()) {
				String message = System.lineSeparator() + String.join(System.lineSeparator(), errorMessages);
				// Con la causa enganchada, mvn -e y mvn -X pueden imprimir la traza real.
				throw cause == null ? new GjsMavenException(message) : new GjsMavenException(message, cause);
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
		result.append("Goal ").append(getGoalName()).append(": ").append(e.getClass().getName());
		if (e.getMessage() != null) {
			result.append(" with message:").append(System.lineSeparator()).append(e.getMessage());
		} else {
			result.append(" without a message");
		}
		return result.toString();
	}

}
