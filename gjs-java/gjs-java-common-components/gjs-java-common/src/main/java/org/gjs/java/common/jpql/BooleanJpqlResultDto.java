package org.gjs.java.common.jpql;

/**
 * The Class JpqlResultDto.
 *
 * Clase abstracta de la librería Gjs
 *
 * Clase abstracta DTO para pensada para ser implementada por clase destinadas a facilitar la transformación de datos de
 * una consulta JPQL a Booleano, teniendo en cuenta que, aunque JPQL esta perfectamente integrado con Java, cuando las
 * consultas van a Oracle puede ser más duro: para no complicarse la vida customizando el OracleExtendedDialect
 * utilizamos DTO especiales para transformar el resultado.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 */
public abstract class BooleanJpqlResultDto extends JpqlResultDto<Boolean> {

}
