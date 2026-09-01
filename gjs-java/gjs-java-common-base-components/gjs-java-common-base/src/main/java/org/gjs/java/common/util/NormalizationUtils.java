package org.gjs.java.common.util;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class NormalizationUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Funciones de normalización de literales. Contiene la función de normalización para procesar los nom bres de atributos
 * o campos de entidades que puedan venir en los ficheros de datos que se tengan que importar.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class NormalizationUtils {

    /**
     * Clase no instanciable.
     */
    private NormalizationUtils() {
        throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
    }

    /**
     * Normalize attribute name.
     *
     * @param initialName
     *            the initial name
     * @return the string
     */
    public static String normalizeAttributeName(String initialName) {
        if (StringUtils.isAllBlank(initialName)) {
            return null;
        }
        final StringBuilder name = new StringBuilder();
        boolean newWord = false;
        boolean lastUpper = false;
        for (int i = 0; i < initialName.length(); i = i + 1) {
            final char c = initialName.charAt(i);
            if (newWord) {
                if (ConditionUtils.oneIsTrue(Character.isLetter(c), Character.isDigit(c))) {
                    name.append(Character.toUpperCase(c));
                    lastUpper = true;
                    newWord = false;
                }
            } else if (ConditionUtils.allAreTrue(!Character.isLetter(c), !Character.isDigit(c))) {
                newWord = true;
                lastUpper = false;
            } else if (Character.isUpperCase(c) && !lastUpper && (i > 0)) {
                name.append(c);
                lastUpper = true;
            } else {
                name.append(Character.toLowerCase(c));
                lastUpper = Character.isUpperCase(c);
            }
        }
        if (name.length() == 0) {
            return null;
        }
        return name.toString();
    }

}
