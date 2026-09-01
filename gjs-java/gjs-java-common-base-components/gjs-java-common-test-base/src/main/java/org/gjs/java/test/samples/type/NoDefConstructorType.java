package org.gjs.java.test.samples.type;

/**
 * The Class NoDefConstructorType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo cuyo constructor por defecto es privado: solo se puede construir con argumento.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class NoDefConstructorType {

    private String value;

    private NoDefConstructorType() {

    }

    public NoDefConstructorType(Object object) {

    }

    public String getValue() {
        return value;
    }

    public void setValue(String value) {
        this.value = value;
    }
}
