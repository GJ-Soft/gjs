package org.gjs.java.common.task;

import org.gjs.java.common.log.BaseLogger;

/**
 * The Class BaseTask.
 *
 * Clase abstracta de datos de la librería Gjs
 *
 * Clase abstracta que sirve de base para implementar una tarea de un job o
 * proceso batch del sistema automatizado de jobs de Semilla.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public abstract class BaseTask extends BaseLogger {

	/** The job name. */
	private final String jobName;

	/** The task order. */
	protected int taskOrder;

	/** The task name. */
	protected String taskName;

	/** The task description. */
	protected String taskDescription;

	/**
	 * Instantiates a new base task.
	 *
	 * @param jobName         the job name
	 * @param taskOrder       the task order
	 * @param taskName        the task name
	 * @param taskDescription the task description
	 */
	protected BaseTask(String jobName, int taskOrder, String taskName, String taskDescription) {
		this.jobName = jobName;
		this.taskOrder = taskOrder;
		this.taskName = taskName;
		this.taskDescription = taskDescription;
	}

	/**
	 * Creates the task result.
	 *
	 * @param name        the name
	 * @param description the description
	 * @return the task result
	 */
	protected TaskResult createTaskResult(String name, String description) {
		return new TaskResult(name, description);
	}

	/**
	 * Execute task.
	 *
	 * @param result the result
	 * @throws Exception the exception
	 */
	protected abstract void executeTask(TaskResult result) throws Exception;

	/**
	 * Run.
	 *
	 * @return the task result
	 */
	public TaskResult run() {
		logInfo(taskName, String.format("%s) %s", taskOrder, taskDescription));
		final TaskResult result = createTaskResult(String.format("%s:%s", jobName, taskName), taskDescription);
		try {
			executeTask(result);
		} catch (final Exception e) {
			logError(taskName, e);
		}
		logInfo(taskName, "Finalizado", result.toString());
		return result;
	}

}
