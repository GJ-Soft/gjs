package org.gjs.java.common.dto;

import java.io.Serializable;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonInclude;

/**
 * The Class BaseDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase base para ser extendida por todos los DTO.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@SuppressWarnings("serial")
@JsonInclude(JsonInclude.Include.NON_EMPTY)
public class BaseDto implements Serializable {

	/**
	 * Checks if is valid.
	 *
	 * @return true, if is valid
	 */
	// @CopiarAtributosConf(ignorar = true)
	@JsonIgnore
	public boolean isValid() {
		return true;
	}

}
