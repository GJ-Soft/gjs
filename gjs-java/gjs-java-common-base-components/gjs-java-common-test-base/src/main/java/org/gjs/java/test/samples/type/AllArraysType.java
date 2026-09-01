package org.gjs.java.test.samples.type;

import java.math.BigDecimal;
import java.util.Date;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class AllArraysType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo con un array de cada tipo primitivo y envuelto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class AllArraysType {
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

    public AllArraysType() {
    }
}
