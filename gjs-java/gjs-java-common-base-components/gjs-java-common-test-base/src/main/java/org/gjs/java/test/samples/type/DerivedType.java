package org.gjs.java.test.samples.type;

/**
 * The Class DerivedType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo derivado de AbstractType, que resuelve el nombre que aquella deja abstracto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class DerivedType extends AbstractType {

    private String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
