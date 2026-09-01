package org.gjs.java.test.mock;

import java.util.Map;
import java.util.Objects;
import java.util.concurrent.ConcurrentHashMap;

import org.gjs.java.common.type.WrappedObject;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class MockModelDataManager.
 *
 * Clase de datos de la librería Gjs
 *
 * Implementa un conjunto de repositorio de datos sencillo en memoria. Esta
 * pensado para actuar como base de datos mock.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockModelDataManager {

	/** The Constant logger. */
	protected static final Logger logger = LoggerFactory.getLogger(MockModelDataManager.class);

	/** The map data base. */
	private final Map<String, MockEntityDataManager<?, ?>> mapDataBase = new ConcurrentHashMap<>();

	/**
	 * Instantiates a new mock model data manager.
	 */
	public MockModelDataManager() {
		// No hace nada
	}

	/**
	 * Adds the entity data manager.
	 *
	 * @param entityDataManger the entity data manger
	 */
	public void addEntityDataManager(MockEntityDataManager<?, ?> entityDataManger) {
		if (Objects.nonNull(entityDataManger)) {
			mapDataBase.put(entityDataManger.getClazz().getCanonicalName(), entityDataManger);
		}
	}

	/**
	 * Gets the entity data manager.
	 *
	 * @param clazz the clazz
	 * @return the entity data manager
	 */
	public MockEntityDataManager<?, ?> getEntityDataManager(Class<?> clazz) {
		return getEntityDataManager(clazz.getCanonicalName());
	}

	/**
	 * Gets the entity data manager.
	 *
	 * @param clazzName the clazz name
	 * @return the entity data manager
	 */
	public MockEntityDataManager<?, ?> getEntityDataManager(String clazzName) {
		return mapDataBase.get(clazzName);
	}

	/**
	 * Manage.
	 *
	 * @param clazz the clazz
	 * @return true, if successful
	 */
	public boolean manage(Class<?> clazz) {
		return manage(clazz.getCanonicalName());
	}

	/**
	 * Manage.
	 *
	 * @param clazzName the clazz name
	 * @return true, if successful
	 */
	public boolean manage(String clazzName) {
		return mapDataBase.containsKey(clazzName);
	}

	/**
	 * Put.
	 *
	 * @param entity the entity
	 */
	public void put(Object entity) {
		if (Objects.nonNull(entity)) {
			final MockEntityDataManager<?, ?> mockEntityDataManager = getEntityDataManager(
					entity.getClass().getCanonicalName());
			if (Objects.nonNull(mockEntityDataManager)) {
				mockEntityDataManager.put(WrappedObject.of(entity));
			}
		}
	}

	/**
	 * Gets the.
	 *
	 * @param id    the id
	 * @param clazz the clazz
	 * @return the object
	 */
	public Object get(Object id, Class<?> clazz) {
		return get(id, clazz.getCanonicalName());
	}

	/**
	 * Gets the.
	 *
	 * @param id        the id
	 * @param clazzName the clazz name
	 * @return the object
	 */
	public Object get(Object id, String clazzName) {
		Object res = null;
		final MockEntityDataManager<?, ?> mockEntityDataManager = getEntityDataManager(clazzName);
		if (Objects.nonNull(mockEntityDataManager)) {
			res = mockEntityDataManager.get(WrappedObject.of(id));
		}
		return res;
	}

	/**
	 * Refresh foreign collections.
	 */
	public void refreshForeignCollections() {
		for (final MockEntityDataManager<?, ?> mockEntityDataManager : mapDataBase.values()) {
			mockEntityDataManager.refreshForeignCollections();
		}
	}
}
