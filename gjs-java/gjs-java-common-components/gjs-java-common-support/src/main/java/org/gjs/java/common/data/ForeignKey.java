package org.gjs.java.common.data;

import java.util.List;
import java.util.Objects;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class ForeignKey.
 *
 * Clase de datos de la librería Gjs
 *
 * Representa una clave foránea entre los atributos de una clase de objetos respecto a los de otra clase de objetos.
 * Relaciona atributo a atributo una ClaveUnica origen con una ClaveUnica destino.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class ForeignKey extends DataKey {

    /** The object name. */
    protected String objectName;

    /** The remote key. */
    private DataKey remoteKey;

    /**
     * Instantiates a new foreign key.
     */
    public ForeignKey() {
        remoteKey = new DataKey();
    }

    /**
     * Instantiates a new foreign key.
     *
     * @param key
     *            the key
     * @param remoteKey
     *            the remote key
     */
    public ForeignKey(DataKey key, DataKey remoteKey) {
        this();
        // No con ConditionUtils: con varargs, Java evalúa todos los argumentos antes
        // de la llamada, y el que usa key y remoteKey se evaluaría aunque fuese nulo.
        if (Objects.nonNull(key) && Objects.nonNull(remoteKey) && (key.countFields() == remoteKey.countFields())) {
            for (final String field : key.getFields()) {
                super.addField(field);
            }
            this.remoteKey = remoteKey;
        }
    }

    /**
     * Instantiates a new foreign key.
     *
     * @param objectName the object name
     * @param key the key
     * @param remoteKey the remote key
     */
    public ForeignKey(String objectName, DataKey key, DataKey remoteKey) {
        this(key, remoteKey);
        this.objectName = objectName;
    }

    /**
     * Gets the object name.
     *
     * @return the object name
     */
    public String getObjectName() {
        return objectName;
    }

    /**
     * Sets the object name.
     *
     * @param objectName
     *            the new object name
     */
    public void setObjectName(String objectName) {
        this.objectName = objectName;
    }

    /**
     * Gets the remote fields.
     *
     * @return the remote fields
     */
    public List<String> getRemoteFields() {
        return remoteKey.getFields();
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.data.DataKey#addField(java.lang.String) */

    @Override
    public void addField(String field) {
        // Por defecto no hace nada
    }

    /**
     * Adds the field.
     *
     * @param field
     *            the field
     * @param remoteField
     *            the remote field
     */
    public void addField(String field, String remoteField) {
        if (!ConditionUtils.oneIsTrue(StringUtils.isAllBlank(field), StringUtils.isAllBlank(remoteField))) {
            super.addField(field);
            remoteKey.addField(remoteField);
        }
    }

    /**
     * Gets the remote field.
     *
     * @param index
     *            the index
     * @return the remote field
     */
    public String getRemoteField(int index) {
        String res = null;
        if (!ConditionUtils.oneIsTrue((index < 0), (index >= remoteKey.countFields()))) {
            res = remoteKey.getField(index);
        }
        return res;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.data.DataKey#clear() */

    @Override
    public void clear() {
        super.clear();
        remoteKey.clear();
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.data.DataKey#hashCode() */

    @Override
    public int hashCode() {
        return super.hashCode();
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.data.DataKey#equals(java.lang.Object) */

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        boolean res = false;
        if (obj instanceof ForeignKey) {
            final ForeignKey other = (ForeignKey) obj;
            res = equals(other);
        }
        if (obj instanceof DataKey) {
            final DataKey other = (DataKey) obj;
            res = equals(other);
        }
        return res;
    }

    /**
     * Equals.
     *
     * @param other
     *            the other
     * @return true, if successful
     */
    private boolean equals(ForeignKey other) {
        boolean res;
        if (other.countFields() != countFields()) {
            return false;
        }
        res = true;
        for (int i = 0; i < fields.size(); i = i + 1) {
            final String field = fields.get(i);
            final String otherField = other.getField(i);
            final String remote = remoteKey.getField(i);
            final String otherRemote = other.getRemoteField(i);
            if (!ConditionUtils.allAreTrue(field.equals(otherField), remote.equals(otherRemote))) {
                res = false;
                break;
            }
        }
        return res;
    }

    /**
     * Equals.
     *
     * @param other
     *            the other
     * @return true, if successful
     */
    private boolean equals(DataKey other) {
        boolean res;
        if (other.countFields() != countFields()) {
            return false;
        }
        res = true;
        for (final String field : fields) {
            if (!other.existsField(field)) {
                res = false;
                break;
            }
        }
        return res;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.data.DataKey#toString() */

    @Override
    public String toString() {
        final StringBuilder builder = new StringBuilder();
        builder.append("ForeignKey=[").append(super.toString()).append("--").append(remoteKey.toString()).append(']');
        return builder.toString();
    }

}
