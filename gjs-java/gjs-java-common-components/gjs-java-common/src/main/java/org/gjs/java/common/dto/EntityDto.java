package org.gjs.java.common.dto;

import java.io.Serializable;
import java.util.Objects;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;
import org.gjs.java.common.util.ComparationUtils;

import com.fasterxml.jackson.annotation.JsonIgnore;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class EntidadDto
 *
 * Clase abtracta de datos de la librería Gjs
 *
 * Clase base para ser extendida por todos los DTO que representan una entida de
 * la base de datos.
 *
 * @author Gjs
 * @version 4.0.0
 * @param <T> la clase de DTO de la clave primaria de la entidad
 * @since 3.0.0
 */

@Getter
@Setter
public abstract class EntityDto<T extends Serializable> extends BaseDto implements Comparable<EntityDto<?>> {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = -7112300404859852087L;

	/** The id. */
	protected T id;

	/**
	 * Instantiates a new entidad dto.
	 */
	protected EntityDto() {
		// No hace nada
	}

	/**
	 * Instantiates a new entidad dto.
	 *
	 * @param other the other
	 */
	protected EntityDto(EntityDto<T> other) {
		if (Objects.nonNull(other)) {
			id = other.getId();
		}
	}

	/**
	 * Instantiates a new entidad dto.
	 *
	 * @param id the id
	 */
	protected EntityDto(T id) {
		this.id = id;
	}

	/**
	 * Gets the nombre entidad.
	 *
	 * @return the nombre entidad
	 */
	@JsonIgnore
	public String getEntityName() {
		final String name = getClass().getSimpleName();
		return name.substring(0, name.length() - 3);
	}

	/**
	 * Checks for id.
	 *
	 * @return true, if successful
	 */
	public boolean hasId() {
		boolean res = false;
		if (Objects.nonNull(id)) {
			res = validId(id);
		}
		return res;
	}

	/**
	 * Valid id.
	 *
	 * @param id the id
	 * @return true, if successful
	 */
	protected boolean validId(T id) {
		return !StringUtils.isAllBlank(Objects.toString(id));
	}

	/**
	 * Compare id.
	 *
	 * @param otherId the other id
	 * @return the int
	 */
	public int compareId(Object otherId) {
		return ComparationUtils.compareTo((Objects.nonNull(id) ? Objects.toString(id) : null),
				(Objects.nonNull(otherId) ? Objects.toString(otherId) : null));
	}

	@Override
	public boolean isValid() {
		return hasId();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Comparable#compareTo(java.lang.Object)
	 */

	@Override
	public int compareTo(EntityDto<?> obj) {
		int res = 1; // Si fuese nulo el objeto se considera que es menor
		if (Objects.nonNull(obj)) {
			res = compareId(obj.getId());
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
		return Objects.hash(id);
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
		if (!(obj instanceof EntityDto)) {
			return false;
		}
		final EntityDto<?> other = (EntityDto<?>) obj;
		return (compareId(other.getId()) == 0);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("id", id).toString();
	}

}
