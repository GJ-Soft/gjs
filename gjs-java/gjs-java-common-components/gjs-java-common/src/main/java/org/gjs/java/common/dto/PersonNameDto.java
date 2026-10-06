package org.gjs.java.common.dto;

import java.io.Serializable;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class PersonNameDto.
 *
 * Clase abstracta de datos de la librería Gjs
 *
 * Base de los nombres de persona. Aporta el nombre y el primer apellido, y deja a cada variante nacional la forma de componer el nombre completo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public abstract class PersonNameDto implements Serializable {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = 4183036187160857968L;

	protected String name;

	protected String firstSurname;

	public abstract String getFullName();

	public abstract String getFormattedFullName();

	@Override
	public abstract PersonNameDto clone();

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("fullName", getFullName()).toString();
	}

}
