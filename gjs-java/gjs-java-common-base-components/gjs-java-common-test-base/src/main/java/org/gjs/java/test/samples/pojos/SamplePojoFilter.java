package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SamplePojoFilter.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo con una marca de activo, pensado para las pruebas de filtrado.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
public class SamplePojoFilter implements Comparable {

    private Long id;
    private String nombre;
    private Boolean activo;

    public SamplePojoFilter() {
    }

    public SamplePojoFilter(Long id, String nombre, Boolean activo) {
        this.id = id;
        this.nombre = nombre;
        this.activo = activo;
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
        if (!(obj instanceof SamplePojoFilter)) {
            return false;
        }
        final SamplePojoFilter other = (SamplePojoFilter) obj;
        return id == other.id && Objects.equals(nombre, other.nombre);
    }

    @Override
    public String toString() {
        return "SamplePojo [id=" + id + ", nombre=" + nombre + ", activo=" + activo + "]";
    }

    @Override
    public int compareTo(Object o) {
        if (o == null) {
            return -1;
        }
        if (o instanceof SamplePojoFilter) {
            final SamplePojoFilter aux = (SamplePojoFilter) o;
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
