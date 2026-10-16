package org.gjs.java.common.dto;

import java.util.Calendar;
import java.util.Objects;

import com.fasterxml.jackson.annotation.JsonIgnore;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class AuditDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para almacenar la información para la auditoria de tiempos de un método.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class AuditDto extends BaseDto {

    /** The Constant serialVersionUID. */
    private static final long serialVersionUID = 765227491514794314L;

    /** The module. */
    @Getter
    private String module;

    /** The primitive. */
    @Getter
    private String primitive;

    /** The start time. */
    @Getter
    private long startTime;

    /** The end time. */
    @Getter
    private long endTime;

    /** Whether the audited call ended without an exception. */
    @Getter
    private boolean ok;

    /** The exception thrown by the audited call, if any. */
    @Getter
    @Setter
    private Throwable throwed;

    /**
     * Instantiates a new audit dto.
     */
    public AuditDto() {
        // No hace nada
    }

    /**
     * Instantiates a new audit dto.
     *
     * @param module
     *            the module
     * @param primitive
     *            the primitive
     */
    public AuditDto(String module, String primitive) {
        init(module, primitive);
    }

    /**
     * Gets the key.
     *
     * @return the key
     */
    @JsonIgnore
    public String getKey() {
        return String.format("%s:%s:%s", module, primitive, Thread.currentThread().getName());
    }

    /**
     * Gets the common key.
     *
     * @return the key
     */
    @JsonIgnore
    public String getCommonKey() {
        return String.format("%s:%s", module, primitive);
    }

    /**
     * Gets the time.
     *
     * @return the time
     */
    @JsonIgnore
    public long getTime() {
        return endTime - startTime;
    }

    /**
     * Inits the.
     *
     * @param module
     *            the module
     * @param primitive
     *            the primitive
     */
    public void init(String module, String primitive) {
        this.module = module;
        this.primitive = primitive;
        this.startTime = Calendar.getInstance().getTimeInMillis();
        this.endTime = 0;
        this.ok = false;
        this.throwed = null;
    }

    /**
     * Begin.
     */
    public void begin() {
        this.startTime = Calendar.getInstance().getTimeInMillis();
    }

    /**
     * End.
     */
    public void end() {
        this.endTime = Calendar.getInstance().getTimeInMillis();
        this.ok = Objects.isNull(this.throwed);
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#toString() */

    @Override
    public String toString() {
        return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("module", module)
                .append("primitive", primitive).append("startTime", startTime).append("endTime", endTime)
                .append("ok", ok).append("throwed", throwed).toString();
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#hashCode() */

    @Override
    public int hashCode() {
        return Objects.hash(module, primitive);
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#equals(java.lang.Object) */

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof final AuditDto other)) {
            return false;
        }
        return Objects.equals(module, other.module) && Objects.equals(primitive, other.primitive);
    }

}
