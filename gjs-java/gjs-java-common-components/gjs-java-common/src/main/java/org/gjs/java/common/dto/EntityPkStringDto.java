package org.gjs.java.common.dto;

/**
 * The Class EntidadPkStringDto.
 *
 * Clase abtracta de datos de la librería Gjs
 *
 * Clase base para ser extendida por todos los DTO que representan una entida de la base de datos con clave primaria
 * cadena.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 */

public abstract class EntityPkStringDto extends EntityDto<String> {

    /** The Constant serialVersionUID. */
    private static final long serialVersionUID = 4273754468033325080L;

    /**
     * Instantiates a new entidad pk string dto.
     */
    protected EntityPkStringDto() {
        // No hace nada
    }

    /**
     * Instantiates a new entidad pk string dto.
     *
     * @param other
     *            the other
     */
    protected EntityPkStringDto(EntityPkStringDto other) {
        super(other);
    }

    /**
     * Instantiates a new entidad pk string dto.
     *
     * @param id
     *            the id
     */
    protected EntityPkStringDto(String id) {
        super(id);
    }

}
