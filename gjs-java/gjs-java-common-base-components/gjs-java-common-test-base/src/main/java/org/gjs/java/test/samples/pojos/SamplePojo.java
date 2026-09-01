package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SamplePojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo básico con identificador y nombre. Es el ejemplo de referencia del que parten los demás.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
public class SamplePojo implements Comparable {

    private long id;
    private String nombre;

    public SamplePojo() {
    }

    public SamplePojo(long id, String nombre) {
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
        if (!(obj instanceof SamplePojo)) {
            return false;
        }
        final SamplePojo other = (SamplePojo) obj;
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
        if (o instanceof SamplePojo) {
            final SamplePojo aux = (SamplePojo) o;
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
