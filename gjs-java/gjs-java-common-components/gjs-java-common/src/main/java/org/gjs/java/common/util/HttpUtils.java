package org.gjs.java.common.util;

import java.util.Objects;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class NormalizationUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Funciones auxiliares de formateo de diferentes tipos de datos.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class HttpUtils {

	/**
	 * Clase no instanciable.
	 */
	private HttpUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Format endpoint.
	 *
	 * @param endpoint    the endpoint
	 * @param projectName the project name
	 * @return the string
	 */
	public static String formatEndpoint(String endpoint, String projectName) {
		String formatted = endpoint;
		if (Objects.nonNull(formatted)) {
			formatted = formatted.replace("{", "").replace("}", "").replace(".html", "");
			if (!formatted.startsWith("/")) {
				formatted = String.format("/%s", formatted);
			}
			if (!StringUtils.isAllBlank(projectName)) {
				final String prefix = String.format("/%s", projectName);
				if (!formatted.startsWith(prefix)) {
					formatted = String.format("%s%s", prefix, formatted);
				}
			}
		}
		return formatted;
	}

}
