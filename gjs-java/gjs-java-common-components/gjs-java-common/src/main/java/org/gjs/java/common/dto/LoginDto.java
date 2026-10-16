package org.gjs.java.common.dto;

import java.util.Date;
import java.util.Objects;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;
import org.gjs.java.common.util.ConditionUtils;

import com.fasterxml.jackson.annotation.JsonIgnore;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class LoginDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para contener la información de logado del usuario de la sesión.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
public class LoginDto extends BaseDto {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = 2577957124597077317L;

	/** The logado. */
	private boolean logged;

	/** The caducado. */
	private boolean lapsed;

	/** The perfil incompleto. */
	private boolean incompleteProfile;

	/** The usuario. */
	private BasicUserDto userDto;

	/** The cert info dto. */
	private CertInfoDto certInfoDto;

	/** The fecha. */
	private Date dateLogin;

	/** The ip origen. */
	private String sourceIp;

	/** The credenciales. */
	private Credentials credentials;

	/**
	 * Instantiates a new login dto.
	 */
	public LoginDto() {
		// No hace nada
	}

	/**
	 * Instantiates a new login dto.
	 *
	 * @param userDto the user dto
	 */
	public LoginDto(BasicUserDto userDto) {
		setUserDto(userDto);
	}

	@JsonIgnore
	public String getAlias() {
		String alias = null;
		if (Objects.nonNull(userDto)) {
			alias = userDto.getAlias();
		}
		return alias;
	}
	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#hashCode()
	 */

	@Override
	public int hashCode() {
		return Objects.hash(userDto, sourceIp, dateLogin);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#equals(java.lang.Object)
	 */

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (!(obj instanceof final LoginDto other)) {
			return false;
		}
		return ConditionUtils.allAreTrue(Objects.equals(getAlias(), other.getAlias()),
				Objects.equals(sourceIp, other.getSourceIp()), Objects.equals(dateLogin, other.getDateLogin()));
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("logged", logged)
				.append("lapsed", lapsed).append("incompleteProfile", incompleteProfile).append("user", userDto)
				.append("sourceIp", sourceIp).toString();
	}

}
