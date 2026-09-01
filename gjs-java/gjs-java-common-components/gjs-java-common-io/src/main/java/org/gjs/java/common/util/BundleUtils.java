package org.gjs.java.common.util;

import java.text.MessageFormat;
import java.util.MissingResourceException;
import java.util.Objects;
import java.util.ResourceBundle;

import org.apache.commons.lang3.ObjectUtils;
import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.constant.CommonIoConstants;
import org.gjs.java.common.exception.GjsException;
import org.gjs.java.common.singleton.GlobalBundleManager;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class BundleUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Funcionalidad de manejo de ficheros bundle de literales multi-idioma.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class BundleUtils {

	/** The logger. */
	private static Logger logger = LoggerFactory.getLogger(BundleUtils.class);

	/** The Constant BUNDLE_MSG. */
	public static final ResourceBundle MESSAGE_BUNDLE = ResourceBundle
			.getBundle(CommonIoConstants.BUNDLE_LITERALS_NAME);

	/** The Constant ERROR_BUNDLE. */
	public static final ResourceBundle ERROR_BUNDLE = ResourceBundle.getBundle(CommonIoConstants.BUNDLE_ERRORS_NAME);

	/**
	 * Clase no instanciable.
	 */
	private BundleUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Gets the locale part.
	 *
	 * @param bundleName the bundle name
	 * @return the locale part
	 */
	public static String getLocalePart(String bundleName) {
		String locale = null;
		if (!StringUtils.isAllBlank(bundleName)) {
			final String[] parts = bundleName.split("-");
			if (parts.length > 1) {
				locale = parts[parts.length - 1];
			}
		}
		return locale;
	}

	/**
	 * Gets the message.
	 *
	 * @param key the key
	 * @return the message
	 */
	public static String getMessage(String key) {
		String message = null;
		try {
			message = GlobalBundleManager.getInstance().getMessage(key);
		} catch (final GjsException e) {
			logger.error(org.apache.commons.lang3.exception.ExceptionUtils.getStackTrace(e));
		}
		return Objects.requireNonNullElse(message, String.format("!%s!", key));
	}

	/**
	 * Gets the error message.
	 *
	 * @param key the key
	 * @return the message
	 */
	public static String getErrorMessage(String key) {
		String message = null;
		try {
			message = GlobalBundleManager.getInstance().getErrorMessage(key);
		} catch (final GjsException e) {
			logger.error(org.apache.commons.lang3.exception.ExceptionUtils.getStackTrace(e));
		}
		return Objects.requireNonNullElse(message, String.format("!%s!", key));
	}

	/**
	 * Gets the message.
	 *
	 * @param key    the key
	 * @param params the params
	 * @return the message
	 */
	public static String getMessage(String key, Object... params) {
		String message = null;
		try {
			message = GlobalBundleManager.getInstance().getMessage(key, params);
		} catch (final GjsException e) {
			logger.error(org.apache.commons.lang3.exception.ExceptionUtils.getStackTrace(e));
		}
		return Objects.requireNonNullElse(message, String.format("!%s!", key));
	}

	/**
	 * Gets the error message.
	 *
	 * @param key    the key
	 * @param params the params
	 * @return the erorr message
	 */
	public static String getErrorMessage(String key, Object... params) {
		String message = null;
		try {
			message = GlobalBundleManager.getInstance().getErrorMessage(key, params);
		} catch (final GjsException e) {
			logger.error(org.apache.commons.lang3.exception.ExceptionUtils.getStackTrace(e));
		}
		return Objects.requireNonNullElse(message, String.format("!%s!", key));
	}

	/**
	 * Gets the message.
	 *
	 * @param bundle the bundle
	 * @param key    the key
	 * @return the message
	 */
	public static String getMessage(ResourceBundle bundle, String key) {
		String message = null;

		if (ObjectUtils.allNotNull(bundle, key)) {
			try {
				message = bundle.getString(key);
			} catch (final MissingResourceException e) {
				message = '!' + key + '!';
			}
		} else {
			message = '!' + key + '!';
		}

		return message;
	}

	/**
	 * Gets the message.
	 *
	 * @param bundle the bundle
	 * @param key    the key
	 * @param params the params
	 * @return the message
	 */
	public static String getMessage(ResourceBundle bundle, String key, Object... params) {
		String message;

		if (ObjectUtils.allNotNull(bundle, key)) {
			try {
				message = MessageFormat.format(bundle.getString(key), params);
			} catch (final MissingResourceException e) {
				message = '!' + key + '!';
			}
		} else {
			message = '!' + key + '!';
		}

		return message;
	}

}
