package org.gjs.java.common.dto;

import java.util.Date;

import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonTypeInfo;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;
import org.springframework.http.HttpStatus;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class ExtendedRespondeDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para representar una respuesta general extendida (que incluye datos específicos de respuesta en otro DTO)
 * de un método de la fachada.
 *
 * --------------------------------------------------------------------------------------------------------------------
 * Gj Software
 *
 * 2025 correspondiente licencia en los activos de la
 * SES. Los programas informáticos propiedad de la SES están protegidos por la propiedad intelectual, y por tanto está
 * estrictamente prohibida su reproducción, modificación, cesión o comunicación sin la debida autorización. Queda
 * estrictamente prohibido el uso, reproducción, cesión, transformación o comunicación pública de cualquier otro tipo de
 * obra o invención protegida por la propiedad intelectual sin la debida autorización.
 *
 * Seguridad Ministerio del Interior
 * Gobierno de España
 * --------------------------------------------------------------------------------------------------------------------
 *
 * @param <T>
 *            la clase de DTO con la información de respuesta
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
@JsonInclude(JsonInclude.Include.NON_NULL)
public class ExtendedResponseDto<T extends BaseDto> extends ResponseDto {

    /** The content. */
    @JsonProperty(required = false, index = 4)
    @JsonTypeInfo(use = JsonTypeInfo.Id.CLASS, include = JsonTypeInfo.As.PROPERTY, property = "@class")
    private T content;

    /**
     * Instantiates a new extended response dto.
     */
    public ExtendedResponseDto() {
        super(HttpStatus.OK, new Date());
    }

    /**
     * Instantiates a new extended response dto.
     *
     * @param status
     *            the status
     */
    public ExtendedResponseDto(HttpStatus status) {
        super(status, new Date());
    }

    /**
     * Instantiates a new extended response dto.
     *
     * @param status
     *            the status
     * @param timestamp
     *            the timestamp
     */
    public ExtendedResponseDto(HttpStatus status, Date timestamp) {
        super(status, timestamp);
    }

    /**
     * Instantiates a new extended response dto.
     *
     * @param status
     *            the status
     * @param message
     *            the message
     */
    public ExtendedResponseDto(HttpStatus status, String message) {
        super(status, message);
    }

    /**
     * Instantiates a new extended response dto.
     *
     * @param status
     *            the status
     * @param timestamp
     *            the timestamp
     * @param message
     *            the message
     */
    public ExtendedResponseDto(HttpStatus status, Date timestamp, String message) {
        super(status, timestamp, message);
    }

    /**
     * Instantiates a new extended response dto.
     *
     * @param content
     *            the content
     */
    public ExtendedResponseDto(T content) {
        this(content, HttpStatus.OK, new Date());
    }

    /**
     * Instantiates a new extended response dto.
     *
     * @param content
     *            the content
     * @param status
     *            the status
     */
    public ExtendedResponseDto(T content, HttpStatus status) {
        this(content, status, new Date());
    }

    /**
     * Instantiates a new extended response dto.
     *
     * @param content
     *            the content
     * @param status
     *            the status
     * @param timestamp
     *            the timestamp
     */
    public ExtendedResponseDto(T content, HttpStatus status, Date timestamp) {
        super(status, timestamp);
        this.content = content;
    }

    /**
     * Instantiates a new extended response dto.
     *
     * @param content
     *            the content
     * @param status
     *            the status
     * @param message
     *            the message
     */
    public ExtendedResponseDto(T content, HttpStatus status, String message) {
        super(status, message);
        this.content = content;
    }

    /**
     * Instantiates a new extended response dto.
     *
     * @param content
     *            the content
     * @param status
     *            the status
     * @param timestamp
     *            the timestamp
     * @param message
     *            the message
     */
    public ExtendedResponseDto(T content, HttpStatus status, Date timestamp, String message) {
        super(status, timestamp, message);
        this.content = content;
    }

    /* (non-Javadoc)
     *
     * @see es.mir.semilla.util.dto.ResponseDto#toString() */

    @Override
    public String toString() {
        return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("status", getStatus())
                .append("timestamp", getTimestamp()).append("message", getMessage()).append("content", content)
                .toString();
    }

}
