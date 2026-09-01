package org.gjs.java.common.dto;

import java.util.Objects;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class ENPersonNameDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Nombre de persona a la inglesa: añade el nombre intermedio.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class ENPersonNameDto extends PersonNameDto {

	private String middleName;

	public ENPersonNameDto(String name, String surname) {
		this(name, surname, null);
	}

	public ENPersonNameDto(String name, String middleName, String surname) {
		this.name = name;
		this.firstSurname = surname;
		this.middleName = middleName;
	}

	@Override
	public String getFullName() {
		return String.format("%s %s %s", name, Objects.nonNull(middleName) ? middleName : "", firstSurname);
	}

	@Override
	public String getFormattedFullName() {
		return String.format("%s, %s %s", firstSurname, name, Objects.nonNull(middleName) ? middleName : "");
	}

	@Override
	public PersonNameDto clone() {
		return new ENPersonNameDto(name, middleName, firstSurname);
	}

}
