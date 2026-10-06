package org.gjs.java.test.mock;

import java.io.IOException;
import java.lang.reflect.Method;
import java.lang.reflect.ParameterizedType;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Objects;
import java.util.Optional;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.commons.lang3.ObjectUtils;
import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.data.DataKey;
import org.gjs.java.common.data.ForeignKey;
import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.files.FileObjects;
import org.gjs.java.common.type.DataObject;
import org.gjs.java.common.type.FieldInfo;
import org.gjs.java.common.type.WrappedObject;
import org.gjs.java.common.util.CollectionUtils;
import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.ConversionUtils;
import org.gjs.java.common.util.NormalizationUtils;
import org.gjs.java.common.util.ReflectionUtils;
import org.gjs.java.test.exception.ParameterizedTypeException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.core.io.Resource;

/**
 * The Class MockEntityDataManager.
 *
 * Clase de datos de la librería Gjs
 *
 * Implementa un repositorio de datos sencillo en memoria para cualquier clase
 * de objetos.
 *
 * @param <T>  la clase de la entidad
 * @param <PK> la clave primaria de la entidad
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 */

public class MockEntityDataManager<T, PK> {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(MockEntityDataManager.class);

	/** The entity clazz. */
	protected final Class<T> entityClazz;

	/** The pk clazz. */
	protected final Class<PK> pkClazz;

	/** The map entity. */
	private final Map<PK, T> mapEntity = new LinkedHashMap<>();

	/** The map relations. */
	protected final Map<ForeignKey, MockEntityDataManager<?, ?>> mapRelations = new ConcurrentHashMap<>();

	/** The map foreign collections. */
	protected final Map<ForeignKey, MockEntityDataManager<?, ?>> mapForeignCollections = new ConcurrentHashMap<>();

	/** The field correspondencies. */
	protected Map<String, String> fieldCorrespondencies = new ConcurrentHashMap<>();

	/** The complex id. */
	protected boolean complexId;

	/** The id name. */
	protected String idName;

	/**
	 * Instantiates a new mock entity data manager.
	 *
	 * PENDIENTE: Arreglar para que no sea necesario consultar el nombre de la
	 * superclase
	 *
	 */
	@SuppressWarnings("unchecked")
	public MockEntityDataManager() {
		idName = "id";
		try {
			entityClazz = (Class<T>) ((ParameterizedType) getClass().getGenericSuperclass())
					.getActualTypeArguments()[0];
			Class<?> classForPK = getClass();
			final String superClass = getClass().getSuperclass().getSimpleName();
			if (ConditionUtils.oneIsTrue("MockSimplePKRepository".equals(superClass),
					"MockStringPKRepository".equals(superClass))) {
				classForPK = getClass().getSuperclass();
			} else if (ConditionUtils.oneIsTrue("MockSimplePKEntityService".equals(superClass),
					"MockStringPKEntityService".equals(superClass))) {
				classForPK = getClass().getSuperclass();
			} else if (ConditionUtils.oneIsTrue("MockSimplePKEntityFromRepositoryService".equals(superClass),
					"MockStringPKEntityFromRepositoryService".equals(superClass))) {
				classForPK = getClass().getSuperclass();
			} else if ("MockCommonEntityService".equals(superClass)) {
				classForPK = getClass().getSuperclass().getSuperclass();
			}
			pkClazz = (Class<PK>) ((ParameterizedType) classForPK.getGenericSuperclass()).getActualTypeArguments()[1];
			this.complexId = !ConditionUtils.oneIsTrue(PrimitiveType.isPrimitive(pkClazz.getCanonicalName()),
					ManagedType.isManaged(pkClazz.getCanonicalName()));
		} catch (final ClassCastException e) {
			throw new ParameterizedTypeException(getClass().getCanonicalName(), e);
		}
	}

	/**
	 * Instantiates a new mock entity data manager.
	 *
	 * @param path the path
	 */
	public MockEntityDataManager(String path) {
		this();
		loadCsv(path);
	}

