package org.gjs.java.common.dto;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.math.BigInteger;

import org.gjs.java.common.constant.CommonConstants;
import org.gjs.java.common.dto.DBSequenceDto;
import org.gjs.java.test.BaseUnitTest;
import org.gjs.java.test.util.AssertionUtils;
import org.junit.jupiter.api.Test;

public class DBSequenceDtoTest extends BaseUnitTest<DBSequenceDto> {

	@Test
	void testDBSequenceDto1() {
		DBSequenceDto dto = new DBSequenceDto();
		logger.info(dto.toString());
		AssertionUtils.assertEqualsInt(BigInteger.ZERO, dto.getLastNumber());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMinValue());
		assertEquals(CommonConstants.SEQUENCE_MAX_VALUE, dto.getMaxValue());
		assertEquals(0, dto.getPercentage());
		assertEquals(100, dto.getFreePercentage());

		dto = new DBSequenceDto("SEQ_TEST", CommonConstants.SEQUENCE_MAX_VALUE);
		logger.info(dto.toString());
		assertEquals(CommonConstants.SEQUENCE_MAX_VALUE, dto.getLastNumber());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMinValue());
		assertEquals(CommonConstants.SEQUENCE_MAX_VALUE, dto.getMaxValue());
		assertEquals(100, dto.getPercentage());
		assertEquals(0, dto.getFreePercentage());

		dto = new DBSequenceDto("SEQ_TEST", new BigInteger("29999999999999999999999"));
		logger.info(dto.toString());
		AssertionUtils.assertEqualsInt(new BigInteger("29999999999999999999999"), dto.getLastNumber());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMinValue());
		assertEquals(CommonConstants.SEQUENCE_MAX_VALUE, dto.getMaxValue());
		assertEquals(30, dto.getPercentage());
		assertEquals(70, dto.getFreePercentage());
	}

	@Test
	void testDBSequenceDto2() {
		final DBSequenceDto dto = new DBSequenceDto("SEQ_TEST", BigInteger.ONE, BigInteger.ONE, BigInteger.ZERO);
		logger.info(dto.toString());
		AssertionUtils.assertEqualsInt(BigInteger.ZERO, dto.getLastNumber());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMinValue());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMaxValue());
		assertEquals(0, dto.getPercentage());
		assertEquals(100, dto.getFreePercentage());
		logger.info(dto.toString());

		dto.setMinValue(BigInteger.ZERO);
		dto.setLastNumber(BigInteger.ZERO);
		AssertionUtils.assertEqualsInt(BigInteger.ZERO, dto.getLastNumber());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMinValue());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMaxValue());
		assertEquals(0, dto.getPercentage());
		assertEquals(100, dto.getFreePercentage());
		logger.info(dto.toString());

		dto.setLastNumber(BigInteger.ONE);
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getLastNumber());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMinValue());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMaxValue());
		assertEquals(100, dto.getPercentage());
		assertEquals(0, dto.getFreePercentage());
		logger.info(dto.toString());

		dto.setLastNumber(new BigInteger("10"));
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getLastNumber());
		dto.setLastNumber(new BigInteger("-10"));
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getLastNumber());

		dto.setMaxValue(BigInteger.ONE);
		logger.info(dto.toString());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getLastNumber());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMinValue());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMaxValue());
		assertEquals(100, dto.getPercentage());
		assertEquals(0, dto.getFreePercentage());
		dto.setLastNumber(BigInteger.ZERO);
		logger.info(dto.toString());
		AssertionUtils.assertEqualsInt(BigInteger.ZERO, dto.getLastNumber());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMinValue());
		AssertionUtils.assertEqualsInt(BigInteger.ONE, dto.getMaxValue());
		assertEquals(0, dto.getPercentage());
		assertEquals(100, dto.getFreePercentage());

		dto.setMinValue(new BigInteger("10"));
		logger.info(dto.toString());
		assertEquals(new BigInteger("9"), dto.getLastNumber());
		assertEquals(new BigInteger("10"), dto.getMinValue());
		assertEquals(new BigInteger("10"), dto.getMaxValue());
		assertEquals(0, dto.getPercentage());
		assertEquals(100, dto.getFreePercentage());
		dto.setLastNumber(new BigInteger("10"));
		logger.info(dto.toString());
		assertEquals(new BigInteger("10"), dto.getLastNumber());
		assertEquals(new BigInteger("10"), dto.getMinValue());
		assertEquals(new BigInteger("10"), dto.getMaxValue());
		assertEquals(100, dto.getPercentage());
		assertEquals(0, dto.getFreePercentage());

		dto.setMaxValue(new BigInteger("110"));
		logger.info(dto.toString());
		assertEquals(new BigInteger("10"), dto.getLastNumber());
		assertEquals(new BigInteger("10"), dto.getMinValue());
		assertEquals(new BigInteger("110"), dto.getMaxValue());
		assertEquals(1, dto.getPercentage());
		assertEquals(99, dto.getFreePercentage());
	}

	@Test
	void testDBSequenceDto3() {
		final DBSequenceDto dto1 = new DBSequenceDto("SEQ_TEST1", BigInteger.ONE, BigInteger.ONE, BigInteger.ZERO);
		final DBSequenceDto dto2 = new DBSequenceDto("SEQ_TEST2", BigInteger.ONE, BigInteger.ONE, BigInteger.ZERO);
		final DBSequenceDto dto3 = new DBSequenceDto("SEQ_TEST1", BigInteger.ONE, BigInteger.ONE, BigInteger.ZERO);
		assertFalse(dto1.equals(null));
		assertTrue(dto1.equals(dto1));
		assertFalse(dto1.equals(dto2));
		assertFalse(dto1.equals(null));
		assertTrue(dto1.equals(dto3));
		assertTrue(dto1.hashCode() > 0);
	}

}
