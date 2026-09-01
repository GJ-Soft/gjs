package org.gjs.java.common.dto;

import org.gjs.java.common.singleton.GlobalBundleManager;

/**
 * The Class ErrorValidacionDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase que contiene la información de un error de validación.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class ValidationErrorDto extends ErrorDto {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = -8286542567656189386L;

	/**
	 * Instantiates a new error validacion dto.
	 */
	public ValidationErrorDto() {
	}

	/**
	 * Instantiates a new error validacion dto.
	 *
	 * @param code the code
	 */
	public ValidationErrorDto(String code) {
		super(code);
	}

	/**
	 * Instantiates a new error validacion dto.
	 *
	 * @param code      the code
	 * @param parameter the parameter
	 */
	public ValidationErrorDto(String code, String parameter) {
		super(code, GlobalBundleManager.getSafetyErrorMessage(code, parameter));
	}

	/**
	 * Instantiates a new error validacion dto.
	 *
	 * @param code      the code
	 * @param parameter the parameter
	 * @param value     the value
	 */
	public ValidationErrorDto(String code, String parameter, String value) {
		super(code, GlobalBundleManager.getSafetyErrorMessage(code, parameter, value));
	}

}
