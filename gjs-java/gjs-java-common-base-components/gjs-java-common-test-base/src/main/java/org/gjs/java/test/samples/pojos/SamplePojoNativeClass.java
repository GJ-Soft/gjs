package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SamplePojoNativeClass.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Como SamplePojo, con el identificador en su clase envolvente ( Long ) en lugar de primitivo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
public class SamplePojoNativeClass implements Comparable {

    private Long id;
    private String nombre;

    public SamplePojoNativeClass() {
    }

    public SamplePojoNativeClass(Long id, String nombre) {
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
        if (obj == null) {
            return false;
        }
        if (!(obj instanceof SamplePojoNativeClass)) {
           return false;
        }
        final SamplePojoNativeClass other = (SamplePojoNativeClass) obj;
        return id == other.id && Objects.equals(nombre, other.nombre);
    }

    @Override
    public String toString() {
        return "SamplePojoNativeClass [id=" + id + ", nombre=" + nombre + "]";
    }

    @Override
    public int compareTo(Object o) {
        if (o == null) {
            return -1;
        }
        if (o instanceof SamplePojoNativeClass) {
            final SamplePojoNativeClass aux = (SamplePojoNativeClass) o;
            int res = -1;
            if (id == null) {
                if (aux.getId() == null) {
                    res = 0;
                } else {
                    res = 1;
                }
            } else if (aux.getId() == null) {
                res = -1;
            } else if (id == aux.getId()) {
                res = 0;
            } else if (id < aux.getId()) {
                res = -1;
            }
            if (res == 0) {
                res = (nombre != null) ? nombre.compareTo(aux.getNombre()) : ((aux.getNombre() == null) ? 0 : 1);
            }
            return res;
        }
        return -1;
    }
}
