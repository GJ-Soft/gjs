package org.gjs.java.test.samples.type;

import java.math.BigDecimal;
import java.util.Date;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;

/**
 * The Class LombokType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo generado entero por Lombok: accesores, constructores, builder y toString.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
@Builder
@NoArgsConstructor
@AllArgsConstructor
@ToString
public class LombokType {
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

}
