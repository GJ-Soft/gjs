package org.gjs.java.common.dto;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.MathContext;
import java.math.RoundingMode;
import java.util.Objects;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;
import org.gjs.java.common.constant.CommonConstants;
import org.gjs.java.common.util.ComparationUtils;
import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class SecuenciaDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO para almacenar el estado de un secuencia de la base de datos.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class DBSequenceDto extends BaseDto implements Comparable<DBSequenceDto> {

	/** The Constant serialVersionUID. */
	private static final long serialVersionUID = -4193935608447257776L;

	/** The sequence name. */
	private String sequenceName;

	/** The min value. */
	private BigInteger minValue;

	/** The min value. */
	private BigInteger maxValue;

	/** The last number. */
	private BigInteger lastNumber;

	/**
	 * Instantiates a new info secuencia dto.
	 */
	public DBSequenceDto() {
		this(null);
	}

	/**
	 * Instantiates a new secuencia dto.
	 *
	 * @param nombre the nombre
	 */
	public DBSequenceDto(String nombre) {
		this(nombre, BigInteger.ZERO);
	}

	/**
	 * Instantiates a new info secuencia dto.
	 *
	 * @param nombre the nombre
	 * @param ultimo the ultimo
	 */
	public DBSequenceDto(String nombre, BigInteger ultimo) {
		this(nombre, BigInteger.ONE, CommonConstants.SEQUENCE_MAX_VALUE, ultimo);
	}

	/**
	 * Instantiates a new secuencia dto.
	 *
	 * @param nombre the nombre
	 * @param min    the min
	 * @param max    the max
	 * @param ultimo the ultimo
	 */
	public DBSequenceDto(String nombre, BigInteger min, BigInteger max, BigInteger ultimo) {
		setSequenceName(nombre);
		setMinValue(min);
		setMaxValue(max);
		setLastNumber(ultimo);
	}

	/**
	 * Gets the sequence name.
	 *
	 * @return the sequence name
	 */
	public String getSequenceName() {
		return sequenceName;
	}

	/**
	 * Sets the sequence name.
	 *
	 * @param sequenceName the new sequence name
	 */
	public void setSequenceName(String sequenceName) {
		this.sequenceName = sequenceName;
	}

	/**
	 * Gets the min value.
	 *
	 * @return the min value
	 */
	public BigInteger getMinValue() {
		return (Objects.nonNull(minValue) ? minValue : BigInteger.ONE);
	}

	/**
	 * Sets the min value.
	 *
	 * @param minValue the new min value
	 */
	public void setMinValue(BigInteger minValue) {
		if (ComparationUtils.compareTo(minValue, BigInteger.ZERO) > 0) {
			this.minValue = minValue;
			this.lastNumber = getMinValue().subtract(BigInteger.ONE).max(getLastNumber());
			this.maxValue = getMinValue().max(getMaxValue());
		}
	}

	/**
	 * Gets the max value.
	 *
	 * @return the max value
	 */
	public BigInteger getMaxValue() {
		return (Objects.nonNull(maxValue) ? maxValue : BigInteger.ONE);
	}

	/**
	 * Sets the max value.
	 *
	 * @param maxValue the new max value
	 */
	public void setMaxValue(BigInteger maxValue) {
		if (ComparationUtils.compareTo(maxValue, minValue) >= 0) {
			this.maxValue = maxValue;
			this.lastNumber = getMaxValue().min(getLastNumber());
		}
	}

	/**
	 * Gets the last number.
	 *
	 * @return the last number
	 */
	public BigInteger getLastNumber() {
		return (Objects.nonNull(lastNumber) ? lastNumber : BigInteger.ZERO);
	}

	/**
	 * Sets the last number.
	 *
	 * @param lastNumber the new last number
	 */
	public void setLastNumber(BigInteger lastNumber) {
		if (ConditionUtils.allAreTrue(
				(ComparationUtils.compareTo(lastNumber, getMinValue().subtract(BigInteger.ONE)) >= 0),
				ComparationUtils.compareTo(lastNumber, getMaxValue()) <= 0)) {
			this.lastNumber = lastNumber;
		}
	}

	/**
	 * Gets the porcentaje.
	 *
	 * @return the porcentaje
	 */
	public int getPercentage() {
		int res = 0;
		if (ComparationUtils.compareTo(lastNumber, minValue) >= 0) {
			final BigDecimal numerator = new BigDecimal(lastNumber.subtract(minValue).add(BigInteger.ONE));
			final BigDecimal denominator = new BigDecimal(maxValue.subtract(minValue).add(BigInteger.ONE));
			final BigDecimal porc = numerator.multiply(new BigDecimal(100)).divide(denominator, 23,
					RoundingMode.HALF_UP);
			final BigDecimal rounded = porc.round(new MathContext(2, RoundingMode.HALF_UP));
			final double value = rounded.doubleValue();
			res = (int) Math.round(value);
		}
		return res;
	}

	/**
	 * Gets the porcentaje libre.
	 *
	 * @return the porcentaje libre
	 */
	public int getFreePercentage() {
		return 100 - getPercentage();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("Name", sequenceName)
				.append("MinValue", minValue).append("MaxValue", maxValue).append("LastNumber", lastNumber)
				.append("Occupied range", getPercentage()).toString();
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Comparable#compareTo(java.lang.Object)
	 */

	@Override
	public int compareTo(DBSequenceDto o) {
		int res = -1;
		if (Objects.nonNull(o)) {
			res = ComparationUtils.compareTo(sequenceName, o.getSequenceName());
		}
		return res;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#hashCode()
	 */

	@Override
	public int hashCode() {
		return Objects.hash(sequenceName);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#equals(java.lang.Object)
	 */

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (!(obj instanceof DBSequenceDto)) {
			return false;
		}
		final DBSequenceDto other = (DBSequenceDto) obj;
		return Objects.equals(sequenceName, other.sequenceName);
	}

}
