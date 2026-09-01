#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
package ${package};

import java.util.Objects;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class Ejemplo.
 * 
 * Clase de la aplicación ${nombreCapitalizado}
 *
 * Clase para TODO.
 *
 * --------------------------------------------------------------------------------------------------------------------
 * 
 * @author GJ Software
 * @version 1.0.0-RC.2
 * @since 1.0.0-RC.2
 *
 */
@Getter
@Setter
public class EjemploType {

	/** The descripcion. */
	private String descripcion;

	/** The nombre. */
	private String nombre;

	/**
	 * Instantiates a new ejemplo type.
	 */
	public EjemploType() {
		// No hace nada
	}

	/**
	 * Example of method.
	 */
	public void doSomething() {
		// No hace nada
	}

	public boolean isValid() {
		return (EjemploUtils.isValidNombre(nombre));
	}

	@Override
	public int hashCode() {
		return Objects.hash(nombre);
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (!(obj instanceof EjemploType)) {
			return false;
		}
		final EjemploType other = (EjemploType) obj;
		return Objects.equals(nombre, other.nombre);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object${symbol_pound}toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("nombre", nombre)
				.append("descripcion", descripcion).toString();
	}

}