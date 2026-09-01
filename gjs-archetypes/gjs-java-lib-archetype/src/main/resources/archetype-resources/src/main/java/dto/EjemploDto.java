#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
package ${package}.dto;

import java.util.Objects;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;
import org.gjs.java.common.dto.EntityDto;
import org.gjs.java.common.dto.EntityPkLongDto;
import org.gjs.java.common.util.ComparationUtils;

import lombok.Getter;
import lombok.Setter;


/**
 * The Class EjemploDto.
 * 
 * Clase de datos de la aplicación ${capitalizedName}
 *
 * Clase DTO para almacenar los datos de un ejemplo.
 *
 * @author Semilla
 * @version ${version}
 * @since ${version}
 *
 */
@Getter
@Setter
public class EjemploDto extends EntityPkLongDto {

	/**
	 * 
	 */
	private static final long serialVersionUID = -6812443784649707144L;

	/** The descripcion. */
	private String descripcion;

	/** The nombre. */
	private String nombre;

	/**
	 * Instantiates a new ejemplo dto.
	 */
	public EjemploDto() {
		// No hace nada
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.common.dto.EntidadDto${symbol_pound}hashCode()
	 */

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = super.hashCode();
		result = prime * result + Objects.hash(nombre);
		return result;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.common.dto.EntidadDto${symbol_pound}equals(java.lang.Object)
	 */

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (!(obj instanceof EjemploDto)) {
			return false;
		}
		final EjemploDto other = (EjemploDto) obj;
		return Objects.equals(nombre, other.nombre);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.common.dto.EntidadDto${symbol_pound}compareTo(org.gjs.java.common.dto.
	 * EntidadDto)
	 */

	@Override
	public int compareTo(EntityDto<?> o) {
		int res = -1;
		if (o instanceof EjemploDto) {
			final EjemploDto aux = (EjemploDto) o;
			res = super.compareTo(aux);
			if (res == 0) {
				res = ComparationUtils.compareTo(nombre, aux.getNombre());
			}
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object${symbol_pound}toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("id", id).append("nombre", nombre)
				.append("descripcion", descripcion).toString();
	}

}
