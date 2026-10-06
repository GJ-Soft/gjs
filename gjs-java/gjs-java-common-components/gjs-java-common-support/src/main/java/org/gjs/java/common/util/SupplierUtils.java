package org.gjs.java.common.util;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.sql.Timestamp;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Date;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import org.apache.commons.lang3.ObjectUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.enums.ManagedType;
import org.gjs.java.common.enums.PrimitiveType;
import org.gjs.java.common.supplier.ManagedObjectSupplierBattery;
import org.gjs.java.common.supplier.PrimitiveObjectSupplierBattery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class SupplierUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Algunas utilidades de ayuda para los generadores de objetos aleatorios y
 * objetos vacíos. Se considera un objeto vacío un objeto no nulo, pero con sus
 * campos a nulo, su contenido de logitud cero, o en caso de tipos primitivos
 * los valores por defecto de cada tipo.
 *
 * generatePrimitiveValue: genera un objeto aleatorio de uno de los tipos
 * incluidos en el enumerado PrimitiveType
 *
 * generateEmptyPrimitiveValue: genera un objeto vacío de uno de los tipos
 * incluidos en el enumerado PrimitiveType
 *
 * generateArrayPrimitiveValue: genera un array de longitud aleatoria de objetos
 * aleatorio de uno de los tipos incluidos en el enumerado PrimitiveType
 *
 * generateEmptyArrayPrimitiveValue: genera un array de longitud aleatoria de
 * objetos vacíos de uno de los tipos incluidos en el enumerado PrimitiveType
 *
 * generateArrayPrimitiveNativeValue: genera un array de longitud aleatoria de
 * objetos aleatorio de uno de los tipos incluidos en el enumerado PrimitiveType
 * transformado en tipo nativo
 *
 * generateEmptyArrayPrimitiveNativeValue: genera un array de longitud aleatoria
 * de objetos vacíos de uno de los tipos incluidos en el enumerado PrimitiveType
 * transformado en tipo nativo
 *
 * generateCollectionPrimitiveValue: genera una colección de longitud aleatoria
 * de objetos aleatorio de uno de los tipos incluidos en el enumerado
 * PrimitiveType
 *
 * generateListPrimitiveValue: genera una lista de longitud aleatoria de objetos
 * aleatorio de uno de los tipos incluidos en el enumerado PrimitiveType
 *
 * generateSetPrimitiveValue: genera un conjunto de longitud aleatoria de
 * objetos aleatorio de uno de los tipos incluidos en el enumerado PrimitiveType
 *
 * generateMenagedValue: genera un objeto aleatorio de uno de los tipos
 * incluidos en el enumerado ManagedType
 *
 * generateEmptyManagedValue: genera un objeto vacío de uno de los tipos
 * incluidos en el enumerado ManagedType
 *
 * generateArrayManagedValue: genera un array de longitud aleatoria de objetos
 * aleatorio de uno de los tipos incluidos en el enumerado ManagedType
 *
 * generateEmptyArrayManagedValue: genera un array de longitud aleatoria de
 * objetos vacíos de uno de los tipos incluidos en el enumerado ManagedType
 *
 * generateCollectionManagedValue: genera una colección de longitud aleatoria de
 * objetos aleatorio de uno de los tipos incluidos en el enumerado ManagedType
 *
 * generateListManagedValue: genera una lista de longitud aleatoria de objetos
 * aleatorio de uno de los tipos incluidos en el enumerado ManagedType
 *
 * generateSetManagedValue: genera un conjunto de longitud aleatoria de objetos
 * aleatorio de uno de los tipos incluidos en el enumerado ManagedType
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class SupplierUtils {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(SupplierUtils.class);

	/** The primitive object suppliers. */
	private static final PrimitiveObjectSupplierBattery primitiveSuppliers = new PrimitiveObjectSupplierBattery();

	/** The managed objects suppliers. */
	private static final ManagedObjectSupplierBattery managedSuppliers = new ManagedObjectSupplierBattery();

	/**
	 * Clase no instanciable.
	 */
	private SupplierUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Generate primitive value.
	 *
	 * Genera un objeto aleatorio del tipo primitivo indicado. En caso de que el
	 * tipo no corresponda a un tipo primitivo retorna nulo.
	 *
	 * @param typeName the type name
	 * @return the object
	 */
	public static Object generatePrimitiveValue(String typeName) {
		Object value = null;
		if (PrimitiveType.LONG.isSameType(typeName)) {
			value = primitiveSuppliers.randomLong();
		} else if (PrimitiveType.INTEGER.isSameType(typeName)) {
			value = primitiveSuppliers.randomInt();
		} else if (PrimitiveType.SHORT.isSameType(typeName)) {
			value = primitiveSuppliers.randomShort();
		} else if (PrimitiveType.BOOLEAN.isSameType(typeName)) {
			value = primitiveSuppliers.randomBoolean();
		} else if (PrimitiveType.CHAR.isSameType(typeName)) {
			value = primitiveSuppliers.randomChar();
		} else if (PrimitiveType.FLOAT.isSameType(typeName)) {
			value = primitiveSuppliers.randomFloat();
		} else if (PrimitiveType.DOUBLE.isSameType(typeName)) {
			value = primitiveSuppliers.randomDouble();
		} else if (PrimitiveType.BYTE.isSameType(typeName)) {
			value = primitiveSuppliers.randomByte();
		} else {
			logger.warn("TIPO PRIMITIVO INESPERADO: {}", typeName);
		}
		return value;
	}

	/**
	 * Generate primitive value.
	 *
	 * Genera un objeto vacío del tipo primitivo indicado. En el caso de los tipos
	 * primitivos el tipo vacío no tiene mucho sentido, pero se necesita para tratar
	 * igual todos los tipos de objetos: para los numéricos sería 0, carácter
	 * blanco... En caso de que el tipo no corresponda a un tipo primitivo retorna
	 * nulo.
	 *
	 * @param typeName the type name
	 * @return the object
	 */
	public static Object generateEmptyPrimitiveValue(String typeName) {
		Object value = null;
		if (PrimitiveType.LONG.isSameType(typeName)) {
			value = primitiveSuppliers.emptyLong();
		} else if (PrimitiveType.INTEGER.isSameType(typeName)) {
			value = primitiveSuppliers.emptyInt();
		} else if (PrimitiveType.SHORT.isSameType(typeName)) {
			value = primitiveSuppliers.emptyShort();
		} else if (PrimitiveType.BOOLEAN.isSameType(typeName)) {
			value = primitiveSuppliers.emptyBoolean();
		} else if (PrimitiveType.CHAR.isSameType(typeName)) {
			value = primitiveSuppliers.emptyChar();
		} else if (PrimitiveType.FLOAT.isSameType(typeName)) {
			value = primitiveSuppliers.emptyFloat();
		} else if (PrimitiveType.DOUBLE.isSameType(typeName)) {
			value = primitiveSuppliers.emptyDouble();
		} else if (PrimitiveType.BYTE.isSameType(typeName)) {
			value = primitiveSuppliers.emptyByte();
		} else {
			logger.warn("TIPO PRIMITIVO INESPERADO: {}", typeName);
		}
		return value;
	}

	/**
	 * Generate array primitive value.
	 *
	 * Genera un array de longitud aleatoria de objetos aleatorio del tipo primitivo
	 * indicado. En caso de que el tipo no corresponda a un tipo primitivo retorna
	 * nulo.
	 *
	 * @param typeName the type name
	 * @return the object[]
	 */
	public static Object[] generateArrayPrimitiveValue(String typeName) {
		Object[] value = null;
		if (PrimitiveType.LONG.isSameClassType(typeName)) {
			value = primitiveSuppliers.randomArrayLong();
		} else if (PrimitiveType.INTEGER.isSameClassType(typeName)) {
			value = primitiveSuppliers.randomArrayInt();
		} else if (PrimitiveType.SHORT.isSameClassType(typeName)) {
			value = primitiveSuppliers.randomArrayShort();
		} else if (PrimitiveType.BOOLEAN.isSameClassType(typeName)) {
			value = primitiveSuppliers.randomArrayBoolean();
		} else if (PrimitiveType.CHAR.isSameClassType(typeName)) {
			value = primitiveSuppliers.randomArrayChar();
		} else if (PrimitiveType.FLOAT.isSameClassType(typeName)) {
			value = primitiveSuppliers.randomArrayFloat();
		} else if (PrimitiveType.DOUBLE.isSameClassType(typeName)) {
			value = primitiveSuppliers.randomArrayDouble();
		} else if (PrimitiveType.BYTE.isSameClassType(typeName)) {
			value = primitiveSuppliers.randomBytes();
		} else {
			logger.warn("TIPO PRIMITIVO INESPERADO: {}", typeName);
		}
		return value;
	}

	/**
	 * Generate empty array primitive value.
	 *
	 * Genera un array de longitud cero de objetos aleatorio del tipo primitivo
	 * indicado. En caso de que el tipo no corresponda a un tipo primitivo retorna
	 * nulo.
	 *
	 * @param typeName the type name
	 * @return the object[]
	 */
	public static Object[] generateEmptyArrayPrimitiveValue(String typeName) {
		Object[] value = null;
		if (PrimitiveType.LONG.isSameClassType(typeName)) {
			value = primitiveSuppliers.emptyArrayLong();
		} else if (PrimitiveType.INTEGER.isSameClassType(typeName)) {
			value = primitiveSuppliers.emptyArrayInt();
		} else if (PrimitiveType.SHORT.isSameClassType(typeName)) {
			value = primitiveSuppliers.emptyArrayShort();
		} else if (PrimitiveType.BOOLEAN.isSameClassType(typeName)) {
			value = primitiveSuppliers.emptyArrayBoolean();
		} else if (PrimitiveType.CHAR.isSameClassType(typeName)) {
			value = primitiveSuppliers.emptyArrayChar();
		} else if (PrimitiveType.FLOAT.isSameClassType(typeName)) {
			value = primitiveSuppliers.emptyArrayFloat();
		} else if (PrimitiveType.DOUBLE.isSameClassType(typeName)) {
			value = primitiveSuppliers.emptyArrayDouble();
		} else if (PrimitiveType.BYTE.isSameClassType(typeName)) {
			value = primitiveSuppliers.emptyBytes();
		} else {
			logger.warn("TIPO PRIMITIVO INESPERADO: {}", typeName);
		}
		return value;
	}

	/**
	 * Generate array primitive native value.
	 *
	 * Genera un array de longitud aleatoria de objetos aleatorio del tipo primitivo
	 * indicado retornado como tipo nativo. En caso de que el tipo no corresponda a
	 * un tipo primitivo retorna nulo.
	 *
	 * @param typeName the type name
	 * @return the object
	 */
	public static Object generateArrayPrimitiveNativeValue(String typeName) {
		Object value = null;
		if (PrimitiveType.LONG.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.randomArrayLong());
		} else if (PrimitiveType.INTEGER.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.randomArrayInt());
		} else if (PrimitiveType.SHORT.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.randomArrayShort());
		} else if (PrimitiveType.BOOLEAN.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.randomArrayBoolean());
		} else if (PrimitiveType.CHAR.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.randomArrayChar());
		} else if (PrimitiveType.FLOAT.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.randomArrayFloat());
		} else if (PrimitiveType.DOUBLE.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.randomArrayDouble());
		} else if (PrimitiveType.BYTE.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.randomBytes());
		} else {
			logger.warn("TIPO PRIMITIVO INESPERADO: {}", typeName);
		}
		return value;
	}

	/**
	 * Generate empty array primitive native value.
	 *
	 * Genera un array de longitud cero de objetos aleatorio del tipo primitivo
	 * indicado retornado como tipo nativo. En caso de que el tipo no corresponda a
	 * un tipo primitivo retorna nulo.
	 *
	 * @param typeName the type name
	 * @return the object
	 */
	public static Object generateEmptyArrayPrimitiveNativeValue(String typeName) {
		Object value = null;
		if (PrimitiveType.LONG.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.emptyArrayLong());
		} else if (PrimitiveType.INTEGER.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.emptyArrayInt());
		} else if (PrimitiveType.SHORT.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.emptyArrayShort());
		} else if (PrimitiveType.BOOLEAN.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.emptyArrayBoolean());
		} else if (PrimitiveType.CHAR.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.emptyArrayChar());
		} else if (PrimitiveType.FLOAT.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.emptyArrayFloat());
		} else if (PrimitiveType.DOUBLE.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.emptyArrayDouble());
		} else if (PrimitiveType.BYTE.isSameNativeType(typeName)) {
			value = ConversionUtils.toNativeArray(primitiveSuppliers.emptyBytes());
		} else {
			logger.warn("TIPO PRIMITIVO INESPERADO: {}", typeName);
		}
		return value;
	}

	/**
	 * Generate collection primitive value.
	 *
	 * Genera una coleccion de longitud aleatoria de objetos aleatorio del tipo
	 * primitivo indicado retornado como tipo nativo. En caso de que el tipo no
	 * corresponda a un tipo primitivo retorna nulo.
	 *
	 * Por ahora sólo se ha implementado para listas (List) y conjuntos (Set).
	 *
	 * @param typeName    the type name
	 * @param subtypeName the subtype name
	 * @return the collection
	 */
	public static Collection<?> generateCollectionPrimitiveValue(String typeName, String subtypeName) {
		Collection<?> value = null;
		if (ObjectUtils.allNotNull(typeName, subtypeName)) {
			if (CollectionUtils.isList(typeName)) {
				value = generateListPrimitiveValue(subtypeName);
			} else if (CollectionUtils.isSet(typeName)) {
				value = generateSetPrimitiveValue(subtypeName);
			} else {
				logger.warn("Colecccion no implementada");
			}
		}
		return value;
	}

	/**
	 * Generate list primitive value.
	 *
	 * Genera una lista de longitud aleatoria de objetos aleatorio del tipo
	 * primitivo indicado retornado como tipo nativo. En caso de que el tipo no
	 * corresponda a un tipo primitivo retorna nulo.
	 *
	 * @param typeName the type name
	 * @return the collection
	 */
	public static Collection<?> generateListPrimitiveValue(String typeName) {
		Collection<?> value = null;
		if (PrimitiveType.LONG.isSameClassType(typeName)) {
			final List<Long> collection = new ArrayList<>();
			Collections.addAll(collection, primitiveSuppliers.randomLong());
			value = collection;
		} else if (PrimitiveType.INTEGER.isSameClassType(typeName)) {
			final List<Integer> collection = new ArrayList<>();
			Collections.addAll(collection, primitiveSuppliers.randomInt());
			value = collection;
		} else if (PrimitiveType.SHORT.isSameClassType(typeName)) {
			final List<Short> collection = new ArrayList<>();
			Collections.addAll(collection, primitiveSuppliers.randomShort());
			value = collection;
		} else if (PrimitiveType.BOOLEAN.isSameClassType(typeName)) {
			final List<Boolean> collection = new ArrayList<>();
			Collections.addAll(collection, primitiveSuppliers.randomBoolean());
			value = collection;
		} else if (PrimitiveType.CHAR.isSameClassType(typeName)) {
			final List<Character> collection = new ArrayList<>();
			Collections.addAll(collection, primitiveSuppliers.randomChar());
			value = collection;
		} else if (PrimitiveType.FLOAT.isSameClassType(typeName)) {
			final List<Float> collection = new ArrayList<>();
			Collections.addAll(collection, primitiveSuppliers.randomFloat());
			value = collection;
		} else if (PrimitiveType.DOUBLE.isSameClassType(typeName)) {
			final List<Double> collection = new ArrayList<>();
			Collections.addAll(collection, primitiveSuppliers.randomDouble());
			value = collection;
		} else if (PrimitiveType.BYTE.isSameClassType(typeName)) {
			final List<Byte> collection = new ArrayList<>();
			Collections.addAll(collection, primitiveSuppliers.randomByte());
			value = collection;
		} else {
			logger.warn("Type={} CANNOT BE ASSIGNED", typeName);
		}
		return value;
	}

	/**
	 * Generate set primitive value.
	 *
	 * Genera un conjunto de longitud aleatoria de objetos aleatorio del tipo
	 * primitivo indicado retornado como tipo nativo. En caso de que el tipo no
	 * corresponda a un tipo primitivo retorna nulo.
	 *
	 * @param typeName the type name
	 * @return the collection
	 */
	public static Collection<?> generateSetPrimitiveValue(String typeName) {
		Collection<?> value = null;
		if (PrimitiveType.LONG.isSameClassType(typeName)) {
			final Set<Long> collection = new HashSet<>();
			Collections.addAll(collection, primitiveSuppliers.randomLong());
			value = collection;
		} else if (PrimitiveType.INTEGER.isSameClassType(typeName)) {
			final Set<Integer> collection = new HashSet<>();
			Collections.addAll(collection, primitiveSuppliers.randomInt());
			value = collection;
		} else if (PrimitiveType.SHORT.isSameClassType(typeName)) {
			final Set<Short> collection = new HashSet<>();
			Collections.addAll(collection, primitiveSuppliers.randomShort());
			value = collection;
		} else if (PrimitiveType.BOOLEAN.isSameClassType(typeName)) {
			final Set<Boolean> collection = new HashSet<>();
			Collections.addAll(collection, primitiveSuppliers.randomBoolean());
			value = collection;
		} else if (PrimitiveType.CHAR.isSameClassType(typeName)) {
			final Set<Character> collection = new HashSet<>();
			Collections.addAll(collection, primitiveSuppliers.randomChar());
			value = collection;
		} else if (PrimitiveType.FLOAT.isSameClassType(typeName)) {
			final Set<Float> collection = new HashSet<>();
			Collections.addAll(collection, primitiveSuppliers.randomFloat());
			value = collection;
		} else if (PrimitiveType.DOUBLE.isSameClassType(typeName)) {
			final Set<Double> collection = new HashSet<>();
			Collections.addAll(collection, primitiveSuppliers.randomDouble());
			value = collection;
		} else if (PrimitiveType.BYTE.isSameClassType(typeName)) {
			final Set<Byte> collection = new HashSet<>();
			Collections.addAll(collection, primitiveSuppliers.randomByte());
			value = collection;
		} else {
			logger.warn("Type={} CANNOT BE ASSIGNED", typeName);
		}
		return value;
	}

	/**
	 * Generate managed value.
	 *
	 * Genera un objeto aleatorio del tipo gestionado indicado. En caso de que el
	 * tipo no corresponda a un tipo gestionado retorna nulo.
	 *
	 * Por ahora como tipos gestionados sólo se admiten: String, Date, LocalDate,
	 * LocalDateTime, Timestamp, BigInteger, BigDecimal, Throwable y Exception
	 *
	 * @param typeName the type name
	 * @return the object
	 */
	public static Object generateManagedValue(String typeName) {
		Object value = null;
		if (ManagedType.STRING.isSameType(typeName)) {
			value = managedSuppliers.randomString();
		} else if (ManagedType.BIGDECIMAL.isSameType(typeName)) {
			value = managedSuppliers.randomBigDecimal();
		} else if (ManagedType.BIGINTEGER.isSameType(typeName)) {
			value = managedSuppliers.randomBigInteger();
		} else if (ManagedType.LOCALDATETIME.isSameType(typeName)) {
			value = managedSuppliers.randomLocalDateTime();
		} else if (ManagedType.LOCALDATE.isSameType(typeName)) {
			value = managedSuppliers.randomLocalDate();
		} else if (ManagedType.TIMESTAMP.isSameType(typeName)) {
			value = managedSuppliers.randomTimestamp();
		} else if (ManagedType.DATE.isSameType(typeName)) {
			value = managedSuppliers.randomDate();
		} else if (ManagedType.THROWABLE.isSameType(typeName)) {
			value = managedSuppliers.randomException();
		} else if (ManagedType.EXCEPTION.isSameType(typeName)) {
			value = managedSuppliers.randomException();
		} else {
			logger.warn("Type={} CANNOT BE ASSIGNED", typeName);
		}
		return value;
	}

	/**
	 * Generate managed value.
	 *
	 * Genera un objeto vacío del tipo gestionado indicado. En caso de que el tipo
	 * no corresponda a un tipo gestionado retorna nulo.
	 *
	 * Por ahora como tipos gestionados sólo se admiten: String, Date, LocalDate,
	 * LocalDateTime, Timestamp, BigInteger, BigDecimal, Throwable y Exception
	 *
	 * @param typeName the type name
	 * @return the object
	 */
	public static Object generateEmptyManagedValue(String typeName) {
		Object value = null;
		if (ManagedType.STRING.isSameType(typeName)) {
			value = managedSuppliers.emptyString();
		} else if (ManagedType.BIGDECIMAL.isSameType(typeName)) {
			value = managedSuppliers.emptyBigDecimal();
		} else if (ManagedType.BIGINTEGER.isSameType(typeName)) {
			value = managedSuppliers.emptyBigInteger();
		} else if (ManagedType.LOCALDATETIME.isSameType(typeName)) {
			value = managedSuppliers.emptyLocalDateTime();
		} else if (ManagedType.LOCALDATE.isSameType(typeName)) {
			value = managedSuppliers.emptyLocalDate();
		} else if (ManagedType.TIMESTAMP.isSameType(typeName)) {
			value = managedSuppliers.emptyTimestamp();
		} else if (ManagedType.DATE.isSameType(typeName)) {
			value = managedSuppliers.emptyDate();
		} else if (ManagedType.THROWABLE.isSameType(typeName)) {
			value = managedSuppliers.emptyException();
		} else if (ManagedType.EXCEPTION.isSameType(typeName)) {
			value = managedSuppliers.emptyException();
		} else {
			logger.warn("Type={} CANNOT BE ASSIGNED", typeName);
		}
		return value;
	}

	/**
	 * Generate array managed value.
	 *
	 * Genera un array de longitud aleatoria de objetos aleatorio del tipo
	 * gestionado indicado. En caso de que el tipo no corresponda a un tipo
	 * gestionado retorna nulo.
	 *
	 * Por ahora como tipos gestionados sólo se admiten: String, Date, LocalDate,
	 * LocalDateTime, Timestamp, BigInteger, BigDecimal, Throwable y Exception
	 *
	 * @param typeName the type name
	 * @return the object
	 */
	public static Object[] generateArrayManagedValue(String typeName) {
		Object[] value = null;
		if (ManagedType.STRING.isSameType(typeName)) {
			value = managedSuppliers.randomArrayString();
		} else if (ManagedType.BIGDECIMAL.isSameType(typeName)) {
			value = managedSuppliers.randomArrayBigDecimal();
		} else if (ManagedType.BIGINTEGER.isSameType(typeName)) {
			value = managedSuppliers.randomArrayBigInteger();
		} else if (ManagedType.LOCALDATETIME.isSameType(typeName)) {
			value = managedSuppliers.randomArrayLocalDateTime();
		} else if (ManagedType.LOCALDATE.isSameType(typeName)) {
			value = managedSuppliers.randomArrayLocalDate();
		} else if (ManagedType.TIMESTAMP.isSameType(typeName)) {
			value = managedSuppliers.randomArrayTimestamp();
		} else if (ManagedType.DATE.isSameType(typeName)) {
			value = managedSuppliers.randomArrayDate();
		} else if (ManagedType.THROWABLE.isSameType(typeName)) {
			value = managedSuppliers.randomArrayException();
		} else if (ManagedType.EXCEPTION.isSameType(typeName)) {
			value = managedSuppliers.randomArrayException();
		} else {
			logger.warn("Type={} CANNOT BE ASSIGNED", typeName);
		}
		return value;
	}

	/**
	 * Generate empty array managed value.
	 *
	 * Genera un array de longitud aleatoria de objetos vacíos del tipo gestionado
	 * indicado. En caso de que el tipo no corresponda a un tipo gestionado retorna
	 * nulo.
	 *
	 * Por ahora como tipos gestionados sólo se admiten: String, Date, LocalDate,
	 * LocalDateTime, Timestamp, BigInteger, BigDecimal, Throwable y Exception
	 *
	 * @param typeName the type name
	 * @return the object[]
	 */
	public static Object[] generateEmptyArrayManagedValue(String typeName) {
		Object[] value = null;
		if (ManagedType.STRING.isSameType(typeName)) {
			value = managedSuppliers.emptyArrayString();
		} else if (ManagedType.BIGDECIMAL.isSameType(typeName)) {
			value = managedSuppliers.emptyArrayBigDecimal();
		} else if (ManagedType.BIGINTEGER.isSameType(typeName)) {
			value = managedSuppliers.emptyArrayBigInteger();
		} else if (ManagedType.LOCALDATETIME.isSameType(typeName)) {
			value = managedSuppliers.emptyArrayLocalDateTime();
		} else if (ManagedType.LOCALDATE.isSameType(typeName)) {
			value = managedSuppliers.emptyArrayLocalDate();
		} else if (ManagedType.TIMESTAMP.isSameType(typeName)) {
			value = managedSuppliers.emptyArrayTimestamp();
		} else if (ManagedType.DATE.isSameType(typeName)) {
			value = managedSuppliers.emptyArrayDate();
		} else if (ManagedType.THROWABLE.isSameType(typeName)) {
			value = managedSuppliers.emptyArrayException();
		} else if (ManagedType.EXCEPTION.isSameType(typeName)) {
			value = managedSuppliers.emptyArrayException();
		} else {
			logger.warn("Type={} CANNOT BE ASSIGNED", typeName);
		}
		return value;
	}

	/**
	 * Generate managed collection value.
	 *
	 * Genera una colección de longitud aleatoria de objetos vacíos del tipo
	 * gestionado indicado. En caso de que el tipo no corresponda a un tipo
	 * gestionado retorna nulo.
	 *
	 * Por ahora como tipos gestionados sólo se admiten: String, Date, LocalDate,
	 * LocalDateTime, Timestamp, BigInteger, BigDecimal, Throwable y Exception
	 *
	 * Por ahora sólo se generan listas(List) y conjuntos(Set)
	 *
	 * @param typeName    the type name
	 * @param subtypeName the subtype name
	 * @return the collection
	 */
	public static Collection<?> generateCollectionManagedValue(String typeName, String subtypeName) {
		Collection<?> value = null;
		if (ObjectUtils.allNotNull(typeName, subtypeName)) {
			if (CollectionUtils.isList(typeName)) {
				value = generateListManagedValue(subtypeName);
			} else if (CollectionUtils.isSet(typeName)) {
				value = generateSetManagedValue(subtypeName);

			} else {
				logger.warn("Colecccion no implementada");
			}
		}
		return value;
	}

	/**
	 * Generate list managed value.
	 *
	 * Genera una lista de longitud aleatoria de objetos vacíos del tipo gestionado
	 * indicado. En caso de que el tipo no corresponda a un tipo gestionado retorna
	 * nulo.
	 *
	 * Por ahora como tipos gestionados sólo se admiten: String, Date, LocalDate,
	 * LocalDateTime, Timestamp, BigInteger, BigDecimal, Throwable y Exception
	 *
	 * @param typeName the type name
	 * @return the collection
	 */
	public static Collection<?> generateListManagedValue(String typeName) {
		Collection<?> value = null;
		if (ManagedType.STRING.isSameType(typeName)) {
			final List<String> collection = new ArrayList<>();
			Collections.addAll(collection, managedSuppliers.randomArrayString());
			value = collection;
		} else if (ManagedType.BIGDECIMAL.isSameType(typeName)) {
			final List<BigDecimal> collection = new ArrayList<>();
			Collections.addAll(collection, managedSuppliers.randomBigDecimal());
			value = collection;
		} else if (ManagedType.BIGINTEGER.isSameType(typeName)) {
			final List<BigInteger> collection = new ArrayList<>();
			Collections.addAll(collection, managedSuppliers.randomBigInteger());
			value = collection;
		} else if (ManagedType.LOCALDATETIME.isSameType(typeName)) {
			final List<LocalDateTime> collection = new ArrayList<>();
			Collections.addAll(collection, managedSuppliers.randomLocalDateTime());
			value = collection;
		} else if (ManagedType.LOCALDATE.isSameType(typeName)) {
			final List<LocalDate> collection = new ArrayList<>();
			Collections.addAll(collection, managedSuppliers.randomLocalDate());
			value = collection;
		} else if (ManagedType.DATE.isSameType(typeName)) {
			final List<Date> collection = new ArrayList<>();
			Collections.addAll(collection, managedSuppliers.randomDate());
			value = collection;
		} else if (ManagedType.TIMESTAMP.isSameType(typeName)) {
			final List<Timestamp> collection = new ArrayList<>();
			Collections.addAll(collection, managedSuppliers.randomTimestamp());
			value = collection;
		} else if (ManagedType.THROWABLE.isSameType(typeName)) {
			final List<Throwable> collection = new ArrayList<>();
			Collections.addAll(collection, (Throwable) managedSuppliers.randomException());
			value = collection;
		} else if (ManagedType.EXCEPTION.isSameType(typeName)) {
			final List<Exception> collection = new ArrayList<>();
			Collections.addAll(collection, managedSuppliers.randomException());
			value = collection;
		} else {
			logger.warn("Type={} CANNOT BE ASSIGNED", typeName);
		}
		return value;
	}

	/**
	 * Generate set managed value.
	 *
	 * Genera un conjunto de longitud aleatoria de objetos vacíos del tipo
	 * gestionado indicado. En caso de que el tipo no corresponda a un tipo
	 * gestionado retorna nulo.
	 *
	 * Por ahora como tipos gestionados sólo se admiten: String, Date, LocalDate,
	 * LocalDateTime, Timestamp, BigInteger, BigDecimal, Throwable y Exception
	 *
	 * @param typeName the type name
	 * @return the collection
	 */
	public static Collection<?> generateSetManagedValue(String typeName) {
		Collection<?> value = null;
		if (ManagedType.STRING.isSameType(typeName)) {
			final Set<String> collection = new HashSet<>();
			Collections.addAll(collection, managedSuppliers.randomString());
			value = collection;
		} else if (ManagedType.BIGDECIMAL.isSameType(typeName)) {
			final Set<BigDecimal> collection = new HashSet<>();
			Collections.addAll(collection, managedSuppliers.randomBigDecimal());
			value = collection;
		} else if (ManagedType.BIGINTEGER.isSameType(typeName)) {
			final Set<BigInteger> collection = new HashSet<>();
			Collections.addAll(collection, managedSuppliers.randomBigInteger());
			value = collection;
		} else if (ManagedType.LOCALDATETIME.isSameType(typeName)) {
			final Set<LocalDateTime> collection = new HashSet<>();
			Collections.addAll(collection, managedSuppliers.randomLocalDateTime());
			value = collection;
		} else if (ManagedType.LOCALDATE.isSameType(typeName)) {
			final Set<LocalDate> collection = new HashSet<>();
			Collections.addAll(collection, managedSuppliers.randomLocalDate());
			value = collection;
		} else if (ManagedType.DATE.isSameType(typeName)) {
			final Set<Date> collection = new HashSet<>();
			Collections.addAll(collection, managedSuppliers.randomDate());
			value = collection;
		} else if (ManagedType.TIMESTAMP.isSameType(typeName)) {
			final Set<Timestamp> collection = new HashSet<>();
			Collections.addAll(collection, managedSuppliers.randomTimestamp());
			value = collection;
		} else if (ManagedType.THROWABLE.isSameType(typeName)) {
			final Set<Throwable> collection = new HashSet<>();
			Collections.addAll(collection, (Throwable) managedSuppliers.randomException());
			value = collection;
		} else if (ManagedType.EXCEPTION.isSameType(typeName)) {
			final Set<Exception> collection = new HashSet<>();
			Collections.addAll(collection, managedSuppliers.randomException());
			value = collection;
		} else {
			logger.warn("Type={} CANNOT BE ASSIGNED", typeName);
		}
		return value;
	}

}
