package org.gjs.java.common.type;

import java.util.Objects;

import org.apache.commons.lang3.ObjectUtils;

/**
 * The Class WrappedObject.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase para recubir cualquier objeto de forma que podamos usarla para definir un parámetro de tipo a priori
 * indefinido.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class WrappedObject {

    /** The Constant EMPTY. */
    private static final WrappedObject EMPTY = new WrappedObject(null);

    /** The value. */
    private Object value;

    /**
     * Instantiates a new wrapped object.
     *
     * @param obj
     *            the obj
     */
    public WrappedObject(Object obj) {
        this.value = obj;
    }

    /**
     * Empty.
     *
     * @return the wrapped object
     */
    public static WrappedObject empty() {
        return EMPTY;
    }

    /**
     * Of.
     *
     * @param value
     *            the value
     * @return the wrapped object
     */
    public static WrappedObject of(Object value) {
        return new WrappedObject(Objects.requireNonNull(value));
    }

    /**
     * Gets the.
     *
     * @return the object
     */
    public Object get() {
        return value;
    }

    /**
     * Sets the.
     *
     * @param value
     *            the value
     */
    public void set(Object value) {
        this.value = value;
    }

    /**
     * If a value is present, returns {@code true}, otherwise {@code false}.
     *
     * @return {@code true} if a value is present, otherwise {@code false}
     */
    public boolean isPresent() {
        return Objects.nonNull(value);
    }

    /**
     * If a value is not present, returns {@code true}, otherwise {@code false}.
     *
     * @return {@code true} if a value is not present, otherwise {@code false}
     * @since 11
     */
    public boolean isEmpty() {
        return Objects.isNull(value);
    }

    /**
     * Checks if is compatible.
     *
     * @param obj
     *            the obj
     * @return true, if is compatible
     */
    public boolean isCompatible(Object obj) {
        boolean res = false;
        if (ObjectUtils.allNotNull(value, obj)) {
            Object other = obj;
            if (obj instanceof final WrappedObject wr) {
                other = wr.get();
            }
            if (Objects.nonNull(other)) {
                res = value.getClass().getCanonicalName().equals(other.getClass().getCanonicalName());
            }
        }
        return res;
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#equals(java.lang.Object) */

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        Object other = obj;
        if (obj instanceof final WrappedObject wr) {
            other = wr.get();
        }
        return Objects.equals(value, other);
    }

    /**
     * Returns the hash code of the value, if present, otherwise {@code 0} (zero) if no value is present.
     *
     * @return hash code value of the present value or {@code 0} if no value is present
     */
    @Override
    public int hashCode() {
        return Objects.hashCode(value);
    }

    /**
     * Returns a non-empty string representation of this {@code Optional} suitable for debugging. The exact presentation
     * format is unspecified and may vary between implementations and versions.
     *
     * @return the string representation of this instance
     * 		   If a value is present the result must include its string representation in the result. Empty and
     *           present {@code Optional}s must be unambiguously differentiable.
     */
    @Override
    public String toString() {
        return Objects.nonNull(value) ? value.toString() : "WrappedObject.empty";
    }

}
