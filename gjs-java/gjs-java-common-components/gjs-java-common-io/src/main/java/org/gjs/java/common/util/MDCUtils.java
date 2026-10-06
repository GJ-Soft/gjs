package org.gjs.java.common.util;

import java.util.Objects;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.slf4j.MDC;

/**
 * The Class MDCUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Algunas funciones de ayuda para manejarse con la MDC de Apache.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class MDCUtils {

    /**
     * Clase no instanciable.
     */
    private MDCUtils() {
        throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
    }

    /**
     * Save.
     *
     * @param key
     *            the key
     * @param value
     *            the value
     */
    public static void save(String key, String value) {
        if (ConditionUtils.allAreTrue(!StringUtils.isAllBlank(key), Objects.nonNull(value))) {
            MDC.put(key, value);
        }
    }

    /**
     * Save.
     *
     * @param key
     *            the key
     * @param value
     *            the value
     */
    public static void save(String key, Object value) {
        if (ConditionUtils.allAreTrue(!StringUtils.isAllBlank(key), Objects.nonNull(value))) {
            MDC.put(key, JsonUtils.safeObjectToJson(value));
        }
    }

    /**
     * Load.
     *
     * @param key
     *            the key
     * @return the string
     */
    public static String load(String key) {
        String res = null;
        if (!StringUtils.isAllBlank(key)) {
            res = MDC.get(key);
        }
        return res;
    }

    /**
     * Load.
     *
     * @param key
     *            the key
     * @param clazz
     *            the clazz
     * @return the object
     */
    public static Object load(String key, Class<?> clazz) {
        Object res = null;
        if (!StringUtils.isAllBlank(key)) {
            res = JsonUtils.safeJsonToObject(MDC.get(key), clazz);
        }
        return res;
    }

    /**
     * Removes the.
     *
     * @param key
     *            the key
     */
    public static void remove(String key) {
        if (!StringUtils.isAllBlank(key)) {
            MDC.remove(key);
        }
    }

    /**
     * Clear.
     */
    public static void clear() {
        MDC.clear();
    }

}
