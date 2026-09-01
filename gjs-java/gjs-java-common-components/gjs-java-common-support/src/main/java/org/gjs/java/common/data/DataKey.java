package org.gjs.java.common.data;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class DataKey.
 *
 * Clase de datos de la librería Gjs
 *
 * Representa una lista de atributos que compone una clave única de algún objeto de datos.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class DataKey {

    /** The fields. */
    protected final List<String> fields = new ArrayList<>();

    /**
     * Instantiates a new data key.
     */
    public DataKey() {
    }

    /**
     * Instantiates a new data key.
     *
     * @param fields
     *            the fields
     */
    public DataKey(String... fields) {
        for (final String field : fields) {
            addField(field);
        }
    }

    /**
     * Gets the fields.
     *
     * @return the fields
     */
    public List<String> getFields() {
        return fields;
    }

    /**
     * Adds the field.
     *
     * @param field
     *            the field
     */
    public void addField(String field) {
        if (!ConditionUtils.oneIsTrue(StringUtils.isAllBlank(field), fields.contains(field))) {
            fields.add(field);
        }
    }

    /**
     * Exists field.
     *
     * @param field
     *            the field
     * @return true, if successful
     */
    public boolean existsField(String field) {
        boolean res = false;
        if (!StringUtils.isAllBlank(field)) {
            res = fields.contains(field);
        }
        return res;
    }

    /**
     * Gets the field.
     *
     * @param index
     *            the index
     * @return the field
     */
    public String getField(int index) {
        String res = null;
        if (!ConditionUtils.oneIsTrue((index < 0), (index >= fields.size()))) {
            res = fields.get(index);
        }
        return res;
    }

    /**
     * Count fields.
     *
     * @return the int
     */
    public int countFields() {
        return fields.size();
    }

    /**
     * Clear.
     */
    public void clear() {
        fields.clear();
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#hashCode() */

    @Override
    public int hashCode() {
        return Objects.hash(fields);
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#equals(java.lang.Object) */

    @Override
    public boolean equals(Object obj) {
        boolean res = false;
        if (this == obj) {
            res = true;
        } else if (obj instanceof DataKey) {
            final DataKey other = (DataKey) obj;
            if (other.countFields() == countFields()) {
                res = true;
                for (final String field : fields) {
                    if (!other.existsField(field)) {
                        res = false;
                        break;
                    }
                }
            }
        }
        return res;
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#toString() */

    @Override
    public String toString() {
        final StringBuilder builder = new StringBuilder();
        builder.append("Key=[");
        boolean begin = true;
        for (final String field : fields) {
            if (!begin) {
                builder.append(", ");
            }
            builder.append(field);
            begin = false;
        }
        builder.append(']');
        return builder.toString();
    }

}
