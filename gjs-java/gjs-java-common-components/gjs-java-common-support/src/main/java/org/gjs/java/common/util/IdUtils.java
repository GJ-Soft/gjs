package org.gjs.java.common.util;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.Objects;
import java.util.Set;
import java.util.TreeSet;

import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class IdUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Algunas funciones de ayuda para tratar con los diferentes tipos de identificadores simples que se utilizan en las
 * entidades.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class IdUtils {

    /**
     * Clase no instanciable.
     */
    private IdUtils() {
        throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
    }

    /**
     * Checks if is valid.
     *
     * @param id
     *            the id
     * @return true, if is valid
     */
    public static boolean isValid(Long id) {
        return (Objects.nonNull(id) && (id > 0));
    }

    /**
     * Checks if is valid.
     *
     * @param id
     *            the id
     * @return true, if is valid
     */
    public static boolean isValid(Integer id) {
        return (Objects.nonNull(id) && (id > 0));
    }

    /**
     * Checks if is valid.
     *
     * @param id
     *            the id
     * @return true, if is valid
     */
    public static boolean isValid(Short id) {
        return (Objects.nonNull(id) && (id > 0));
    }

    /**
     * Checks if is valid.
     *
     * @param id
     *            the id
     * @return true, if is valid
     */
    public static boolean isValid(BigDecimal id) {
        return (Objects.nonNull(id) && (id.compareTo(BigDecimal.ZERO) > 0));
    }

    /**
     * Checks if is valid.
     *
     * @param id
     *            the id
     * @return true, if is valid
     */
    public static boolean isValid(BigInteger id) {
        return (Objects.nonNull(id) && (id.compareTo(BigInteger.ZERO) > 0));
    }

    /**
     * Checks if is one of.
     *
     * @param id
     *            the id
     * @param values
     *            the values
     * @return true, if is one of
     */
    public static boolean isOneOf(Long id, Long... values) {
        boolean res = false;
        if (isValid(id)) {
            final Set<Long> setValues = new TreeSet<>(Arrays.asList(values));
            res = setValues.contains(id);
        }
        return res;

    }

    /**
     * Checks if is between.
     *
     * @param id
     *            the id
     * @param valueMin
     *            the value min
     * @param valueMax
     *            the value max
     * @return true, if is between
     */
    public static boolean isBetween(Long id, Long valueMin, Long valueMax) {
        boolean res = false;
        if (ConditionUtils.allAreTrue(isValid(id), isValid(valueMin), isValid(valueMax))) {
            res = ConditionUtils.allAreTrue((valueMin <= id), (id <= valueMax));
        }
        return res;

    }

}
