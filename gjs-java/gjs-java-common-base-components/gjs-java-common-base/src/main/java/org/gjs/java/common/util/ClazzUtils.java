package org.gjs.java.common.util;

import java.lang.reflect.Array;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Parameter;
import java.lang.reflect.Type;
import java.util.Objects;

import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.slf4j.Logger;

/**
 * The Class ClazzUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Algunas rutinas para crear objetos de cualquier clase de forma dinámica, junto con algunas funciones adicionales de
 * ayuda.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class ClazzUtils {

    /** The Constant OBJECT_CLASSNAME. */
    public static final String OBJECT_CLASSNAME = "java.lang.Object";

    /**
     * Clase no instanciable.
     */
    private ClazzUtils() {
        throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
    }

    /**
     * Creates the instance.
     *
     * @param className
     *            the class name
     * @return the object
     */
    public static Object createInstance(String className) {
        return createInstance(className, null);
    }

    /**
     * Creates the instance.
     *
     * @param className
     *            the class name
     * @param logger
     *            the logger
     * @return the object
     */
    public static Object createInstance(String className, Logger logger) {
        Object object = null;
        try {
            // En Java 11 no se puede llamar al constructor de las clases primitivas
            if (PrimitiveType.isPrimitiveClass(className)) {
                final PrimitiveType type = PrimitiveType.getFromClass(className);
                object = type.getDefaultObject();
            } else if (ManagedType.isManaged(className)) {
                final ManagedType type = ManagedType.get(className);
                object = type.getDefaultObject();
            } else {
                object = createObjectInstance(className);
            }
        } catch (final ClassNotFoundException | InstantiationException | IllegalAccessException
                | IllegalArgumentException | InvocationTargetException | NoSuchMethodException | SecurityException e) {
            if (Objects.nonNull(logger)) {
                logger.error("Error creating an empty instance of Class=[{}]", className, e);
            }
        }
        return object;
    }

    /**
     * Creates the array instance.
     *
     * @param className
     *            the class name
     * @return the object
     */
    public static Object createArrayInstance(String className) {
        return createArrayInstance(className, null);
    }

    /**
     * Creates the array instance.
     *
     * @param className
     *            the class name
     * @param logger
     *            the logger
     * @return the object
     */
    public static Object createArrayInstance(String className, Logger logger) {
        return createArrayInstance(className, 0, logger);
    }

    /**
     * Creates the array instance.
     *
     * @param className
     *            the class name
     * @param size
     *            the size
     * @param logger
     *            the logger
     * @return the object
     */
    public static Object createArrayInstance(String className, int size, Logger logger) {
        Object object = null;
        try {
            object = Array.newInstance(Class.forName(className), size);
        } catch (NegativeArraySizeException | ClassNotFoundException e) {
            logger.error("Error evaluating empty object of Class=[{}]", className, e);
        }
        return object;
    }

    /**
     * Gets the generic superclass.
     *
     * @param clazz
     *            the clazz
     * @return the generic superclass
     */
    public static Type getGenericSuperclass(Class<?> clazz) {
        Type superclass = clazz.getGenericSuperclass();
        if (Objects.nonNull(superclass) && OBJECT_CLASSNAME.equals(superclass.getTypeName())) {
            superclass = null;
        }
        return superclass;
    }

    /**
     * Creates the object instance.
     *
     * @param className
     *            the class name
     * @return the object
     * @throws InstantiationException
     *             the instantiation exception
     * @throws IllegalAccessException
     *             the illegal access exception
     * @throws InvocationTargetException
     *             the invocation target exception
     * @throws NoSuchMethodException
     *             the no such method exception
     * @throws ClassNotFoundException
     *             the class not found exception
     */
    private static Object createObjectInstance(String className) throws InstantiationException, IllegalAccessException,
            InvocationTargetException, NoSuchMethodException, ClassNotFoundException {
        Object object = null;
        if (ReflectionUtils.hasDefaultConstructor(className)) {
            object = Class.forName(className).getDeclaredConstructor().newInstance();
        } else if (Class.forName(className).getDeclaredConstructors().length > 0) {
            final Constructor<?> constructor = Class.forName(className).getDeclaredConstructors()[0];
            object = constructor.newInstance(generateEmptyParameters(constructor));
        }
        return object;
    }

    /**
     * Generate empty parameters.
     *
     * @param constructor
     *            the constructor
     * @return the object[]
     */
    private static Object[] generateEmptyParameters(Constructor<?> constructor) {
        final Object[] parameters = new Object[constructor.getParameters().length];
        for (int i = 0; i < constructor.getParameters().length; i = i + 1) {
            final Parameter param = constructor.getParameters()[i];
            final String paramTypeName = getTypeName(param);
            if (PrimitiveType.isPrimitiveNative(paramTypeName)) {
                if (!param.getType().isArray()) {
                    final PrimitiveType type = PrimitiveType.get(paramTypeName);
                    parameters[i] = type.getDefaultValue();
                } else {
                    parameters[i] = null;
                }
            } else {
                parameters[i] = null;
            }
        }
        return parameters;
    }

    private static String getTypeName(Parameter param) {
        return param.getType().getCanonicalName().replace("[]", "");
    }

}
