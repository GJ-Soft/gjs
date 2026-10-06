package org.gjs.java.common.task;

import java.io.IOException;
import java.util.Date;
import java.util.Objects;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;
import org.gjs.java.common.type.DocumentTemplate;
import org.gjs.java.common.util.ConversionUtils;
import org.gjs.java.common.util.DateUtils;

import lombok.Getter;

/**
 * The Class TaskResult.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase que almacena los resultados de una tarea simple. Básicamente almacena contadores de registros totales y
 * erroneos y el tiempo transcurrido que se controla mediante métodos de begin/end.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
public class TaskResult {

	/** The name. */
	protected final String name;

	/** The description. */
	protected final String description;

	/** The begin. */
	protected final Date begin;

	/** The end. */
	protected Date end;

	/** The duration. */
	protected long duration;

	/** The report template. */
	protected final String reportTemplate;

	/** The processed. */
	protected long processed;

	/** The errors. */
	protected long errors;

	/** The completed. */
	protected long completed;

	/**
	 * Instantiates a new task result.
	 *
	 */
	public TaskResult() {
		this("Anonima", "Tarea anonima");
	}

	/**
	 * Instantiates a new task result.
	 *
	 * @param name        the name
	 * @param description the description
	 */
	public TaskResult(String name, String description) {
		this(name, description, "informes/jobBasico.txt");
	}

	/**
	 * Instantiates a new task result.
	 *
	 * @param name           the name
	 * @param description    the description
	 * @param reportTemplate the report template
	 */
	public TaskResult(String name, String description, String reportTemplate) {
		this.name = name;
		this.description = description;
		this.reportTemplate = reportTemplate;
		this.begin = new Date();
	}

	/**
	 * Increment ok.
	 */
	public void incrementOk() {
		increment(true);
	}

	/**
	 * Increment ko.
	 */
	public void incrementKo() {
		increment(false);
	}

	/**
	 * Increment.
	 *
	 * @param ok the ok
	 */
	public void increment(boolean ok) {
		processed = processed + 1;
		if (ok) {
			completed = completed + 1;
		} else {
			errors = errors + 1;
		}
	}

	/**
	 * Checks if is executed.
	 *
	 * @return true, if is executed
	 */
	public boolean isExecuted() {
		return (processed > 0);
	}

	/**
	 * Checks if is ok.
	 *
	 * @return true, if is ok
	 */
	public boolean isOk() {
		return (errors == 0);
	}

	/**
	 * Checks for errors.
	 *
	 * @return true, if successful
	 */
	public boolean hasErrors() {
		return (errors > 0);
	}

	/**
	 * End job.
	 */
	public void endTask() {
		if (Objects.isNull(end)) {
			this.end = new Date();
			this.duration = Math.abs(end.getTime() - begin.getTime());
		}
	}

	/**
	 * To report.
	 *
	 * @return the string
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	public String toReport() throws IOException {
		final DocumentTemplate document = prepareReport();
		return document.generateDocument();
	}

	/**
	 * Prepare report.
	 *
	 * @return the document template
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	protected DocumentTemplate prepareReport() throws IOException {
		endTask();
		final DocumentTemplate document = new DocumentTemplate(getReportTemplate());
		document.setField("name", ConversionUtils.toString(getName()));
		document.setField("description", ConversionUtils.toString(getDescription()));
		document.setField("begin", DateUtils.format(getBegin(), DateUtils.FORMAT_DATETIME_DEFAULT));
		document.setField("end", DateUtils.format(getEnd(), DateUtils.FORMAT_DATETIME_DEFAULT));
		document.setField("duration", ConversionUtils.toString(duration));
		document.setField("processed", ConversionUtils.toString(processed));
		document.setField("completed", ConversionUtils.toString(completed));
		document.setField("errors", ConversionUtils.toString(errors));
		return document;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("name", name).append("begin", begin)
				.append("end", end).append("duration", duration).append("reportTemplate", reportTemplate)
				.append("processed", processed).append("errors", errors).append("completed", completed).toString();
	}

}
