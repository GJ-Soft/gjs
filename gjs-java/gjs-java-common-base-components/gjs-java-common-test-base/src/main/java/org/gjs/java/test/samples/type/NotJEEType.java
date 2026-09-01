package org.gjs.java.test.samples.type;

import java.math.BigDecimal;
import java.util.Date;

/**
 * The Class NotJEEType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo con todos los campos públicos y sin accesores, que incumple a propósito el convenio JavaBean.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class NotJEEType {
    public boolean bVal;
    public int iVal;
    public long lVal;
    public char cVal;
    public double dVal;
    public float fVal;
    public Boolean obVal;
    public Integer oiVal;
    public Long olVal;
    public Character ocVal;
    public Double odVal;
    public Float ofVal;
    public String sVal;
    public BigDecimal decVal;
    public Date datVal;
    public byte byVal;
    public Byte obyVal;

    public NotJEEType() {
    }

    @Override
    public String toString() {
        return "SampleNotJEE [bVal=" + bVal + ", iVal=" + iVal + ", lVal=" + lVal + ", cVal=" + cVal + ", dVal=" + dVal
                + ", fVal=" + fVal + ", obVal=" + obVal + ", oiVal=" + oiVal + ", olVal=" + olVal + ", ocVal=" + ocVal
                + ", odVal=" + odVal + ", ofVal=" + ofVal + ", sVal=" + sVal + ", decVal=" + decVal + ", datVal="
                + datVal + ", byVal=" + byVal + ", obyVal=" + obyVal + "]";
    }

}
