package org.gjs.java.common.constant;

/**
 * The Class CommonErrors.
 *
 * Clase de constantes de la librería Gjs
 *
 * Códigos de error comunes, con el formato área-número: autorización, configuración, seguridad, validación, operativa y comunicaciones.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class CommonErrors {

	public static final String ERROR_SEMI0000 = "semi-0000"; // Error desconocido / por defecto

	public static final String ERROR_AUTH0000 = "auth-0000"; // El usuario no tiene autorización

	public static final String ERROR_CONF0000 = "conf-0000"; // La configuracion es incorrecta

	public static final String ERROR_SEGU0000 = "segu-0000"; // Error de seguridad

	public static final String ERROR_VALI0000 = "vali-0000"; // Los parámetros recibidos son incorrectos
	public static final String ERROR_VALI0001 = "vali-0001"; // El campo {0} no puede ser nulo

	public static final String ERROR_OPER0000 = "oper-0000"; // Se ha producido un error operativo

	public static final String ERROR_COMM0000 = "comm-0000"; // Se ha producido un error de comunicaciones

	public static final String ERROR_BBDD0000 = "bbdd-0000"; // Se ha producido un error de base de datos

	public static final String ERROR_TECH0000 = "tech-0000"; // Error tecnico
	public static final String ERROR_TECH0001 = "tech-0001"; // Se ha lanzado una respuesta con status y/o mensaje nulo

	private CommonErrors() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

}
