package org.gjs.java.test.samples.pojos;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleWrapperPojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo que envuelve a otro pojo como único campo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("rawtypes")
@Getter
@Setter
public class SampleWrapperPojo implements Comparable {

    private SamplePojo pojo;

    public SampleWrapperPojo() {
    }

    public SampleWrapperPojo(long id, String nombre) {
        pojo = new SamplePojo(id, nombre);
    }

    public SampleWrapperPojo(SamplePojo pojo) {
        this.pojo = pojo;
    }

    @Override
    public int hashCode() {
        return Objects.hash(pojo);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof SampleWrapperPojo)) {
            return false;
        }
        final SampleWrapperPojo other = (SampleWrapperPojo) obj;
        return (compareTo(other) == 0);
    }

    @Override
    public String toString() {
        return "SampleWrappedPojo [pojo=" + pojo + "]";
    }

    @Override
    public int compareTo(Object o) {
        if (o == null) {
            return -1;
        }
        if (o instanceof SampleWrapperPojo) {
            final SampleWrapperPojo aux = (SampleWrapperPojo) o;
            if (pojo == null) {
                if (aux.getPojo() == null) {
                    return 0;
                }
                return 1;
            }
            return pojo.compareTo(aux.getPojo());
        }
        return -1;
    }
}
