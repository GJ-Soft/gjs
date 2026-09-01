package org.gjs.java.test.samples.pojos;

import java.math.BigDecimal;
import java.util.Date;
import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

// NOTA: @Getter y @Setter generan nombres diferentes de los que se generan segun
// el estandar JEE cuando sólo hay una minúscula inicial
/**
 * The Class SampleAllTypesPojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo con un campo de cada tipo, primitivo y envuelto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleAllTypesPojo {

    private short siVal;
    private int intVal;
    private long lonVal;
    private char carVal;
    private double douVal;
    private float floVal;
    private Boolean obVal;
    private Integer oiVal;
    private Short osiVal;
    private Long olVal;
    private Character ocVal;
    private Double odVal;
    private Float ofVal;
    private String strVal;
    private BigDecimal decVal;
    private Date datVal;
    private byte byVal;
    private boolean boolVal;

    public SampleAllTypesPojo() {
    }

    public SampleAllTypesPojo(boolean boolVal, short siVal, int intVal, long lonVal, char carVal, double douVal,
            float floVal, byte byVal) {
        this.boolVal = boolVal;
        this.siVal = siVal;
        this.intVal = intVal;
        this.lonVal = lonVal;
        this.carVal = carVal;
        this.douVal = douVal;
        this.floVal = floVal;
        this.byVal = byVal;
    }

    public SampleAllTypesPojo(Boolean obVal, Integer oiVal, Long olVal, Character ocVal, Double odVal, Float ofVal,
            String strVal, BigDecimal decVal, Date datVal, Short osiVal) {
        this.obVal = obVal;
        this.oiVal = oiVal;
        this.olVal = olVal;
        this.ocVal = ocVal;
        this.odVal = odVal;
        this.ofVal = ofVal;
        this.strVal = strVal;
        this.decVal = decVal;
        this.datVal = datVal;
        this.osiVal = osiVal;
    }

    public SampleAllTypesPojo(boolean boolVal, short siVal, int intVal, long lonVal, char carVal, double douVal,
            float floVal, Boolean obVal, Integer oiVal, Long olVal, Character ocVal, Double odVal, Float ofVal,
            String strVal, BigDecimal decVal, Date datVal, byte byVal, Short osiVal) {
        this.boolVal = boolVal;
        this.siVal = siVal;
        this.intVal = intVal;
        this.lonVal = lonVal;
        this.carVal = carVal;
        this.douVal = douVal;
        this.floVal = floVal;
        this.obVal = obVal;
        this.oiVal = oiVal;
        this.olVal = olVal;
        this.ocVal = ocVal;
        this.odVal = odVal;
        this.ofVal = ofVal;
        this.strVal = strVal;
        this.decVal = decVal;
        this.datVal = datVal;
        this.byVal = byVal;
        this.osiVal = osiVal;
    }

    @Override
    public int hashCode() {
        return Objects.hash(boolVal, byVal, carVal, douVal, datVal, decVal, floVal, intVal, lonVal, obVal, ocVal, odVal,
                ofVal, oiVal, olVal, strVal, siVal);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof SampleAllTypesPojo)) {
            return false;
        }
        final SampleAllTypesPojo other = (SampleAllTypesPojo) obj;
        return boolVal == other.boolVal && byVal == other.byVal && carVal == other.carVal
                && Double.doubleToLongBits(douVal) == Double.doubleToLongBits(other.douVal)
                && Objects.equals(datVal, other.datVal) && Objects.equals(decVal, other.decVal)
                && Float.floatToIntBits(floVal) == Float.floatToIntBits(other.floVal) && intVal == other.intVal
                && lonVal == other.lonVal && Objects.equals(obVal, other.obVal) && Objects.equals(ocVal, other.ocVal)
                && Objects.equals(odVal, other.odVal) && Objects.equals(ofVal, other.ofVal)
                && Objects.equals(oiVal, other.oiVal) && Objects.equals(olVal, other.olVal)
                && Objects.equals(strVal, other.strVal) && siVal == other.siVal;
    }

    @Override
    public String toString() {
        return "SampleAllTypesPojo [boolVal=" + boolVal + ", siVal=" + siVal + ", intVal=" + intVal + ", lonVal="
                + lonVal + ", carVal=" + carVal + ", douVal=" + douVal + ", floVal=" + floVal + ", obVal=" + obVal
                + ", oiVal=" + oiVal + ", olVal=" + olVal + ", ocVal=" + ocVal + ", odVal=" + odVal + ", ofVal=" + ofVal
                + ", strVal=" + strVal + ", decVal=" + decVal + ", datVal=" + datVal + ", byVal=" + byVal + "]";
    }

}
