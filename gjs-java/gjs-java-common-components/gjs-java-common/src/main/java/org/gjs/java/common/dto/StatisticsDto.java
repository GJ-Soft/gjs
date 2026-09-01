package org.gjs.java.common.dto;

import java.util.Objects;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class StatisticsDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para almacenar informaciones estadísticas sobre uso de un método.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
public class StatisticsDto extends PrimitiveDto {

    /**
     *
     */
    private static final long serialVersionUID = -3010066469087758181L;

    /** The executions. */
    private long executions;

    /** The min time. */
    private long minTime;

    /** The max time. */
    private long maxTime;

    /** The medium time. */
    private long mediumTime;

    /** The sum time. */
    private double sumTime;

    /**
     * Instantiates a new statistics dto.
     */
    public StatisticsDto() {
        minTime = Long.MAX_VALUE;
        maxTime = 0;
        mediumTime = 0;
        sumTime = 0;
    }

    /**
     * Instantiates a new statistics dto.
     *
     * @param module
     *            the module
     * @param primitive
     *            the primitive
     */
    public StatisticsDto(String module, String primitive) {
        super(module, primitive);
        minTime = Long.MAX_VALUE;
        maxTime = 0;
        mediumTime = 0;
        sumTime = 0;
    }

    /**
     * Adds the meassure.
     *
     * @param auditDto
     *            the audit dto
     */
    public void addMeassure(AuditDto auditDto) {
        if (Objects.nonNull(auditDto) && auditDto.getCommonKey().equals(getKey())) {
            addMeassure(auditDto.getTime());
        }
    }

    /**
     * Adds the meassure.
     *
     * @param value
     *            the value
     */
    public void addMeassure(long value) {
        if (value >= 0) {
            if (minTime > value) {
                minTime = value;
            }
            if (maxTime < value) {
                maxTime = value;
            }
            // Nota: Pese a que se produce un error en el cálculo numérico estimado
            // en 1 ms cada cinco medidas, a falta de guardar todas las medidas por espacio,
            // numericamente es mejor usar esta formula:
            // Nota2: El error se ha computado entre executions/3 y executions/5 pudiendo ser excesivo
            // por eso guardamos la suma pese a que corremos riesgo de overflow
            // mediumTime = (mediumTime * executions + value) / (executions + 1);
            sumTime = sumTime + value;
            executions = executions + 1;
            mediumTime = Math.round(sumTime / executions);
        }
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#toString() */

    @Override
    public String toString() {
        return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("module", module)
                .append("primitive", primitive).append("executions", executions).append("mediumTime", mediumTime)
                .append("minTime", minTime).append("maxTime", maxTime).toString();
    }

}
