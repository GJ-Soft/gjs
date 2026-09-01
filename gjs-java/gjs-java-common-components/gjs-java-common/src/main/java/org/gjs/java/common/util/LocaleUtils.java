package org.gjs.java.common.util;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Locale;
import java.util.Map;
import java.util.Objects;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.commons.collections4.CollectionUtils;
import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.dto.CodedEntityDto;

/**
 * The Class LocaleUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Funciones generales de serialización/deserialización JSON.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class LocaleUtils {

	/** The map countries. */
	private static Map<String, CodedEntityDto> mapCountries;

	/** The map languages. */
	private static Map<String, CodedEntityDto> mapLanguages;

	static {
		mapCountries = new ConcurrentHashMap<>();
		mapLanguages = new ConcurrentHashMap<>();
		for (final Locale locale : Locale.getAvailableLocales()) {
			if (!StringUtils.isAllBlank(locale.getCountry())) {
				final CodedEntityDto countryDto = new CodedEntityDto(locale.getCountry(), locale.getDisplayCountry());
				mapCountries.put(locale.getCountry().toUpperCase(Locale.getDefault()), countryDto);
			}
			final CodedEntityDto languageDto = new CodedEntityDto(locale.toLanguageTag(), locale.getDisplayLanguage());
			mapLanguages.put(locale.toLanguageTag(), languageDto);
		}
	}

	/**
	 * Clase no instanciable.
	 */
	private LocaleUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Gets the country name.
	 *
	 * @param country code the country code
	 * @return the country name
	 */
	public static String getCountryName(String country) {
		String code = null;
		if (Objects.nonNull(country)) {
			final CodedEntityDto dto = mapCountries.get(country.toUpperCase(Locale.getDefault()));
			if (Objects.nonNull(dto)) {
				code = dto.getName();
			}
		}
		return code;
	}

	/**
	 * Gets the countries.
	 *
	 * @return the countries
	 */
	public static Collection<CodedEntityDto> getCountries() {
		return mapCountries.values();
	}

	/**
	 * Gets the languages.
	 *
	 * @return the languages
	 */
	public static Collection<CodedEntityDto> getLanguages() {
		return mapLanguages.values();
	}

	/**
	 * Gets the countries.
	 *
	 * @param setAllowed the set permitidos
	 * @return the countries
	 */
	public static Collection<CodedEntityDto> getCountries(Set<String> setAllowed) {
		return filterValues(mapCountries.values(), setAllowed);
	}

	/**
	 * Gets the languages.
	 *
	 * @param setAllowed the set permitidos
	 * @return the languages
	 */
	public static Collection<CodedEntityDto> getLanguages(Set<String> setAllowed) {
		return filterValues(mapLanguages.values(), setAllowed);
	}

	/**
	 * Filter values.
	 *
	 * @param values     the values
	 * @param setAllowed the set allowed
	 * @return the collection
	 */
	private static Collection<CodedEntityDto> filterValues(Collection<CodedEntityDto> values, Set<String> setAllowed) {
		if (CollectionUtils.isEmpty(setAllowed)) {
			return values;
		}
		final Collection<CodedEntityDto> list = new ArrayList<>();
		for (final CodedEntityDto dto : values) {
			if (setAllowed.contains(dto.getCode())) {
				list.add(dto);
			}
		}
		return list;
	}

	/**
	 * Checks if is valid country.
	 *
	 * @param country the country
	 * @return true, if is valid country
	 */
	public static boolean isValidCountry(String country) {
		boolean res = false;
		if (Objects.nonNull(country)) {
			res = mapCountries.containsKey(country.toUpperCase(Locale.getDefault()));
		}
		return res;
	}

	/**
	 * Checks if is valid language.
	 *
	 * @param language the language
	 * @return true, if is valid language
	 */
	public static boolean isValidLanguage(String language) {
		boolean res = false;
		if (Objects.nonNull(language)) {
			res = mapLanguages.containsKey(language);
		}
		return res;
	}

}
