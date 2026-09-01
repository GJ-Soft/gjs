package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import org.apache.commons.lang3.ObjectUtils;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleStringIdPojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo con el identificador de tipo cadena.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
public class SampleStringIdPojo implements Comparable {

	private String id;
	private String nombre;

	public SampleStringIdPojo() {
	}

	public SampleStringIdPojo(String id, String nombre) {
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
		if (!(obj instanceof SampleStringIdPojo)) {
			return false;
		}
		final SampleStringIdPojo other = (SampleStringIdPojo) obj;
		return Objects.equals(id, other.id) && Objects.equals(nombre, other.nombre);
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
		int res = -1;
		if (o instanceof SampleStringIdPojo) {
			final SampleStringIdPojo aux = (SampleStringIdPojo) o;
			res = ObjectUtils.compare(id, aux.getId());
			if (res == 0) {
				res = ObjectUtils.compare(nombre, aux.getNombre());
			}
		}
		return res;
	}
}