	/**
	 * Instantiates a new mock entity data manager.
	 *
	 * @param resource the resource
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	public MockEntityDataManager(Resource resource) throws IOException {
		this(resource.getFile().getAbsolutePath());
	}

	/**
	 * Gets the id name.
	 *
	 * @return the id name
	 */
	public String getIdName() {
		return idName;
	}

	/**
	 * Sets the id name.
	 *
	 * @param idName the new id name
	 */
	protected void setIdName(String idName) {
		this.idName = idName;
	}

	/**
	 * Adds the relation.
	 *
	 * @param key               the key
	 * @param entityDataManager the entity data manager
	 */
	public void addRelation(ForeignKey key, MockEntityDataManager<?, ?> entityDataManager) {
		if (ObjectUtils.allNotNull(key, entityDataManager)) {
			mapRelations.put(key, entityDataManager);
		}
	}

	/**
	 * Checks for relations.
	 *
	 * @return true, if successful
	 */
	public boolean hasRelations() {
		return !mapRelations.isEmpty();
	}

	/**
	 * Gets the relations.
	 *
	 * @return the relations
	 */
	public Map<ForeignKey, MockEntityDataManager<?, ?>> getRelations() {
		return mapRelations;
	}

	/**
	 * Adds the foreign collection.
	 *
	 * @param field             the field
	 * @param remoteField       the remote field
	 * @param entityDataManager the entity data manager
	 */
	public void addForeignCollection(String field, String remoteField, MockEntityDataManager<?, ?> entityDataManager) {
		if (ObjectUtils.allNotNull(field, remoteField, entityDataManager)) {
			mapForeignCollections.put(new ForeignKey(new DataKey(field), new DataKey(remoteField)), entityDataManager);
		}
	}

	/**
	 * Checks for foreign collections.
	 *
	 * @return true, if successful
	 */
	public boolean hasForeignCollections() {
		return !mapForeignCollections.isEmpty();
	}

	/**
	 * Gets the foreign collections.
	 *
	 * @return the foreign collections
	 */
	public Map<ForeignKey, MockEntityDataManager<?, ?>> getForeignCollections() {
		return mapForeignCollections;
	}

	/**
	 * Adds the field translation.
	 *
	 * @param fieldFrom the field from
	 * @param fieldTo   the field to
	 */
	public void addFieldTranslation(String fieldFrom, String fieldTo) {
		fieldCorrespondencies.put(fieldFrom, fieldTo);
	}

	/**
	 * Post load data tasks.
	 */
	public void postLoadDataTasks() {
		// Por defecto no hace nada
	}

	/**
	 * Load csv.
	 *
	 * @param resource the resource
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	public void loadCsv(Resource resource) throws IOException {
		loadCsv(resource.getFile().getAbsolutePath());
	}

	/**
	 * Load csv.
	 *
	 * @param path the path
	 */
	public void loadCsv(String path) {
		logger.debug("Loading data file={}", path);
		final FileObjects file = new FileObjects(',', path);
		if (file.isValid()) {
			for (int i = 0; i < file.count(); i = i + 1) {
				final DataObject dataObj = file.getObject(i);
				logger.debug("Object={}", dataObj);

				@SuppressWarnings("unchecked")
				final T obj = (T) dataObj.toObject(getClazz().getCanonicalName());
				if (Objects.nonNull(obj)) {

					if (complexId) {
						// Complex primary key
						resolveComplexPrimaryKey(dataObj, obj);
					}
					// Simple attribute name translation
					resolveFieldCorrespondencies(dataObj, obj);
					// Dependency objects:
					resolveDependecies(dataObj, obj);
					put(obj);
				} else {
					logger.warn("Object cannot loaded into class {}", getClazz().getCanonicalName());
				}
			}
			postLoadDataTasks();
		}
	}

