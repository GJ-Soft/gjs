package org.gjs.java.common.dto;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Objects;

import org.apache.commons.collections4.CollectionUtils;
import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.contant.CommonErrors;
import org.gjs.java.common.util.StringUtils;
import org.springframework.http.HttpStatus;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class ResponseDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para representar una respuesta general de un método de la fachada.
 *
 * --------------------------------------------------------------------------------------------------------------------
 * Gj Software
 *
 * 2025
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * --------------------------------------------------------------------------------------------------------------------
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
@JsonInclude(JsonInclude.Include.NON_NULL)
public class ResponseDto {

	/** The status. */
	@JsonProperty(required = true, index = 1)
	private Integer status;

	/** The timestamp. */
	@JsonFormat(pattern = CommonBaseConstants.DATETIME_OUTPUT_FORMAT, timezone = "Europe/Madrid")
	@JsonProperty(required = true, index = 2)
	private Date timestamp;

	/** The message. */
	@JsonProperty(required = true, index = 3)
	private String message;

	/** The warnings. */
	@JsonProperty(required = false, index = 5)
	private List<ErrorDto> warnings;

	/** The errors. */
	@JsonProperty(required = false, index = 6)
	private List<ErrorDto> errors;

	/**
	 * Instantiates a new response dto.
	 */
	public ResponseDto() {
		this(HttpStatus.OK, new Date());
	}

	/**
	 * Instantiates a new response dto.
	 *
	 * @param status the status
	 */
	public ResponseDto(HttpStatus status) {
		this(status, new Date());
	}

	/**
	 * Instantiates a new response dto.
	 *
	 * @param status    the status
	 * @param timestamp the timestamp
	 */
	public ResponseDto(HttpStatus status, Date timestamp) {
		if (Objects.isNull(status)) {
			status = HttpStatus.INTERNAL_SERVER_ERROR;
			addError(CommonErrors.ERROR_TECH0001);
		}
		this.status = status.value();
		this.timestamp = Objects.requireNonNullElse(timestamp, new Date());
		setMessage(status.getReasonPhrase());
	}

	/**
	 * Instantiates a new response dto.
	 *
	 * @param status  the status
	 * @param message the message
	 */
	public ResponseDto(HttpStatus status, String message) {
		this(status, new Date(), message);
	}

	/**
	 * Instantiates a new response dto.
	 *
	 * @param status    the status
	 * @param timestamp the timestamp
	 * @param message   the message
	 */
	public ResponseDto(HttpStatus status, Date timestamp, String message) {
		if (Objects.isNull(status)) {
			status = HttpStatus.INTERNAL_SERVER_ERROR;
			addError(CommonErrors.ERROR_TECH0001);
		}
		this.status = status.value();
		this.timestamp = Objects.requireNonNullElse(timestamp, new Date());
		setMessage(Objects.requireNonNullElse(message, status.getReasonPhrase()));
	}

	/**
	 * Sets the message.
	 *
	 * @param message the new message
	 */
	public void setMessage(String message) {
		this.message = StringUtils.nvl(message).replace("{0}", "").replace("{1}", "").replace("{2}", "");
	}

	/**
	 * Adds the error.
	 *
	 * @param code the code
	 */
	public void addError(String code) {
		addError(new ErrorDto(code));
	}

	/**
	 * Adds the error.
	 *
	 * @param code    the code
	 * @param message the message
	 */
	public void addError(String code, String message) {
		addError(new ErrorDto(code, message));
	}

	/**
	 * Adds the error.
	 *
	 * @param error the error
	 */
	public void addError(ErrorDto error) {
		if (Objects.nonNull(error)) {
			if (Objects.isNull(errors)) {
				errors = new ArrayList<>();
			}
			errors.add(error);
		}
	}

	/**
	 * Adds the warning.
	 *
	 * @param code the code
	 */
	public void addWarning(String code) {
		addWarning(new ErrorDto(code));
	}

	/**
	 * Adds the warning.
	 *
	 * @param code    the code
	 * @param message the message
	 */
	public void addWarning(String code, String message) {
		addWarning(new ErrorDto(code, message));
	}

	/**
	 * Adds the warning.
	 *
	 * @param warning the warning
	 */
	public void addWarning(ErrorDto warning) {
		if (Objects.nonNull(warning)) {
			if (Objects.isNull(warnings)) {
				warnings = new ArrayList<>();
			}
			warnings.add(warning);
		}
	}

	/**
	 * Checks for errors.
	 *
	 * @return true, if successful
	 */
	public boolean hasErrors() {
		return (!CollectionUtils.isEmpty(errors));
	}

	/**
	 * Checks for warnings.
	 *
	 * @return true, if successful
	 */
	public boolean hasWarnings() {
		return (!CollectionUtils.isEmpty(warnings));
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("status", status)
				.append("timestamp", timestamp).append("message", message).toString();
	}

}
