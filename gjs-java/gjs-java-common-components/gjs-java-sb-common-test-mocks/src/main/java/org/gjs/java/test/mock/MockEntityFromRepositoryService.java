package org.gjs.java.test.mock;

import java.util.List;

import org.gjs.java.common.util.ConversionUtils;
import org.gjs.java.common.util.ReflectionUtils;

/**
 * The Class MockEntityFromRepositoryService.
 *
 * Clase de datos de la librería Gjs
 *
 * Implementa un servicio de datos sencillo en memoria para cualquier clase de objetos definido a partir de un mock de
 * su repositorio.
 *
 * @param <DTO>
 *            el DTO de la entidad
 * @param <PKDTO>
 *            la clave primaria del DTO
 * @param <E>
 *            la entidad
 * @param <PK>
 *            la clave primaria de la entidad
 * @param <FDTO>
 *            el DTO de filtrado
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class MockEntityFromRepositoryService<DTO, PKDTO, E, PK, FDTO>
        extends MockEntityService<DTO, PKDTO, FDTO> {

    /**
     * Instantiates a new mock entity from repository service.
     */
    protected MockEntityFromRepositoryService() {
    }

    /**
     * Instantiates a new mock entity from repository service.
     *
     * @param mockRepository
     *            the mock repository
     */
    protected MockEntityFromRepositoryService(MockEntityDataManager<E, PK> mockRepository) {
        for (final E entity : mockRepository.getAll()) {
            super.put(entityToDto(entity));
        }
    }

    /**
     * Entity to dto.
     *
     * @param entity
     *            the entity
     * @return the dto
     */
    protected abstract DTO entityToDto(E entity);

    /**
     * Export.
     *
     * @param columns
     *            the columns
     * @param order
     *            the order
     * @param asc
     *            the asc
     * @param filterDto
     *            the filter dto
     * @return the byte[]
     */
    public byte[] export(String columns, String order, Integer asc, FDTO filterDto) {

        final List<DTO> list = this.filter(order, asc, filterDto);
        logger.debug("Seleccionados {} registros", list.size());
        final StringBuilder textCsv = new StringBuilder();
        final String[] listColumns = columns.split(",");
        boolean begin = true;
        for (final String column : listColumns) {
            if (!begin) {
                textCsv.append(',');
            }
            textCsv.append('\"').append(column).append('\"');
            begin = false;
        }
        textCsv.append('\n');
        for (int i = 0; i < list.size(); i = i + 1) {
            final DTO dto = list.get(i);
            for (int j = 0; j < listColumns.length; j = j + 1) {
                final String column = listColumns[j];
                final String value = ConversionUtils.toString(ReflectionUtils.getFieldValue(dto, column));
                logger.debug("Registro {}; Columna {}({}): Valor={}", i, j, column, value);
                if (j > 0) {
                    textCsv.append(',');
                }
                textCsv.append('\"').append(value).append('\"');
            }
            textCsv.append('\n');
        }
        return textCsv.toString().getBytes();
    }

    /**
     * Creates the export dto.
     *
     * @param content
     *            the content
     * @return the object
     */
    protected Object createExportDto(byte[] content) {
        return new String(content);
    }

    /**
     * Custom export.
     *
     * @param columns
     *            the columns
     * @param order
     *            the order
     * @param asc
     *            the asc
     * @param filterDto
     *            the filter dto
     * @return the object
     */
    public Object customExport(String columns, String order, Integer asc, FDTO filterDto) {
        return createExportDto(export(columns, order, asc, filterDto));
    }

}