	/**
	 * Resolve complex primary key.
	 *
	 * @param dataObj the data obj
	 * @param obj     the obj
	 */
	private void resolveComplexPrimaryKey(final DataObject dataObj, T obj) {
		logger.debug("Completing complex identifier object...");
		final FieldInfo fieldInfo = ReflectionUtils.findField(entityClazz, "id");
		if (Objects.nonNull(fieldInfo)) {
			logger.debug("ID of class {}", fieldInfo.getField().getType().getCanonicalName());
			@SuppressWarnings("unchecked")
			final PK idObject = (PK) dataObj.toObject(fieldInfo.getField().getType().getCanonicalName());
			if (Objects.nonNull(idObject)) {
				ReflectionUtils.setFieldValue(obj, fieldInfo.getField(), idObject);
			} else {
				logger.warn("Cannot create object of class {}", fieldInfo.getClazz().getCanonicalName());
			}
		} else {
			logger.warn("Not find metadata of field id");
		}
	}

	/**
	 * Resolve field correspondencies.
	 *
	 * @param dataObj the data obj
	 * @param obj     the obj
	 */
	private void resolveFieldCorrespondencies(DataObject dataObj, T obj) {
		for (final Entry<String, String> entry : fieldCorrespondencies.entrySet()) {
			final String field = entry.getKey();
			final String translatedField = entry.getValue();
			logger.debug("Translating field from {} to {}", field, translatedField);
			Object valueObject = dataObj.getValue(field);
			if (Objects.nonNull(valueObject)) {
				final FieldInfo fieldInfo = ReflectionUtils.findField(getClazz(), translatedField);
				if (Objects.nonNull(fieldInfo)) {
					final String type = ReflectionUtils.getTypeName(fieldInfo.getField(), fieldInfo.getGenericClass());
					valueObject = ConversionUtils.convertValue(type, fieldInfo.getField().getType().isArray(),
							valueObject);
					if (Objects.isNull(valueObject)) {
						logger.warn("VALUE {} OF TYPE {} CONVERTED TO NULL", valueObject, type);
					}
					ReflectionUtils.setFieldValue(obj, fieldInfo.getField(), valueObject);
				} else {
					logger.warn("Not find metadata of translated field {}/{}", field, translatedField);
				}
			}
		}
	}

	/**
	 * Resolve dependecies.
	 *
	 * @param dataObj the data obj
	 * @param obj     the obj
	 */
	private void resolveDependecies(DataObject dataObj, T obj) {
		for (final Entry<ForeignKey, MockEntityDataManager<?, ?>> entry : mapRelations.entrySet()) {
			final ForeignKey key = entry.getKey();
			logger.debug("Processing relation with fields {}", key);
			final DataObject keyData = new DataObject();
			for (int j = 0; j < key.countFields(); j = j + 1) {
				final String field = key.getField(j);
				final String remoteField = key.getRemoteField(j);
				keyData.setValue(remoteField, dataObj.getValue(field));
				if (dataObj.getValue(field) == null) {
					logger.warn("Value for remote field marked as null!");
				}
			}
			logger.debug("KeyData={}", keyData);
			final MockEntityDataManager<?, ?> dataManager = entry.getValue();
			if (Objects.nonNull(dataManager)) {
				final Object objPKKey = keyData.toObject(dataManager.getPKClazz().getCanonicalName());
				if (Objects.nonNull(objPKKey)) {
					final String fkFieldName = calculateFKFieldName(key, dataManager.getClazz());
					translateFKValue(dataManager, fkFieldName, keyData, objPKKey, obj);
				} else {
					logger.warn("Identifier for relation object for class {} created null",
							dataManager.getClazz().getCanonicalName());
				}
			} else {
				logger.warn("Relation object for key {} cannot be created", key);
			}
		}
	}

	/**
	 * Calculate FK field name.
	 *
	 * @param key         the key
	 * @param objectClass the object class
	 * @return the string
	 */
	private String calculateFKFieldName(ForeignKey key, Class<?> objectClass) {
		String keyField = key.getObjectName();
		if (StringUtils.isAllBlank(keyField)) {
			keyField = NormalizationUtils.normalizeAttributeName(objectClass.getSimpleName());
		}
		// El objeto podría tener un nombre diferente:
		final String translatedKeyField = fieldCorrespondencies.get(keyField);
		if (Objects.nonNull(translatedKeyField)) {
			keyField = translatedKeyField;
		}
		return keyField;
	}

