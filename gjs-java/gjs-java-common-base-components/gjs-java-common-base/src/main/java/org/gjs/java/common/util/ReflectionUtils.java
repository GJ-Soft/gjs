package org.gjs.java.common.util;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.math.BigDecimal;
import java.sql.Timestamp;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Objects;
import java.util.Set;
import java.util.Stack;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.Vector;
import java.util.function.Predicate;
import java.util.stream.Collectors;

import org.apache.commons.lang3.ObjectUtils;
import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.exception.ObjectClonerException;
import org.gjs.java.common.type.FieldInfo;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class ReflectionUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Contiene algunas funcionalidades genéricas basadas en Reflection aunque
 * muchas de ellas adaptadas a las especificidades que se necesitan para la
 * funcionalidades de tests automatizados de Gjs.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class ReflectionUtils {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(ReflectionUtils.class);

	/**
	 * Clase no instanciable.
	 */
	private ReflectionUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Checks if is parametrized.
	 *
	 * @param clazz the clazz
	 * @return true, if is parametrized
	 */
	public static boolean isParametrized(Class<?> clazz) {
		return (clazz.getTypeParameters().length > 0);
	}

	/**
	 * Checks if is abstract.
	 *
	 * @param clazz the clazz
	 * @return true, if is abstract
	 */
	public static boolean isAbstract(Class<?> clazz) {
		return Modifier.isAbstract(clazz.getModifiers());
	}

	/**
	 * Checks if is updatable.
	 *
	 * @param field the field
	 * @return true, if is updatable
	 */
	public static boolean isUpdatable(Field field) {
		return !ConditionUtils.oneIsTrue(field.isEnumConstant(), field.isSynthetic(),
				Modifier.isStatic(field.getModifiers()));
	}

	/**
	 * Gets the all methods. Este método retorna lo mismo que getMethods excluyendo
	 * los que se heredan de la clase Object
	 *
	 * @param clazz the clazz
	 * @return the all methods
	 */
	public static List<Method> getAllMethods(Class<?> clazz) {
		final List<Method> methods = new ArrayList<>();
		final Set<String> included = new TreeSet<>();
		for (final Method method : clazz.getDeclaredMethods()) {
			if (!method.isSynthetic()) {
				methods.add(method);
				included.add(method.getName());
			}
		}
		if (Objects.nonNull(clazz.getSuperclass())
				&& !clazz.getSuperclass().getCanonicalName().equals(Object.class.getCanonicalName())) {
			for (final Method method : getAllMethods(clazz.getSuperclass())) {
				if (!included.contains(method.getName())) {
					methods.add(method);
				}
			}
		}
		return methods;
	}

	/**
	 * Gets the all classes.
	 *
	 * @param className the class name
	 * @return the all classes
	 */
	public static List<String> getAllClasses(String className) {
		List<String> res = new ArrayList<>();
		if (!StringUtils.isAllBlank(className)) {
			try {
				res = getAllClasses(Class.forName(className));
			} catch (final ClassNotFoundException e) {
				logger.error(String.format("%s is not a valid classname", className), e);
			}
		}
		return res;
	}

	/**
	 * Gets the all classes.
	 *
	 * @param clazz the clazz
	 * @return the all classes
	 */
	public static List<String> getAllClasses(Class<?> clazz) {
		final List<String> classes = new ArrayList<>();
		classes.add(clazz.getCanonicalName());
		while (Objects.nonNull(clazz.getSuperclass())
				&& !clazz.getSuperclass().getCanonicalName().equals(Object.class.getCanonicalName())) {
			clazz = clazz.getSuperclass();
			classes.add(clazz.getCanonicalName());
		}
		return classes;
	}

	/**
	 * Gets the all interfaces.
	 *
	 * @param className the class name
	 * @return the all interfaces
	 */
	public static List<String> getAllInterfaces(String className) {
		List<String> res = new ArrayList<>();
		if (!StringUtils.isAllBlank(className)) {
			try {
				res = getAllInterfaces(Class.forName(className));
			} catch (final ClassNotFoundException e) {
				logger.error(String.format("%s is not a valid classname", className), e);
			}
		}
		return res;
	}

	/**
	 * Gets the all interfaces.
	 *
	 * @param clazz the clazz
	 * @return the all interfaces
	 */
	public static List<String> getAllInterfaces(Class<?> clazz) {
		final List<String> interfaces = new ArrayList<>();
		getAllInterfaces(interfaces, clazz);
		return interfaces;
	}

	/**
	 * Gets the all interfaces.
	 *
	 * @param interfaces the interfaces
	 * @param clazz      the clazz
	 * @return the all interfaces
	 */
	private static List<String> getAllInterfaces(List<String> interfaces, Class<?> clazz) {
		for (final Class<?> interfaze : clazz.getInterfaces()) {
			interfaces.add(interfaze.getCanonicalName());
		}
		if (Objects.nonNull(clazz.getSuperclass())) {
			getAllInterfaces(interfaces, clazz.getSuperclass());
		}
		return interfaces;
	}

	/**
	 * Checks for method.
	 *
	 * @param clazz  the clazz
	 * @param method the method
	 * @return true, if successful
	 */
	public static boolean hasMethod(Class<?> clazz, String method) {
		final Set<String> setMethods = new TreeSet<>(
				getAllMethods(clazz).stream().map(Method::getName).collect(Collectors.toList()));
		return setMethods.contains(method);
	}

	/**
	 * Checks if is instance of.
	 *
	 * @param clazzName the clazz name
	 * @param className the class name
	 * @return true, if is instance of
	 */
	public static boolean isInstanceOf(String clazzName, String className) {
		boolean res = false;
		if (!ConditionUtils.oneIsTrue(StringUtils.isAllBlank(clazzName), StringUtils.isAllBlank(className))) {
			try {
				res = isInstanceOf(Class.forName(clazzName), className);
			} catch (final ClassNotFoundException e) {
				logger.error(String.format("%s is not a valid classname", clazzName), e);
			}
		}
		return res;
	}

	/**
	 * Checks if is instance of.
	 *
	 * @param clazz     the clazz
	 * @param className the class name
	 * @return true, if is instance of
	 */
	public static boolean isInstanceOf(Class<?> clazz, String className) {
		return ConditionUtils.oneIsTrue(Object.class.getCanonicalName().equals(className),
				getAllClasses(clazz).stream().anyMatch(Predicate.isEqual(className)));
	}

	/**
	 * Checks if is interface of.
	 *
	 * @param clazzName     the clazz name
	 * @param interfaceName the interface name
	 * @return true, if is interface of
	 */
	public static boolean implementsInterface(String clazzName, String interfaceName) {
		boolean res = false;
		if (!ConditionUtils.oneIsTrue(StringUtils.isAllBlank(clazzName), StringUtils.isAllBlank(interfaceName))) {
			try {
				res = implementsInterface(Class.forName(clazzName), interfaceName);
			} catch (final ClassNotFoundException e) {
				logger.error(String.format("%s is not a valid classname", clazzName), e);
			}
		}
		return res;
	}

	/**
	 * Checks if is interface of.
	 *
	 * @param clazz         the clazz
	 * @param interfaceName the interface name
	 * @return true, if is interface of
	 */
	public static boolean implementsInterface(Class<?> clazz, String interfaceName) {
		return getAllInterfaces(clazz).stream().anyMatch(Predicate.isEqual(interfaceName));
	}

	/**
	 * Find getter.
	 *
	 * @param clazz     the clazz
	 * @param fieldName the field name
	 * @return the method
	 */
	public static Method findGetter(Class<?> clazz, String fieldName) {
		Method getter = null;
		FieldInfo field = null;
		try {
			field = findField(clazz, fieldName);
		} catch (final SecurityException e) {
			logger.warn(e.getMessage());
		}
		if (Objects.nonNull(field)) {
			getter = findGetter(clazz, field.getField().getType(), fieldName);
		}
		return getter;
	}

	/**
	 * Find getter. NOTA: @Getter y @Setter generan nombres diferentes de los que se
	 * generan segun
	 *
	 * @param clazz     the clazz
	 * @param fieldType the field type
	 * @param fieldName the field name
	 * @return the method
	 */
	// el estandar JEE cuando sólo hay una minúscula inicial
	public static Method findGetter(Class<?> clazz, Class<?> fieldType, String fieldName) {
		Method getter = null;
		String getterName = String.format("get%s", StringUtils.capitalize(fieldName));
		if (PrimitiveType.BOOLEAN.isSameNativeType(fieldType.getName())) {
			getterName = String.format("is%s", StringUtils.capitalize(fieldName));
		}
		// logger.debug("Finding getter {} in Class {}", getterName,
		// clazz.getCanonicalName());
		for (final Method method : getAllMethods(clazz)) {
			// logger.debug("\tMethod={} ->{}", method.getName(),
			// method.getName().equals(getterName));
			if (method.getName().equals(getterName)) {
				getter = method;
				break;
			}
		}
		if (Objects.isNull(getter) && Objects.nonNull(clazz.getSuperclass())) {
			getter = findGetter(clazz.getSuperclass(), fieldType, fieldName);
		}
		return getter;
	}

	/**
	 * Find setter.
	 *
	 * @param clazz     the clazz
	 * @param fieldName the field name
	 * @return the method
	 */
	public static Method findSetter(Class<?> clazz, String fieldName) {
		final String setterName = String.format("set%s", StringUtils.capitalize(fieldName));
		Method setter = null;
		for (final Method method : getAllMethods(clazz)) {
			if (method.getName().equals(setterName)) {
				setter = method;
				break;
			}
		}
		return setter;
	}

	/**
	 * Find field.
	 *
	 * @param clazz     the clazz
	 * @param fieldName the field name
	 * @return the field
	 */
	public static FieldInfo findField(Class<?> clazz, String fieldName) {
		FieldInfo res = null;
		for (final FieldInfo field : getAllFields(clazz)) {
			// logger.debug("Search field {}: field {}", fieldName,
			// field.getField().getName());
			if (field.getField().getName().equals(fieldName)) {
				res = field;
				break;
			}
		}
		return res;
	}

	/**
	 * Find method.
	 *
	 * @param clazz      the clazz
	 * @param methodName the method name
	 * @return the method
	 */
	public static Method findMethod(Class<?> clazz, String methodName) {
		Method setter = null;
		for (final Method method : getAllMethods(clazz)) {
			if (method.getName().equals(methodName)) {
				setter = method;
				break;
			}
		}
		return setter;
	}

	/**
	 * Find constructor.
	 *
	 * @param clazz    the clazz
	 * @param typeName the type name
	 * @return the constructor
	 */
	public static Constructor<?> findConstructor(Class<?> clazz, String typeName) {
		Constructor<?> res = null;
		for (final Constructor<?> constructor : clazz.getDeclaredConstructors()) {
			if ((constructor.getParameterCount() == 1)
					&& constructor.getParameterTypes()[0].getCanonicalName().equals(typeName)) {
				res = constructor;
				break;
			}
		}
		return res;
	}

	/**
	 * Gets the all fields. Este método retorna lo mismo que getFields excluyendo
	 * algunos campos que no nos interesan
	 *
	 * @param clazz the clazz
	 * @return the all fields
	 */
	public static List<FieldInfo> getAllFields(Class<?> clazz) {
		return getAllFields(clazz, ClazzUtils.getGenericSuperclass(clazz));
	}

	/**
	 * Gets the all fields.
	 *
	 * @param clazz        the clazz
	 * @param genericClass the generic class
	 * @return the all fields
	 */
	private static List<FieldInfo> getAllFields(Class<?> clazz, Type genericClass) {
		final List<FieldInfo> fields = new ArrayList<>();
		if (Objects.nonNull(clazz.getSuperclass())) {
			fields.addAll(getAllFields(clazz.getSuperclass(), ClazzUtils.getGenericSuperclass(clazz)));
		}
		for (final Field field : clazz.getDeclaredFields()) {
			if (!ConditionUtils.oneIsTrue(Modifier.isStatic(field.getModifiers()),
					"$jacocoData".equals(field.getName()))) {
				fields.add(new FieldInfo(field, clazz, genericClass));
			}
		}
		return fields;
	}

	/**
	 * Gets the all getters.
	 *
	 * @param clazz the clazz
	 * @return the all getters
	 */
	public static List<Method> getAllGetters(Class<?> clazz) {
		final List<Method> methods = new ArrayList<>();
		final List<FieldInfo> fields = getAllFields(clazz);
		for (final FieldInfo field : fields) {
			final Method method = findGetter(clazz, field.getField().getType(), field.getField().getName());
			if (Objects.nonNull(method)) {
				methods.add(method);
			}
		}
		return methods;
	}

	/**
	 * Checks for field.
	 *
	 * @param clazz the clazz
	 * @param field the field
	 * @return true, if successful
	 */
	public static boolean hasField(Class<?> clazz, String field) {
		boolean res = false;
		final List<FieldInfo> fields = getAllFields(clazz);
		for (final FieldInfo fieldInfo : fields) {
			if (fieldInfo.getField().getName().equals(field)) {
				res = true;
				break;
			}
		}
		return res;

	}

	/**
	 * Gets the type name.
	 *
	 * @param field the field
	 * @return the type name
	 */
	public static String getTypeName(Field field) {
		return getTypeName(field, null);
	}

	/**
	 * Gets the type name.
	 *
	 * PENDIENTE:Puede haber una generic type de un generic type y ademas no se
	 * tratan los
	 *
	 * @param field             the field
	 * @param genericSuperClass the generic super class
	 * @return the type name
	 */
	public static String getTypeName(Field field, Type genericSuperClass) {
		if ((genericSuperClass instanceof ParameterizedType)
				&& !field.getType().getTypeName().equals(field.getGenericType().getTypeName())) {
			// Puede ser un tipo genérico o una colección
			// logger.debug("Comprobando si es una colection: " +
			// field.getType().getName());
			if (CollectionUtils.isCollection(field.getType().getName())) {
				logger.debug("COLLECTION:" + field.getGenericType().getTypeName());
			} else {
				logger.debug("TIPO GENERICO:" + field.getGenericType().getTypeName());
				final ParameterizedType parametrizedType = (ParameterizedType) genericSuperClass;
				if (parametrizedType.getActualTypeArguments().length >= 1) {
					return parametrizedType.getActualTypeArguments()[0].getTypeName().replace("[]", "");
				}
			}
		}
		return field.getType().getCanonicalName().replace("[]", "");
	}

	/**
	 * Gets the field value.
	 *
	 * @param obj       the obj
	 * @param fieldName the field name
	 * @return the field value
	 */
	public static Object getFieldValue(Object obj, String fieldName) {
		Object value = null;
		final FieldInfo field = findField(obj.getClass(), fieldName);
		if (Objects.nonNull(field)) {
			value = getFieldValue(obj, field.getField());
		}
		return value;
	}

	/**
	 * Sets the field value.
	 *
	 * @param obj       the obj
	 * @param fieldName the field name
	 * @param value     the value
	 */
	public static void setFieldValue(Object obj, String fieldName, Object value) {
		final FieldInfo field = findField(obj.getClass(), fieldName);
		if (Objects.nonNull(field)) {
			setFieldValue(obj, field.getField(), value);
		}
	}

	/**
	 * Get field value.
	 *
	 * @param obj   the obj
	 * @param field the field
	 * @return the object
	 */
	public static Object getFieldValue(Object obj, Field field) {
		Object value = null;
		try {
			if (Modifier.isPublic(field.getModifiers())) {
				logger.debug("Se va a actualizar directamente el campo {}", field.getName());
				value = field.get(obj);
			} else {
				final Method getter = ReflectionUtils.findGetter(obj.getClass(), field.getType(), field.getName());
				if (Objects.nonNull(getter)) {
					logger.debug("Se va a obtener con el getter el campo {}", field.getName(), value);
					value = getter.invoke(obj);
				} else {
					logger.warn("El valor del atributo=[{}] no puede obtenerse.", field.getName());
				}
			}
		} catch (InvocationTargetException | IllegalAccessException | IllegalArgumentException e) {
			logger.error("Error obteniendo el valor del atributo=[{}]: [{}]", field.getName(), e.getMessage(), e);
		}
		return value;
	}

	/**
	 * Gets the field value.
	 *
	 * @param data   the data
	 * @param getter the getter
	 * @return the field value
	 */
	public static Object getFieldValue(Object data, Method getter) {
		Object res = null;
		if (ObjectUtils.allNotNull(data, getter)) {
			try {
				logger.debug("Invocando {} sobre el objeto {}", getter.getName(), data);
				res = getter.invoke(data);
			} catch (final InvocationTargetException | IllegalAccessException | IllegalArgumentException e) {
				logger.warn("Error obteniendo el valor del atributo con getter={}", getter.getName(), e);
			}
		}
		return res;
	}

	/**
	 * Set field value.
	 *
	 * @param obj   the obj
	 * @param field the field
	 * @param value the value
	 */
	public static void setFieldValue(Object obj, Field field, Object value) {
		if (!Modifier.isStatic(field.getModifiers())) {
			try {
				if (Modifier.isPublic(field.getModifiers())) {
					logger.debug("Se va a actualizar directamente el campo {} con el valor [{}]", field.getName(),
							value);
					if (field.getType().isArray()) {
						field.set(obj, new Object[] { value });
					} else {
						field.set(obj, value);
					}
				} else {
					final Method setter = findSetter(obj.getClass(), field.getName());
					if (Objects.nonNull(setter)) {
						logger.debug("Se va a actualizar con el setter el campo {} con el valor [{}]", field.getName(),
								value);
						setter.invoke(obj, value);
					} else {
						logger.warn("El valor del atributo {} no puede actualizarse.", field.getName());
					}
				}
			} catch (InvocationTargetException | IllegalAccessException | IllegalArgumentException e) {
				logger.error("Error actualizando el valor del atributo=[{}]: [{}]", field.getName(), e.getMessage(), e);
			}
		} else {
			logger.warn("El atributo {} es estatico y no puede actualizarse.", field.getName());
		}
	}

	/**
	 * Clone.
	 *
	 * @param obj the obj
	 * @return the object
	 */
	public static Object clone(Object obj) {
		Object copy = null;
		if (Objects.nonNull(obj)) {
			final String className = obj.getClass().getCanonicalName().replace("[]", "");
			final boolean isArray = obj.getClass().isArray();
			try {
				if (isArray) {
					logger.debug("CREATING ARRAY OF CLASS: {}", className);
					final Object[] array = (Object[]) obj;
					logger.debug("Array size: {}", array.length);
					final Object[] copyArray = (Object[]) ClazzUtils.createArrayInstance(className, array.length,
							logger);
					logger.debug("Copy array size: {}", copyArray.length);
					for (int i = 0; i < array.length; i = i + 1) {
						final Object objElem = array[i];
						copyArray[i] = singleClone(objElem, className);
					}
					copy = copyArray;
				} else {
					logger.debug("CREATING OBJECT OF CLASS: {}", className);
					copy = singleClone(obj, className);
				}
			} catch (IllegalArgumentException | SecurityException | IllegalAccessException | InvocationTargetException
					| InstantiationException e) {
				throw new ObjectClonerException(
						String.format("Error generating object for the class=[%s] (array=%s)", className, isArray), e);
			}
		}
		return copy;
	}

	/**
	 * Single clone.
	 *
	 * @param obj       the obj
	 * @param className the class name
	 * @return the object
	 * @throws IllegalAccessException    the illegal access exception
	 * @throws InvocationTargetException the invocation target exception
	 * @throws InstantiationException    the instantiation exception
	 */
	private static Object singleClone(Object obj, String className)
			throws IllegalAccessException, InvocationTargetException, InstantiationException {
		Object copy = null;
		if (PrimitiveType.isPrimitiveClass(className)) {
			logger.debug("Using primitive copy");
			copy = primitiveCopy(PrimitiveType.getFromClass(className), obj);
		} else if (ManagedType.isManaged(className)) {
			logger.debug("Using managed copy");
			copy = managedCopy(ManagedType.get(className), obj);
		} else {
			logger.debug("Using general copy");
			copy = generalClone(obj, className);
		}
		return copy;
	}

	/**
	 * General clone.
	 *
	 * @param obj       the obj
	 * @param className the class name
	 * @return the object
	 * @throws IllegalAccessException    the illegal access exception
	 * @throws InvocationTargetException the invocation target exception
	 * @throws InstantiationException    the instantiation exception
	 */
	private static Object generalClone(Object obj, String className)
			throws IllegalAccessException, InvocationTargetException, InstantiationException {
		Object copy = null;
		final Method clone = findMethod(obj.getClass(), "clone");
		if (Objects.nonNull(clone)) {
			logger.debug("Using clone()");
			copy = clone.invoke(obj);
		} else {
			final Constructor<?> constructor = findConstructor(obj.getClass(), className);
			if (Objects.nonNull(constructor)) {
				logger.debug("Using constructor()");
				copy = constructor.newInstance(obj);
			} else {
				logger.debug("Using field to field cloning");
				final List<FieldInfo> allFields = ReflectionUtils.getAllFields(obj.getClass());
				copy = ClazzUtils.createInstance(className, logger);
				for (final FieldInfo field : allFields) {
					final String typeName = getTypeName(field.getField(), field.getGenericClass());
					if (isUpdatable(field.getField())) {
						copyField(field.getField(), typeName, obj, copy);
					}
				}
			}
		}
		return copy;
	}

	/**
	 * Copy field.
	 *
	 * @param field     the field
	 * @param typeName  the type name
	 * @param objSource the obj source
	 * @param objDest   the obj dest
	 */
	private static void copyField(Field field, String typeName, Object objSource, Object objDest) {
		logger.debug("COPY FIELD {}: {}", field.getName(), typeName);
		final Object value = ReflectionUtils.getFieldValue(objSource, field);
		// Presuponemos que se trata de un objeto creado vacío: no hace falta informar
		// los nulos
		if (Objects.nonNull(value)) {
			if (CollectionUtils.isCollection(typeName)) {
				if (CollectionUtils.isList(typeName)) {
					logger.debug("COPY LIST COLLECTION");
					final List<?> copy = clone((List<?>) value);
					setFieldValue(objDest, field, copy);
				} else if (CollectionUtils.isSet(typeName)) {
					logger.debug("COPY SET COLLECTION");
					final Set<?> copy = clone((Set<?>) value);
					setFieldValue(objDest, field, copy);

				} else if (CollectionUtils.isMap(typeName)) {
					logger.debug("COPY MAP COLLECTION");
					final Map<?, ?> copy = clone((Map<?, ?>) value);
					setFieldValue(objDest, field, copy);

				} else {
					logger.warn("** CLONAR COLLECTION NO CONTEMPLADA{}", typeName);
				}

			} else if (PrimitiveType.isPrimitive(typeName)) {
				logger.debug("COPY PRIMITIVE TYPE");
				setFieldValue(objDest, field, value);
			} else {
				logger.debug("COPY OBJECT");
				final Object copy = clone(value);
				setFieldValue(objDest, field, copy);
			}
		}
	}

	/**
	 * Clone.
	 *
	 * @param <T>        the generic type
	 * @param collection the collection
	 * @return the list
	 */
	@SuppressWarnings("unchecked")
	public static <T> List<T> clone(List<T> collection) {
		List<T> cloned = null;
		if (collection instanceof ArrayList) {
			cloned = new ArrayList<>(collection.size());
		} else if (collection instanceof LinkedList) {
			cloned = new LinkedList<>();
		} else if (collection instanceof Vector) {
			cloned = new Vector<>(collection.size());
		} else if (collection instanceof Stack) {
			cloned = new Stack<>();
		}
		if (Objects.nonNull(cloned)) {
			for (final T item : collection) {
				cloned.add((T) ReflectionUtils.clone(item));
			}
		}
		return cloned;
	}

	/**
	 * Clone.
	 *
	 * @param <T>        the generic type
	 * @param collection the collection
	 * @return the sets the
	 */
	@SuppressWarnings("unchecked")
	public static <T> Set<T> clone(Set<T> collection) {
		Set<T> cloned = null;
		if (collection instanceof TreeSet) {
			cloned = new TreeSet<>();
		} else if (collection instanceof HashSet) {
			cloned = new HashSet<>();
		} else if (collection instanceof LinkedHashSet) {
			cloned = new LinkedHashSet<>();
		}
		if (Objects.nonNull(cloned)) {
			for (final T item : collection) {
				cloned.add((T) ReflectionUtils.clone(item));
			}
		}
		return cloned;
	}

	/**
	 * Clone.
	 *
	 * @param <K>        the key type
	 * @param <T>        the generic type
	 * @param collection the collection
	 * @return the map
	 */
	@SuppressWarnings("unchecked")
	public static <K, T> Map<K, T> clone(Map<K, T> collection) {
		Map<K, T> cloned = null;
		if (collection instanceof TreeMap) {
			cloned = new TreeMap<>();
		} else if (collection instanceof HashMap) {
			cloned = new HashMap<>();
		} else if (collection instanceof LinkedHashMap) {
			cloned = new LinkedHashMap<>();
		}
		if (Objects.nonNull(cloned)) {
			for (final Entry<K, T> entry : collection.entrySet()) {
				final K key = entry.getKey();
				final T item = entry.getValue();
				cloned.put(key, (T) ReflectionUtils.clone(item));
			}
		}
		return cloned;
	}

	/**
	 * Filter.
	 *
	 * @param <T>    the generic type
	 * @param object the object
	 * @param filter the filter
	 * @return true, if successful
	 */
	public static <T> boolean meetsFilter(T object, T filter) {
		boolean res = Objects.isNull(filter);
		if (ConditionUtils.allAreTrue(!res, Objects.nonNull(object))) {
			res = true;
			final List<FieldInfo> fields = getAllFields(object.getClass());
			for (final FieldInfo fieldInfo : fields) {
				if (!ConditionUtils.oneIsTrue(fieldInfo.getField().getType().isPrimitive(),
						CollectionUtils.isCollection(fieldInfo.getField().getType()))) {
					res = meetsField(fieldInfo, object, filter);
					if (!res) {
						break;
					}
				}
			}
		}
		return res;

	}

	/**
	 * Meets field.
	 *
	 * @param <T>       the generic type
	 * @param fieldInfo the field info
	 * @param object    the object
	 * @param filter    the filter
	 * @return true, if successful
	 */
	private static <T> boolean meetsField(FieldInfo fieldInfo, T object, T filter) {
		boolean res = true;
		final Object filterValue = getFieldValue(filter, fieldInfo.getField());
		if (Objects.nonNull(filterValue)) {
			final Object value = getFieldValue(object, fieldInfo.getField());
			if (Objects.nonNull(value)) {
				if (ManagedType.STRING.getClassName().equals(fieldInfo.getField().getType().getCanonicalName())) {
					final String filterString = (String) filterValue;
					final String matchString = filterString.replace("%", "");
					final String string = (String) value;
					// logger.debug("filtering by string: value={}; filter={}, match={}", string,
					// filterString,
					// matchString);
					// if (BooleanUtils.allAreTrue(filterString.startsWith("%"),
					// filterString.endsWith("%"))) {
					res = string.contains(matchString);
					// } else if (filterString.startsWith("%")) {
					// res = res && string.endsWith(matchString);
					// } else {
					// res = res && string.startsWith(matchString);
					// }
					logger.debug("Contains Meets for {}. Res={}", fieldInfo.getField().getName(), res);
				} else if (ConditionUtils.oneIsTrue(
						PrimitiveType.isPrimitive(fieldInfo.getField().getType().getCanonicalName()),
						ManagedType.isManaged(fieldInfo.getField().getType().getCanonicalName()))) {
					res = filterValue.equals(value);
					logger.debug("Equals Meets for {}. Res={}", fieldInfo.getField().getName(), res);
				} else {
					res = meetsFilter(value, filterValue);
					logger.debug("Sub-Object Meets for {}. Res={}", fieldInfo.getField().getName(), res);
				}
			} else {
				res = false;
			}
		}
		return res;
	}

	/**
	 * Gets the id.
	 *
	 * @param object  the object
	 * @param clazz   the clazz
	 * @param idClazz the id clazz
	 * @return the id
	 */
	public static Object getId(Object object, Class<?> clazz, Class<?> idClazz) {
		return getId(object, clazz, idClazz, "id");
	}

	/**
	 * Sets the id.
	 *
	 * @param object the object
	 * @param id     the id
	 * @param clazz  the clazz
	 */
	public static void setId(Object object, Object id, Class<?> clazz) {
		setId(object, id, clazz, "id");
	}

	/**
	 * Gets the id.
	 *
	 * @param object  the object
	 * @param clazz   the clazz
	 * @param idClazz the id clazz
	 * @param idName  the id name
	 * @return the id
	 */
	public static Object getId(Object object, Class<?> clazz, Class<?> idClazz, String idName) {
		Object res = null;
		final Method getter = ReflectionUtils.findGetter(clazz, idClazz, idName);
		if (Objects.nonNull(getter)) {
			try {
				res = getter.invoke(object);
			} catch (final InvocationTargetException | IllegalAccessException | IllegalArgumentException e) {
				logger.warn(String.format("Error obteniendo el valor del atributo=%s", idName), e);
			}
		} else {
			logger.warn("Error obteniendo el getter del atributo={}", idName);
		}
		return res;
	}

	/**
	 * Sets the id.
	 *
	 * @param object the object
	 * @param id     the id
	 * @param clazz  the clazz
	 * @param idName the id name
	 */
	public static void setId(Object object, Object id, Class<?> clazz, String idName) {
		final Method setter = ReflectionUtils.findSetter(clazz, idName);
		if (Objects.nonNull(setter)) {
			try {
				setter.invoke(object, id);
			} catch (final InvocationTargetException | IllegalAccessException | IllegalArgumentException e) {
				logger.warn(String.format("Error obteniendo el valor del atributo=%s", idName), e);
			}
		} else {
			logger.warn("Error estableciendo el setter del atributo={}", idName);
		}
	}

	/**
	 * Checks for annotation.
	 *
	 * @param clazz          the clazz
	 * @param annotationName the annotation name
	 * @return true, if successful
	 */
	public static boolean hasAnnotation(Class<?> clazz, String annotationName) {
		boolean res = false;
		for (final Annotation annotation : clazz.getAnnotations()) {
			if (annotation.annotationType().getCanonicalName().equals(annotationName)) {
				res = true;
				break;
			}
		}
		return res;
	}

	/**
	 * Checks for annotation.
	 *
	 * @param clazz          the clazz
	 * @param fieldName      the field name
	 * @param annotationName the annotation name
	 * @return true, if successful
	 */
	public static boolean hasAnnotation(Class<?> clazz, String fieldName, String annotationName) {
		final FieldInfo field = findField(clazz, fieldName);
		return hasAnnotation(field, annotationName);
	}

	/**
	 * Checks for annotation.
	 *
	 * @param field          the field
	 * @param annotationName the annotation name
	 * @return true, if successful
	 */
	public static boolean hasAnnotation(FieldInfo field, String annotationName) {
		boolean res = false;
		if (Objects.nonNull(field)) {
			for (final Annotation annotation : field.getField().getAnnotations()) {
				if (annotation.annotationType().getCanonicalName().equals(annotationName)) {
					res = true;
					break;
				}
			}
		}
		return res;
	}

	/**
	 * Checks for default constructor.
	 *
	 * @param className the class name
	 * @return true, if successful
	 */
	public static boolean hasDefaultConstructor(String className) {
		boolean res = false;
		if (!StringUtils.isAllBlank(className)) {
			try {
				Class.forName(className).getDeclaredConstructor();
				res = true;
			} catch (final NoSuchMethodException e) {
				// No hacer nada. Es correcto que pase por aquí si no existe
				res = false;
			} catch (final Exception e) {
				logger.error(String.format("Error looking for default constructor of class %s", className), e);
			}
		}
		return res;
	}

	/**
	 * Fill object.
	 *
	 * @param obj    the obj
	 * @param values the values
	 */
	public static void fillObject(Object obj, Map<String, Object> values) {
		if (ObjectUtils.allNotNull(obj, values)) {
			for (final Entry<String, Object> value : values.entrySet()) {
				final FieldInfo fieldInfo = ReflectionUtils.findField(obj.getClass(), value.getKey());
				if (Objects.nonNull(fieldInfo)) {
					ReflectionUtils.setFieldValue(obj, fieldInfo.getField(), value.getValue());
				}
			}
		}
	}

	/**
	 * Primitive copy.
	 *
	 * @param type the type
	 * @param obj  the obj
	 * @return the object
	 */
	private static Object primitiveCopy(PrimitiveType type, Object obj) {
		Object copy = null;
		if (PrimitiveType.BOOLEAN.equals(type)) {
			final boolean value = ((Boolean) obj).booleanValue();
			copy = Boolean.valueOf(value);
		} else if (PrimitiveType.BYTE.equals(type)) {
			final byte value = ((Byte) obj).byteValue();
			copy = Byte.valueOf(value);
		} else if (PrimitiveType.DOUBLE.equals(type)) {
			final double value = ((Double) obj).doubleValue();
			copy = Double.valueOf(value);
		} else if (PrimitiveType.FLOAT.equals(type)) {
			final float value = ((Float) obj).floatValue();
			copy = Float.valueOf(value);
		} else if (PrimitiveType.CHAR.equals(type)) {
			final char value = ((Character) obj).charValue();
			copy = Character.valueOf(value);
		} else if (PrimitiveType.SHORT.equals(type)) {
			final short value = ((Short) obj).shortValue();
			copy = Short.valueOf(value);
		} else if (PrimitiveType.INTEGER.equals(type)) {
			final int value = ((Integer) obj).intValue();
			copy = Integer.valueOf(value);
		} else if (PrimitiveType.LONG.equals(type)) {
			final long value = ((Long) obj).longValue();
			copy = Long.valueOf(value);
		}
		return copy;
	}

	/**
	 * Managed copy.
	 *
	 * @param type the type
	 * @param obj  the obj
	 * @return the object
	 */
	private static Object managedCopy(ManagedType type, Object obj) {
		Object copy = null;
		if (ManagedType.BIGDECIMAL.equals(type)) {
			copy = new BigDecimal(((BigDecimal) obj).toString());
		} else if (ManagedType.STRING.equals(type)) {
			copy = new String((String) obj);
		} else if (ManagedType.DATE.equals(type)) {
			copy = new Date(((Date) obj).getTime());
		} else if (ManagedType.LOCALDATETIME.equals(type)) {
			final LocalDateTime copied = (LocalDateTime) obj;
			copy = LocalDateTime.of(copied.getYear(), copied.getMonth(), copied.getDayOfMonth(), copied.getHour(),
					copied.getMinute(), copied.getSecond(), copied.getNano());
		} else if (ManagedType.LOCALDATE.equals(type)) {
			final LocalDate copied = (LocalDate) obj;
			copy = LocalDate.of(copied.getYear(), copied.getMonth(), copied.getDayOfMonth());
		} else if (ManagedType.TIMESTAMP.equals(type)) {
			copy = ((Timestamp) obj).clone();
		}
		return copy;
	}

}
