package org.gjs.java.common.util;

import java.lang.reflect.Field;
import java.util.Objects;

import org.gjs.java.common.constant.CommonBaseConstants;

import jakarta.persistence.Entity;
import jakarta.persistence.Id;

/**
 * The Class JpaUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Algunas funciones de ayuda para el manejo de entidades JPA.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class JpaUtils {

    /**
     * Clase no instanciable.
     */
    private JpaUtils() {
        throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
    }

    /**
     * Checks if is entity.
     *
     * @param clazz
     *            the clazz
     * @return true, if is entity
     */
    public static boolean isEntity(Class<?> clazz) {
        return clazz.isAnnotationPresent(Entity.class);
    }

    /**
     * Gets the id attribute.
     *
     * @param clazz
     *            the clazz
     * @return the id attribute
     */
    public static String getIdAttribute(Class<?> clazz) {
        // Por defecto, y para cualquier clase no JPA se pide que el atributo identificador se llame "id"
        String attribute = null;
        if (clazz.isAnnotationPresent(Entity.class)) {
            // NOTA: Se presupone que en una @Entity el campo @Id no va a estar en una superclase
            for (final Field field : clazz.getDeclaredFields()) {
                if (field.isAnnotationPresent(Id.class)) {
                    attribute = field.getName();
                    break;
                }
            }
        }
        if (Objects.isNull(attribute)) {
            for (final Field field : clazz.getDeclaredFields()) {
                if ("id".equals(field.getName())) {
                    attribute = field.getName();
                    break;
                }
            }
        }
        return attribute;
    }
}
