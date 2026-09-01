package org.gjs.java.common.util;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class AdministrativeUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Funciones generales de validación oficial de códigos de carñacter administrativo estatal: DNI/NIF, NIE...
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class AdministrativeUtils {

    /** The Constant NIF_STRING_ASOCIATION. */
    private static final String NIF_STRING_ASOCIATION = "TRWAGMYFPDXBNJZSQVHLCKE";

    /** The Constant NIE_PREFIX_ASOCIATION. */
    private static final String NIE_PREFIX_ASOCIATION = "XYZ";

    /** The Constant NUMERIC_PREFIX_ASOCIATION. */
    private static final String NUMERIC_PREFIX_ASOCIATION = "012";

    /**
     * Clase no instanciable.
     */
    private AdministrativeUtils() {
        throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
    }

    /**
     * Validate nif.
     *
     * @param nif
     *            the nif
     * @return true, if successful
     */
    public static boolean validateNif(String nif) {
        boolean res = false;
        if (!StringUtils.isAllBlank(nif) && (nif.length() == 9)) {
            final char letter = nif.charAt(8);
            final String dni = nif.substring(0, 8);
            if (StringUtils.isNumeric(dni)) {
                final Integer value = Integer.valueOf(dni);
                res = (NIF_STRING_ASOCIATION.charAt(value % 23) == letter);
            }
        }
        return res;
    }

    /**
     * Validate nie.
     *
     * @param nie
     *            the nie
     * @return true, if successful
     */
    public static boolean validateNie(String nie) {
        boolean res = false;
        if (!StringUtils.isAllBlank(nie) && (nie.length() == 9)) {
            final char prefix = nie.charAt(0);
            final char letter = nie.charAt(8);
            final String number = nie.substring(1, 8);
            final int index = NIE_PREFIX_ASOCIATION.indexOf(prefix);
            if (StringUtils.isNumeric(number) && (index >= 0)) {
                final String numericPart = String.valueOf(NUMERIC_PREFIX_ASOCIATION.charAt(index)).concat(number);
                final Integer value = Integer.valueOf(numericPart);
                res = (NIF_STRING_ASOCIATION.charAt(value % 23) == letter);
            }
        }
        return res;
    }

    /**
     * Validate nif nie.
     *
     * @param nif
     *            the nif
     * @return true, if successful
     */
    public static boolean validateNifNie(String nif) {
        return ConditionUtils.oneIsTrue(validateNif(nif), validateNie(nif));
    }

}
