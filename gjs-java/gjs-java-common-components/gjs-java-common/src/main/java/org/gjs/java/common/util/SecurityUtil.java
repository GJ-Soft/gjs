package org.gjs.java.common.util;

import java.nio.charset.StandardCharsets;
import java.util.Base64;
import java.util.Objects;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.exception.GjsException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class SecurityUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Función de interpretación de las cabeceras de seguridad SOAP.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class SecurityUtil {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(SecurityUtil.class);

	/**
	 * Clase no instanciable.
	 */
	private SecurityUtil() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Gets the credentials from authorization header.
	 *
	 * @param authHeader the auth header
	 * @return the credentials from authorization header
	 */
	public static String[] getCredentialsFromAuthorizationHeader(String authHeader) {
		String[] res = null;
		if (Objects.nonNull(authHeader) && authHeader.startsWith("Basic ")) {
			final String base64Credentials = authHeader.substring("Basic".length()).trim();
			try {
				// Basic username:password (base64)
				final byte[] decodedCredentials = Base64.getDecoder().decode(base64Credentials);
				final String credentials = new String(decodedCredentials, StandardCharsets.UTF_8);
				res = credentials.split(":", 2);
				if (res.length != 2) {
					throw new GjsException("Invalid header");
				}
			} catch (final Exception e) {// could not decode
				logger.error(ExceptionUtils.getStackTrace(e));
				res = null;
			}

		}
		return res;
	}

}
