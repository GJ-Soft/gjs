package org.gjs.java.common.dto;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.Date;
import java.util.Objects;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;
import org.gjs.java.common.util.DateUtils;

import com.fasterxml.jackson.annotation.JsonIgnore;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class RangoFechasDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para almacenar los datos de un rango de fechas.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */

/**
 * Gets the fecha fin.
 *
 * @return the fecha fin
 */
@Getter

/**
 * Sets the fecha fin.
 *
 * @param fechaFin the new fecha fin
 */
@Setter
public class DateRangeDto implements Serializable {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = 3989936758485969028L;

	/** The fecha ini. */
	private LocalDateTime fechaIni;

	/** The fecha fin. */
	private LocalDateTime fechaFin;

	/**
	 * Instantiates a new rango fecha dto.
	 */
	public DateRangeDto() {
		// No hace nada
	}

	/**
	 * Instantiates a new rango fecha dto.
	 *
	 * @param fechaIni the fecha ini
	 * @param fechaFin the fecha fin
	 */
	public DateRangeDto(Date fechaIni, Date fechaFin) {
		this.fechaIni = DateUtils.toLocalDateTime(fechaIni);
		this.fechaFin = DateUtils.toLocalDateTime(fechaFin);
	}

	/**
	 * Instantiates a new rango fechas dto.
	 *
	 * @param fechaIni the fecha ini
	 * @param fechaFin the fecha fin
	 */
	public DateRangeDto(LocalDate fechaIni, LocalDate fechaFin) {
		if (Objects.nonNull(fechaIni)) {
			this.fechaIni = fechaIni.atStartOfDay();
		}
		if (Objects.nonNull(fechaFin)) {
			this.fechaFin = fechaFin.atTime(23, 59, 59);
		}
	}

	/**
	 * Instantiates a new rango fechas dto.
	 *
	 * @param fechaIni the fecha ini
	 * @param fechaFin the fecha fin
	 */
	public DateRangeDto(LocalDateTime fechaIni, LocalDateTime fechaFin) {
		this.fechaIni = fechaIni;
		this.fechaFin = fechaFin;
	}

	/**
	 * Gets the fecha ini as date.
	 *
	 * @return the fecha ini as date
	 */
	@JsonIgnore
	public Date getFechaIniAsDate() {
		return DateUtils.toDate(fechaIni);
	}

	/**
	 * Gets the fecha fin as date.
	 *
	 * @return the fecha fin as date
	 */
	@JsonIgnore
	public Date getFechaFinAsDate() {
		return DateUtils.toDate(fechaFin);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("fechaIni", fechaIni)
				.append("fechaFin", fechaFin).toString();
	}

}
