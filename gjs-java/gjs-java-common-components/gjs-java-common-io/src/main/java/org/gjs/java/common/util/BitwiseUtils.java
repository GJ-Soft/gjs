package org.gjs.java.common.util;

import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class BitwiseUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Funciones de manejo de enteros como mapa de bits.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class BitwiseUtils {

    /**
     * Instantiates a new bitwise util.
     */
    private BitwiseUtils() {
        throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
    }

    /**
     * Checks if is sets the.
     *
     * @param value
     *            the value
     * @param pos
     *            the pos
     * @return true, if is sets the
     */
    public static boolean isSet(int value, int pos) {
        boolean res = false;
        if (pos >= 0) {
            final int mask = 1 << pos;
            res = (value & mask) > 0;
        }
        return res;
    }

}
