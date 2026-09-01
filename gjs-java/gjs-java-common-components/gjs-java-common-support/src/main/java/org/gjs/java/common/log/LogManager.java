package org.gjs.java.common.log;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.util.LogUtils;
import org.slf4j.Logger;

import ch.qos.logback.classic.Level;

/**
 * The Class LogManager.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase base para incorporar el logger a otras clases que puedan necesitarlo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class LogManager {

	/** The logger. */
	private Logger logger;

	/**
	 * Instantiates a new log manager.
	 */
	public LogManager() {
	}

	/**
	 * Instantiates a new log manager.
	 *
	 * @param logger the logger
	 */
	public LogManager(Logger logger) {
		this.logger = logger;
	}

	/**
	 * Gets the logger.
	 *
	 * @return the logger
	 */
	public Logger getLogger() {
		return logger;
	}

	/**
	 * Sets the logger.
	 *
	 * @param logger the new logger
	 */
	public void setLogger(Logger logger) {
		this.logger = logger;
	}

	/**
	 * Log.
	 *
	 * @param level  the level
	 * @param method the method
	 * @param infos  the infos
	 */
	protected void log(Level level, String method, Object... infos) {
		LogUtils.log(logger, level, method, infos);
	}

	/**
	 * Log info.
	 *
	 * @param method the method
	 * @param infos  the infos
	 */
	protected void logInfo(String method, Object... infos) {
		LogUtils.logInfo(logger, method, infos);
	}

	/**
	 * Log debug.
	 *
	 * @param method the method
	 * @param infos  the infos
	 */
	protected void logDebug(String method, Object... infos) {
		LogUtils.logDebug(logger, method, infos);
	}

	/**
	 * Log trace.
	 *
	 * @param method the method
	 * @param infos  the infos
	 */
	protected void logTrace(String method, Object... infos) {
		LogUtils.logTrace(logger, method, infos);
	}

	/**
	 * Log error.
	 *
	 * @param method the method
	 * @param infos  the infos
	 */
	protected void logError(String method, Object... infos) {
		LogUtils.logError(logger, method, infos);
	}

	/**
	 * Log error.
	 *
	 * @param method the method
	 * @param e      the e
	 */
	protected void logError(String method, Exception e) {
		LogUtils.logError(logger, method, ExceptionUtils.getStackTrace(e));
	}

	/**
	 * Log controlled error.
	 *
	 * @param method the method
	 * @param e      the e
	 */
	protected void logControlledError(String method, Exception e) {
		LogUtils.logError(logger, method, e.getMessage());
	}

	/**
	 * Log warn.
	 *
	 * @param method the method
	 * @param infos  the infos
	 */
	protected void logWarn(String method, Object... infos) {
		LogUtils.logWarn(logger, method, infos);
	}

	/**
	 * Log formatted.
	 *
	 * @param level  the level
	 * @param method the method
	 * @param format the format
	 * @param param  the param
	 */
	protected void logFormatted(Level level, String method, String format, Object... param) {
		LogUtils.logFormatted(logger, level, method, format, param);
	}

	/**
	 * Log formatted info.
	 *
	 * @param method the method
	 * @param format the format
	 * @param param  the param
	 */
	protected void logFormattedInfo(String method, String format, Object... param) {
		LogUtils.logFormattedInfo(logger, method, format, param);
	}

	/**
	 * Log formatted debug.
	 *
	 * @param method the method
	 * @param format the format
	 * @param param  the param
	 */
	protected void logFormattedDebug(String method, String format, Object... param) {
		LogUtils.logFormattedDebug(logger, method, format, param);
	}

	/**
	 * Log formatted trace.
	 *
	 * @param method the method
	 * @param format the format
	 * @param param  the param
	 */
	protected void logFormattedTrace(String method, String format, Object... param) {
		LogUtils.logFormattedTrace(logger, method, format, param);
	}

	/**
	 * Log formatted error.
	 *
	 * @param method the method
	 * @param format the format
	 * @param param  the param
	 */
	protected void logFormattedError(String method, String format, Object... param) {
		LogUtils.logFormattedError(logger, method, format, param);
	}

	/**
	 * Log formatted warn.
	 *
	 * @param method the method
	 * @param format the format
	 * @param param  the param
	 */
	protected void logFormattedWarn(String method, String format, Object... param) {
		LogUtils.logFormattedWarn(logger, method, format, param);
	}
}
