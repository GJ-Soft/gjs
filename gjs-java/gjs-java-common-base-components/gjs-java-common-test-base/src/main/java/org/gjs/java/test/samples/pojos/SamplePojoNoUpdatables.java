package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SamplePojoNoUpdatables.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo con un campo estático y otro final, que no se pueden actualizar.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
public class SamplePojoNoUpdatables implements Comparable {

    public static final String staticValue = "XXXXX";
    final Long finalValue = Long.valueOf(1);
    private long id;
    private String nombre;

    public SamplePojoNoUpdatables() {
    }

    public SamplePojoNoUpdatables(long id, String nombre) {
        this.id = id;
        this.nombre = nombre;
    }

    // public SamplePojo(SamplePojo obj) {
    // this.id = obj.getId();
    // this.nombre = obj.getNombre();
    // }

    @Override
    public int hashCode() {
        return Objects.hash(id, nombre);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof SamplePojoNoUpdatables)) {
            return false;
        }
        final SamplePojoNoUpdatables other = (SamplePojoNoUpdatables) obj;
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
        if (o instanceof SamplePojoNoUpdatables) {
            final SamplePojoNoUpdatables aux = (SamplePojoNoUpdatables) o;
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
