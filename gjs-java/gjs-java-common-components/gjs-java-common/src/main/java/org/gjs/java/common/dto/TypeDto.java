package org.gjs.java.common.dto;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class TypeDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para almacenar los datos de un tipo genérico de cualquier cosa.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
public class TypeDto extends BaseDto {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = -4211879294171610447L;

	/** The nombre. */
	private String nombre;

	/** The descripcion. */
	private String descripcion;

	/** The valor. */
	@JsonProperty(required = false)
	private Integer valor;

	/**
	 * Instantiates a new tipo dto.
	 */
	public TypeDto() {
		// No hace nada
	}

	/**
	 * Instantiates a new tipo dto.
	 *
	 * @param nombre      the nombre
	 * @param valor       the valor
	 * @param descripcion the descripcion
	 */
	public TypeDto(String nombre, Integer valor, String descripcion) {
		this.nombre = nombre;
		this.descripcion = descripcion;
		this.valor = valor;
	}

	/**
	 * Instantiates a new tipo dto.
	 *
	 * @param nombre      the nombre
	 * @param descripcion the descripcion
	 */
	public TypeDto(String nombre, String descripcion) {
		this.nombre = nombre;
		this.descripcion = descripcion;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("nombre", nombre)
				.append("valor", valor).append("descripcion", descripcion).toString();
	}

}
