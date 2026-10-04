package org.gjs.java.common.dto;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class GenericDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Esta clase esta pensada para ser utilizada en consultas JPQL genericas,
 * siendo que Hibernate no encuentra el constructor con argumentos variables y
 * por eso se incluyen constructores mas limitados, de pocos parametros, pero
 * que no serian necesarios de no ser por eso.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class GenericDto extends BaseDto {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = 659336272252905518L;

	/** The fields. */
	private final transient List<Object> fields = new ArrayList<>();

	/**
	 * The estado valoracion.
	 *
	 * @param fields the fields
	 */
	public GenericDto(Object... fields) {
		this.fields.addAll(Arrays.asList(fields));
	}

	/**
	 * Instantiates a new generic dto.
	 *
	 * @param field the field
	 */
	public GenericDto(Object field) {
		this.fields.add(field);
	}

	/**
	 * Instantiates a new generic dto.
	 *
	 * @param field1 the field 1
	 * @param field2 the field 2
	 */
	public GenericDto(Object field1, Object field2) {
		this.fields.add(field1);
		this.fields.add(field2);
	}

	/**
	 * Instantiates a new generic dto.
	 *
	 * @param field1 the field 1
	 * @param field2 the field 2
	 * @param field3 the field 3
	 */
	public GenericDto(Object field1, Object field2, Object field3) {
		this.fields.add(field1);
		this.fields.add(field2);
		this.fields.add(field3);
	}

	/**
	 * Gets the field.
	 *
	 * @param index the index
	 * @return the field
	 */
	public Object getField(int index) {
		Object res = null;
		if (ConditionUtils.allAreTrue((index >= 0), (index < fields.size()))) {
			res = fields.get(index);
		}
		return res;
	}

	/**
	 * Size.
	 *
	 * @return the int
	 */
	public int size() {
		return fields.size();
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		for (final Object field : fields) {
			result = prime * result + field.hashCode();
		}
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (!(obj instanceof final GenericDto castOther)) {
			return false;
		}
		boolean result = (fields.size() == castOther.size());
		int i = 0;
		while (ConditionUtils.allAreTrue(result, (i < fields.size()))) {
			result = fields.get(i).equals(castOther.getField(i));
			i = i + 1;
		}
		return result;
	}

	@Override
	public String toString() {
		// fields is final and never null.
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE)
				.append("fields", fields.stream().map(Object::toString).collect(Collectors.joining(","))).toString();
	}

}
