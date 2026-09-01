package org.gjs.java.common.dto;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

import com.fasterxml.jackson.annotation.JsonProperty;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class UsuarioDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para almacenar los datos de un usuario.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
public class BasicUserDto implements Comparable<BasicUserDto> {

	/** The id sgu. */
	private String alias;

	/** The nombre. */
	private PersonNameDto personName;

	/** The dni. */
	private String document;

	/** The email. */
	private String email;

	/** The cert info dto. */
	@JsonProperty("certInfo")
	private CertInfoDto certInfoDto;

	/** The roles. */
	@JsonProperty(required = false)
	private List<BasicRoleDto> roles;

	/**
	 * Instantiates a new usuario dto.
	 */
	public BasicUserDto() {
		// No hace nada
	}

	/**
	 * Instantiates a new usuario dto.
	 *
	 * @param alias the id sgu
	 */
	public BasicUserDto(String alias) {
		setAlias(alias);
	}

	/**
	 * Instantiates a new usuario dto.
	 *
	 * @param other the other
	 */
	public BasicUserDto(BasicUserDto other) {
		assign(other);
	}

	/**
	 * Assign.
	 *
	 * @param other the other
	 */
	protected void assign(BasicUserDto other) {
		if (Objects.nonNull(other)) {
			setAlias(other.alias);
			setPersonName(org.apache.commons.lang3.ObjectUtils.clone(other.getPersonName()));
			setDocument(other.document);
			setEmail(other.email);
			for (final BasicRoleDto rol : other.getRoles()) {
				getRoles().add(new BasicRoleDto(rol.getName()));
			}
			if (Objects.nonNull(other.certInfoDto)) {
				this.certInfoDto = new CertInfoDto(other.certInfoDto);
			}
		}
	}

	@Override
	public int compareTo(BasicUserDto o) {
		int res = -1;
		if (Objects.nonNull(o)) {
			res = StringUtils.compare(alias, o.getAlias());
		}
		return res;
	}

	/**
	 * Devuelve el valor de roles.
	 *
	 * @return el valor actual de roles.
	 */
	public List<BasicRoleDto> getRoles() {
		if (roles == null) {
			roles = new ArrayList<>();
		}
		return roles;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = super.hashCode();
		result = prime * result + Objects.hash(alias);
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (!(obj instanceof final BasicUserDto other)) {
			return false;
		}
		return (compareTo(other) == 0);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("alias", alias)
				.append("name", personName).append("document", document).append("email", email)
				.append("roles",
						Objects.nonNull(roles) ? roles.stream().map(Object::toString).collect(Collectors.joining(","))
								: "null")
				.toString();
	}

}
