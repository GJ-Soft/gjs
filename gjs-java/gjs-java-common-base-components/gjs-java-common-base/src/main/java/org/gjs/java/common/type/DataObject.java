package org.gjs.java.common.type;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Objects;
import java.util.Set;


import org.apache.commons.collections4.MapUtils;
import org.apache.commons.lang3.StringUtils;
import org.slf4j.LoggerFactory;

import org.slf4j.Logger;
import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.util.ClazzUtils;
import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.ConversionUtils;
import org.gjs.java.common.util.ReflectionUtils;

/**
 * The Class DataObject.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase útil para contener los datos de cualquier clase de objetos en un simple mapa de atributos con sus valores.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class DataObject {

    /** The Constant logger. */
    private static final Logger logger = LoggerFactory.getLogger(DataObject.class);

    /**
     * The fields. NOTA: No puede usarse un ConcurrentHashMap porque se necesita que contenga valores nulos.
     **/
    private final Map<String, Object> fields = new HashMap<>();

    /**
     * Instantiates a new data object.
     */
    public DataObject() {
    }

    /**
     * Instantiates a new data object.
     *
     * @param values
     *            the values
     */
    public DataObject(Map<String, Object> values) {
        setValues(values);
    }

    /**
     * Instantiates a new data object.
     *
     * @param obj
     *            the obj
     */
    public DataObject(Object obj) {
        load(obj);
    }

    /**
     * Sets the value.
     *
     * @param field
     *            the field
     * @param value
     *            the value
     */
    public void setValue(String field, Object value) {
        if (!StringUtils.isAllBlank(field)) {
            synchronized (this) {
                fields.put(field, value);
            }
        }
    }

    /**
     * Gets the fields.
     *
     * @return the fields
     */
    public Set<String> getFields() {
        return fields.keySet();
    }

    /**
     * Sets the values.
     *
     * @param values
     *            the values
     */
    public void setValues(Map<String, Object> values) {
        if (!MapUtils.isEmpty(values)) {
            for (final Entry<String, Object> entry : values.entrySet()) {
                setValue(entry.getKey(), entry.getValue());
            }
        }
    }

    /**
     * Gets the values.
     *
     * @return the values
     */
    public Map<String, Object> getValues() {
        return fields;
    }

    /**
     * Checks for field.
     *
     * @param name
     *            the name
     * @return true, if successful
     */
    public boolean hasField(String name) {
        boolean res = false;
        if (!StringUtils.isAllBlank(name)) {
            res = fields.containsKey(name);
        }
        return res;
    }

    /**
     * Gets the value.
     *
     * @param name
     *            the name
     * @return the value
     */
    public Object getValue(String name) {
        Object res = null;
        if (!StringUtils.isAllBlank(name)) {
            res = fields.get(name);
        }
        return res;
    }

    /**
     * Num fields.
     *
     * @return the int
     */
    public int numFields() {
        return fields.size();
    }

    /**
     * Removes the field.
     *
     * @param name
     *            the name
     */
    public void removeField(String name) {
        if (hasField(name)) {
            synchronized (this) {
                fields.remove(name);
            }
        }
    }

    /**
     * Clear.
     */
    public void clear() {
        synchronized (this) {
            fields.clear();
        }
    }

    /**
     * Nullify.
     */
    public void nullify() {
        synchronized (this) {
            for (final String field : fields.keySet()) {
                fields.put(field, null);
            }
        }
    }

    /**
     * Load.
     *
     * @param obj
     *            the obj
     */
    public void load(Object obj) {
        clear();
        if (Objects.nonNull(obj)) {
            synchronized (this) {
                final List<FieldInfo> objectFields = ReflectionUtils.getAllFields(obj.getClass());
                for (final FieldInfo fieldInfo : objectFields) {
                    final String field = fieldInfo.getField().getName();
                    final Object value = ReflectionUtils.getFieldValue(obj, fieldInfo.getField());
                    setValue(field, value);
                }
            }
        }
    }

    /**
     * To object.
     *
     * @param className
     *            the class name
     * @return the object
     */
    public Object toObject(String className) {
        Object obj = null;
        logger.debug("DataObject to {}", className);
        if (ConditionUtils.oneIsTrue(PrimitiveType.isPrimitiveClass(className), ManagedType.isManaged(className))) {
            if (numFields() == 1) {
                logger.debug("Primitive or managed case");
                final String field = fields.keySet().toArray(new String[fields.size()])[0];
                obj = getValue(field);
            }
        } else {
            logger.debug("Generic case");
            obj = ClazzUtils.createInstance(className, null);
            if (Objects.nonNull(obj)) {
                for (final String field : getFields()) {
                    final FieldInfo fieldInfo = ReflectionUtils.findField(obj.getClass(), field);
                    if (Objects.nonNull(fieldInfo)) {
                        final Object value = getFieldValue(field, fieldInfo);
                        ReflectionUtils.setFieldValue(obj, fieldInfo.getField(), value);
                    } else {
                        logger.warn("Metadata of field {} not found in class {}", field,
                                obj.getClass().getCanonicalName());
                    }
                }
            }
        }
        return obj;
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder();
        sb.append("DataObject [");
        boolean inicio = true;
        for (final Entry<String, Object> entry : fields.entrySet()) {
            if (!inicio) {
                sb.append(", ");
            }
            sb.append(entry.getKey()).append('=').append(entry.getValue());
            inicio = false;
        }
        sb.append(']');
        return sb.toString();
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#hashCode() */

    @Override
    public int hashCode() {
        return Objects.hash(fields.values().toArray());
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#equals(java.lang.Object) */

    @Override
    public boolean equals(Object obj) {
        boolean res = false;
        if (this == obj) {
            res = true;
        } else if ((obj instanceof final DataObject other) && (fields.size() == other.getFields().size())) {
            res = true;
            for (final Entry<String, Object> entry : fields.entrySet()) {
                if (!Objects.equals(entry.getValue(), other.getValue(entry.getKey()))) {
                    res = false;
                    break;
                }
            }
        }
        return res;
    }

    /**
     * Gets the field value.
     *
     * @param field
     *            the field
     * @param fieldInfo
     *            the field info
     * @return the field value
     */
    private Object getFieldValue(String field, FieldInfo fieldInfo) {
        Object value = getValue(field);
        if (Objects.nonNull(value)) {
            final String type = ReflectionUtils.getTypeName(fieldInfo.getField(), fieldInfo.getGenericClass());
            logger.debug("Field {} of type {} (array={})", fieldInfo.getField().getName(), type,
                    fieldInfo.getField().getType().isArray());

            final Object convValue = ConversionUtils.convertValue(type, fieldInfo.getField().getType().isArray(),
                    value);
            if (Objects.isNull(convValue)) {
                logger.warn("VALUE {} OF TYPE {} CONVERTED TO NULL", value, type);
                if (!Object.class.getCanonicalName().equals(type)) {
                    logger.warn("### CLASS={} NOT MANAGED FOR CONVERSION", type);
                } else if (fieldInfo.getField().getType().isArray()) {
                    logger.warn("### ARRAY OF CLASS={} NOT MANAGED FOR CONVERSION", type);
                }
            }
            value = convValue;
        } else {
            logger.debug("Value of field {} is null", field);
        }
        return value;
    }

}