	/**
	 * Refresh foreign collections.
	 */
	public void refreshForeignCollections() {
		if (hasForeignCollections()) {
			for (final T entity : getAll()) {
				for (final ForeignKey key : mapForeignCollections.keySet()) {
					final String field = key.getField(0);
					final String remoteField = key.getRemoteField(0);
					logger.debug("Collection's field ={} mapped by remote field={}", field, remoteField);
					refreshFK(entity, key, field, remoteField);
				}
			}
		}
	}

	/**
	 * Translate FK value.
	 *
	 * @param dataManager the data manager
	 * @param keyData     the key data
	 * @param objPKKey    the obj PK key
	 * @param obj         the obj
	 */
	private void translateFKValue(MockEntityDataManager<?, ?> dataManager, String keyField, DataObject keyData,
			Object objPKKey, T obj) {
		logger.debug("Find id={}. Total objects={}", objPKKey, dataManager.size());
		final Object objKey = dataManager.getObject(objPKKey);
		logger.debug("ObjKey={}", objKey);
		if (Objects.nonNull(objKey)) {
			logger.debug("KeyField={}", keyField);
			final FieldInfo fieldInfo = ReflectionUtils.findField(getClazz(), keyField);
			if (Objects.nonNull(fieldInfo)) {
				logger.debug("FiledInfo={}", fieldInfo.getField());
				ReflectionUtils.setFieldValue(obj, fieldInfo.getField(), objKey);
			} else {
				logger.warn("Cannot retrieve field {} in class {}", keyField, getClazz().getCanonicalName());
			}

		} else if (logger.isWarnEnabled()) {
			logger.warn("Identifier {} not exists in repository for class {}", keyData,
					dataManager.getClazz().getCanonicalName());
		}
	}

	/**
	 * Refresh FK.
	 *
	 * @param entity      the entity
	 * @param key         the key
	 * @param field       the field
	 * @param remoteField the remote field
	 */
	private void refreshFK(T entity, ForeignKey key, String field, String remoteField) {
		final FieldInfo fieldInfo = ReflectionUtils.findField(getClazz(), field);
		if (Objects.nonNull(fieldInfo)) {
			logger.debug("FieldInfo={}", fieldInfo.getField());
			final MockEntityDataManager<?, ?> mockForeignEntityDataManager = mapForeignCollections.get(key);
			if (Objects.nonNull(mockForeignEntityDataManager)) {
				final FieldInfo remoteFieldInfo = ReflectionUtils.findField(mockForeignEntityDataManager.getClazz(),
						remoteField);
				if (Objects.nonNull(remoteFieldInfo)) {
					logger.debug("RemoteFieldInfo={}", remoteFieldInfo.getField());
					final Collection<Object> value = getForeignCollection(entity, fieldInfo, remoteFieldInfo,
							mockForeignEntityDataManager);
					ReflectionUtils.setFieldValue(entity, fieldInfo.getField(), value);
				} else {
					logger.warn("Cannot retrieve field {} in class {}", remoteField,
							mockForeignEntityDataManager.getClazz().getCanonicalName());
				}
			} else {
				logger.warn("The foreign entity repository for field {} in class {} is null", field,
						getClazz().getCanonicalName());
			}
		} else {
			logger.warn("Cannot retrieve field {} in class {}", field, getClazz().getCanonicalName());
		}

	}

