package org.gjs.java.common.dto;

import java.io.Serializable;
import java.util.Objects;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;
import org.gjs.java.common.util.ComparationUtils;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class ReferenceCodeDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para representar una referencia o identificador de tipo código
 * (String) que puede utilizarse para referirse a una ocurrencia de cualquier
 * entidad simple de la base de datos.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */

@Getter
@Setter
public class ReferenceCodeDto implements Comparable<ReferenceCodeDto>, Serializable {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = 6414442543166002192L;

	/** The code. */
	private String code;

	/**
	 * Instantiates a new rol dto.
	 */
	public ReferenceCodeDto() {
		// No hace nada
	}

	/**
	 * Instantiates a new rol dto.
	 *
	 * @param code the code
	 */
	public ReferenceCodeDto(String code) {
		this.code = code;
	}

	/**
	 * Instantiates a new referencia dto.
	 *
	 * @param other the other
	 */
	public ReferenceCodeDto(ReferenceCodeDto other) {
		if (Objects.nonNull(other)) {
			this.code = other.code;
		}
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Comparable#compareTo(java.lang.Object)
	 */

	@Override
	public int compareTo(ReferenceCodeDto obj) {
		int res = -1;
		if (Objects.nonNull(obj)) {
			res = ComparationUtils.compareTo(code, obj.getCode());
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#hashCode()
	 */

	@Override
	public int hashCode() {
		return Objects.hash(code);
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
		if (!(obj instanceof ReferenceCodeDto)) {
			return false;
		}
		final ReferenceCodeDto other = (ReferenceCodeDto) obj;
		return (compareTo(other) == 0);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("code", code).toString();
	}

}
