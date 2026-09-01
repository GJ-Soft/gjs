package org.gjs.java.test.samples.type;

/**
 * The Class AbstractType.
 *
 * Clase abstracta de ejemplo de la librería Gjs
 *
 * Tipo base con un valor propio y el nombre por resolver en la clase derivada.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class AbstractType {

    private String value;

    public abstract String getName();
	public abstract void setName(String name);
	
    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }
}
