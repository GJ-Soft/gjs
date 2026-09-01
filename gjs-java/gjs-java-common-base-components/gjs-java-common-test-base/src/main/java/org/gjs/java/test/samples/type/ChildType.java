package org.gjs.java.test.samples.type;

/**
 * The Class ChildType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo derivado de ParentType, para las pruebas de herencia.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class ChildType extends ParentType {

    private String name;
    private Integer integerValue;
    private int intValue;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getIntegerValue() {
        return integerValue;
    }

    public void setIntegerValue(Integer integerValue) {
        this.integerValue = integerValue;
    }

    public int getIntValue() {
        return intValue;
    }

    public void setIntValue(int intValue) {
        this.intValue = intValue;
    }
}
