package org.gjs.java.common.enums;

import java.util.Objects;

import org.gjs.java.common.util.ConditionUtils;

/**
 * The Enum PrimitiveType.
 *
 * Enumerado de la librería Gjs
 *
 * Tipos primitivos.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public enum PrimitiveType {

    /** The byte. */
    BYTE("byte", "java.lang.Byte", "B", (byte) 0, Byte.valueOf((byte) 0), new byte[0]),
    /** The integer. */
    INTEGER("int", "java.lang.Integer", "I", 0, Integer.valueOf(0), new int[0]),
    /** The long. */
    LONG("long", "java.lang.Long", "J", (long) 0, Long.valueOf(0), new long[0]),
    /** The short. */
    SHORT("short", "java.lang.Short", "S", (short) 0, Short.valueOf((short) 0), new short[0]),
    /** The boolean. */
    BOOLEAN("boolean", "java.lang.Boolean", "Z", false, Boolean.FALSE, new boolean[0]),
    /** The float. */
    FLOAT("float", "java.lang.Float", "F", 0.0f, Float.valueOf(0.0f), new float[0]),
    /** The double. */
    DOUBLE("double", "java.lang.Double", "D", 0.0, Double.valueOf(0.0), new double[0]),
    /** The char. */
    CHAR("char", "java.lang.Character", "C", '\0', Character.valueOf('\0'), new char[0]);

    /** The name. */
    private String name;

    /** The class name. */
    private String className;

    /** The jvm name. */
    private String jvmName;

    /** The default value. */
    private Object defaultValue;

    /** The default object. */
    private Object defaultObject;

    /** The default array. */
    private Object defaultArray;

    /**
     * Instantiates a new primitive type.
     *
     * @param name
     *            the name
     * @param className
     *            the class name
     * @param jvmName
     *            the jvm name
     * @param defaultValue
     *            the default value
     * @param defaultObject
     *            the default object
     * @param defaultArray
     *            the default array
     */
    PrimitiveType(String name, String className, String jvmName, Object defaultValue, Object defaultObject,
            Object defaultArray) {
        this.name = name;
        this.className = className;
        this.jvmName = jvmName;
        this.defaultValue = defaultValue;
        this.defaultObject = defaultObject;
        this.defaultArray = defaultArray;
    }

    /**
     * Gets the name.
     *
     * @return the name
     */
    public String getName() {
        return name;
    }

    /**
     * Gets the class name.
     *
     * @return the class name
     */
    public String getClassName() {
        return className;
    }

    /**
     * Gets the JVM name.
     *
     * @return the JVM name
     */
    public String getJVMName() {
        return jvmName;
    }

    /**
     * Gets the default value.
     *
     * @return the default value
     */
    public Object getDefaultValue() {
        return defaultValue;
    }

    /**
     * Gets the default object.
     *
     * @return the default object
     */
    public Object getDefaultObject() {
        return defaultObject;
    }

    /**
     * Gets the default array.
     *
     * @return the default array
     */
    public Object getDefaultArray() {
        return defaultArray;
    }

    /**
     * Gets the array type name.
     *
     * @return the array type name
     */
    public String getArrayTypeName() {
        final StringBuilder builder = new StringBuilder();
        builder.append('[').append(jvmName).append(';');
        return builder.toString();
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Enum#toString() */

    @Override
    public String toString() {
        return name;
    }

    /**
     * Checks if is same type.
     *
     * @param typeName
     *            the type name
     * @return true, if is same type
     */
    public boolean isSameType(String typeName) {
        return ConditionUtils.oneIsTrue(name.equals(typeName), className.equals(typeName));
    }

    /**
     * Checks if is same native type.
     *
     * @param typeName
     *            the type name
     * @return true, if is same native type
     */
    public boolean isSameNativeType(String typeName) {
        return (name.equals(typeName));
    }

    /**
     * Checks if is same class type.
     *
     * @param typeName
     *            the type name
     * @return true, if is same class type
     */
    public boolean isSameClassType(String typeName) {
        return (className.equals(typeName));
    }

    /**
     * Equals.
     *
     * @param obj
     *            the obj
     * @return true, if successful
     */
    public boolean equalsTo(PrimitiveType obj) {
        boolean res = false;
        if (Objects.nonNull(obj)) {
            res = name.equals(obj.getName());
        }
        return res;
    }

    /**
     * Equals.
     *
     * @param obj
     *            the obj
     * @return true, if successful
     */
    public boolean equalsTo(String obj) {
        boolean res = false;
        if (Objects.nonNull(obj)) {
            res = name.equals(obj);
        }
        return res;
    }

    /**
     * Checks if is primitive.
     *
     * @param typeName
     *            the type name
     * @return true, if is primitive
     */
    public static boolean isPrimitive(String typeName) {
        boolean res = false;
        for (final PrimitiveType type : PrimitiveType.values()) {
            if (ConditionUtils.oneIsTrue(type.getName().equals(typeName), type.getClassName().equals(typeName))) {
                res = true;
                break;
            }
        }
        return res;
    }

    /**
     * Checks if is primitive native.
     *
     * @param typeName
     *            the type name
     * @return true, if is primitive native
     */
    public static boolean isPrimitiveNative(String typeName) {
        boolean res = false;
        for (final PrimitiveType type : PrimitiveType.values()) {
            if (type.getName().equals(typeName)) {
                res = true;
                break;
            }
        }
        return res;
    }

    /**
     * Checks if is primitive class.
     *
     * @param typeName
     *            the type name
     * @return true, if is primitive class
     */
    public static boolean isPrimitiveClass(String typeName) {
        boolean res = false;
        for (final PrimitiveType type : PrimitiveType.values()) {
            if (type.getClassName().equals(typeName)) {
                res = true;
                break;
            }
        }
        return res;
    }

    /**
     * Gets the.
     *
     * @param typeName
     *            the type name
     * @return the primitive type
     */
    public static PrimitiveType get(String typeName) {
        PrimitiveType res = null;
        for (final PrimitiveType type : PrimitiveType.values()) {
            if (type.getName().equals(typeName)) {
                res = type;
                break;
            }
        }
        return res;
    }

    /**
     * Gets the form class.
     *
     * @param typeName
     *            the type name
     * @return the form class
     */
    public static PrimitiveType getFromClass(String typeName) {
        PrimitiveType res = null;
        for (final PrimitiveType type : PrimitiveType.values()) {
            if (type.getClassName().equals(typeName)) {
                res = type;
                break;
            }
        }
        return res;
    }

}
