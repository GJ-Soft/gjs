package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleDerivedPojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo derivado de SamplePojo, para las pruebas de herencia.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleDerivedPojo extends SamplePojo {

    private boolean activo;
    private char codigo;

    public SampleDerivedPojo() {
    }

    public SampleDerivedPojo(long id, String nombre, char codigo, boolean activo) {
        super(id, nombre);
        this.codigo = codigo;
        this.activo = activo;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), codigo, activo);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (!(obj instanceof SampleDerivedPojo)) {
           return false;
        }
        final SampleDerivedPojo other = (SampleDerivedPojo) obj;
        return super.equals(obj) && (codigo == other.codigo) && (activo == other.activo);
    }

    @Override
    public String toString() {
        return "SampleDerivedPojo [" + super.toString() + ", codigo=" + codigo + ", activo=" + activo + "]";
    }

    @Override
    public int compareTo(Object o) {
        if (o == null) {
            return -1;
        }
        if (o instanceof SampleDerivedPojo) {
            final SampleDerivedPojo aux = (SampleDerivedPojo) o;
            int res = super.compareTo(aux);
            if (res == 0) {
                res = (codigo < aux.codigo) ? -1 : ((codigo > aux.codigo) ? -1 : 0);
                if (res == 0) {
                    res = (!activo && aux.activo) ? -1 : ((activo && !aux.activo) ? -1 : 0);
                }
            }
            return res;
        }
        return -1;
    }
}
