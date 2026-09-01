package org.gjs.java.common.dto;

import java.util.Set;
import java.util.TreeSet;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SetDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO genérica para almacenar un conjunto de otros DTO del tipo que sean.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
public class SetDto extends BaseDto {

    /** The Constant serialVersionUID. */
    private static final long serialVersionUID = 4127095647545500940L;

    /** The contenido. */
    private final Set<BaseDto> contenido = new TreeSet<>();

}
