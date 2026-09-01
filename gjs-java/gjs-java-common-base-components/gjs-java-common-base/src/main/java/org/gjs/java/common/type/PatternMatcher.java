package org.gjs.java.common.type;

import java.util.regex.Pattern;

import org.apache.commons.lang3.ObjectUtils;
import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class PatternMatcher.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Algunas funciones de ayuda para el uso de expresiones regulares.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class PatternMatcher {

	/** The Constant EMAIL_PATTERN. */
	/* The RFC 5322 official e-mail pattern */
	private static final String EMAIL_PATTERN = "^[a-zA-Z0-9_!#$%&'*+/=?`{|}~^.-]+@[a-zA-Z0-9.-]+$";

	/**
	 * Clase no instanciable.
	 */
	private PatternMatcher() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Pattern matches.
	 *
	 * @param value        the value
	 * @param regexPattern the regex pattern
	 * @return true, if successful
	 */
	public static boolean patternMatches(String value, String regexPattern) {
		boolean res = false;
		if (ObjectUtils.allNotNull(value, regexPattern)) {
			res = Pattern.compile(regexPattern).matcher(value).matches();
		}
		return res;
	}

	/**
	 * Checks if is valid email.
	 *
	 * @param value the value
	 * @return true, if is valid email
	 */
	public static boolean isValidEmail(String value) {
		return patternMatches(value, EMAIL_PATTERN);
	}
}
