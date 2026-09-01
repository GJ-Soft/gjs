package org.gjs.java.common.dto;

import com.fasterxml.jackson.annotation.JsonIgnore;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class PrimitiveDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para identificar un método cualquiera de una clase cualquiera.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
public class PrimitiveDto extends BaseDto {

    /**
     *
     */
    private static final long serialVersionUID = 816255496120767119L;

    /** The module. */
    protected String module;

    /** The primitive. */
    protected String primitive;

    /**
     * Instantiates a new statistics dto.
     */
    public PrimitiveDto() {
        // No hace nada
    }

    /**
     * Instantiates a new statistics dto.
     *
     * @param module
     *            the module
     * @param primitive
     *            the primitive
     */
    public PrimitiveDto(String module, String primitive) {
        this.module = StringUtils.trim(module);
        this.primitive = StringUtils.trim(primitive);
    }

    /**
     * Gets the key.
     *
     * @return the key
     */
    @JsonIgnore
    public String getKey() {
        return String.format("%s:%s", module, primitive);
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#toString() */

    @Override
    public String toString() {
        return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("module", module)
                .append("primitive", primitive).toString();
    }

}