	/**
	 * Gets the foreign collection.
	 *
	 * @param entity                       the entity
	 * @param fieldInfo                    the field info
	 * @param remoteFieldInfo              the remote field info
	 * @param mockForeignEntityDataManager the mock foreign entity data manager
	 * @return the foreign collection
	 */
	private Collection<Object> getForeignCollection(T entity, FieldInfo fieldInfo, FieldInfo remoteFieldInfo,
			MockEntityDataManager<?, ?> mockForeignEntityDataManager) {
		Collection<Object> value = null;
		if (CollectionUtils.isList(fieldInfo.getField().getType())) {
			final List<Object> list = new ArrayList<>();
			value = list;
		} else if (CollectionUtils.isSet(fieldInfo.getField().getType())) {
			final Set<Object> set = new HashSet<>();
			value = set;
		} else {
			logger.warn("Collection of type {} not implemented", fieldInfo.getField().getType().getCanonicalName());
		}
		if (Objects.nonNull(value)) {
			for (final Object remoteEntity : mockForeignEntityDataManager.getAll()) {
				@SuppressWarnings("unchecked")
				final T remoteObject = (T) ReflectionUtils.getFieldValue(remoteEntity,
						remoteFieldInfo.getField().getName());
				if (entity.equals(remoteObject)) {
					logger.debug("Added remote {} to {}", remoteEntity, entity);
					value.add(remoteEntity);
				}
			}
		}
		return value;
	}

	/**
	 * Gets the id.
	 *
	 * @param entity the entity
	 * @return the id
	 */
	@SuppressWarnings("unchecked")
	protected PK getId(T entity) {
		return (PK) ReflectionUtils.getId(entity, getClazz(), getPKClazz(), idName);
	}

	/**
	 * Sets the id.
	 *
	 * @param entity the entity
	 * @param id     the id
	 */
	protected void setId(T entity, PK id) {
		ReflectionUtils.setId(entity, id, getClazz(), idName);
	}

	/**
	 * Gets the clazz.
	 *
	 * @return the clazz
	 */
	protected Class<?> getClazz() {
		return entityClazz;
	}

	/**
	 * Gets the PK clazz.
	 *
	 * @return the PK clazz
	 */
	protected Class<?> getPKClazz() {
		return pkClazz;
	}

	/**
	 * Find by field.
	 *
	 * @param fieldName the field name
	 * @param value     the value
	 * @return the list
	 */
	protected List<T> findByField(String fieldName, Object value) {
		final List<T> res = new ArrayList<>();
		if (Objects.nonNull(value)) {
			if (fieldName.contains(".")) {
				logger.debug("FieldName compuesto {}", fieldName);
				final String[] fieldNames = fieldName.split("\\.");
				res.addAll(findByFieldCascade(fieldNames, value));
			} else {
				final Method getter = ReflectionUtils.findGetter(getClazz(), fieldName);
				if (Objects.nonNull(getter)) {
					logger.debug("Obtenido Getter={}", getter.getName());
					filterByGetter(getAll(), res, getter, value);
				} else {
					logger.warn("Error obteniendo el getter del atributo={}", fieldName);
				}
			}
		}
		return res;
	}

	/**
	 * Find one by field.
	 *
	 * @param fieldName the field name
	 * @param value     the value
	 * @return the optional
	 */
	protected Optional<T> findOneByField(String fieldName, Object value) {
		Optional<T> res = Optional.empty();
		if (Objects.nonNull(value)) {
			final Method getter = ReflectionUtils.findGetter(getClazz(), fieldName);
			if (Objects.nonNull(getter)) {
				for (final T entity : getAll()) {
					final Object objValue = ReflectionUtils.getFieldValue(entity, getter);
					if (Objects.equals(objValue, value)) {
						res = Optional.ofNullable(entity);
						break;
					}
				}
			} else {
				logger.warn("Error obteniendo el getter del atributo={}", fieldName);
			}
		}
		return res;
	}

	/**
	 * Filter by getter.
	 *
	 * @param originals the originals
	 * @param results   the results
	 * @param getter    the getter
	 * @param value     the value
	 */
	protected void filterByGetter(List<T> originals, List<T> results, Method getter, Object value) {
		for (final T entity : originals) {
			final Object objValue = ReflectionUtils.getFieldValue(entity, getter);
			if (Objects.equals(objValue, value)) {
				results.add(entity);
			}
		}
	}

	/**
	 * Find by field cascade.
	 *
	 * @param fieldNames the field names
	 * @param value      the value
	 * @return the list
	 */
	private List<T> findByFieldCascade(String[] fieldNames, Object value) {
		final List<T> res = new ArrayList<>();
		logger.debug("{}", fieldNames.length);
		for (final T entity : getAll()) {
			final Object objValue = entity;
			if (!(objValue instanceof Collection) && objectMatch(fieldNames, value, objValue)) {
				res.add(entity);
			}
		}
		return res;
	}

