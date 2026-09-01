package org.gjs.java.test.samples.dto;

import java.util.Date;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleWithFKEntityDto.
 *
 * Clase de datos de ejemplo de la librería Gjs
 *
 * DTO con una referencia a otro DTO, para las pruebas que necesitan una clave ajena.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleWithFKEntityDto {

	private Long id;
	protected String nombre;
	protected String descripcion;
	private Date fechaAlta;
	private Date fechaBaja;
	private Boolean activo;
	private SampleEntityDto sample;

	public SampleWithFKEntityDto() {
	}

	@Override
	public String toString() {
		return "SampleWithFKEntityDto [" + "id=" + id + ", activo=" + activo + ", descripcion='" + descripcion + '\''
				+ ", fechaAlta=" + fechaAlta + ", fechaBaja=" + fechaBaja + ", nombre='" + nombre + '\'' + ", sample="
				+ sample + "]";
	}
}
