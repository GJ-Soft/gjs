package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import org.gjs.java.test.samples.annotation.SampleAnnotation;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleAnnotationClass.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo con una anotación a nivel de clase.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
@SampleAnnotation
public class SampleAnnotationClass implements Comparable<Object> {

	private long id;
	private String nombre;

	public SampleAnnotationClass() {
	}

	public SampleAnnotationClass(long id, String nombre) {
		this.id = id;
		this.nombre = nombre;
	}

	@Override
	public int hashCode() {
		return Objects.hash(id, nombre);
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (!(obj instanceof SampleAnnotationClass)) {
			return false;
		}
		final SampleAnnotationClass other = (SampleAnnotationClass) obj;
		return id == other.id && Objects.equals(nombre, other.nombre);
	}

	@Override
	public String toString() {
		return "SamplePojo [id=" + id + ", nombre=" + nombre + "]";
	}

	@Override
	public int compareTo(Object o) {
		if (o == null) {
			return -1;
		}
		if (o instanceof SampleAnnotationClass) {
			final SampleAnnotationClass aux = (SampleAnnotationClass) o;
			if (id == aux.getId()) {
				return (nombre != null) ? nombre.compareTo(aux.getNombre()) : ((aux.getNombre() == null) ? 0 : 1);
			}
			if (id < aux.getId()) {
				return -1;
			}
			return 1;
		}
		return -1;
	}
}
