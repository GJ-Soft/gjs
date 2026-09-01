package org.gjs.java.common.comparator;

import java.util.Comparator;
import java.util.Locale;
import java.util.Objects;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class AlpahbeticComparator.
 *
 * Clase de datos de la librería Gjs
 *
 * Comparador para ordenar cadena de forma alfabética.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class AlphabeticComparator implements Comparator<String> {

	/*
	 * (non-Javadoc)
	 *
	 * @see java.util.Comparator#compare(java.lang.Object, java.lang.Object)
	 */

	@Override
	public int compare(String o1, String o2) {
		int res = 0;
		if (ConditionUtils.oneIsTrue(Objects.nonNull(o1), Objects.nonNull(o2))) {
			if (Objects.isNull(o2)) {
				res = 1;
			} else if (Objects.isNull(o1)) {
				res = -1;
			} else {
				final String s1 = StringUtils.stripAccents(o1.toUpperCase(Locale.getDefault()));
				final String s2 = StringUtils.stripAccents(o2.toUpperCase(Locale.getDefault()));
				res = characterStringCompare(s1, s2);
			}
		}
		return res;
	}

	/**
	 * Character string compare.
	 *
	 * @param s1 the s 1
	 * @param s2 the s 2
	 * @return the int
	 */
	private int characterStringCompare(String s1, String s2) {
		int res = 0;
		final int min = Integer.min(s1.length(), s2.length());
		for (int i = 0; i < min; i = i + 1) {
			res = Character.compare(s1.charAt(i), s2.charAt(i));
			if (res != 0) {
				break;
			}
		}
		if (res == 0) {
			if (s1.length() > min) {
				res = 1;
			} else if (s2.length() > min) {
				res = -1;
			}
		}
		return res;
	}

}
