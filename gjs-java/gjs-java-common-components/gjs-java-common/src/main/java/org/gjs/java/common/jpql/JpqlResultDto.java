package org.gjs.java.common.jpql;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

/**
 * The Class JpqlResultDto.
 *
 * Clase abstracta de la librería Gjs
 *
 * Clase abstracta DTO para pensada para ser implementada por clase destinadas a facilitar la transformación de datos de
 * una consulta JPQL, teniendo en cuenta que, aunque JPQL esta perfectamente integrado con Java, cuando las consultas
 * van a Oracle puede ser más duro: para no complicarse la vida customizando el OracleExtendedDialect utilizamos DTO
 * especiales para transformar el resultado.
 *
 * @param <T>
 *            the generic type
 *            --------------------------------------------------------------------------------------------------------------------
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 */
public class JpqlResultDto<T> {

    /** The value. */
    protected T value;

    /**
     * Gets the value.
     *
     * @return the value
     */
    public T getValue() {
        return value;
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#toString() */

    @Override
    public String toString() {
        return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("value", value).toString();
    }

}
