package org.gjs.java.test.samples.type;

import java.math.BigDecimal;
import java.util.Date;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class AllPrimitivesType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo con un campo de cada tipo primitivo y envuelto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class AllPrimitivesType {
    private boolean boolVal;
    private short siVal;
    private int intVal;
    private long lonVal;
    private char carVal;
    private double douVal;
    private float floVal;
    private Boolean obVal;
    private Integer oiVal;
    private Long olVal;
    private Character ocVal;
    private Double odVal;
    private Float ofVal;
    private String strVal;
    private BigDecimal decVal;
    private Date datVal;
    private byte byVal;
    private Byte obyVal;

    public AllPrimitivesType() {
    }

    public AllPrimitivesType(boolean boolVal, int intVal, short siVal, long lonVal, char carVal, double douVal, float floVal,
            Boolean obVal, Integer oiVal, Long olVal, Character ocVal, Double odVal, Float ofVal, String strVal,
            BigDecimal decVal, Date datVal, byte byVal, Byte obyVal) {
        this.boolVal = boolVal;
        this.intVal = intVal;
        this.siVal = siVal;
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
        this.obyVal = obyVal;
    }

    @Override
    public String toString() {
        return "Sample [boolVal=" + boolVal + ", siVal=" + siVal + ", intVal=" + intVal + ", lonVal=" + lonVal
                + ", carVal=" + carVal + ", douVal=" + douVal + ", floVal=" + floVal + ", obVal=" + obVal + ", oiVal="
                + oiVal + ", olVal=" + olVal + ", ocVal=" + ocVal + ", odVal=" + odVal + ", ofVal=" + ofVal
                + ", strVal=" + strVal + ", decVal=" + decVal + ", datVal=" + datVal + ", byVal=" + byVal + ", obyVal="
                + obyVal + "]";
    }

}
