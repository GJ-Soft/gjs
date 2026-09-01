package org.gjs.java.test.samples.pojos.error;

/**
 * The Class SampleAllErrorsPojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo que incumple a propósito las reglas de validación, para los casos negativos. Vive fuera del paquete pojos precisamente para que no lo recoja el escaneo que valida a los demás.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class SampleAllErrorsPojo implements Comparable<Object> {

    private long codigo;

    public SampleAllErrorsPojo() {
    }

    public long getCodigo() {
        return codigo;
    }

    public void setCodigo(long codigo) {
        this.codigo = -1;
    }

    @Override
    public int hashCode() {
        return 0;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof SampleAllErrorsPojo)) {
            return false;
        }
        final SampleAllErrorsPojo other = (SampleAllErrorsPojo) obj;
        return codigo != other.codigo;
    }

    @Override
    public int compareTo(Object o) {
        if (o == null) {
            return 1;
        }
        if (o instanceof SampleAllErrorsPojo) {
            final SampleAllErrorsPojo aux = (SampleAllErrorsPojo) o;
            if (codigo == aux.getCodigo()) {
                return -1;
            }
            if (codigo < aux.getCodigo()) {
                return 1;
            }
            return 0;
        }
        return -1;
    }

    @Override
    public String toString() {
        return null;
    }

}
