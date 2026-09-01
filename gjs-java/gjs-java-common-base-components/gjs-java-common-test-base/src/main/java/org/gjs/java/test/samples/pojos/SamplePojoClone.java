package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SamplePojoClone.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Gemelo de SamplePojo, para comparar dos clases de igual forma y distinto tipo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
public class SamplePojoClone implements Comparable {

    private long id;
    private String nombre;

    public SamplePojoClone() {
    }

    public SamplePojoClone(long id, String nombre) {
        this.id = id;
        this.nombre = nombre;
    }

    @Override
    public SamplePojoClone clone() {
        return new SamplePojoClone(id, nombre);
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
        if (!(obj instanceof SamplePojoClone)) {
           return false;
        }
        final SamplePojoClone other = (SamplePojoClone) obj;
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
        if (o instanceof SamplePojoClone) {
            final SamplePojoClone aux = (SamplePojoClone) o;
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
