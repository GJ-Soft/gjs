package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleContainerWithRenamePojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Como SampleContainerPojo, pero con el campo contenido nombrado distinto que
 * su tipo, para probar la correspondencia por nombre.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
public class SampleContainerWithRenamePojo implements Comparable {

	private long id;
	private String nombre;
	private SamplePojo data;

	public SampleContainerWithRenamePojo() {
	}

	public SampleContainerWithRenamePojo(long id, String nombre, SamplePojo samplePojo) {
		this.id = id;
		this.nombre = nombre;
		this.data = samplePojo;
	}

	@Override
	public int hashCode() {
		return Objects.hash(id, nombre, data);
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (!(obj instanceof SampleContainerWithRenamePojo)) {
			return false;
		}
		final SampleContainerWithRenamePojo other = (SampleContainerWithRenamePojo) obj;
		return id == other.id && Objects.equals(nombre, other.nombre) && Objects.equals(data, other.data);
	}

	@Override
	public String toString() {
		return "SampleContainerPojo [id=" + id + ", nombre=" + nombre + ", data=" + data + "]";
	}

	@Override
	public int compareTo(Object o) {
		if (o == null) {
			return -1;
		}
		if (o instanceof SampleContainerWithRenamePojo) {
			final SampleContainerWithRenamePojo aux = (SampleContainerWithRenamePojo) o;
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
