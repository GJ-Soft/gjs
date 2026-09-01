package org.gjs.java.test.samples.pojos;

import java.math.BigDecimal;
import java.util.Arrays;
import java.util.Date;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleManagedArraysPojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo con arrays de tipos gestionados: cadenas, fechas y decimales.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleManagedArraysPojo {

    private String[] strings;
    private Date[] dates;
    private BigDecimal[] bigDecimals;

    public SampleManagedArraysPojo() {
    }

    public SampleManagedArraysPojo(String[] strings, Date[] dates, BigDecimal[] bigDecimals) {
        this.strings = strings;
        this.dates = dates;
        this.bigDecimals = bigDecimals;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + Arrays.hashCode(bigDecimals);
        result = prime * result + Arrays.hashCode(dates);
        result = prime * result + Arrays.hashCode(strings);
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (!(obj instanceof SampleManagedArraysPojo)) {
            return false;
        }
        final SampleManagedArraysPojo other = (SampleManagedArraysPojo) obj;
        return Arrays.equals(bigDecimals, other.bigDecimals) && Arrays.equals(dates, other.dates)
                && Arrays.equals(strings, other.strings);
    }

    @Override
    public String toString() {
        return "SampleManagedArraysPojo [strings=" + Arrays.toString(strings) + ", dates=" + Arrays.toString(dates)
                + ", bigDecimals=" + Arrays.toString(bigDecimals) + "]";
    }

}
