package org.gjs.java.common.dto;

import java.io.Serializable;
import java.util.Objects;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class RolDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para almacenar los datos de un rol.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
public class BasicRoleDto implements Serializable, Comparable<BasicRoleDto> {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = -4735351294972433073L;

	/** The nombre. */
	protected String name;

	/**
	 * Instantiates a new rol dto.
	 */
	public BasicRoleDto() {
		// No hace nada
	}

	/**
	 * Instantiates a new rol dto.
	 *
	 * @param name the name
	 */
	public BasicRoleDto(String name) {
		this.name = name;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (!(obj instanceof final BasicRoleDto other)) {
			return false;
		}
		return (compareTo(other) == 0);
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = super.hashCode();
		result = prime * result + Objects.hash(name);
		return result;
	}

	@Override
	public int compareTo(BasicRoleDto o) {
		int res = -1;
		if (Objects.nonNull(o)) {
			res = StringUtils.compare(name, o.getName());
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("name", name).toString();
	}
}
