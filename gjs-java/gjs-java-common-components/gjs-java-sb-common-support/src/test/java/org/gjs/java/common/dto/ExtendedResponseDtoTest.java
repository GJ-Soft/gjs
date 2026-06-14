package org.gjs.java.common.dto;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.fail;

import java.util.Date;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.contant.CommonErrors;
import org.gjs.java.common.util.JsonUtils;
import org.gjs.java.test.BaseUnitTest;
import org.gjs.java.test.util.AssertionUtils;
import org.junit.jupiter.api.Test;
import org.springframework.http.HttpStatus;

import lombok.Getter;
import lombok.Setter;
import tools.jackson.core.JacksonException;

@SuppressWarnings("rawtypes")
public class ExtendedResponseDtoTest extends BaseUnitTest<ExtendedResponseDto> {

	@Getter
	@Setter
	@SuppressWarnings("serial")
	static class WsEstadoDto extends EntityDto<Long> {
		private String descripcion;
		private String valor;
		private Long codigo;
	}

	static class TestResponseDto extends ExtendedResponseDto<WsEstadoDto> {
		public TestResponseDto() {
		}

		public TestResponseDto(HttpStatus status) {
			super(status);
		}

		public TestResponseDto(HttpStatus status, Date timestamp) {
			super(status, timestamp);
		}

		public TestResponseDto(HttpStatus status, String message) {
			super(status, message);
		}

		public TestResponseDto(HttpStatus status, Date timestamp, String message) {
			super(status, timestamp, message);
		}

		public TestResponseDto(WsEstadoDto content) {
			super(content);
		}

		public TestResponseDto(WsEstadoDto content, HttpStatus status) {
			super(content, status);
		}

		public TestResponseDto(WsEstadoDto content, HttpStatus status, Date timestamp) {
			super(content, status, timestamp);
		}

		public TestResponseDto(WsEstadoDto content, HttpStatus status, String message) {
			super(content, status, message);
		}

		public TestResponseDto(WsEstadoDto content, HttpStatus status, Date timestamp, String message) {
			super(content, status, timestamp, message);
		}

	}

