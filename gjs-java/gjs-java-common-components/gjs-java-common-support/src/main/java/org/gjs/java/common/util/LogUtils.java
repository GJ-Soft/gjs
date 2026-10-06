package org.gjs.java.common.util;

import java.util.IllegalFormatException;
import java.util.Locale;
import java.util.MissingFormatArgumentException;
import java.util.Objects;

import org.apache.commons.lang3.ObjectUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.constant.CommonSupportConstants;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import ch.qos.logback.classic.Level;

/**
 * The Class LogUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Métodos que facilitan el logado utilizando el formato definido por la
 * arquitectura de Semilla.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class LogUtils {

	/**
	 * Clase no instanciable.
	 */
	private LogUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Gets the method name.
	 *
	 * Retorna el nombre del metodo que llama a la función
	 *
	 * NOTA: getStackTrace() contiene: [0] getStackTrace; [1] getMethodName; [2] el
	 * metodo que llama
	 *
	 * Funciona para JRE 11 y 20. Para JRE antiguos era diferente y podria cambiar
	 * en el futuro.
	 *
	 * @return the method name
	 */
	public static String getMethodName() {
		final StackTraceElement[] ste = Thread.currentThread().getStackTrace();
		return ste[2].getMethodName();
	}

	/**
	 * Builds the log text.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 * @return the string
	 */
	public static String buildLogText(String clazz, String method, Object... infos) {
		final StringBuilder text = new StringBuilder();
		text.append('[').append(clazz).append("][").append(method).append(']');
		for (final Object info : infos) {
			text.append('[').append(Objects.toString(info)).append(']');
		}
		return text.toString();
	}

	/**
	 * Log.
	 *
	 * @param logger the logger
	 * @param level  the level
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void log(Logger logger, Level level, String clazz, String method, Object... infos) {
		if (Objects.nonNull(logger)) {
			level = Objects.requireNonNullElse(level, Objects.requireNonNullElse(
					((ch.qos.logback.classic.Logger) logger).getLevel(), CommonSupportConstants.LOG_LEVEL_DEFAULT));
			log(logger, level, buildLogText(clazz, method, infos));
		}
	}

	/**
	 * Log.
	 *
	 * @param logger the logger
	 * @param level  the level
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void log(Logger logger, Level level, String method, Object... infos) {
		if (Objects.nonNull(logger)) {
			level = Objects.requireNonNullElse(level, Objects.requireNonNullElse(
					((ch.qos.logback.classic.Logger) logger).getLevel(), CommonSupportConstants.LOG_LEVEL_DEFAULT));
			log(logger, level, buildLogText(logger.getName(), method, infos));
		}
	}

	/**
	 * Log.
	 *
	 * @param logger  the logger
	 * @param level   the level
	 * @param message the message
	 */
	private static void log(Logger logger, Level level, String message) {
		if (Objects.nonNull(logger)) {
			if (Level.DEBUG.equals(level)) {
				logger.debug(message);
			} else if (Level.INFO.equals(level)) {
				logger.info(message);
			} else if (Level.WARN.equals(level)) {
				logger.warn(message);
			} else if (Level.ERROR.equals(level)) {
				logger.error(message);
			} else {
				logger.trace(message);
			}
		}
	}

	/**
	 * Log formatted.
	 *
	 * @param logger the logger
	 * @param level  the level
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormatted(Logger logger, Level level, String clazz, String method, String format,
			Object... params) {
		if (ObjectUtils.allNotNull(logger, format)) {
			format = format.replace("{}", "%s");
			final String message = formatMessage(format, params);
			log(logger, level, clazz, method, message);
		}
	}

	/**
	 * Log formatted.
	 *
	 * @param logger the logger
	 * @param level  the level
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormatted(Logger logger, Level level, String method, String format, Object... params) {
		if (ObjectUtils.allNotNull(logger, format)) {
			format = format.replace("{}", "%s");
			final String message = formatMessage(format, params);
			log(logger, level, logger.getName(), method, message);
		}
	}

	/**
	 * Log.
	 *
	 * @param level  the level
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void log(Level level, String clazz, String method, Object... infos) {
		log(getLogger(clazz), level, clazz, method, infos);
	}

	/**
	 * Log formatted.
	 *
	 * @param level  the level
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormatted(Level level, String clazz, String method, String format, Object... params) {
		logFormatted(getLogger(clazz), level, clazz, method, format, params);
	}

	/**
	 * Gets the logger.
	 *
	 * @param clazz the clazz
	 * @return the logger
	 */
	public static Logger getLogger(String clazz) {
		Logger logger = null;
		try {
			logger = LoggerFactory.getLogger(clazz);
		} catch (IllegalArgumentException e) {
			// Sin logger para esa clase: se usa el raiz, justo debajo.
		}
		if (Objects.isNull(logger)) {
			logger = LoggerFactory.getLogger(Logger.ROOT_LOGGER_NAME);
		}
		return logger;
	}

	/**
	 * Gets the logger.
	 *
	 * @param clazz the clazz
	 * @return the logger
	 */
	public static Logger getLogger(Class<?> clazz) {
		Logger logger = null;
		try {
			logger = LoggerFactory.getLogger(clazz);
		} catch (IllegalArgumentException e) {
			// Sin logger para esa clase: se usa el raiz, justo debajo.
		}
		if (Objects.isNull(logger)) {
			logger = LoggerFactory.getLogger(Logger.ROOT_LOGGER_NAME);
		}
		return logger;
	}

	/**
	 * Log info.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logInfo(String clazz, String method, Object... infos) {
		log(Level.INFO, clazz, method, infos);
	}

	/**
	 * Log debug.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logDebug(String clazz, String method, Object... infos) {
		log(Level.DEBUG, clazz, method, infos);
	}

	/**
	 * Log trace.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logTrace(String clazz, String method, Object... infos) {
		log(Level.TRACE, clazz, method, infos);
	}

	/**
	 * Log error.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logError(String clazz, String method, Object... infos) {
		log(Level.ERROR, clazz, method, infos);
	}

	/**
	 * Log warn.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logWarn(String clazz, String method, Object... infos) {
		log(Level.WARN, clazz, method, infos);
	}

	/**
	 * Log formatted info.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedInfo(String clazz, String method, String format, Object... params) {
		logFormatted(Level.INFO, clazz, method, format, params);
	}

	/**
	 * Log formatted debug.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedDebug(String clazz, String method, String format, Object... params) {
		logFormatted(Level.DEBUG, clazz, method, format, params);
	}

	/**
	 * Log formatted trace.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedTrace(String clazz, String method, String format, Object... params) {
		logFormatted(Level.TRACE, clazz, method, format, params);
	}

	/**
	 * Log formatted error.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedError(String clazz, String method, String format, Object... params) {
		logFormatted(Level.ERROR, clazz, method, format, params);
	}

	/**
	 * Log formatted warn.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedWarn(String clazz, String method, String format, Object... params) {
		logFormatted(Level.WARN, clazz, method, format, params);
	}

	/**
	 * Log info.
	 *
	 * @param logger the logger
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logInfo(Logger logger, String clazz, String method, Object... infos) {
		log(logger, Level.INFO, clazz, method, infos);
	}

	/**
	 * Log debug.
	 *
	 * @param logger the logger
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logDebug(Logger logger, String clazz, String method, Object... infos) {
		log(logger, Level.DEBUG, clazz, method, infos);
	}

	/**
	 * Log trace.
	 *
	 * @param logger the logger
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logTrace(Logger logger, String clazz, String method, Object... infos) {
		log(logger, Level.TRACE, clazz, method, infos);
	}

	/**
	 * Log error.
	 *
	 * @param logger the logger
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logError(Logger logger, String clazz, String method, Object... infos) {
		log(logger, Level.ERROR, clazz, method, infos);
	}

	/**
	 * Log warn.
	 *
	 * @param logger the logger
	 * @param clazz  the clazz
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logWarn(Logger logger, String clazz, String method, Object... infos) {
		log(Level.WARN, clazz, method, infos);
	}

	/**
	 * Log formatted info.
	 *
	 * @param logger the logger
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedInfo(Logger logger, String clazz, String method, String format, Object... params) {
		logFormatted(logger, Level.INFO, clazz, method, format, params);
	}

	/**
	 * Log formatted debug.
	 *
	 * @param logger the logger
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedDebug(Logger logger, String clazz, String method, String format, Object... params) {
		logFormatted(logger, Level.DEBUG, clazz, method, format, params);
	}

	/**
	 * Log formatted trace.
	 *
	 * @param logger the logger
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedTrace(Logger logger, String clazz, String method, String format, Object... params) {
		logFormatted(logger, Level.TRACE, clazz, method, format, params);
	}

	/**
	 * Log formatted error.
	 *
	 * @param logger the logger
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedError(Logger logger, String clazz, String method, String format, Object... params) {
		logFormatted(logger, Level.ERROR, clazz, method, format, params);
	}

	/**
	 * Log formatted warn.
	 *
	 * @param logger the logger
	 * @param clazz  the clazz
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedWarn(Logger logger, String clazz, String method, String format, Object... params) {
		logFormatted(logger, Level.WARN, clazz, method, format, params);
	}

	/**
	 * Log info.
	 *
	 * @param logger the logger
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logInfo(Logger logger, String method, Object... infos) {
		log(logger, Level.INFO, method, infos);
	}

	/**
	 * Log debug.
	 *
	 * @param logger the logger
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logDebug(Logger logger, String method, Object... infos) {
		log(logger, Level.DEBUG, method, infos);
	}

	/**
	 * Log trace.
	 *
	 * @param logger the logger
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logTrace(Logger logger, String method, Object... infos) {
		log(logger, Level.TRACE, method, infos);
	}

	/**
	 * Log error.
	 *
	 * @param logger the logger
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logError(Logger logger, String method, Object... infos) {
		log(logger, Level.ERROR, method, infos);
	}

	/**
	 * Log warn.
	 *
	 * @param logger the logger
	 * @param method the method
	 * @param infos  the infos
	 */
	public static void logWarn(Logger logger, String method, Object... infos) {
		log(logger, Level.WARN, method, infos);
	}

	/**
	 * Log formatted info.
	 *
	 * @param logger the logger
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedInfo(Logger logger, String method, String format, Object... params) {
		logFormatted(logger, Level.INFO, method, format, params);
	}

	/**
	 * Log formatted debug.
	 *
	 * @param logger the logger
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedDebug(Logger logger, String method, String format, Object... params) {
		logFormatted(logger, Level.DEBUG, method, format, params);
	}

	/**
	 * Log formatted trace.
	 *
	 * @param logger the logger
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedTrace(Logger logger, String method, String format, Object... params) {
		logFormatted(logger, Level.TRACE, method, format, params);
	}

	/**
	 * Log formatted error.
	 *
	 * @param logger the logger
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedError(Logger logger, String method, String format, Object... params) {
		logFormatted(logger, Level.ERROR, method, format, params);
	}

	/**
	 * Log formatted warn.
	 *
	 * @param logger the logger
	 * @param method the method
	 * @param format the format
	 * @param params the params
	 */
	public static void logFormattedWarn(Logger logger, String method, String format, Object... params) {
		logFormatted(logger, Level.WARN, method, format, params);
	}

	/**
	 * Format message.
	 *
	 * @param msgPattern the msg pattern
	 * @param args       the args
	 * @return the string
	 */
	private static String formatMessage(String msgPattern, final Object... args) {
		String res = msgPattern;
		boolean end = false;
		while (!end) {
			try {
				res = String.format(Locale.getDefault(Locale.Category.FORMAT), msgPattern, args);
				end = true;
			} catch (final MissingFormatArgumentException e) {
				final int pos = msgPattern.lastIndexOf("%s");
				msgPattern = msgPattern.substring(0, pos).concat(msgPattern.substring(pos + 2));
			} catch (final IllegalFormatException e) {
				end = true;
			}
		}
		return res;
	}

}
