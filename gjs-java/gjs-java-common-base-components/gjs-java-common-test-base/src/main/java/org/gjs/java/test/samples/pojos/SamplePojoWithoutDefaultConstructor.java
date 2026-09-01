package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SamplePojoWithoutDefaultConstructor.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo sin constructor por defecto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
public class SamplePojoWithoutDefaultConstructor implements Comparable {

    private long id;
    private String nombre;

    public SamplePojoWithoutDefaultConstructor(long id, String nombre) {
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
        if (!(obj instanceof SamplePojoWithoutDefaultConstructor)) {
            return false;
        }
        final SamplePojoWithoutDefaultConstructor other = (SamplePojoWithoutDefaultConstructor) obj;
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
        if (o instanceof SamplePojoWithoutDefaultConstructor) {
            final SamplePojoWithoutDefaultConstructor aux = (SamplePojoWithoutDefaultConstructor) o;
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
