package org.gjs.java.test.samples.type;

/**
 * The Class ParentType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo base con un nombre protegido, del que deriva ChildType.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class ParentType {

    protected String parentName;

    public String getParentName() {
        return parentName;
    }

    public void setParentName(String parentName) {
        this.parentName = parentName;
    }
}
