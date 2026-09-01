package org.gjs.java.common.type;

import java.lang.reflect.Field;
import java.lang.reflect.Type;
import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class FieldInfo.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase utilizada en nuestras utilidades de Reflection y que nos sirve para manejar los atributos de forma general,
 * tratando por igual los normales y los que son de una clase parametrizada.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class FieldInfo {

    /** The field. */
    private Field field;

    /** The clazz. */
    private Class<?> clazz;

    /** The generic class. */
    private Type genericClass;

    /**
     * Instantiates a new field info.
     */
    public FieldInfo() {
    }

    /**
     * Instantiates a new field info.
     *
     * @param field
     *            the field
     * @param clazz
     *            the clazz
     */
    public FieldInfo(Field field, Class<?> clazz) {
        this.field = field;
        this.clazz = clazz;
    }

    /**
     * Instantiates a new field info.
     *
     * @param field
     *            the field
     * @param clazz
     *            the clazz
     * @param genericClass
     *            the generic class
     */
    public FieldInfo(Field field, Class<?> clazz, Type genericClass) {
        this.field = field;
        this.clazz = clazz;
        this.genericClass = genericClass;
    }

    /**
     * Checks if is from generic class.
     *
     * @return true, if is from generic class
     */
    public boolean isFromGenericClass() {
        return Objects.nonNull(genericClass);
    }
}
