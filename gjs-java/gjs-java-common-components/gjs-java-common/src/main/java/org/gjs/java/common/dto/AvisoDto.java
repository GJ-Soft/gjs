package org.gjs.java.common.dto;

import java.util.Date;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class AvisoDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para contener la información de un aviso.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
public class AvisoDto extends EntityPkLongDto {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = -6449645719040346268L;

	/** The Constant MAX_LEN_MENSAJE. */
	private static final int MAX_LEN_MENSAJE = 1024;

	/** The instancia. */
	private String instancia;

	/** The fecha hora. */
	private Date fechaHora;

	/** The mensaje. */
	private String mensaje;

	/** The causa. */
	private String causa;

	/**
	 * Instantiates a new endpoint dto.
	 */
	public AvisoDto() {
		// No hace nada
	}

	/**
	 * Instantiates a new aviso dto.
	 *
	 * @param instancia the instancia
	 * @param mensaje   the mensaje
	 * @param causa     the causa
	 */
	public AvisoDto(String instancia, String mensaje, String causa) {
		this.instancia = instancia;
		setMensaje(mensaje);
		this.causa = causa;
		this.fechaHora = new Date();
	}

	/**
	 * Sets the mensaje.
	 *
	 * @param mensaje the new mensaje
	 */
	public void setMensaje(String mensaje) {
		this.mensaje = StringUtils.abbreviate(mensaje, MAX_LEN_MENSAJE);
	}

	@Override
	public boolean equals(Object o) {
		return super.equals(o);
	}

	@Override
	public int hashCode() {
		return super.hashCode();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("instancia", instancia)
				.append("fechaHora", fechaHora).append("mensaje", mensaje).append("causa", causa).append("id", id)
				.toString();
	}

}
