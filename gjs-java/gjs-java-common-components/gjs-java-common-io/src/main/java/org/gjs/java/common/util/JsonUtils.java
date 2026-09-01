package org.gjs.java.common.util;

import java.io.IOException;
import java.util.Objects;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.fasterxml.jackson.annotation.JsonInclude;

import tools.jackson.databind.DeserializationFeature;
import tools.jackson.databind.ObjectMapper;
import tools.jackson.databind.ObjectReader;
import tools.jackson.databind.json.JsonMapper;

/**
 * The Class JsonUtil.
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
public final class JsonUtils {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(JsonUtils.class);

	/**
	 * Clase no instanciable.
	 */
	private JsonUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Json to object.
	 *
	 * @param json  the json
	 * @param clazz the clazz
	 * @return the object
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	public static Object jsonToObject(String json, Class<?> clazz) throws IOException {
		if (StringUtils.isAllBlank(json)) {
			return null;
		}
		final ObjectMapper objectMapper = JsonMapper.builder().build();
		// objectMapper.registeredModules().add(new JavaTimeModule());
		// objectMapper.setSerializationInclusion(JsonInclude.Include.NON_NULL);
		final ObjectReader reader = objectMapper.readerFor(clazz);
		reader.without(DeserializationFeature.ACCEPT_EMPTY_STRING_AS_NULL_OBJECT);
		// Si se ja serializado con writeValueAsString los string nulos los habrá puesto
		// a "null"
		// json = json.replace("\"null\"", "\"\"");
		return reader.readValue(json);
		// return objectMapper.readValue(json, clazz);
	}

	/**
	 * Object to json.
	 *
	 * @param object the object
	 * @return the string
	 * @throws JsonProcessingException the json processing exception
	 */
	public static String objectToJson(Object object) {
		if (Objects.isNull(object)) {
			return null;
		}
		final ObjectMapper objectMapper = JsonMapper.builder()
				.changeDefaultPropertyInclusion(incl -> incl.withValueInclusion(JsonInclude.Include.ALWAYS))
				.changeDefaultPropertyInclusion(incl -> incl.withValueInclusion(JsonInclude.Include.NON_NULL)).build();
		// objectMapper.registeredModules().add(new JavaTimeModule());
		return objectMapper.writeValueAsString(object);
	}

	/**
	 * Safe object to json.
	 *
	 * @param object the object
	 * @return the string
	 */
	public static String safeObjectToJson(Object object) {
		String res = null;
		try {
			res = objectToJson(object);
		} catch (final Exception e) {
			logger.warn(e.getMessage());
		}
		return res;
	}

	/**
	 * Safe json to object.
	 *
	 * @param json  the json
	 * @param clazz the clazz
	 * @return the object
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	public static Object safeJsonToObject(String json, Class<?> clazz) {
		Object res = null;
		try {
			res = jsonToObject(json, clazz);
		} catch (final IOException e) {
			logger.warn(e.getMessage());
		}
		return res;
	}

}
