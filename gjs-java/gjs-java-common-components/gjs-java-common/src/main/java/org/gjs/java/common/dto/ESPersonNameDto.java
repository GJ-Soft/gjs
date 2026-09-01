package org.gjs.java.common.dto;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class ESPersonNameDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Nombre de persona a la española: añade el segundo apellido.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class ESPersonNameDto extends PersonNameDto {

	private String secondSurname;

	public ESPersonNameDto(String name, String firstSurname) {
		this(name, firstSurname, null);
	}

	public ESPersonNameDto(String name, String firstSurname, String secondSurname) {
		this.name = name;
		this.firstSurname = firstSurname;
		this.secondSurname = secondSurname;
	}

	@Override
	public String getFullName() {
		return String.format("%s %s %s", name, firstSurname, Objects.nonNull(secondSurname) ? secondSurname : "");
	}

	@Override
	public String getFormattedFullName() {
		return String.format("%s %s, %s", firstSurname, Objects.nonNull(secondSurname) ? secondSurname : "", name);
	}

	@Override
	public PersonNameDto clone() {
		return new ESPersonNameDto(name, firstSurname, secondSurname);
	}

}
