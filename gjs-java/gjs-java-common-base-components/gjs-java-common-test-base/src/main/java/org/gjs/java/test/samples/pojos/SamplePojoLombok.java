package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;

/**
 * The Class SamplePojoLombok.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Como SamplePojo, pero generado entero por Lombok: accesores, constructores, builder y toString.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor
@ToString
public class SamplePojoLombok implements Comparable {

    private long id;
    private String nombre;

    @Override
    public int hashCode() {
        return Objects.hash(id, nombre);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof SamplePojoLombok)) {
            return false;
        }
        final SamplePojoLombok other = (SamplePojoLombok) obj;
        return id == other.id && Objects.equals(nombre, other.nombre);
    }

    @Override
    public int compareTo(Object o) {
        if (o == null) {
            return -1;
        }
        if (o instanceof SamplePojoLombok) {
            final SamplePojoLombok aux = (SamplePojoLombok) o;
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
