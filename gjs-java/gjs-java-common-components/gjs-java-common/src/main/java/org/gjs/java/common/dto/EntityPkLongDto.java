package org.gjs.java.common.dto;

import org.gjs.java.common.util.ComparationUtils;

/**
 * The Class EntidadPkLongDto.
 *
 * Clase abtracta de datos de la librería Gjs
 *
 * Clase base para ser extendida por todos los DTO que representan una entida de
 * la base de datos con clave primaria entera.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 */
public abstract class EntityPkLongDto extends EntityDto<Long> {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = -7274829768924889168L;

	/**
	 * Instantiates a new entidad pk long dto.
	 */
	public EntityPkLongDto() {
		// No hace nada
	}

	/**
	 * Instantiates a new entidad pk long dto.
	 *
	 * @param other the other
	 */
	public EntityPkLongDto(EntityPkLongDto other) {
		super(other);
	}

	/**
	 * Instantiates a new entidad pk long dto.
	 *
	 * @param id the id
	 */
	public EntityPkLongDto(Long id) {
		super(id);
	}

	@Override
	protected boolean validId(Long id) {
		return (id > 0);
	}

	@Override
	public int compareId(Object otherId) {
		int res = 1; // Si el objeto no es Long se considera nulo
		if (otherId instanceof Long) {
			res = ComparationUtils.compareTo(id, (Long) otherId);
		}
		return res;
	}

}
