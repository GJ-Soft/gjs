package org.gjs.java.test.samples.type;

/**
 * The Class StaticType.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Tipo cuyo único campo y cuyos accesores son estáticos.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class StaticType {

    private static String value;

    public static void setValue(String value) {
        StaticType.value = value;
    }

    public static String getValue() {
        return value;
    }
}
