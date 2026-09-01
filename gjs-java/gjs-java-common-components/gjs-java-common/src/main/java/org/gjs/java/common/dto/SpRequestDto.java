package org.gjs.java.common.dto;

import java.util.Objects;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SpRequestDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para almacenar los datos de un requerimiento al Service Provider.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
public class SpRequestDto {

    /** The saml response. */
    private String samlResponse;

    /** The relay state. */
    private String relayState;

    /**
     * Instantiates a new sp request dto.
     */
    public SpRequestDto() {
        // No hace nada
    }

    /**
     * Instantiates a new sp request dto.
     *
     * @param samlResponse
     *            the saml response
     * @param relayState
     *            the relay state
     */
    public SpRequestDto(String samlResponse, String relayState) {
        this.samlResponse = samlResponse;
        this.relayState = relayState;
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#hashCode() */

    @Override
    public int hashCode() {
        return Objects.hash(relayState, samlResponse);
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#equals(java.lang.Object) */

    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (!(obj instanceof final SpRequestDto other)) {
            return false;
        }
        return Objects.equals(relayState, other.relayState) && Objects.equals(samlResponse, other.samlResponse);
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#toString() */

    @Override
    public String toString() {
        return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("samlResponse", samlResponse)
                .append("relayState", relayState).toString();
    }

}
