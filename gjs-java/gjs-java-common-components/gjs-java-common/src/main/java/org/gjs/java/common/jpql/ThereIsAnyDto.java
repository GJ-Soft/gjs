package org.gjs.java.common.jpql;

/**
 * The Class ThereIsAnyDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para facilitar la transformación de una condición sobre un count(*) en booleano. En JPQL eso sería
 * inmediato, y bastaría incluir un Select count(*) > 0 en la consulta, pero en Oracle, y más con la transformación a
 * Booleano de Java la cosa se complica: para no complicarse la vida customizando el OracleExtendedDialect utilizamos
 * DTO especiales para transformar el resultado.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class ThereIsAnyDto extends BooleanJpqlResultDto {

    /**
     * Instantiates a new there is any dto.
     *
     * @param count
     *            the count
     */
    public ThereIsAnyDto(long count) {
        if (count > 0) {
            value = Boolean.TRUE;
        } else {
            value = Boolean.FALSE;
        }
    }

}
