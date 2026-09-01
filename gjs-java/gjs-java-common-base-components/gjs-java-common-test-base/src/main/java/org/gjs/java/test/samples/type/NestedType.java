package org.gjs.java.test.samples.type;

/**
 * The Class NestedType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo que se contiene a sí mismo, para las pruebas de anidamiento recursivo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class NestedType {

    private NestedType child;

    public NestedType getChild() {
        return child;
    }

    public void setChild(NestedType child) {
        this.child = child;
    }
}
