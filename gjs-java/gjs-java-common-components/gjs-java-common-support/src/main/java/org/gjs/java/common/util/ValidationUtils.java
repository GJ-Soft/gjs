package org.gjs.java.common.util;

import java.util.Collection;
import java.util.Locale;
import java.util.Objects;

import org.apache.commons.lang3.LocaleUtils;
import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class ValidationUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Funciones de validación generales de la librería Gjs.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class ValidationUtils {

	/** The Constant NAME_PATTERN. */
	// private static final String NAME_PATTERN =
	// "^[A-ZÑÇÁÉÍÓÚÀÈÒ][a-zñçáéíóúàèò]{1,}((
	// |-)[A-ZÑÇÁÉÍÓÚÀÈÒ][a-zñçáéíóúàèò]{1,})*";
	private static final String NAME_PATTERN = "^\\p{Upper}[\\p{Lower}]{1,}((( |-)[\\p{Upper}][\\p{Lower}]{1,})*| \\p{Upper}.)";

	/** The Constant SURNAME_PATTERN. */
	private static final String SURNAME_PATTERN = "^(de ){0,1}\\p{Upper}[\\p{Lower}]{1,}(( |-| de | del | de la | la )[\\p{Upper}][\\p{Lower}]{1,})*";

	/** The Constant PATH_PART_PATTERN. */
	private static final String PATH_PART_PATTERN = "^[a-zA-Z][A-Za-z0-9-]*";

	/** The Constant CODE_PATTERN. */
	private static final String CODE_PATTERN = "^[a-zA-Z]([a-zA-Z0-9_]{0,49})";

	/** The Constant VARIABLE_CODE_PATTERN. */
	private static final String VARIABLE_CODE_PATTERN = "^[a-zA-Z]([a-zA-Z0-9/_-]*)";

	/** The Constant THING_NAME_PATTERN. */
	private static final String THING_NAME_PATTERN = "[\\p{Alnum}]+([( |/|\\-|_)[\\p{Alnum}]+]*)";

	/** The Constant TEXT_PATTERN. */
	private static final String TEXT_PATTERN = "\\p{Print}+";

	/** The Constant FILE_NAME_PATTERN. */
	private static final String FILE_NAME_PATTERN = "^[a-zA-Z]([a-zA-Z0-9_@$-.]{0,249})";

	/** The Constant IDSGU_PATTERN. */
	private static final String IDSGU_PATTERN = "^[a-zA-Z]([a-zA-Z0-9]{2,24})";

	/** The Constant CID_PATTERN. */
	private static final String CID_PATTERN = "[0-9a-zA-Z+_=]{1,128}";

	/** The Constant URL_PATTERN. */
	private static final String HTTP_PATTERN = "^https?://[-a-zA-Z0-9+&@#/%?=~_|!:,.;]*[-a-zA-Z0-9+&@#/%=~_|]";

	/** The Constant URL_PATH_PATTERN. */
	private static final String URL_PATH_PATTERN = "/|(/[a-zA-Z][a-zA-Z0-9_-]+)+/?";

	/** The Constant EMAIL_PATTERN. */
	private static final String EMAIL_PATTERN = "^(?=.{1,64}@)[A-Za-z0-9_-]+(\\.[A-Za-z0-9_-]+)*@[^-][A-Za-z0-9-]+(\\.[A-Za-z0-9-]+)*(\\.[A-Za-z]{2,})$";

	/** The Constant WATCHWORD_PATTERN. */
	public static final String WATCHWORD_PATTERN = "^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=\\S+$).{8,40}$";

	/** The Constant DNI_LETTERS. */
	private static final String DNI_LETTERS = "TRWAGMYFPDXBNJZSQVHLCKE";

	/** The Constant CIF_LETTERS. */
	private static final String CIF_LETTERS = "ABCDEFGHJKLMNPQRSUVW";

	/** The control letters cif. */
	private static final String CONTROL_LETTERS_CIF = "JABCDEFGHI";

	/** The kind digit cif letters. */
	private static final String KIND_DIGIT_CIF_LETTERS = "ABEH";

	/** The kind letter cif letters. */
	private static final String KIND_LETTER_CIF_LETTERS = "KPQS";

	/** The Constant LOCALE_PATTERN. */
	private static final String LOCALE_PATTERN = "^[a-z]{2}([_][A-Za-z]{2})?$";

	/** The Constant LIST_PATTERN. */
	private static final String LIST_PATTERN = "\\s*[-_\\w.@]+\\s*(,\\s*[-_\\w.@]+\\s*)*";

	/**
	 * Clase no instanciable.
	 */
	private ValidationUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Checks if is valid id.
	 *
	 * @param id the id
	 * @return true, if is valid id
	 */
	public static boolean isValidId(Long id) {
		return (Objects.nonNull(id) && (id > 0));
	}

	/**
	 * Checks if is valid id.
	 *
	 * @param id the id
	 * @return true, if is valid id
	 */
	public static boolean isValidId(String id) {
		return isValidCode(id);
	}

	/**
	 * Checks if is valid id.
	 *
	 * @param id   the id
	 * @param size the size
	 * @return true, if is valid id
	 */
	public static boolean isValidId(String id, int size) {
		return isValidCode(id, size);
	}

	/**
	 * Are valid id.
	 *
	 * @param ids the ids
	 * @return true, if successful
	 */
	public static boolean areValidId(Collection<Long> ids) {
		boolean res = false;
		if (!org.apache.commons.collections4.CollectionUtils.isEmpty(ids)) {
			res = true;
			for (final Long id : ids) {
				if (!isValidId(id)) {
					res = false;
					break;
				}
			}
		}
		return res;
	}

	/**
	 * Are valid string id.
	 *
	 * @param ids the ids
	 * @return true, if successful
	 */
	public static boolean areValidStringId(Collection<String> ids) {
		boolean res = false;
		if (!org.apache.commons.collections4.CollectionUtils.isEmpty(ids)) {
			res = true;
			for (final String id : ids) {
				if (!isValidId(id)) {
					res = false;
					break;
				}
			}
		}
		return res;
	}

	/**
	 * Are valid string id.
	 *
	 * @param ids  the ids
	 * @param size the size
	 * @return true, if successful
	 */
	public static boolean areValidStringId(Collection<String> ids, int size) {
		boolean res = false;
		if (!org.apache.commons.collections4.CollectionUtils.isEmpty(ids)) {
			res = true;
			for (final String id : ids) {
				if (!isValidId(id, size)) {
					res = false;
					break;
				}
			}
		}
		return res;
	}

	/**
	 * Checks if is valid id sgu.
	 *
	 * @param id the id
	 * @return true, if is valid id sgu
	 */
	public static boolean isValidIdSgu(String id) {
		return ConditionUtils.oneIsTrue(meetsPattern(id, IDSGU_PATTERN), ValidationUtils.isValidNifNieCif(id));
	}

	/**
	 * Checks if is valid name.
	 *
	 * @param name the name
	 * @return true, if is valid name
	 */
	public static boolean isValidName(String name) {
		return meetsPattern(StringUtils.stripAccents(name), NAME_PATTERN);
	}

	/**
	 * Checks if is valid surname.
	 *
	 * @param surname the surname
	 * @return true, if is valid name
	 */
	public static boolean isValidSurname(String surname) {
		return meetsPattern(StringUtils.stripAccents(surname), SURNAME_PATTERN);
	}

	/**
	 * Checks if is valid person name.
	 *
	 * @param name     the name
	 * @param surname1 the surname 1
	 * @param surname2 the surname 2
	 * @return true, if is valid name
	 */
	public static boolean isValidPersonName(String name, String surname1, String surname2) {
		boolean res = ConditionUtils.allAreTrue(isValidName(name), isValidSurname(surname1));
		if (ConditionUtils.allAreTrue(res, Objects.nonNull(surname2))) {
			res = isValidSurname(surname2);
		}
		return res;
	}

	/**
	 * Checks if is valid path part.
	 *
	 * @param part the part
	 * @return true, if is valid path part
	 */
	public static boolean isValidPathPart(String part) {
		return meetsPattern(part, PATH_PART_PATTERN);
	}

	/**
	 * Checks if is valid code.
	 *
	 * @param code the code
	 * @return true, if is valid code
	 */
	public static boolean isValidCode(String code) {
		return meetsPattern(code, CODE_PATTERN);
	}

	/**
	 * Checks if is valid code.
	 *
	 * @param code the code
	 * @param size the size
	 * @return true, if is valid code
	 */
	public static boolean isValidCode(String code, int size) {
		final int length = StringUtils.length(code);
		return ConditionUtils.allAreTrue((length > 0), (length <= size), meetsPattern(code, VARIABLE_CODE_PATTERN));
	}

	/**
	 * Checks if is valid thing name.
	 *
	 * @param name the name
	 * @param size the size
	 * @return true, if is valid text
	 */
	public static boolean isValidThingName(String name, int size) {
		final int length = StringUtils.length(name);
		return ConditionUtils.allAreTrue((length > 0), (length <= size),
				meetsPattern(StringUtils.stripAccents(name), THING_NAME_PATTERN));
	}

	/**
	 * Checks if is valid text.
	 *
	 * @param text the text
	 * @param size the size
	 * @return true, if is valid text
	 */
	public static boolean isValidText(String text, int size) {
		final int length = StringUtils.length(text);
		return ConditionUtils.allAreTrue((length > 0), (length <= size),
				meetsPattern(StringUtils.stripAccents(text), TEXT_PATTERN));
	}

	/**
	 * Checks if is null or valid thing name.
	 *
	 * @param text the text
	 * @param size the size
	 * @return true, if is null or valid text
	 */
	public static boolean isNullOrValidThingName(String name, int size) {
		boolean res = true;
		if (Objects.nonNull(name)) {
			res = isValidThingName(name, size);
		}
		return res;
	}

	/**
	 * Checks if is null or valid text.
	 *
	 * @param text the text
	 * @param size the size
	 * @return true, if is null or valid text
	 */
	public static boolean isNullOrValidText(String text, int size) {
		boolean res = true;
		if (Objects.nonNull(text)) {
			res = isValidText(text, size);
		}
		return res;
	}

	/**
	 * Checks if is valid cid.
	 *
	 * @param code the code
	 * @return true, if is valid cid
	 */
	public static boolean isValidCid(String code) {
		return meetsPattern(code, CID_PATTERN);
	}

	/**
	 * Checks if is valid file name.
	 *
	 * @param code the code
	 * @return true, if is valid file name
	 */
	public static boolean isValidFileName(String code) {
		return meetsPattern(code, FILE_NAME_PATTERN);
	}

	/**
	 * Checks if is valid path.
	 *
	 * @param path the path
	 * @return true, if is valid path
	 */
	public static boolean isValidPath(String path) {
		return meetsPattern(path, URL_PATH_PATTERN);
	}

	/**
	 * Checks if is valid email.
	 *
	 * @param email the email
	 * @return true, if is valid email
	 */
	public static boolean isValidEmail(String email) {
		return meetsPattern(email, EMAIL_PATTERN);
	}

	/**
	 * Checks if is valid dni nie.
	 *
	 * @param value the value
	 * @return true, if is valid dni nie
	 */
	public static boolean isValidNifNie(String value) {
		boolean res = false;
		if (!StringUtils.isAllBlank(value) && (value.length() == 9)) {
			String number = "";
			char letter;
			boolean error = false;
			if (Character.isLetter(value.charAt(0))) {
				final char kind = value.charAt(0);
				switch (kind) {
				case 'X':
					number = "0" + value.substring(1, 8);
					break;
				case 'Y':
					number = "1" + value.substring(1, 8);
					break;
				case 'Z':
					number = "2" + value.substring(1, 8);
					break;
				default:
					error = true;
					break;
				}
			} else {
				number = value.substring(0, 8);
			}
			letter = value.charAt(8);
			if ((!error && StringUtils.isNumeric(number))) {
				final int total = Integer.parseInt(number);
				final int rest = total % 23;
				final char expected = DNI_LETTERS.charAt(rest);
				res = (expected == letter);
			}
		}
		return res;
	}

	/**
	 * Checks if is valid cif.
	 *
	 * @param value the value
	 * @return true, if is valid cif
	 */
	public static boolean isValidCif(String value) {
		boolean res = false;
		if (StringUtils.length(value) == 9) {
			final char kind = value.charAt(0);
			final String number = value.substring(1, 8);
			final char control = value.charAt(8);
			if (ConditionUtils.allAreTrue((CIF_LETTERS.indexOf(kind) != -1), StringUtils.isNumeric(number))) {
				final int sumaPares = sumaPares(number);
				final int sumaImpares = sumaImpares(number);
				final int sumaTotal = sumaPares + sumaImpares;
				final int unidades = sumaTotal % 10;
				int digitoControl = 0;
				if (unidades > 0) {
					digitoControl = 10 - unidades;
				}
				final char letraControl = CONTROL_LETTERS_CIF.charAt(digitoControl);
				if (KIND_DIGIT_CIF_LETTERS.indexOf(kind) != -1) {
					res = (digitoControl == control - '0');
				} else if (KIND_LETTER_CIF_LETTERS.indexOf(kind) != -1) {
					res = (letraControl == control);
				} else {
					res = ConditionUtils.oneIsTrue((digitoControl == control - '0'), (letraControl == control));
				}
			}
		}
		return res;
	}

	/**
	 * Suma pares.
	 *
	 * @param number the number
	 * @return the int
	 */
	private static int sumaPares(String number) {
		int sumaPares = 0;
		for (int pos = 1; pos < number.length(); pos = pos + 2) {
			sumaPares = sumaPares + number.charAt(pos) - '0';
		}
		return sumaPares;
	}

	/**
	 * Suma impares.
	 *
	 * @param number the number
	 * @return the int
	 */
	private static int sumaImpares(String number) {
		int sumaImpares = 0;
		for (int pos = 0; pos < number.length(); pos = pos + 2) {
			int sumando = 2 * (number.charAt(pos) - '0');
			if (sumando > 9) {
				sumando = sumando - 9;
			}
			sumaImpares = sumaImpares + sumando;
		}
		return sumaImpares;
	}

	/**
	 * Checks if is valid nif nie cif.
	 *
	 * @param value the value
	 * @return true, if is valid nif nie cif
	 */
	public static boolean isValidNifNieCif(String value) {
		return ConditionUtils.oneIsTrue(isValidNifNie(value), isValidCif(value));
	}

	/**
	 * Checks if is valid password.
	 *
	 * @param password the password
	 * @return true, if is valid password
	 */
	public static boolean isValidPassword(String password) {
		return meetsPattern(password, WATCHWORD_PATTERN);
	}

	/**
	 * Meets pattern.
	 *
	 * @param value   the value
	 * @param pattern the pattern
	 * @return true, if successful
	 */
	public static boolean meetsPattern(String value, String pattern) {
		boolean res = false;
		if (!StringUtils.isAllBlank(value)) {
			res = value.matches(pattern);
		}
		return res;
	}

	/**
	 * Checks if is valid string.
	 *
	 * @param value the value
	 * @return true, if is valid string
	 */
	public static boolean isValidString(String value) {
		boolean res = false;
		if (!StringUtils.isAllBlank(value)) {
			res = !value.isBlank();
		}
		return res;
	}

	/**
	 * Checks if is valid http url.
	 *
	 * @param url the url
	 * @return true, if is valid http url
	 */
	public static boolean isValidHttpUrl(String url) {
		return meetsPattern(url, HTTP_PATTERN);
	}

	/**
	 * Validate locale.
	 *
	 * @param localeCode the locale code
	 * @return the locale
	 */
	public static Locale validateLocale(String localeCode) {
		Locale locale = null;
		if (meetsPattern(localeCode, LOCALE_PATTERN)) {
			locale = LocaleUtils.toLocale(localeCode.replace('-', '_'));
		}
		return locale;
	}

	/**
	 * Checks if is valid comma separated values.
	 *
	 * @param values the valies
	 * @return true, if is valid comma separated values
	 */
	public static boolean isValidCommaSeparatedValues(String values) {
		return meetsPattern(values, LIST_PATTERN);
	}

}