	/**
	 * Object match.
	 *
	 * @param fieldNames the field names
	 * @param value      the value
	 * @param objValue   the obj value
	 * @return true, if successful
	 */
	private boolean objectMatch(String[] fieldNames, Object value, Object objValue) {
		boolean res = false;
		for (final String fieldName : fieldNames) {
			logger.debug("Buscando atributo {} en Objeto {} ", fieldName, objValue.getClass().getName());
			final Method getter = ReflectionUtils.findGetter(objValue.getClass(), fieldName);
			if (Objects.isNull(getter)) {
				logger.warn("Error obteniendo el getter del atributo={}", fieldName);
				objValue = null;
			} else {
				objValue = ReflectionUtils.getFieldValue(objValue, getter);
			}
			if (Objects.isNull(objValue)) {
				break;
			}
		}
		if (Objects.equals(objValue, value)) {
			res = true;
		}
		return res;
	}

	/**
	 * Exists.
	 *
	 * @param id the id
	 * @return true, if successful
	 */
	protected boolean exists(PK id) {
		boolean res = false;
		if (Objects.nonNull(id)) {
			res = mapEntity.containsKey(id);
		}
		return res;
	}

	/**
	 * Gets the.
	 *
	 * @param id the id
	 * @return the t
	 */
	protected T get(PK id) {
		T res = null;
		if (Objects.nonNull(id)) {
			res = mapEntity.get(id);
		}
		return res;
	}

	/**
	 * Gets the.
	 *
	 * @param id the id
	 * @return the t
	 */
	@SuppressWarnings("unchecked")
	protected T get(WrappedObject id) {
		return get((PK) id.get());
	}

	/**
	 * Gets the object.
	 *
	 * @param objectId the object id
	 * @return the object
	 */
	@SuppressWarnings("unchecked")
	protected T getObject(Object objectId) {
		PK id = (PK) objectId;
		for (final PK pk : mapEntity.keySet()) {
			if (pk.toString().equals(id.toString())) {
				id = pk;
				break;
			}
		}
		return get(id);
	}

	/**
	 * Size.
	 *
	 * @return the int
	 */
	protected int size() {
		return mapEntity.size();
	}

	/**
	 * Removes the.
	 *
	 * @param id the id
	 */
	protected void remove(PK id) {
		if (Objects.nonNull(id)) {
			mapEntity.remove(id);
		}
	}

	/**
	 * Process PK.
	 *
	 * @param id     the id
	 * @param entity the entity
	 * @return the pk
	 */
	protected PK processPK(PK id, T entity) {
		return id;
	}

	/**
	 * Put.
	 *
	 * @param entity the entity
	 */
	protected void put(T entity) {
		if (Objects.nonNull(entity)) {
			PK id = getId(entity);
			id = processPK(id, entity);
			if (Objects.nonNull(id)) {
				logger.debug("Put id={}; entity={}", id, entity);
				mapEntity.put(id, entity);
			} else {
				logger.warn("PUT ENTIDAD CON ID NULO: {}", entity);
			}
		} else {
			logger.warn("PUT ENTIDAD NULA");
		}
	}

	/**
	 * Put.
	 *
	 * @param entity the entity
	 */
	@SuppressWarnings("unchecked")
	protected void put(WrappedObject entity) {
		put((T) entity.get());
	}

	/**
	 * Gets the all.
	 *
	 * @return the all
	 */
	protected List<T> getAll() {
		return new ArrayList<>(mapEntity.values());
	}

	/**
	 * Gets the all PK.
	 *
	 * @return the all PK
	 */
	protected Set<PK> getAllPK() {
		return mapEntity.keySet();
	}

	/**
	 * Removes the all.
	 */
	protected void removeAll() {
		mapEntity.clear();
	}

	/**
	 * Clear.
	 */
	public void clear() {
		removeAll();
	}
}
