package org.gjs.java.test.sample.model;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleEntityWhitoutIdAnnotation.
 *
 * Clase de datos de ejemplo de la librería Gjs
 *
 * Entidad de ejemplo con campo id pero sin la anotación que lo marca como clave, para los casos negativos del envoltorio de repositorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
@Entity
public class SampleEntityWhitoutIdAnnotation {

	@Column
	private long id;

	@Column
	private String nombre;

	@Column
	private Boolean activo;

	public SampleEntityWhitoutIdAnnotation() {
	}

}
