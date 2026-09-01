package org.gjs.java.common.log;

import org.slf4j.LoggerFactory;
import org.slf4j.Marker;

/**
 * The Interface Logger.
 *
 * Interfaz de la librería Gjs
 *
 * Amplía el Logger de SLF4J con métodos que aceptan directamente una excepción, y trae la implementación que delega en el logger real.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public interface Logger extends org.slf4j.Logger {
	void error(Exception ex);

	void error(String message, Exception ex);

	void warn(Exception ex);

	void warn(String message, Exception ex);

	static Logger getLogger(Class<?> clazz) {
		return new LoggerImpl(LoggerFactory.getLogger(clazz));
	}

	static Logger getLogger(String name) {
		return new LoggerImpl(LoggerFactory.getLogger(name));
	}

	// -------------------------------------------------------------------------
	// Implementación interna
	// -------------------------------------------------------------------------

	class LoggerImpl implements Logger {

		private final org.slf4j.Logger delegate;

		LoggerImpl(org.slf4j.Logger delegate) {
			this.delegate = delegate;
		}

		// --- Métodos extra ---

		@Override
		public void error(Exception ex) {
			delegate.error(ex.getMessage(), ex);
		}

		@Override
		public void error(String message, Exception ex) {
			delegate.error(message, ex);
		}

		@Override
		public void warn(Exception ex) {
			delegate.warn(ex.getMessage(), ex);
		}

		@Override
		public void warn(String message, Exception ex) {
			delegate.warn(message, ex);
		}

		// --- Delegación de Logger ---

		@Override
		public String getName() {
			return delegate.getName();
		}

		@Override
		public boolean isTraceEnabled() {
			return delegate.isTraceEnabled();
		}

		@Override
		public void trace(String msg) {
			delegate.trace(msg);
		}

		@Override
		public void trace(String format, Object arg) {
			delegate.trace(format, arg);
		}

		@Override
		public void trace(String format, Object arg1, Object arg2) {
			delegate.trace(format, arg1, arg2);
		}

		@Override
		public void trace(String format, Object... arguments) {
			delegate.trace(format, arguments);
		}

		@Override
		public void trace(String msg, Throwable t) {
			delegate.trace(msg, t);
		}

		@Override
		public boolean isTraceEnabled(Marker marker) {
			return delegate.isTraceEnabled(marker);
		}

		@Override
		public void trace(Marker marker, String msg) {
			delegate.trace(marker, msg);
		}

		@Override
		public void trace(Marker marker, String format, Object arg) {
			delegate.trace(marker, format, arg);
		}

		@Override
		public void trace(Marker marker, String format, Object arg1, Object arg2) {
			delegate.trace(marker, format, arg1, arg2);
		}

		@Override
		public void trace(Marker marker, String format, Object... argArray) {
			delegate.trace(marker, format, argArray);
		}

		@Override
		public void trace(Marker marker, String msg, Throwable t) {
			delegate.trace(marker, msg, t);
		}

		@Override
		public boolean isDebugEnabled() {
			return delegate.isDebugEnabled();
		}

		@Override
		public void debug(String msg) {
			delegate.debug(msg);
		}

		@Override
		public void debug(String format, Object arg) {
			delegate.debug(format, arg);
		}

		@Override
		public void debug(String format, Object arg1, Object arg2) {
			delegate.debug(format, arg1, arg2);
		}

		@Override
		public void debug(String format, Object... arguments) {
			delegate.debug(format, arguments);
		}

		@Override
		public void debug(String msg, Throwable t) {
			delegate.debug(msg, t);
		}

		@Override
		public boolean isDebugEnabled(Marker marker) {
			return delegate.isDebugEnabled(marker);
		}

		@Override
		public void debug(Marker marker, String msg) {
			delegate.debug(marker, msg);
		}

		@Override
		public void debug(Marker marker, String format, Object arg) {
			delegate.debug(marker, format, arg);
		}

		@Override
		public void debug(Marker marker, String format, Object arg1, Object arg2) {
			delegate.debug(marker, format, arg1, arg2);
		}

		@Override
		public void debug(Marker marker, String format, Object... arguments) {
			delegate.debug(marker, format, arguments);
		}

		@Override
		public void debug(Marker marker, String msg, Throwable t) {
			delegate.debug(marker, msg, t);
		}

		@Override
		public boolean isInfoEnabled() {
			return delegate.isInfoEnabled();
		}

		@Override
		public void info(String msg) {
			delegate.info(msg);
		}

		@Override
		public void info(String format, Object arg) {
			delegate.info(format, arg);
		}

		@Override
		public void info(String format, Object arg1, Object arg2) {
			delegate.info(format, arg1, arg2);
		}

		@Override
		public void info(String format, Object... arguments) {
			delegate.info(format, arguments);
		}

		@Override
		public void info(String msg, Throwable t) {
			delegate.info(msg, t);
		}

		@Override
		public boolean isInfoEnabled(Marker marker) {
			return delegate.isInfoEnabled(marker);
		}

		@Override
		public void info(Marker marker, String msg) {
			delegate.info(marker, msg);
		}

		@Override
		public void info(Marker marker, String format, Object arg) {
			delegate.info(marker, format, arg);
		}

		@Override
		public void info(Marker marker, String format, Object arg1, Object arg2) {
			delegate.info(marker, format, arg1, arg2);
		}

		@Override
		public void info(Marker marker, String format, Object... arguments) {
			delegate.info(marker, format, arguments);
		}

		@Override
		public void info(Marker marker, String msg, Throwable t) {
			delegate.info(marker, msg, t);
		}

		@Override
		public boolean isWarnEnabled() {
			return delegate.isWarnEnabled();
		}

		@Override
		public void warn(String msg) {
			delegate.warn(msg);
		}

		@Override
		public void warn(String format, Object arg) {
			delegate.warn(format, arg);
		}

		@Override
		public void warn(String format, Object arg1, Object arg2) {
			delegate.warn(format, arg1, arg2);
		}

		@Override
		public void warn(String format, Object... arguments) {
			delegate.warn(format, arguments);
		}

		@Override
		public void warn(String msg, Throwable t) {
			delegate.warn(msg, t);
		}

		@Override
		public boolean isWarnEnabled(Marker marker) {
			return delegate.isWarnEnabled(marker);
		}

		@Override
		public void warn(Marker marker, String msg) {
			delegate.warn(marker, msg);
		}

		@Override
		public void warn(Marker marker, String format, Object arg) {
			delegate.warn(marker, format, arg);
		}

		@Override
		public void warn(Marker marker, String format, Object arg1, Object arg2) {
			delegate.warn(marker, format, arg1, arg2);
		}

		@Override
		public void warn(Marker marker, String format, Object... arguments) {
			delegate.warn(marker, format, arguments);
		}

		@Override
		public void warn(Marker marker, String msg, Throwable t) {
			delegate.warn(marker, msg, t);
		}

		@Override
		public boolean isErrorEnabled() {
			return delegate.isErrorEnabled();
		}

		@Override
		public void error(String msg) {
			delegate.error(msg);
		}

		@Override
		public void error(String format, Object arg) {
			delegate.error(format, arg);
		}

		@Override
		public void error(String format, Object arg1, Object arg2) {
			delegate.error(format, arg1, arg2);
		}

		@Override
		public void error(String format, Object... arguments) {
			delegate.error(format, arguments);
		}

		@Override
		public void error(String msg, Throwable t) {
			delegate.error(msg, t);
		}

		@Override
		public boolean isErrorEnabled(Marker marker) {
			return delegate.isErrorEnabled(marker);
		}

		@Override
		public void error(Marker marker, String msg) {
			delegate.error(marker, msg);
		}

		@Override
		public void error(Marker marker, String format, Object arg) {
			delegate.error(marker, format, arg);
		}

		@Override
		public void error(Marker marker, String format, Object arg1, Object arg2) {
			delegate.error(marker, format, arg1, arg2);
		}

		@Override
		public void error(Marker marker, String format, Object... arguments) {
			delegate.error(marker, format, arguments);
		}

		@Override
		public void error(Marker marker, String msg, Throwable t) {
			delegate.error(marker, msg, t);
		}
	}

}
