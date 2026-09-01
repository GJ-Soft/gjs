package org.gjs.java.common.util;

import java.text.Collator;
import java.util.Arrays;
import java.util.Objects;
import java.util.stream.Collectors;

import org.apache.commons.lang3.ObjectUtils;
import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class StringUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Algunas funciones adicionales de manejo de cadenas.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class StringUtils {

	/**
	 * Clase no instanciable.
	 */
	private StringUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Concatenate.
	 *
	 * @param strings the strings
	 * @return the string
	 */
	public static String concatenate(String... strings) {
		final StringBuilder builder = new StringBuilder();
		if (Objects.nonNull(strings)) {
			for (final String string : strings) {
				if (Objects.nonNull(string)) {
					builder.append(string);
				}
			}
		}
		return builder.toString();
	}

	/**
	 * Concatenate with separator.
	 *
	 * @param separator the separator
	 * @param strings   the strings
	 * @return the string
	 */
	public static String concatenateWithSeparator(String separator, String... strings) {
		final StringBuilder builder = new StringBuilder();
		if (Objects.nonNull(strings)) {
			separator = Objects.requireNonNullElse(separator, "");
			boolean begin = true;
			for (final String string : strings) {
				if (Objects.nonNull(string)) {
					if (!begin) {
						builder.append(separator);
					}
					begin = false;
					builder.append(string);
				}
			}
		}
		return builder.toString();
	}

	/**
	 * Nvl.
	 *
	 * @param value the value
	 * @return the string
	 */
	public static String nvl(String value) {
		String res = CommonBaseConstants.NULL_VALUE;
		if (!org.apache.commons.lang3.StringUtils.isAllBlank(value)) {
			res = value;
		}
		return res;
	}

	/**
	 * Secure Nvl.
	 *
	 * @param value the value
	 * @return the string
	 */
	public static String secureNvl(String value) {
		String res = CommonBaseConstants.NULL_VALUE;
		if (!org.apache.commons.lang3.StringUtils.isAllBlank(value)) {
			res = CommonBaseConstants.INFORMED_VALUE;
		}
		return res;
	}

	/**
	 * Checks if is same.
	 *
	 * @param a the a
	 * @param b the b
	 * @return true, if is same
	 */
	public static boolean isSame(String a, String b) {
		boolean res = false;
		if (ObjectUtils.allNotNull(a, b)) {
			final Collator insenstiveStringComparator = Collator.getInstance();
			insenstiveStringComparator.setStrength(Collator.PRIMARY);
			res = insenstiveStringComparator.compare(a, b) == 0;
		}
		return res;
	}

	/**
	 * Capitalizae all words.
	 *
	 * @param text the text
	 * @return the string
	 */
	public static String capitalizeAllWords(String text) {
		String capitalized = text;
		if (!org.apache.commons.lang3.StringUtils.isAllBlank(text)) {
			capitalized = Arrays.stream(text.split("\\s+"))
					.map(word -> word.substring(0, 1).toUpperCase(CommonBaseConstants.DEFAULT_LOCALE)
							+ word.substring(1).toLowerCase(CommonBaseConstants.DEFAULT_LOCALE))
					.collect(Collectors.joining(" "));
		}
		return capitalized;
	}
}
