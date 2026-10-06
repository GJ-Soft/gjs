package org.gjs.java.common.util;

import java.util.Arrays;
import java.util.Collection;
import java.util.Objects;
import java.util.Set;
import java.util.TreeSet;

import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class CollectionUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Rutinas de ayuda para manejarse con clases que tengan atributos que sean
 * colecciones de objetos en las rutinas de automatización de test de Gjs.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class CollectionUtils {

	/** The Constant COLLECTIONS. */
	private static final String[] COLLECTIONS = { "java.util.Collection", "java.util.List", "java.util.Set",
			"java.util.Map" };

	/** The Constant COLLECTIONS_LIST. */
	private static final String[] COLLECTIONS_LIST = { "java.util.List", "java.util.ArrayList", "java.util.LinkedList",
			"java.util.Vector", "java.util.Stack" };

	/** The Constant COLLECTIONS_SET. */
	private static final String[] COLLECTIONS_SET = { "java.util.Set", "java.util.TreeSet", "java.util.HashSet",
			"java.util.EnumSet", "java.util.LinkedHashSet" };

	/** The Constant COLLECTIONS_MAP. */
	private static final String[] COLLECTIONS_MAP = { "java.util.Map", "java.util.TreeMap", "java.util.HashMap",
			"java.util.EnumMap", "java.util.LinkedHashMap" };

	/** The collections. */
	private static Set<String> collectionsAll;

	/** The collections set. */
	private static Set<String> collectionsSet;

	/** The collections list. */
	private static Set<String> collectionsList;

	/** The collections map. */
	private static Set<String> collectionsMap;

	static {
		collectionsAll = new TreeSet<>();
		collectionsSet = new TreeSet<>();
		collectionsList = new TreeSet<>();
		collectionsMap = new TreeSet<>();
		collectionsAll.addAll(Arrays.asList(COLLECTIONS));
		collectionsSet.addAll(Arrays.asList(COLLECTIONS_SET));
		collectionsList.addAll(Arrays.asList(COLLECTIONS_LIST));
		collectionsMap.addAll(Arrays.asList(COLLECTIONS_MAP));
		collectionsAll.addAll(collectionsSet);
		collectionsAll.addAll(collectionsList);
		collectionsAll.addAll(collectionsMap);
	}

	/**
	 * Clase no instanciable.
	 */
	private CollectionUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Checks if is collection.
	 *
	 * @param clazz the clazz
	 * @return true, if is collection
	 */
	public static boolean isCollection(Class<?> clazz) {
		return isCollection(clazz.getCanonicalName());
	}

	/**
	 * Checks if is collection.
	 *
	 * @param className the class name
	 * @return true, if is collection
	 */
	public static boolean isCollection(String className) {
		return collectionsAll.contains(className);
	}

	/**
	 * Checks if is list.
	 *
	 * @param clazz the clazz
	 * @return true, if is list
	 */
	public static boolean isList(Class<?> clazz) {
		return isList(clazz.getCanonicalName());
	}

	/**
	 * Checks if is list.
	 *
	 * @param className the class name
	 * @return true, if is list
	 */
	public static boolean isList(String className) {
		return collectionsList.contains(className);
	}

	/**
	 * Checks if is sets the.
	 *
	 * @param clazz the clazz
	 * @return true, if is sets the
	 */
	public static boolean isSet(Class<?> clazz) {
		return isSet(clazz.getCanonicalName());
	}

	/**
	 * Checks if is sets the.
	 *
	 * @param className the class name
	 * @return true, if is sets the
	 */
	public static boolean isSet(String className) {
		return collectionsSet.contains(className);
	}

	/**
	 * Checks if is map.
	 *
	 * @param clazz the clazz
	 * @return true, if is map
	 */
	public static boolean isMap(Class<?> clazz) {
		return isMap(clazz.getCanonicalName());
	}

	/**
	 * Checks if is map.
	 *
	 * @param className the class name
	 * @return true, if is map
	 */
	public static boolean isMap(String className) {
		return collectionsMap.contains(className);
	}

	/**
	 * Contains.
	 *
	 * @param <T>        the generic type
	 * @param collection the collection
	 * @param value      the value
	 * @return true, if successful
	 */
	public static <T> boolean contains(final Collection<T> collection, T value) {
		boolean res = false;
		if (ConditionUtils.allAreTrue(!org.apache.commons.collections4.CollectionUtils.isEmpty(collection),
				Objects.nonNull(value))) {
			for (final Object obj : collection) {
				if (value.equals(obj)) {
					res = true;
					break;
				}
			}
		}
		return res;
	}

}
