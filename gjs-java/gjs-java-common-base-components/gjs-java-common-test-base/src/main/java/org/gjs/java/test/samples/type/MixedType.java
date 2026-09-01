package org.gjs.java.test.samples.type;

/**
 * The Class MixedType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo que mezcla un campo público con otros privados, para distinguir el acceso directo del acceso por accesor.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MixedType {
    public boolean boolVal;
    private int intVal;
    private char carVal;

    public MixedType() {
    }

    public int getIntVal() {
        return intVal;
    }

    public void setIntVal(int intVal) {
        this.intVal = intVal;
    }

    public char getCarVal() {
        return carVal;
    }

}
