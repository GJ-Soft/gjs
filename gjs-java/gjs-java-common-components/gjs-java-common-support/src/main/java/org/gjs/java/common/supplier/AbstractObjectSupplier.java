package org.gjs.java.common.supplier;

import java.lang.reflect.Field;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Objects;
import java.util.Set;

import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.exception.ObjectSupplierException;
import org.gjs.java.common.supplier.random.AbstractRandomSupplier;
import org.gjs.java.common.type.FieldInfo;
import org.gjs.java.common.util.ClazzUtils;
import org.gjs.java.common.util.CollectionUtils;
import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.LogUtils;
import org.gjs.java.common.util.ReflectionUtils;
import org.gjs.java.common.util.SupplierUtils;
import org.slf4j.LoggerFactory;

/**
 * The Class AbstractObjectSupplier.
 *
 * Clase abstracta de datos de la librería Gjs
 *
 * Clase abtracta base para definir un generador de objetos de una clase
 * cualquiera. *
 *
 * PENDIENTE: Permitir definir el número de niveles a generar
 *
 * @param <T> la clase de objetos
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class AbstractObjectSupplier<T> extends AbstractRandomSupplier<T> {

	/** The Constant OBJECT_TYPE. */
	private static final String OBJECT_TYPE = "java.lang.Object";

	/** The manager. */
	private ObjectSupplierManager manager;

	/** The class name. */
	private String className;

	/** The inform collections. */
	private boolean informCollections = true;

	/** The inform all fields. */
	private boolean informAllFields = true;

	/** The min size collections. */
	private int minSizeCollections = 1;

	/** The max size collections. */
	private int maxSizeCollections = 5;

	/** The max level. */
	private int maxLevel = 2;

	/**
	 * Instantiates a new abstract object supplier.
	 *
	 * @param className the class name
	 */
	protected AbstractObjectSupplier(String className) {
		this(className, new ObjectSupplierManager());
	}

	/**
	 * Instantiates a new abstract object supplier.
	 *
	 * @param className the class name
	 * @param manager   the manager
	 */
	protected AbstractObjectSupplier(String className, ObjectSupplierManager manager) {
		this.className = className;
		this.manager = manager;
		if (Objects.nonNull(this.manager)) {
			this.manager.registerSupplier(getClassName(), this);
			this.setLogger(manager.getLogger());
		} else {
			this.setLogger(LoggerFactory.getLogger(getClass()));
		}
	}

	/**
	 * Gets the class name.
	 *
	 * @return the class name
	 */
	public String getClassName() {
		return className;
	}

	/**
	 * Checks if is inform collections.
	 *
	 * @return true, if is inform collections
	 */
	public boolean isInformCollections() {
		return informCollections;
	}

	/**
	 * Sets the inform collections.
	 *
	 * @param informCollections the new inform collections
	 */
	public void setInformCollections(boolean informCollections) {
		this.informCollections = informCollections;
	}

	/**
	 * Checks if is inform all fields.
	 *
	 * @return boolean
	 */
	public boolean isInformAllFields() {
		return informAllFields;
	}

	/**
	 * Sets the inform all fields.
	 *
	 * @param informAllFields the new inform all fields
	 */
	public void setInformAllFields(boolean informAllFields) {
		this.informAllFields = informAllFields;
	}

	/**
	 * Gets the min size collections.
	 *
	 * @return the min size collections
	 */
	public int getMinSizeCollections() {
		return minSizeCollections;
	}

	/**
	 * Gets the max size collections.
	 *
	 * @return the max size collections
	 */
	public int getMaxSizeCollections() {
		return maxSizeCollections;
	}

	/**
	 * Sets the min size collections.
	 *
	 * @param minSizeCollections the new min size collections
	 */
	public void setMinSizeCollections(int minSizeCollections) {
		this.minSizeCollections = minSizeCollections;
	}

	/**
	 * Sets the max size collections.
	 *
	 * @param maxSizeCollections the new max size collections
	 */
	public void setMaxSizeCollections(int maxSizeCollections) {
		this.maxSizeCollections = maxSizeCollections;
	}

	/**
	 * Gets the max level.
	 *
	 * @return the max level
	 */
	protected int getMaxLevel() {
		return maxLevel;
	}

	/**
	 * Sets the max level.
	 *
	 * @param maxLevel the new max level
	 */
	protected void setMaxLevel(int maxLevel) {
		this.maxLevel = maxLevel;
	}

	/**
	 * Generate supplied collection value.
	 *
	 * @param typeName       the type name
	 * @param subtypeName    the subtype name
	 * @param objectSupplier the object supplier
	 * @return the collection
	 */
	private Collection<?> generateSuppliedCollectionValue(String typeName, String subtypeName,
			AbstractObjectSupplier<?> objectSupplier) {
		final String _METHOD_ = LogUtils.getMethodName();
		Collection<?> value = null;
		logFormattedInfo(_METHOD_, "Se va a generar una colection: informCollections={}", informCollections);
		if (informCollections) {
			final boolean subInformCollections = objectSupplier.isInformCollections();
			objectSupplier.setInformCollections(false);
			logFormattedDebug(_METHOD_, "Generando ARRAY DE {} CON INFORMCOLLECTION={}", subtypeName,
					objectSupplier.isInformCollections());
			if (CollectionUtils.isList(typeName)) {
				final List<Object> list = new ArrayList<>();
				Collections.addAll(list, objectSupplier.getArray());
				value = list;
			} else if (CollectionUtils.isSet(typeName)) {
				final Set<Object> set = new HashSet<>();
				Collections.addAll(set, objectSupplier.getArray());
				value = set;

			} else {
				logWarn(_METHOD_, "Colecccion no implementada");
			}
			objectSupplier.setInformCollections(subInformCollections);
		}
		return value;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#getNullius()
	 */

	@Override
	@SuppressWarnings("unchecked")
	public T getNullius() {
		return (T) ClazzUtils.createInstance(className, getLogger());
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.testinggame.suppliers.Supplier#get()
	 */
	@Override
	public T get() {
		return get(0);
	}

	/**
	 * Gets the.
	 *
	 * @param level the level
	 * @return the t
	 */
	private T get(int level) {
		final String _METHOD_ = LogUtils.getMethodName();
		try {
			if (level > maxLevel) {
				return null;
			}
			@SuppressWarnings("unchecked")
			final T obj = (T) ClazzUtils.createInstance(className, getLogger());
			logFormattedDebug(_METHOD_, "Creating object of class: {}", className);
			if (Objects.nonNull(obj)) {
				if (ReflectionUtils.isParametrized(obj.getClass())) {
					logDebug(_METHOD_, "PARAMETRIZED CLASS FOUND");
				}
				final List<FieldInfo> allFields = ReflectionUtils.getAllFields(obj.getClass());
				final StringBuilder info = new StringBuilder();
				info.append("Fields:\n");
				for (final FieldInfo field : allFields) {
					info.append(field.getField().getName()).append(':')
							.append(field.getField().getType().getCanonicalName()).append(" Generic: ")
							.append(field.isFromGenericClass()).append(" Array: ")
							.append(field.getField().getType().isArray()).append('\n');
				}
				logFormattedDebug(_METHOD_, info.toString());
				for (final FieldInfo field : allFields) {
					logFormattedDebug(_METHOD_, "PROCESANDO {}", field.getField().getName());
					supplyField(obj, field, level);
				}
			}
			return obj;
		} catch (IllegalArgumentException | SecurityException e) {
			throw new ObjectSupplierException(String.format("Error generating object for the class=[%s]", className),
					e);
		}
	}

	/**
	 * Supply field.
	 *
	 * @param obj   the obj
	 * @param field the field
	 * @param level the level
	 */
	private void supplyField(T obj, FieldInfo field, int level) {
		final String _METHOD_ = LogUtils.getMethodName();
		// if (field.isFromGenericClass()) {
		// logFormattedDebug(_METHOD_,"WARN: CASO NORMAL FIELD {} OF GENERIC CLASS: {}",
		// field.getField().getName(),
		// field.getGenericClass().getTypeName());
		// }
		final String typeName = ReflectionUtils.getTypeName(field.getField(), field.getGenericClass());
		boolean inform = !ConditionUtils.oneIsTrue(field.getField().isSynthetic(), field.getField().isEnumConstant());
		if (!informAllFields) {
			logFormattedDebug(_METHOD_, "FIELD: {}  OF TYPE: {}", field.getField().getName(), typeName);
			inform = ConditionUtils.allAreTrue(inform, random.nextBoolean());
		}
		if (inform) {
			logFormattedDebug(_METHOD_, "UPDATING FIELD {} OF TYPE {} (Array={})", field.getField().getName(), typeName,
					field.getField().getType().isArray());
			updateField(field.getField(), typeName, obj, level);
		}

	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.testinggame.suppliers.Supplier#get()
	 */
	@Override
	public T getEmpty() {
		try {
			@SuppressWarnings("unchecked")
			final T obj = (T) ClazzUtils.createInstance(className, getLogger());
			if (Objects.nonNull(obj)) {
				final List<FieldInfo> allFields = ReflectionUtils.getAllFields(obj.getClass());
				for (final FieldInfo field : allFields) {
					// if (field.isFromGenericClass()) {
					// logFormattedDebug(_METHOD_,"WARN: CASO EMPTY FIELD {} OF GENERIC CLASS: {}",
					// field.getField().getName(),
					// field.getGenericClass().getTypeName());
					// }
					final String typeName = ReflectionUtils.getTypeName(field.getField(), field.getGenericClass());
					final boolean inform = !ConditionUtils.oneIsTrue(field.getField().isSynthetic(),
							field.getField().isEnumConstant());
					if (inform) {
						updateEmptyField(field.getField(), typeName, obj);
					}
				}
			}
			return obj;
		} catch (IllegalArgumentException | SecurityException e) {
			throw new ObjectSupplierException(String.format("Error generating object for the class=[%s]", className),
					e);
		}
	}

	/**
	 * Gets the type name.
	 *
	 * @param type the type
	 * @return the type name
	 */
	private String getTypeName(Type type) {
		return type.getTypeName().replace("[]", "");
	}

	/**
	 * Update field.
	 *
	 * @param field    the field
	 * @param typeName the type name
	 * @param obj      the obj
	 * @param level    the level
	 */
	private void updateField(Field field, String typeName, Object obj, int level) {
		final String _METHOD_ = LogUtils.getMethodName();
		logFormattedDebug(_METHOD_, "UPDATE FIELD {}:{}", field.getName(), typeName);
		if (PrimitiveType.isPrimitive(typeName)) {
			logDebug(_METHOD_, "UPDATE PRIMITIVE TYPE");
			updatePrimitiveField(field, typeName, obj);
		} else if (ManagedType.isManaged(typeName)) {
			logDebug(_METHOD_, "UPDATE MANAGED TYPE");
			updateManagedField(field, typeName, obj);
		} else if ((field.getGenericType() instanceof ParameterizedType)) {
			logDebug(_METHOD_, "UPDATE PARAMETRIZED TYPE");
			updateParametrizedField(field, typeName, obj);
		} else if (Objects.nonNull(manager)) {
			logDebug(_METHOD_, "UPDATE SUPPLIED TYPE " + typeName);
			AbstractObjectSupplier<?> objectSupplier = findSupplier(typeName);
			if (Objects.isNull(objectSupplier)) {
				logFormattedWarn(_METHOD_, "NO ENCONTRADO SUPLIER DE TIPO {}", typeName);
				objectSupplier = new GenericObjectSupplier(typeName);
			}
			updateSuppliedField(field, typeName, obj, objectSupplier, level);
		} else {
			logFormattedWarn(_METHOD_, "NO HAY MANAGER PARA GENERAR {}", typeName);
		}
	}

	/**
	 * Find supplier.
	 *
	 * @param typeName the type name
	 * @return the abstract object supplier
	 */
	private AbstractObjectSupplier<?> findSupplier(String typeName) {
		final String _METHOD_ = LogUtils.getMethodName();
		AbstractObjectSupplier<?> objectSupplier = manager.findSupplier(typeName);
		if (Objects.isNull(objectSupplier)) {
			logDebug(_METHOD_, "No encontrado supplier del tipo {} buscando el supplier por defecto...");
			objectSupplier = manager.findSupplier(OBJECT_TYPE);
		}
		return objectSupplier;
	}

	/**
	 * Update primitive field.
	 *
	 * @param field    the field
	 * @param typeName the type name
	 * @param obj      the obj
	 */
	private void updatePrimitiveField(Field field, String typeName, Object obj) {
		final String _METHOD_ = LogUtils.getMethodName();
		if (!field.getType().isArray()) {
			Object value;
			logFormattedDebug(_METHOD_, "updatePrimitiveField: Class {}", typeName);
			value = SupplierUtils.generatePrimitiveValue(typeName);
			if (Objects.isNull(value)) {
				throw new ObjectSupplierException(String.format("CAMPO %s DE TIPO PRIMITIVO NO TRATADO: [%s]",
						field.getName(), ReflectionUtils.getTypeName(field)));
			}
			ReflectionUtils.setFieldValue(obj, field, value);
		} else if (PrimitiveType.isPrimitiveClass(typeName)) {
			logFormattedDebug(_METHOD_, "updatePrimitiveField: Class Array {}", typeName);
			final Object[] value = SupplierUtils.generateArrayPrimitiveValue(typeName);
			setArrayField(obj, field, value);
		} else {
			logFormattedDebug(_METHOD_, "updatePrimitiveField: Native Array {}", typeName);
			final Object value = SupplierUtils.generateArrayPrimitiveNativeValue(typeName);
			ReflectionUtils.setFieldValue(obj, field, value);
		}
	}

	/**
	 * Update managed field.
	 *
	 * @param field    the field
	 * @param typeName the type name
	 * @param obj      the obj
	 */
	private void updateManagedField(Field field, String typeName, Object obj) {
		final String _METHOD_ = LogUtils.getMethodName();
		logDebug(_METHOD_, "updateManagedField");
		if (!field.getType().isArray()) {
			final Object value = SupplierUtils.generateManagedValue(typeName);
			ReflectionUtils.setFieldValue(obj, field, value);
		} else {
			logFormattedInfo(_METHOD_, "RELLENANDO ARRAY TIPO MANAGED {}", typeName);
			final Object[] value = SupplierUtils.generateArrayManagedValue(typeName);
			setArrayField(obj, field, value);
		}
	}

	/**
	 * Update supplied field.
	 *
	 * @param field          the field
	 * @param typeName       the type name
	 * @param obj            the obj
	 * @param objectSupplier the object supplier
	 * @param level          the level
	 */
	private void updateSuppliedField(Field field, String typeName, Object obj, AbstractObjectSupplier<?> objectSupplier,
			int level) {
		final String _METHOD_ = LogUtils.getMethodName();
		final boolean subInformCollections = objectSupplier.isInformCollections();
		logFormattedDebug(_METHOD_, "updateSuppliedField {}", typeName);
		objectSupplier.setInformCollections(false);
		if (!field.getType().isArray()) {
			logFormattedDebug(_METHOD_, "Generando OBJETO {} CON INFORMCOLLECTION={}", typeName,
					objectSupplier.isInformCollections());
			final Object value = objectSupplier.get(level + 1);
			logFormattedDebug(_METHOD_, "GENERADO: {}", value);
			ReflectionUtils.setFieldValue(obj, field, value);
		} else {
			logFormattedDebug(_METHOD_, "Generando ARRAY DE {} CON INFORMCOLLECTION={}", typeName,
					objectSupplier.isInformCollections());
			final Object[] value = objectSupplier.getArray();
			setArrayField(obj, field, value);
		}
		objectSupplier.setInformCollections(subInformCollections);
	}

	/**
	 * Update parametrized field.
	 *
	 * PENDIENTES: Caso array of Collection???
	 *
	 * Pensando en tener suppliers de List<x> en lugar de esto
	 *
	 * @param field    the field
	 * @param typeName the type name
	 * @param obj      the obj
	 */
	private void updateParametrizedField(Field field, String typeName, Object obj) {
		final String _METHOD_ = LogUtils.getMethodName();
		logDebug(_METHOD_, "updateParametrizedField");
		if (!field.getType().isArray()) {
			logFormattedDebug(_METHOD_, "COLLECTION={}", typeName);
			final ParameterizedType parametrizedType = (ParameterizedType) field.getGenericType();
			if (parametrizedType.getActualTypeArguments().length == 1) {
				final Type argType = parametrizedType.getActualTypeArguments()[0];
				final String subtypeName = getTypeName(argType);
				logFormattedDebug(_METHOD_, "SUBTIPO= {}", subtypeName);
				final Collection<?> collection = generateSimpleCollection(typeName, subtypeName);
				if (Objects.nonNull(collection)) {
					ReflectionUtils.setFieldValue(obj, field, collection);
				}
			} else {
				logWarn(_METHOD_, "COLLECTION DE MULTIPLES TIPOS: CASO NO IMPLEMENTADO");
			}
		} else {
			logWarn(_METHOD_, "ARRAY DE COLLECTION: CASO NO IMPLEMENTADO");
		}
	}

	/**
	 * Generate simple collection.
	 *
	 * @param typeName    the type name
	 * @param subtypeName the subtype name
	 * @return the collection
	 */
	private Collection<?> generateSimpleCollection(String typeName, String subtypeName) {
		final String _METHOD_ = LogUtils.getMethodName();
		Collection<?> collection = null;
		if (PrimitiveType.isPrimitive(subtypeName)) {
			if (PrimitiveType.isPrimitiveClass(subtypeName)) {
				logInfo(_METHOD_, "Generando COLLECTION caso PRIMITIVO");
				collection = SupplierUtils.generateCollectionPrimitiveValue(typeName, subtypeName);
			} else {
				logError(_METHOD_, "Una coleccion no puede ser de un tipo primitivo");
			}
		} else if (ManagedType.isManaged(subtypeName)) {
			logInfo(_METHOD_, "Generando COLLECTION caso MANAGED");
			collection = SupplierUtils.generateCollectionManagedValue(typeName, subtypeName);
		} else if (Objects.nonNull(manager)) {
			logInfo(_METHOD_, "Generando COLLECTION caso SUPPLIED");
			final AbstractObjectSupplier<?> subobjectSupplier = findSupplier(subtypeName);
			if (Objects.nonNull(subobjectSupplier)) {
				collection = generateSuppliedCollectionValue(typeName, subtypeName, subobjectSupplier);
			}
			// throw new ObjectSupplierException(String.format("The class=[%s] has no
			// ObjectSupplier",
			// subtypeName));

		} else {
			logFormattedWarn(_METHOD_, "NO HAY MANAGER PARA GENERAR {}", subtypeName);
		}
		return collection;
	}

	/**
	 * Update empty field.
	 *
	 * @param field    the field
	 * @param typeName the type name
	 * @param obj      the obj
	 */
	private void updateEmptyField(Field field, String typeName, Object obj) {
		final String _METHOD_ = LogUtils.getMethodName();
		logFormattedDebug(_METHOD_, "updateEmptyField {}", field.getName());
		if (PrimitiveType.isPrimitive(typeName)) {
			if (!field.getType().isArray()) {
				Object value;
				value = SupplierUtils.generateEmptyPrimitiveValue(typeName);
				if (Objects.isNull(value)) {
					throw new ObjectSupplierException(String.format("CAMPO %s DE TIPO PRIMITIVO NO TRATADO: [%s]",
							field.getName(), ReflectionUtils.getTypeName(field)));
				}
				ReflectionUtils.setFieldValue(obj, field, value);
			} else if (PrimitiveType.isPrimitiveClass(typeName)) {
				logFormattedDebug(_METHOD_, "RELLENANDO ARRAY TIPO PRIMITIVO CLASE {}", typeName);
				final Object[] value = SupplierUtils.generateEmptyArrayPrimitiveValue(typeName);
				setArrayField(obj, field, value);
			} else {
				logFormattedDebug(_METHOD_, "RELLENANDO ARRAY TIPO PRIMITIVO NATIVO  {}", typeName);
				final Object value = SupplierUtils.generateEmptyArrayPrimitiveNativeValue(typeName);
				ReflectionUtils.setFieldValue(obj, field, value);
			}
		} else if (ManagedType.isManaged(typeName)) {
			if (!field.getType().isArray()) {
				final Object value = SupplierUtils.generateEmptyManagedValue(typeName);
				ReflectionUtils.setFieldValue(obj, field, value);
			} else {
				final Object[] value = SupplierUtils.generateEmptyArrayManagedValue(typeName);
				setArrayField(obj, field, value);
			}
		} else if (!field.getType().isArray()) {
			final Object value = null;
			ReflectionUtils.setFieldValue(obj, field, value);
		} else {
			final Object[] value = new Object[0];
			setArrayField(obj, field, value);
		}
	}

	/**
	 * Sets the array field.
	 *
	 * @param obj   the obj
	 * @param field the field
	 * @param value the value
	 */
	private void setArrayField(Object obj, Field field, Object... value) {
		final String _METHOD_ = LogUtils.getMethodName();
		logFormattedDebug(_METHOD_, "setArrayFieldvalue {}", field.getName());
		final String typeName = ReflectionUtils.getTypeName(field);
		if ((value.length > 0) && !Arrays.stream(value).allMatch(Objects::nonNull)) {
			throw new ObjectSupplierException(String.format("ARRAY MAL GENERADO: [%s]", typeName));
		}
		ReflectionUtils.setFieldValue(obj, field, value);
	}

}