	@Test
	void testExtendedResponseDto1() {
		final TestResponseDto responseDto = new TestResponseDto();
		assertNull(responseDto.getContent());
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(200, responseDto.getStatus());
		assertEquals("OK", responseDto.getMessage());
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
	void testExtendedResponseDto2() {
		final HttpStatus status = HttpStatus.CONFLICT;
		final TestResponseDto responseDto = new TestResponseDto(status);
		assertNull(responseDto.getContent());
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(status.value(), responseDto.getStatus());
		assertEquals(status.getReasonPhrase(), responseDto.getMessage());
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
	void testExtendedResponseDto3() {
		final HttpStatus status = HttpStatus.FORBIDDEN;
		final Date now = new Date();
		final TestResponseDto responseDto = new TestResponseDto(status, now);
		assertNull(responseDto.getContent());
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(status.value(), responseDto.getStatus());
		assertEquals(now, responseDto.getTimestamp());
		assertEquals(status.getReasonPhrase(), responseDto.getMessage());
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
	void testExtendedResponseDto4() {
		final HttpStatus status = HttpStatus.NOT_FOUND;
		final Date now = new Date();
		final String message = "Entity object not found";
		final TestResponseDto responseDto = new TestResponseDto(status, now, message);
		assertNull(responseDto.getContent());
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(status.value(), responseDto.getStatus());
		assertEquals(now, responseDto.getTimestamp());
		assertEquals(message, responseDto.getMessage());
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
	void testExtendedResponseDto5() {
		final HttpStatus status = HttpStatus.NOT_FOUND;
		final Date now = new Date();
		final String message = "Entity object not found";
		final TestResponseDto responseDto = new TestResponseDto(status, now, message);
		final String errCode1 = CommonErrors.ERROR_SEMI0000;
		final String errMessage1 = "The organization object not exists";
		responseDto.addError(new ErrorDto(errCode1, errMessage1));
		assertNull(responseDto.getContent());
		assertNull(responseDto.getWarnings());
		assertNotNull(responseDto.getErrors());
		assertEquals(1, responseDto.getErrors().size());
		assertNotNull(responseDto.getErrors().get(0));
		assertEquals(errCode1.toString(), responseDto.getErrors().get(0).getCode());
		assertEquals(errMessage1, responseDto.getErrors().get(0).getMessage());
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
	}

	@Test
	void testExtendedResponseDto6() {
		final TestResponseDto responseDto = new TestResponseDto();
		final String errCode1 = CommonErrors.ERROR_SEMI0000;
		final String errMessage1 = "The organization object not exists";
		responseDto.addWarning(new ErrorDto(errCode1, errMessage1));
		assertNull(responseDto.getContent());
		assertNull(responseDto.getErrors());
		assertNotNull(responseDto.getWarnings());
		assertEquals(1, responseDto.getWarnings().size());
		assertNotNull(responseDto.getWarnings().get(0));
		assertEquals(errCode1.toString(), responseDto.getWarnings().get(0).getCode());
		assertEquals(errMessage1, responseDto.getWarnings().get(0).getMessage());
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
	}

	@Test
	void testExtendedResponseDto7() {
		final HttpStatus status = HttpStatus.CONFLICT;
		final String message = "Conflict of interest";
		final TestResponseDto responseDto = new TestResponseDto(status, message);
		assertNull(responseDto.getContent());
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
	void testExtendedResponseDto8() {
		try {
			final TestResponseDto responseDto = new TestResponseDto((HttpStatus) null);
			assertNull(responseDto.getContent());
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
	void testExtendedResponseDto9() {
		try {
			final TestResponseDto responseDto = new TestResponseDto(null, (Date) null);
			assertNull(responseDto.getContent());
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
	void testExtendedResponseDto10() {
		try {
			final TestResponseDto responseDto = new TestResponseDto((HttpStatus) null, null, null);
			assertNull(responseDto.getContent());
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
	void testExtendedResponseDto11() {
		final WsEstadoDto dto = null;
		final TestResponseDto responseDto = new TestResponseDto(dto);
		assertNull(responseDto.getContent());
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(200, responseDto.getStatus());
		assertEquals("OK", responseDto.getMessage());
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
	void testExtendedResponseDto12() {
		final WsEstadoDto dto = new WsEstadoDto();
		dto.setId(Long.valueOf(1));
		dto.setCodigo(Long.valueOf(10));
		dto.setDescripcion("Descripcion");
		final TestResponseDto responseDto = new TestResponseDto(dto);
		assertNotNull(responseDto.getContent());
		assertEquals(dto.getId(), responseDto.getContent().getId());
		assertEquals(dto.getCodigo(), responseDto.getContent().getCodigo());
		assertEquals(dto.getDescripcion(), responseDto.getContent().getDescripcion());
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(200, responseDto.getStatus());
		assertEquals("OK", responseDto.getMessage());
		try {
			final String json = JsonUtils.objectToJson(responseDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches(
					"\\{\"status\":200,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"OK\",\"content\":\\{\"@class\":\"org.gjs.java.common.dto.ExtendedResponseDtoTest\\$WsEstadoDto\",\"codigo\":10,\"descripcion\":\"Descripcion\",\"id\":1\\}\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testExtendedResponseDto13() {
		final WsEstadoDto dto = new WsEstadoDto();
		dto.setId(Long.valueOf(1));
		dto.setCodigo(Long.valueOf(10));
		dto.setDescripcion("Descripcion");
		final HttpStatus status = HttpStatus.CONFLICT;
		final TestResponseDto responseDto = new TestResponseDto(dto, status);
		assertNotNull(responseDto.getContent());
		assertEquals(dto.getId(), responseDto.getContent().getId());
		assertEquals(dto.getCodigo(), responseDto.getContent().getCodigo());
		assertEquals(dto.getDescripcion(), responseDto.getContent().getDescripcion());
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(status.value(), responseDto.getStatus());
		assertEquals(status.getReasonPhrase(), responseDto.getMessage());
		try {
			final String json = JsonUtils.objectToJson(responseDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches(
					"\\{\"status\":409,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"Conflict\",\"content\":\\{\"@class\":\"org.gjs.java.common.dto.ExtendedResponseDtoTest\\$WsEstadoDto\",\"codigo\":10,\"descripcion\":\"Descripcion\",\"id\":1\\}\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testExtendedResponseDto14() {
		final WsEstadoDto dto = new WsEstadoDto();
		dto.setId(Long.valueOf(1));
		dto.setCodigo(Long.valueOf(10));
		dto.setDescripcion("Descripcion");
		final HttpStatus status = HttpStatus.FORBIDDEN;
		final Date now = new Date();
		final TestResponseDto responseDto = new TestResponseDto(dto, status, now);
		assertNotNull(responseDto.getContent());
		assertEquals(dto.getId(), responseDto.getContent().getId());
		assertEquals(dto.getCodigo(), responseDto.getContent().getCodigo());
		assertEquals(dto.getDescripcion(), responseDto.getContent().getDescripcion());
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(status.value(), responseDto.getStatus());
		assertEquals(now, responseDto.getTimestamp());
		assertEquals(status.getReasonPhrase(), responseDto.getMessage());
		try {
			final String json = JsonUtils.objectToJson(responseDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches(
					"\\{\"status\":403,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"Forbidden\",\"content\":\\{\"@class\":\"org.gjs.java.common.dto.ExtendedResponseDtoTest\\$WsEstadoDto\",\"codigo\":10,\"descripcion\":\"Descripcion\",\"id\":1\\}\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testExtendedResponseDto15() {
		final WsEstadoDto dto = new WsEstadoDto();
		dto.setId(Long.valueOf(1));
		dto.setCodigo(Long.valueOf(10));
		dto.setDescripcion("Descripcion");
		final HttpStatus status = HttpStatus.NOT_FOUND;
		final Date now = new Date();
		final String message = "Entity object not found";
		final TestResponseDto responseDto = new TestResponseDto(dto, status, now, message);
		assertNotNull(responseDto.getContent());
		assertEquals(dto.getId(), responseDto.getContent().getId());
		assertEquals(dto.getCodigo(), responseDto.getContent().getCodigo());
		assertEquals(dto.getDescripcion(), responseDto.getContent().getDescripcion());
		assertNotNull(responseDto.getStatus());
		assertNotNull(responseDto.getTimestamp());
		assertNotNull(responseDto.getMessage());
		assertEquals(status.value(), responseDto.getStatus());
		assertEquals(now, responseDto.getTimestamp());
		assertEquals(message, responseDto.getMessage());
		try {
			final String json = JsonUtils.objectToJson(responseDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches(
					"\\{\"status\":404,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"Entity object not found\",\"content\":\\{\"@class\":\"org.gjs.java.common.dto.ExtendedResponseDtoTest\\$WsEstadoDto\",\"codigo\":10,\"descripcion\":\"Descripcion\",\"id\":1\\}\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testExtendedResponseDto16() {
		final WsEstadoDto dto = new WsEstadoDto();
		dto.setId(Long.valueOf(1));
		dto.setCodigo(Long.valueOf(10));
		dto.setDescripcion("Descripcion");
		final HttpStatus status = HttpStatus.CONFLICT;
		final String message = "Conflict of interest";
		final TestResponseDto responseDto = new TestResponseDto(dto, status, message);
		assertNotNull(responseDto.getContent());
		assertEquals(dto.getId(), responseDto.getContent().getId());
		assertEquals(dto.getCodigo(), responseDto.getContent().getCodigo());
		assertEquals(dto.getDescripcion(), responseDto.getContent().getDescripcion());
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
					"\\{\"status\":409,\"timestamp\":\"\\d+{2}-\\d+{2}-\\d+{4}T\\d+{2}:\\d+{2}:\\d+{2}\",\"message\":\"Conflict of interest\",\"content\":\\{\"@class\":\"org.gjs.java.common.dto.ExtendedResponseDtoTest\\$WsEstadoDto\",\"codigo\":10,\"descripcion\":\"Descripcion\",\"id\":1\\}\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

}
