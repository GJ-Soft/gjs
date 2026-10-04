package org.gjs.java.common.enums;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.sql.Timestamp;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Date;
import java.util.Objects;

/**
 * The Enum ManagedType.
 *
 * Enumerado de la librería Gjs
 *
 * Tipos gestionados por la librería.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public enum ManagedType {

    /** The string. */
    STRING("java.lang.String", ""),
    /** The bigdecimal. */
    BIGDECIMAL("java.math.BigDecimal", BigDecimal.ZERO),
    /** The biginteger. */
    BIGINTEGER("java.math.BigInteger", BigInteger.ZERO),
    /** The date type. */
    DATE("java.util.Date", new Date()),
    /** The localdatetime. */
    LOCALDATETIME("java.time.LocalDateTime", LocalDateTime.now(ZoneId.systemDefault())),
    /** The localdate. */
    LOCALDATE("java.time.LocalDate", LocalDateTime.now(ZoneId.systemDefault()).toLocalDate()),
    /** The timestamp. */
    TIMESTAMP("java.sql.Timestamp", Timestamp.valueOf(LocalDateTime.now(ZoneId.systemDefault()))),
    /** The throwable. */
    THROWABLE("java.lang.Throwable", new Exception()),
    /** The exception. */
    EXCEPTION("java.lang.Exception", new Exception());

    /** The class name. */
    private String className;

    /** The default object. */
    private Object defaultObject;

    /**
     * Instantiates a new primitive type.
     *
     * @param className
     *            the class name
     * @param defaultObject
     *            the default object
     */
    ManagedType(String className, Object defaultObject) {
        this.className = className;
        this.defaultObject = defaultObject;
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
     * Gets the default object.
     *
     * @return the default object
     */
    public Object getDefaultObject() {
        return defaultObject;
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Enum#toString() */

    @Override
    public String toString() {
        return className;
    }

    /**
     * Checks if is same type.
     *
     * @param typeName
     *            the type name
     * @return true, if is same type
     */
    public boolean isSameType(String typeName) {
        return className.equals(typeName);
    }

    /**
     * Equals.
     *
     * @param obj
     *            the obj
     * @return true, if successful
     */
    public boolean equalsTo(ManagedType obj) {
        boolean res = false;
        if (Objects.nonNull(obj)) {
            res = className.equals(obj.getClassName());
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
            res = className.equals(obj);
        }
        return res;
    }

    /**
     * Checks if is managed.
     *
     * @param typeName
     *            the type name
     * @return true, if is managed
     */
    public static boolean isManaged(String typeName) {
        boolean res = false;
        for (final ManagedType type : ManagedType.values()) {
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
    public static ManagedType get(String typeName) {
        ManagedType res = null;
        for (final ManagedType type : ManagedType.values()) {
            if (type.getClassName().equals(typeName)) {
                res = type;
                break;
            }
        }
        return res;
    }

}
