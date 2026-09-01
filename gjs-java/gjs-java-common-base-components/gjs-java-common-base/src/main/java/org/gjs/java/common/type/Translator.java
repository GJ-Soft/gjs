package org.gjs.java.common.type;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class Translator.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase que mantiene una asociación de parejas de cadenas.Está pensada para se utilizada como ayuda en el tratamiento
 * multi-idioma de literales de uso dinámico que sean utilizados como parámetros en la construcción de cadenas o
 * mensajes: nombres de atributo, por ejemplo.
 *
 * PENDIENTE: Constructor qe cargue un fichero
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class Translator {

    /** The map translations. */
    private final Map<String, String> mapTranslations = new ConcurrentHashMap<>();

    /**
     * Instantiates a new translator.
     */
    public Translator() {
        // No hace nada
    }

    /**
     * Adds the.
     *
     * @param original
     *            the original
     * @param translation
     *            the translation
     */
    public void add(String original, String translation) {
        if (!ConditionUtils.oneIsTrue(StringUtils.isAllBlank(original), StringUtils.isAllBlank(translation))) {
            mapTranslations.put(original, translation);
        }
    }

    /**
     * Translate.
     *
     * @param original
     *            the original
     * @return the string
     */
    public String translate(String original) {
        String res = null;
        if (!StringUtils.isAllBlank(original)) {
            res = mapTranslations.get(original);
        }
        return res;
    }

    /**
     * Clear.
     */
    public void clear() {
        mapTranslations.clear();
    }
}
