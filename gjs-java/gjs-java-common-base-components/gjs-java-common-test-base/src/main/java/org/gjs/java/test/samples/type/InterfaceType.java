package org.gjs.java.test.samples.type;


/**
 * The Class InterfaceType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo que implementa Interface.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class InterfaceType implements Interface {

    private String name = "name";
	private int index = 0;
	
    public int getIndex() {
        return index;
    }

    public String getName() {
        return name;
    }

}
