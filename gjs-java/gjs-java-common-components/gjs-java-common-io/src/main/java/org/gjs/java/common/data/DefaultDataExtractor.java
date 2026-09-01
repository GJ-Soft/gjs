package org.gjs.java.common.data;

import java.util.List;
import java.util.Objects;

import org.gjs.java.common.type.FieldInfo;
import org.gjs.java.common.util.ConditionUtils;
import org.gjs.java.common.util.ConversionUtils;
import org.gjs.java.common.util.ReflectionUtils;

/**
 * The Class DefaultDataExtractor.
 *
 * Clase de datos de la librería Gjs
 *
 * Extractor de datos genérico que actua sobre la clase Object.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class DefaultDataExtractor extends BaseDataExtractor<Object> {

	/** The fields. */
	private List<FieldInfo> fields;

	/**
	 * Instantiates a new default data extractor.
	 *
	 * @param obj the obj
	 */
	public DefaultDataExtractor(Object obj) {
		if (Objects.nonNull(obj)) {
			fields = ReflectionUtils.getAllFields(obj.getClass());
			for (final FieldInfo field : fields) {
				super.addColumnName(field.getField().getName());
			}
		}
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.data.DataExtractor#getColumnValue(java.lang.Object, int)
	 */

	@Override
	public String getColumnValue(Object obj, int column) {
		String value = null;
		if (ConditionUtils.allAreTrue(Objects.nonNull(obj), validColumn(column))) {
			final String typeName = fields.get(column).getField().getType().getName();
			final boolean isString = "java.lang.String".equals(typeName);
			value = ConversionUtils.toString(ReflectionUtils.getFieldValue(obj, fields.get(column).getField()));
			if (isString) {
				value = String.format("\"%s\"", value);
			}
		}
		return value;
	}

}
