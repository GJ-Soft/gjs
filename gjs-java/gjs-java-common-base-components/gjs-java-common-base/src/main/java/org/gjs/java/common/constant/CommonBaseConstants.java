package org.gjs.java.common.constant;

import java.util.Locale;

import org.apache.commons.lang3.LocaleUtils;

/**
 * The Class CommonBaseConstants.
 *
 * Clase de constantes de la librería Gjs
 *
 * Constantes del núcleo: mensajes genéricos, marcadores de valor nulo e informado, locale por defecto y patrones de fecha.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class CommonBaseConstants {

	public static final String MSG_UTILITY_CLASS = "Non-instantable utility class";

	public static final String MSG_UNKNOWN_ERROR = "Unknown error";

	/** The Constant NULL_VALUE. */
	public static final String NULL_VALUE = "NUL";

	/** The Constant INFORMED_VALUE. */
	public static final String INFORMED_VALUE = "XXX";

	/** The Constant DEFAULT_LOCALE . */
	public static final Locale DEFAULT_LOCALE = LocaleUtils.toLocale("es_ES");

	/** The Constant SIMPLE_DATETIME__FORMAT. */
	public static final String SIMPLE_DATETIME_FORMAT = "dd/MM/yyyy HH:mm:ss";

	/** The Constant DATE_OUTPUT_FORMAT. */
	public static final String DATE_OUTPUT_FORMAT = "yyyy-MM-dd";

	/** The Constant DATETIME_OUTPUT_FORMAT. */
	public static final String DATETIME_OUTPUT_FORMAT = "yyyy-MM-dd'T'HH:mm:ss";

	/** The Constant TIMESTAMP_OUTPUT_FORMAT. */
	public static final String TIMESTAMP_OUTPUT_FORMAT = "yyyy-MM-dd'T'HH:mm:ss.SSS";

	private CommonBaseConstants() {
		throw new IllegalStateException(MSG_UTILITY_CLASS);
	}

}
