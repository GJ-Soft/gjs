package org.gjs.java.test.samples.dto;

import java.util.Date;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleEntityDto.
 *
 * Clase de datos de ejemplo de la librería Gjs
 *
 * DTO con los campos habituales de una entidad: identificador, nombre, descripción, fechas de alta y baja y marca de activo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleEntityDto {

	private Long id;
	private String nombre;
	private String descripcion;
	private Date fechaAlta;
	private Date fechaBaja;
	private Boolean activo;

	public SampleEntityDto() {
	}

	@Override
	public String toString() {
		return "SampleEntityDto [ id=" + id + ", nombre=" + nombre + ", descripcion=" + descripcion + ", fechaAlta="
				+ fechaAlta + ", fechaBaja=" + fechaBaja + ", activo=" + activo + "]";
	}

}
