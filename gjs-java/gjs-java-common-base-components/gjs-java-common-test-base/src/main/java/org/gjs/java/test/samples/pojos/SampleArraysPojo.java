package org.gjs.java.test.samples.pojos;

import java.math.BigDecimal;
import java.util.Arrays;
import java.util.Date;

import lombok.Getter;
import lombok.Setter;

// NOTA: @Getter y @Setter generan nombres diferentes de los que se generan segun
// el estandar JEE cuando sólo hay una minúscula inicial
/**
 * The Class SampleArraysPojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo con un array de cada tipo primitivo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleArraysPojo {

    private boolean[] boolVal;
    private short[] siVal;
    private int[] intVal;
    private long[] lonVal;
    private char[] carVal;
    private double[] douVal;
    private float[] floVal;
    private Boolean[] obVal;
    private Short[] osiVal;
    private Integer[] oiVal;
    private Long[] olVal;
    private Character[] ocVal;
    private Double[] odVal;
    private Float[] ofVal;
    private String[] strVal;
    private BigDecimal[] decVal;
    private Date[] datVal;
    private byte[] byVal;
    private Byte[] obyVal;

    public SampleArraysPojo() {
    }

    public SampleArraysPojo(boolean[] boolVal, short[] siVal, int[] intVal, long[] lonVal, char[] carVal,
            double[] douVal, float[] floVal, Boolean[] obVal, Short[] osiVal, Integer[] oiVal, Long[] olVal,
            Character[] ocVal, Double[] odVal, Float[] ofVal, String[] strVal, BigDecimal[] decVal, Date[] datVal,
            byte[] byVal, Byte[] obyVal) {
        this.boolVal = boolVal;
        this.siVal = siVal;
        this.intVal = intVal;
        this.lonVal = lonVal;
        this.carVal = carVal;
        this.douVal = douVal;
        this.floVal = floVal;
        this.obVal = obVal;
        this.osiVal = osiVal;
        this.oiVal = oiVal;
        this.olVal = olVal;
        this.ocVal = ocVal;
        this.odVal = odVal;
        this.ofVal = ofVal;
        this.strVal = strVal;
        this.decVal = decVal;
        this.datVal = datVal;
        this.byVal = byVal;
        this.obyVal = obyVal;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + Arrays.hashCode(boolVal);
        result = prime * result + Arrays.hashCode(byVal);
        result = prime * result + Arrays.hashCode(carVal);
        result = prime * result + Arrays.hashCode(douVal);
        result = prime * result + Arrays.hashCode(datVal);
        result = prime * result + Arrays.hashCode(decVal);
        result = prime * result + Arrays.hashCode(floVal);
        result = prime * result + Arrays.hashCode(intVal);
        result = prime * result + Arrays.hashCode(lonVal);
        result = prime * result + Arrays.hashCode(obVal);
        result = prime * result + Arrays.hashCode(obyVal);
        result = prime * result + Arrays.hashCode(ocVal);
        result = prime * result + Arrays.hashCode(odVal);
        result = prime * result + Arrays.hashCode(ofVal);
        result = prime * result + Arrays.hashCode(oiVal);
        result = prime * result + Arrays.hashCode(olVal);
        result = prime * result + Arrays.hashCode(osiVal);
        result = prime * result + Arrays.hashCode(strVal);
        result = prime * result + Arrays.hashCode(siVal);
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof SampleArraysPojo)) {
            return false;
        }
        // Los mismos arrays que hashCode, en el mismo orden.
        final SampleArraysPojo other = (SampleArraysPojo) obj;
        return Arrays.equals(boolVal, other.boolVal)
                && Arrays.equals(byVal, other.byVal)
                && Arrays.equals(carVal, other.carVal)
                && Arrays.equals(douVal, other.douVal)
                && Arrays.equals(datVal, other.datVal)
                && Arrays.equals(decVal, other.decVal)
                && Arrays.equals(floVal, other.floVal)
                && Arrays.equals(intVal, other.intVal)
                && Arrays.equals(lonVal, other.lonVal)
                && Arrays.equals(obVal, other.obVal)
                && Arrays.equals(obyVal, other.obyVal)
                && Arrays.equals(ocVal, other.ocVal)
                && Arrays.equals(odVal, other.odVal)
                && Arrays.equals(ofVal, other.ofVal)
                && Arrays.equals(oiVal, other.oiVal)
                && Arrays.equals(olVal, other.olVal)
                && Arrays.equals(osiVal, other.osiVal)
                && Arrays.equals(strVal, other.strVal)
                && Arrays.equals(siVal, other.siVal);
    }

    @Override
    public String toString() {
        return "SampleArraysPojo [boolVal=" + Arrays.toString(boolVal) + ", siVal=" + Arrays.toString(siVal)
                + ", intVal=" + Arrays.toString(intVal) + ", lonVal=" + Arrays.toString(lonVal) + ", carVal="
                + Arrays.toString(carVal) + ", douVal=" + Arrays.toString(douVal) + ", floVal="
                + Arrays.toString(floVal) + ", obVal=" + Arrays.toString(obVal) + ", oiVal=" + Arrays.toString(oiVal)
                + ", olVal=" + Arrays.toString(olVal) + ", ocVal=" + Arrays.toString(ocVal) + ", odVal="
                + Arrays.toString(odVal) + ", ofVal=" + Arrays.toString(ofVal) + ", strVal=" + Arrays.toString(strVal)
                + ", decVal=" + Arrays.toString(decVal) + ", datVal=" + Arrays.toString(datVal) + ", byVal="
                + Arrays.toString(byVal) + "]";
    }

}
