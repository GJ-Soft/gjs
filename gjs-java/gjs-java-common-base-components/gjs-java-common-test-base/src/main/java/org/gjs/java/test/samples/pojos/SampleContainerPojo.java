package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleContainerPojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo que contiene otro pojo, para las pruebas de anidamiento.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
public class SampleContainerPojo implements Comparable {

    private long id;
    private String nombre;
    private SamplePojo samplePojo;

    public SampleContainerPojo() {
    }

    public SampleContainerPojo(long id, String nombre, SamplePojo samplePojo) {
        this.id = id;
        this.nombre = nombre;
        this.samplePojo = samplePojo;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, nombre, samplePojo);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof SampleContainerPojo)) {
            return false;
        }
        final SampleContainerPojo other = (SampleContainerPojo) obj;
        return id == other.id && Objects.equals(nombre, other.nombre);
    }

    @Override
    public String toString() {
        return "SampleContainerPojo [id=" + id + ", nombre=" + nombre + ", samplePojo=" + samplePojo + "]";
    }

    @Override
    public int compareTo(Object o) {
        if (o == null) {
            return -1;
        }
        if (o instanceof SampleContainerPojo) {
            final SampleContainerPojo aux = (SampleContainerPojo) o;
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
