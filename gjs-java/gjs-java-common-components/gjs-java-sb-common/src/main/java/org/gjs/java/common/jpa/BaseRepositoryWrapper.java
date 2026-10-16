package org.gjs.java.common.jpa;

import java.io.IOException;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.files.FileObjects;
import org.gjs.java.common.type.DataObject;
import org.gjs.java.common.type.FieldInfo;
import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.ConversionUtils;
import org.gjs.java.common.util.ReflectionUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.core.io.Resource;
import org.springframework.data.repository.CrudRepository;
import org.springframework.util.CollectionUtils;

import lombok.Getter;
import lombok.Setter;

/**
 * Class BaseRepositoryWrapper.
 *
 * Clase abtracta de datos de la librería Gjs
 *
 * Clase abstracta que permite recubrir un repositorio cualquiera.
 *
 * @param <T>  la clase de objetos
 * @param <ID> la clase del identificador o clave primaria del objeto
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
public abstract class BaseRepositoryWrapper<T, ID> {

	/** The Constant logger. */
	protected Logger logger = LoggerFactory.getLogger(BaseRepositoryWrapper.class);

	/** The entity. */
	protected Class<T> entity;

	/** The pk. */
	protected Class<ID> pk;

	/** The complex id. */
	protected boolean complexId;

	/** The loaded. */
	protected boolean loaded;

	/** The data file. */
	@Setter
	protected String dataFile;

	/** The field correspondencies. */
	@Setter
	protected Map<String, String> fieldCorrespondencies;

	/**
	 * Instantiates a new crud getRepository() wrapper.
	 *
	 * @param entity the entity
	 * @param pk     the pk
	 * @param logger the logger
	 */
	protected BaseRepositoryWrapper(Class<T> entity, Class<ID> pk, Logger logger) {
		this.entity = entity;
		this.pk = pk;
		this.logger = logger;
		this.complexId = !ConditionUtils.oneIsTrue(PrimitiveType.isPrimitive(pk.getCanonicalName()),
				ManagedType.isManaged(pk.getCanonicalName()));
		this.loaded = false;
	}

	/**
	 * Instantiates a new crud getRepository() wrapper.
	 *
	 * @param entity   the entity
	 * @param pk       the pk
	 * @param dataFile the data file
	 * @param logger   the logger
	 */
	protected BaseRepositoryWrapper(Class<T> entity, Class<ID> pk, String dataFile, Logger logger) {
		this(entity, pk, logger);
		this.dataFile = dataFile;
	}

	/**
	 * Gets the repository.
	 *
	 * @return the repository
	 */
	public abstract CrudRepository<T, ID> getRepository();

	/**
	 * Load csv.
	 */
	public void loadCsv() {
		if (!StringUtils.isAllBlank(dataFile)) {
			loadCsv(dataFile);
		}
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
	 * Post load csv tasks.
	 */
	protected void postLoadCsvTasks() {
	}

	/**
	 * Load csv.
	 *
	 * @param path the path
	 */
	public void loadCsv(String path) {
		logger.debug("Loading data file {}", path);
		if (!loaded) {
			dataFile = path;
			final FileObjects file = new FileObjects(',', path);
			logger.debug("File is valid: {}", file.isValid());
			logger.debug("File count: {}", file.count());
			if (ConditionUtils.allAreTrue(file.isValid(), Objects.nonNull(getRepository()))) {
				loadDependencies();
				for (int i = 0; i < file.count(); i = i + 1) {
					final DataObject dataObj = file.getObject(i);
					logger.debug("Object={}", dataObj);
					loadObject(dataObj);
				}
			}
			loaded = true;
			postLoadCsvTasks();
		}
	}

	/**
	 * Load object.
	 *
	 * @param dataObj the data obj
	 */
	private void loadObject(DataObject dataObj) {
		@SuppressWarnings("unchecked")
		final T obj = (T) dataObj.toObject(entity.getCanonicalName());
		if (Objects.nonNull(obj)) {
			// Complex primary key
			if (complexId) {
				processComplexId(dataObj, obj);
			}
			// Simple attribute name translation
			resolveFieldCorrespondencies(dataObj, obj);
			// Dependency objects:
			resolveDependecies(dataObj, obj);
			getRepository().save(obj);
		} else {
			logger.warn("Object cannot loaded into class {}", entity.getCanonicalName());
		}
	}

	/**
	 * Load dependencies.
	 */
	protected abstract void loadDependencies();

	/**
	 * Checks if is field to translate.
	 *
	 * @param field the field
	 * @return true, if is field to translate
	 */
	protected abstract boolean isFieldToTranslate(String field);

	/**
	 * Resolve dependecies.
	 *
	 * @param dataObj the data obj
	 * @param obj     the obj
	 */
	protected abstract void resolveDependecies(DataObject dataObj, T obj);

	/**
	 * Process complex id.
	 *
	 * @param dataObj the data obj
	 * @param obj     the obj
	 */
	private void processComplexId(DataObject dataObj, T obj) {
		logger.debug("Completing complex identifier object...");
		final FieldInfo fieldInfo = ReflectionUtils.findField(getEntity(), "id");
		if (Objects.nonNull(fieldInfo)) {
			logger.debug("ID of class {}", fieldInfo.getField().getType().getCanonicalName());
			@SuppressWarnings("unchecked")
			final ID idObject = (ID) dataObj.toObject(fieldInfo.getField().getType().getCanonicalName());
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
		if (!CollectionUtils.isEmpty(fieldCorrespondencies)) {
			for (final String field : fieldCorrespondencies.keySet()) {
				if (isFieldToTranslate(field)) {
					final String translatedField = getFinalFieldName(field);
					logger.debug("Translating field from {} to {}", field, translatedField);
					translateValue(field, translatedField, dataObj, obj);
				}
			}
		}
	}

	/**
	 * Translate value.
	 *
	 * @param field           the field
	 * @param translatedField the translated field
	 * @param dataObj         the data obj
	 * @param obj             the obj
	 */
	private void translateValue(String field, String translatedField, DataObject dataObj, T obj) {
		Object valueObject = dataObj.getValue(field);
		if (Objects.nonNull(valueObject)) {
			final FieldInfo fieldInfo = ReflectionUtils.findField(getEntity(), translatedField);
			if (Objects.nonNull(fieldInfo)) {
				final String type = ReflectionUtils.getTypeName(fieldInfo.getField(), fieldInfo.getGenericClass());
				valueObject = ConversionUtils.convertValue(type, fieldInfo.getField().getType().isArray(), valueObject);
				if (Objects.isNull(valueObject)) {
					logger.warn("VALUE {} OF TYPE {} CONVERTED TO NULL", valueObject, type);
				}
				ReflectionUtils.setFieldValue(obj, fieldInfo.getField(), valueObject);
			} else {
				logger.warn("Not find metadata of translated field {}/{}", field, translatedField);
			}
		}

	}

	/**
	 * Assign dependency obj.
	 *
	 * @param <PK>             the generic type
	 * @param field            the field
	 * @param obj              the obj
	 * @param id               the id
	 * @param simpleDependency the simple dependency
	 */
	private <PK> void assignDependencyObj(String field, T obj, PK id, BaseRepositoryWrapper<?, PK> simpleDependency) {
		final Optional<?> dependencyObj = simpleDependency.getRepository().findById(id);
		logger.debug("Dependency object={}", dependencyObj);
		if (dependencyObj.isPresent()) {
			final String entityField = getFinalFieldName(field);
			logger.debug("Setting object into field {}", entityField);
			final FieldInfo fieldInfo = ReflectionUtils.findField(getEntity(), entityField);
			if (Objects.nonNull(fieldInfo)) {
				ReflectionUtils.setFieldValue(obj, fieldInfo.getField(), dependencyObj.get());
			} else {
				logger.warn("Not find metadata of field {}", entityField);
			}
		} else {
			logger.warn("Remote object for dependency field {}={} is null", field, id);
		}

	}

	/**
	 * Assign dependency field by long id.
	 *
	 * @param dataObj          the data obj
	 * @param obj              the obj
	 * @param field            the field
	 * @param simpleDependency the simple dependency
	 */
	protected void assignDependencyFieldByLongId(DataObject dataObj, T obj, String field,
			BaseRepositoryWrapper<?, Long> simpleDependency) {
		Long id = null;
		final Object idObject = dataObj.getValue(field);
		if (Objects.nonNull(idObject)) {
			id = Long.parseLong(idObject.toString());
		}
		if (Objects.nonNull(id)) {
			assignDependencyObj(field, obj, id, simpleDependency);
		} else {
			logger.debug("Value for dependency field {} is null", field);
		}
	}

	/**
	 * Assign dependency field by string id.
	 *
	 * @param dataObj          the data obj
	 * @param obj              the obj
	 * @param field            the field
	 * @param simpleDependency the simple dependency
	 */
	protected void assignDependencyFieldByStringId(DataObject dataObj, T obj, String field,
			BaseRepositoryWrapper<?, String> simpleDependency) {
		String id = null;
		final Object idObject = dataObj.getValue(field);
		if (Objects.nonNull(idObject)) {
			id = ConversionUtils.toString(idObject);
		}
		if (Objects.nonNull(id)) {
			assignDependencyObj(field, obj, id, simpleDependency);
		} else {
			logger.debug("Value for dependency field {} is null", field);
		}
	}

	/**
	 * Gets the final field name.
	 *
	 * @param field the field
	 * @return the final field name
	 */
	protected String getFinalFieldName(String field) {
		String finalField = field;
		// No con ConditionUtils: con varargs, Java evalúa todos los argumentos antes
		// de la llamada, y el que usa fieldCorrespondencies se evaluaría aunque fuese nulo.
		if (!CollectionUtils.isEmpty(fieldCorrespondencies) && fieldCorrespondencies.containsKey(field)) {
			finalField = fieldCorrespondencies.get(field);
		}
		return finalField;
	}
}
