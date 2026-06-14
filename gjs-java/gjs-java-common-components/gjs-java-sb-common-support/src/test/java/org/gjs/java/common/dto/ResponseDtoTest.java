package org.gjs.java.common.dto;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.util.Date;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.contant.CommonErrors;
import org.gjs.java.common.dto.ErrorDto;
import org.gjs.java.common.dto.ResponseDto;
import org.gjs.java.common.util.JsonUtils;
import org.gjs.java.test.BaseUnitTest;
import org.gjs.java.test.util.AssertionUtils;
import org.junit.jupiter.api.Test;
import org.springframework.http.HttpStatus;

import tools.jackson.core.JacksonException;

public class ResponseDtoTest extends BaseUnitTest<ResponseDto> {

	@Test
	void testResponseDto1() {
		final ResponseDto responseDto = new ResponseDto();
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(200, responseDto.getStatus());
		assertEquals("OK", responseDto.getMessage());
		assertFalse(responseDto.hasErrors());
		assertFalse(responseDto.hasWarnings());
		try {
			final String json = JsonUtils.objectToJson(responseDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches(
					"\\{\"status\":200,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"OK\"\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testResponseDto2() {
		final HttpStatus status = HttpStatus.CONFLICT;
		final ResponseDto responseDto = new ResponseDto(status);
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(status.value(), responseDto.getStatus());
		assertEquals(status.getReasonPhrase(), responseDto.getMessage());
		assertFalse(responseDto.hasErrors());
		assertFalse(responseDto.hasWarnings());
		try {
			final String json = JsonUtils.objectToJson(responseDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches(
					"\\{\"status\":409,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"Conflict\"\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testResponseDto3() {
		final HttpStatus status = HttpStatus.FORBIDDEN;
		final Date now = new Date();
		final ResponseDto responseDto = new ResponseDto(status, now);
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(status.value(), responseDto.getStatus());
		assertEquals(now, responseDto.getTimestamp());
		assertEquals(status.getReasonPhrase(), responseDto.getMessage());
		assertFalse(responseDto.hasErrors());
		assertFalse(responseDto.hasWarnings());
		try {
			final String json = JsonUtils.objectToJson(responseDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches(
					"\\{\"status\":403,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"Forbidden\"\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testResponseDto4() {
		final HttpStatus status = HttpStatus.NOT_FOUND;
		final Date now = new Date();
		final String message = "Entity object not found";
		final ResponseDto responseDto = new ResponseDto(status, now, message);
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(status.value(), responseDto.getStatus());
		assertEquals(now, responseDto.getTimestamp());
		assertEquals(message, responseDto.getMessage());
		assertFalse(responseDto.hasErrors());
		assertFalse(responseDto.hasWarnings());
		try {
			final String json = JsonUtils.objectToJson(responseDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches(
					"\\{\"status\":404,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"Entity object not found\"\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testResponseDto5() {
		final HttpStatus status = HttpStatus.NOT_FOUND;
		final Date now = new Date();
		final String message = "Entity object not found";
		final ResponseDto responseDto = new ResponseDto(status, now, message);
		final String errCode1 = CommonErrors.ERROR_SEMI0000;
		final String errMessage1 = "The organization object not exists";
		responseDto.addError(new ErrorDto(errCode1, errMessage1));
		assertNull(responseDto.getWarnings());
		assertNotNull(responseDto.getErrors());
		assertEquals(1, responseDto.getErrors().size());
		assertNotNull(responseDto.getErrors().get(0));
		assertEquals(errCode1.toString(), responseDto.getErrors().get(0).getCode());
		assertEquals(errMessage1, responseDto.getErrors().get(0).getMessage());
		assertTrue(responseDto.hasErrors());
		assertFalse(responseDto.hasWarnings());
		try {
			final String json = JsonUtils.objectToJson(responseDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches(
					"\\{\"status\":404,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"Entity object not found\",\"errors\":\\[\\{\"code\":\"semi-0000\",\"message\":\"The organization object not exists\"\\}\\]\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
		final String errCode2 = CommonErrors.ERROR_AUTH0000;
		final String errMessage2 = "Additional error";
		responseDto.addError(errCode2, errMessage2);
		assertNotNull(responseDto.getErrors());
		assertEquals(2, responseDto.getErrors().size());
		assertNotNull(responseDto.getErrors().get(0));
		assertEquals(errCode1.toString(), responseDto.getErrors().get(0).getCode());
		assertEquals(errMessage1, responseDto.getErrors().get(0).getMessage());
		assertNotNull(responseDto.getErrors().get(1));
		assertEquals(errCode2.toString(), responseDto.getErrors().get(1).getCode());
		assertEquals(errMessage2, responseDto.getErrors().get(1).getMessage());
		assertTrue(responseDto.hasErrors());
		assertFalse(responseDto.hasWarnings());
	}

	@Test
	void testResponseDto6() {
		final ResponseDto responseDto = new ResponseDto();
		final String errCode1 = CommonErrors.ERROR_SEMI0000;
		final String errMessage1 = "The organization object not exists";
		responseDto.addWarning(new ErrorDto(errCode1, errMessage1));
		assertNull(responseDto.getErrors());
		assertNotNull(responseDto.getWarnings());
		assertEquals(1, responseDto.getWarnings().size());
		assertNotNull(responseDto.getWarnings().get(0));
		assertEquals(errCode1.toString(), responseDto.getWarnings().get(0).getCode());
		assertEquals(errMessage1, responseDto.getWarnings().get(0).getMessage());
		assertFalse(responseDto.hasErrors());
		assertTrue(responseDto.hasWarnings());
		try {
			final String json = JsonUtils.objectToJson(responseDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches(
					"\\{\"status\":200,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"OK\",\"warnings\":\\[\\{\"code\":\"semi-0000\",\"message\":\"The organization object not exists\"\\}\\]\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
		final String errCode2 = CommonErrors.ERROR_AUTH0000;
		final String errMessage2 = "Additional error";
		responseDto.addWarning(errCode2, errMessage2);
		assertNotNull(responseDto.getWarnings());
		assertEquals(2, responseDto.getWarnings().size());
		assertNotNull(responseDto.getWarnings().get(0));
		assertEquals(errCode1.toString(), responseDto.getWarnings().get(0).getCode());
		assertEquals(errMessage1, responseDto.getWarnings().get(0).getMessage());
		assertNotNull(responseDto.getWarnings().get(1));
		assertEquals(errCode2.toString(), responseDto.getWarnings().get(1).getCode());
		assertEquals(errMessage2, responseDto.getWarnings().get(1).getMessage());
		assertFalse(responseDto.hasErrors());
		assertTrue(responseDto.hasWarnings());
	}

	@Test
	void testResponseDto7() {
		final HttpStatus status = HttpStatus.CONFLICT;
		final String message = "Conflict of interest";
		final ResponseDto responseDto = new ResponseDto(status, message);
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(status.value(), responseDto.getStatus());
		assertEquals(message, responseDto.getMessage());
		try {
			final String json = JsonUtils.objectToJson(responseDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches(
					"\\{\"status\":409,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"Conflict of interest\"\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testResponseDto8() {
		try {
			final ResponseDto responseDto = new ResponseDto(null);
			assertNotNull(responseDto.getStatus());
			assertNotNull(responseDto.getTimestamp());
			assertNotNull(responseDto.getMessage());
			assertEquals(500, responseDto.getStatus());
			assertEquals("Internal Server Error", responseDto.getMessage());
			assertNotNull(responseDto.getErrors());
			assertEquals(1, responseDto.getErrors().size());
			assertNotNull(responseDto.getErrors().get(0));
			assertEquals(CommonErrors.ERROR_TECH0001, responseDto.getErrors().get(0).getCode());
			assertNotNull(responseDto.getErrors().get(0).getMessage());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testResponseDto9() {
		try {
			final ResponseDto responseDto = new ResponseDto(null, (Date) null);
			assertNotNull(responseDto.getStatus());
			assertNotNull(responseDto.getTimestamp());
			assertNotNull(responseDto.getMessage());
			assertEquals(500, responseDto.getStatus());
			assertEquals("Internal Server Error", responseDto.getMessage());
			assertNotNull(responseDto.getErrors());
			assertEquals(1, responseDto.getErrors().size());
			assertNotNull(responseDto.getErrors().get(0));
			assertEquals(CommonErrors.ERROR_TECH0001, responseDto.getErrors().get(0).getCode());
			assertNotNull(responseDto.getErrors().get(0).getMessage());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testResponseDto10() {
		try {
			final ResponseDto responseDto = new ResponseDto(null, null, null);
			assertNotNull(responseDto.getStatus());
			assertNotNull(responseDto.getTimestamp());
			assertNotNull(responseDto.getMessage());
			assertEquals(500, responseDto.getStatus());
			assertEquals("Internal Server Error", responseDto.getMessage());
			assertNotNull(responseDto.getErrors());
			assertEquals(1, responseDto.getErrors().size());
			assertNotNull(responseDto.getErrors().get(0));
			assertEquals(CommonErrors.ERROR_TECH0001, responseDto.getErrors().get(0).getCode());
			assertNotNull(responseDto.getErrors().get(0).getMessage());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

}
