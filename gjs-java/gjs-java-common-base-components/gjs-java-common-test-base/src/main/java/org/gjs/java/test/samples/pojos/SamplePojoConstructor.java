package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SamplePojoConstructor.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Como SamplePojo, para las pruebas centradas en sus constructores.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
public class SamplePojoConstructor implements Comparable {

    private long id;
    private String nombre;

    public SamplePojoConstructor() {
    }

    public SamplePojoConstructor(long id, String nombre) {
        this.id = id;
        this.nombre = nombre;
    }

    public SamplePojoConstructor(SamplePojo obj) {
        if (Objects.nonNull(obj)) {
            this.id = obj.getId();
            this.nombre = obj.getNombre();
        }
    }

    public SamplePojoConstructor(SamplePojoConstructor obj) {
        if (Objects.nonNull(obj)) {
            this.id = obj.getId();
            this.nombre = obj.getNombre();
        }
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
        if (!(obj instanceof SamplePojoConstructor)) {
            return false;
        }
        final SamplePojoConstructor other = (SamplePojoConstructor) obj;
        return id == other.id && Objects.equals(nombre, other.nombre);
    }

    @Override
    public String toString() {
        return "SamplePojoConstructor [id=" + id + ", nombre=" + nombre + "]";
    }

    @Override
    public int compareTo(Object o) {
        if (o == null) {
            return -1;
        }
        if (o instanceof SamplePojoConstructor) {
            final SamplePojoConstructor aux = (SamplePojoConstructor) o;
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
