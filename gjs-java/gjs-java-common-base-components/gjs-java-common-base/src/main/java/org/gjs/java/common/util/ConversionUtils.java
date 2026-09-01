package org.gjs.java.common.util;

import java.util.Arrays;
import java.util.Enumeration;
import java.util.List;
import java.util.Locale;
import java.util.Objects;
import java.util.Properties;

import org.apache.commons.lang3.BooleanUtils;
import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.exception.GjsException;
import org.gjs.java.common.type.GenericValue;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class ConvertionUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Rutinas genéricas seguras de conversión de tipos que se utilzan en las
 * rutinas de automatización de test de Gjs.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class ConversionUtils {

	/** The Constant SI. */
	private static final List<String> BOOLEAN_TRUE_STRING_VALUES = Arrays.asList("SI", "YES", "1", "TRUE");

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(ConversionUtils.class);

	/**
	 * Clase no instanciable.
	 */
	private ConversionUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * To boolean.
	 *
	 * @param value the value
	 * @return the boolean
	 */
	public static Boolean toBoolean(String value) {
		return ConditionUtils.oneIsTrue("true".equalsIgnoreCase(value), "cierto".equalsIgnoreCase(value),
				"1".equals(value));
	}

	/**
	 * To string.
	 *
	 * @param obj the obj
	 * @return the string
	 */
	public static String toString(Object obj) {
		String res = "null";
		if (Objects.nonNull(obj)) {
			try {
				if (obj.getClass().isArray()) {
					if (obj.getClass().getComponentType().isPrimitive()) {
						res = nullSafePrimitiveArrayToString(obj);
					} else {
						res = Arrays.deepToString((Object[]) obj);
					}
				} else {
					res = obj.toString();
				}
			} catch (final Exception e) {
				res = defaultToString(obj);
			}
		}
		return res;
	}

	/**
	 * Null safe primitive array to string.
	 *
	 * @param obj the obj
	 * @return the string
	 */
	private static String nullSafePrimitiveArrayToString(Object obj) {
		String res;
		if (obj instanceof boolean[]) {
			res = Arrays.toString((boolean[]) obj);
		} else if (obj instanceof char[]) {
			res = Arrays.toString((char[]) obj);
		} else if (obj instanceof short[]) {
			res = Arrays.toString((short[]) obj);
		} else if (obj instanceof byte[]) {
			res = Arrays.toString((byte[]) obj);
		} else if (obj instanceof int[]) {
			res = Arrays.toString((int[]) obj);
		} else if (obj instanceof long[]) {
			res = Arrays.toString((long[]) obj);
		} else if (obj instanceof float[]) {
			res = Arrays.toString((float[]) obj);
		} else {
			res = Arrays.toString((double[]) obj);
		}
		return res;
	}

	/**
	 * To primitive value.
	 *
	 * @param typeName the type name
	 * @param value    the value
	 * @return the object
	 */
	public static Object toPrimitiveValue(String typeName, String value) {
		Object primitiveValue = null;
		if (Objects.nonNull(value)) {
			final GenericValue genericValue = new GenericValue(value);
			final PrimitiveType type = getPrimitiveType(typeName);
			if (PrimitiveType.BOOLEAN.equals(type)) {
				primitiveValue = genericValue.toBoolean();
			} else if (PrimitiveType.CHAR.equals(type)) {
				primitiveValue = genericValue.toChar();
			} else if (PrimitiveType.BYTE.equals(type)) {
				primitiveValue = genericValue.toByte();
			} else if (PrimitiveType.SHORT.equals(type)) {
				primitiveValue = genericValue.toShort();
			} else if (PrimitiveType.INTEGER.equals(type)) {
				primitiveValue = genericValue.toInt();
			} else if (PrimitiveType.LONG.equals(type)) {
				primitiveValue = genericValue.toLong();
			} else if (PrimitiveType.FLOAT.equals(type)) {
				primitiveValue = genericValue.toFloat();
			} else if (PrimitiveType.DOUBLE.equals(type)) {
				primitiveValue = genericValue.toDouble();
			}
		}
		return primitiveValue;
	}

	/**
	 * Gets the primitive type.
	 *
	 * @param typeName the type name
	 * @return the primitive type
	 */
	private static PrimitiveType getPrimitiveType(String typeName) {
		PrimitiveType type = null;
		if (PrimitiveType.isPrimitiveNative(typeName)) {
			type = PrimitiveType.get(typeName);
		} else if (PrimitiveType.isPrimitiveClass(typeName)) {
			type = PrimitiveType.getFromClass(typeName);
		}
		return type;
	}

	/**
	 * To managed value.
	 *
	 * @param typeName the type name
	 * @param value    the value
	 * @return the object
	 */
	public static Object toManagedValue(String typeName, String value) {
		Object managedValue = null;
		if (Objects.nonNull(value)) {
			logger.debug("Crendo GenericValue {} para convertir a {}", value, typeName);
			final GenericValue genericValue = new GenericValue(value);
			ManagedType type = null;
			if (ManagedType.isManaged(typeName)) {
				type = ManagedType.get(typeName);
			}
			if (ManagedType.BIGDECIMAL.equals(type)) {
				managedValue = genericValue.toBigDecimal();
			} else if (ManagedType.BIGINTEGER.equals(type)) {
				managedValue = genericValue.toBigInteger();
			} else if (ManagedType.DATE.equals(type)) {
				managedValue = genericValue.toDate();
			} else if (ManagedType.TIMESTAMP.equals(type)) {
				managedValue = genericValue.toTimestamp();
			} else if (ManagedType.LOCALDATETIME.equals(type)) {
				managedValue = genericValue.toLocalDateTime();
			} else if (ManagedType.LOCALDATE.equals(type)) {
				managedValue = genericValue.toLocalDate();
			} else if (ManagedType.STRING.equals(type)) {
				managedValue = genericValue.toString();
			}
		}
		return managedValue;
	}

	/**
	 * To object value.
	 *
	 * @param typeName the type name
	 * @param value    the value
	 * @return the object
	 */
	public static Object toObjectValue(String typeName, String value) {
		Object objectValue = null;
		if (Objects.nonNull(value)) {
			if (PrimitiveType.isPrimitive(typeName)) {
				objectValue = ConversionUtils.toPrimitiveValue(typeName, value);
			} else if (ManagedType.isManaged(typeName)) {
				objectValue = ConversionUtils.toManagedValue(typeName, value);
			}
		}
		return objectValue;
	}

	/**
	 * convert value.
	 *
	 * IMPORTANTE: Sólo contempla los casos que nos han sido necesarios hasta ahora
	 *
	 * @param typeName the type name
	 * @param isArray  the is array
	 * @param value    the value
	 * @return the object
	 */
	public static Object convertValue(String typeName, boolean isArray, Object value) {
		Object objectValue = value;
		if (Objects.nonNull(value)) {
			if (BooleanUtils.isFalse(isArray)) {
				if (ConditionUtils.allAreTrue(ManagedType.STRING.isSameType(value.getClass().getCanonicalName()),
						!ManagedType.STRING.isSameType(typeName))) {
					logger.debug("Convirtiendo String a {}", typeName);
					objectValue = ConversionUtils.toObjectValue(typeName, (String) value);
				}

			} else if (PrimitiveType.BYTE.isSameNativeType(typeName)) {
				objectValue = ((String) value).getBytes();
			} else {
				logger.warn("CASO DE CONVERSION NO CONTEMPLADO: {}", value.getClass().getCanonicalName());
				objectValue = null;
			}
		}
		return objectValue;
	}

	/**
	 * To native array.
	 *
	 * @param values the values
	 * @return the byte[]
	 */
	public static byte[] toNativeArray(Byte[] values) {
		if (Objects.isNull(values)) {
			return new byte[0];
		}
		final byte[] array = new byte[values.length];
		for (int i = 0; i < values.length; i = i + 1) {
			if (Objects.isNull(values[i])) {
				array[i] = 0;
			} else {
				array[i] = values[i].byteValue();
			}
		}
		return array;
	}

	/**
	 * To native array.
	 *
	 * @param values the values
	 * @return the long[]
	 */
	public static long[] toNativeArray(Long[] values) {
		if (Objects.isNull(values)) {
			return new long[0];
		}
		final long[] array = new long[values.length];
		for (int i = 0; i < values.length; i = i + 1) {
			if (Objects.isNull(values[i])) {
				array[i] = 0;
			} else {
				array[i] = values[i].longValue();
			}
		}
		return array;
	}

	/**
	 * To native array.
	 *
	 * @param values the values
	 * @return the int[]
	 */
	public static int[] toNativeArray(Integer[] values) {
		if (Objects.isNull(values)) {
			return new int[0];
		}
		final int[] array = new int[values.length];
		for (int i = 0; i < values.length; i = i + 1) {
			if (Objects.isNull(values[i])) {
				array[i] = 0;
			} else {
				array[i] = values[i].intValue();
			}
		}
		return array;
	}

	/**
	 * To native array.
	 *
	 * @param values the values
	 * @return the short[]
	 */
	public static short[] toNativeArray(Short[] values) {
		if (Objects.isNull(values)) {
			return new short[0];
		}
		final short[] array = new short[values.length];
		for (int i = 0; i < values.length; i = i + 1) {
			if (Objects.isNull(values[i])) {
				array[i] = 0;
			} else {
				array[i] = values[i].shortValue();
			}
		}
		return array;
	}

	/**
	 * To native array.
	 *
	 * @param values the values
	 * @return the boolean[]
	 */
	public static boolean[] toNativeArray(Boolean[] values) {
		if (Objects.isNull(values)) {
			return new boolean[0];
		}
		final boolean[] array = new boolean[values.length];
		for (int i = 0; i < values.length; i = i + 1) {
			if (Objects.isNull(values[i])) {
				array[i] = false;
			} else {
				array[i] = values[i].booleanValue();
			}
		}
		return array;
	}

	/**
	 * To native array.
	 *
	 * @param values the values
	 * @return the float[]
	 */
	public static float[] toNativeArray(Float[] values) {
		if (Objects.isNull(values)) {
			return new float[0];
		}
		final float[] array = new float[values.length];
		for (int i = 0; i < values.length; i = i + 1) {
			if (Objects.isNull(values[i])) {
				array[i] = 0;
			} else {
				array[i] = values[i].floatValue();
			}
		}
		return array;
	}

	/**
	 * To native array.
	 *
	 * @param values the values
	 * @return the double[]
	 */
	public static double[] toNativeArray(Double[] values) {
		if (Objects.isNull(values)) {
			return new double[0];
		}
		final double[] array = new double[values.length];
		for (int i = 0; i < values.length; i = i + 1) {
			if (Objects.isNull(values[i])) {
				array[i] = 0;
			} else {
				array[i] = values[i].doubleValue();
			}
		}
		return array;
	}

	/**
	 * To native array.
	 *
	 * @param values the values
	 * @return the char[]
	 */
	public static char[] toNativeArray(Character[] values) {
		if (Objects.isNull(values)) {
			return new char[0];
		}
		final char[] array = new char[values.length];
		for (int i = 0; i < values.length; i = i + 1) {
			if (Objects.isNull(values[i])) {
				array[i] = 0;
			} else {
				array[i] = values[i].charValue();
			}
		}
		return array;
	}

	/**
	 * Default to string.
	 *
	 * @param obj the obj
	 * @return the string
	 */
	private static String defaultToString(Object obj) {
		if (Objects.isNull(obj)) {
			return "null";
		}
		return String.format("%s@%s", obj.getClass().getName(), Integer.toHexString(System.identityHashCode(obj)));
	}

	/**
	 * To string.
	 *
	 * @param prop the Properties
	 * @return the string
	 */
	public static String toString(Properties prop) {
		String res = "null";
		if (Objects.nonNull(prop)) {
			final StringBuilder builder = new StringBuilder();
			@SuppressWarnings("rawtypes")
			final Enumeration keys = prop.keys();
			while (keys.hasMoreElements()) {
				final String key = (String) keys.nextElement();
				final String value = (String) prop.get(key);
				builder.append(key).append('=').append(value).append(';');
			}
			res = builder.toString();
		}
		return res;
	}

	/**
	 * Long value.
	 *
	 * @param value the value
	 * @return the long
	 */
	public static long longValue(Long value) {
		return (value == null ? 0 : value.longValue());
	}

	/**
	 * Int value.
	 *
	 * @param value the value
	 * @return the int
	 */
	public static int intValue(Integer value) {
		return (value == null ? 0 : value.intValue());
	}

	/**
	 * Int value.
	 *
	 * @param value the value
	 * @return the int
	 */
	public static int intValue(Short value) {
		return (value == null ? 0 : value.intValue());
	}

	/**
	 * Long value.
	 *
	 * @param value the value
	 * @return the long
	 * @throws GjsException the semilla util exception
	 */
	public static long longValue(String value) throws GjsException {
		try {
			return Long.parseLong(value);
		} catch (final NumberFormatException e) {
			final String message = String.format("Valor entero largo invalido: %s", value);
			throw new GjsException(message);
		}
	}

	/**
	 * Unsigned value.
	 *
	 * @param value the value
	 * @return the long
	 * @throws GjsException the semilla util exception
	 */
	public static long unsignedLongValue(String value) throws GjsException {
		try {
			return Long.parseUnsignedLong(value);
		} catch (final NumberFormatException e) {
			final String message = String.format("Valor entero largo invalido: %s", value);
			throw new GjsException(message);
		}
	}

	/**
	 * Obtiene un boolean a partir de un string en base de datos.
	 *
	 * @param value se pasa como parametro
	 * @return Devuelve true or false
	 */
	public static boolean booleanValue(String value) {
		boolean res = false;
		if (!StringUtils.isAllBlank(value)) {
			res = CollectionUtils.contains(BOOLEAN_TRUE_STRING_VALUES, value.trim().toUpperCase(Locale.getDefault()));
		}
		return res;
	}

	/**
	 * Assign value.
	 *
	 * @param <T>          the generic type
	 * @param value        the value
	 * @param defaultValue the default value
	 * @return the t
	 */
	public static <T> T assignValue(T value, T defaultValue) {
		return (Objects.nonNull(value) ? value : defaultValue);
	}

}
