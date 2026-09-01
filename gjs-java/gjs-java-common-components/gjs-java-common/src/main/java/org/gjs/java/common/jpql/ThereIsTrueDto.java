package org.gjs.java.common.jpql;

/**
 * The Class ThereIsTrueDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para facilitar la transformación de una condición sobre un flag.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class ThereIsTrueDto extends BooleanJpqlResultDto {

    /**
     * Instantiates a new there is any dto.
     *
     * @param count
     *            the count
     */
    public ThereIsTrueDto(long count) {
        if (count > 0) {
            value = Boolean.TRUE;
        } else {
            value = Boolean.FALSE;
        }
    }

    /**
     * Instantiates a new there is true dto.
     *
     * @param val
     *            the val
     */
    public ThereIsTrueDto(boolean val) {
        if (val) {
            value = Boolean.TRUE;
        } else {
            value = Boolean.FALSE;
        }
    }

}
