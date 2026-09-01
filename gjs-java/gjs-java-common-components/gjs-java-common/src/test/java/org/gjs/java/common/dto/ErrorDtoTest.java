package org.gjs.java.common.dto;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.fail;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.constant.CommonErrors;
import org.gjs.java.common.dto.ErrorDto;
import org.gjs.java.common.util.JsonUtils;
import org.gjs.java.test.BaseUnitTest;
import org.gjs.java.test.util.AssertionUtils;
import org.junit.jupiter.api.Test;

import tools.jackson.core.JacksonException;

public class ErrorDtoTest extends BaseUnitTest<ErrorDto> {

	@Test
	void testErrorDto1() {
		ErrorDto errorDto = new ErrorDto();
		assertNull(errorDto.getCode());
		assertNull(errorDto.getMessage());
		final String code = CommonErrors.ERROR_SEMI0000;
		final String message = "message1";
		errorDto = new ErrorDto(code, message);
		assertNotNull(errorDto.getCode());
		assertNotNull(errorDto.getMessage());
		assertEquals(code.toString(), errorDto.getCode());
		assertEquals(message, errorDto.getMessage());
		try {
			final String json = JsonUtils.objectToJson(errorDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches("\\{\"code\":\"semi-0000\",\"message\":\"message1\"\\}", json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testErrorDto2() {
		ErrorDto errorDto = new ErrorDto();
		assertNull(errorDto.getCode());
		assertNull(errorDto.getMessage());
		final String code = CommonErrors.ERROR_AUTH0000;
		final String message = "El usuario no tiene autorización";
		errorDto = new ErrorDto(code);
		assertNotNull(errorDto.getCode());
		assertNotNull(errorDto.getMessage());
		assertEquals(code.toString(), errorDto.getCode());
		assertEquals(message, errorDto.getMessage());
	}

	@Test
	void testErrorDto3() {
		ErrorDto errorDto = new ErrorDto();
		assertNull(errorDto.getCode());
		assertNull(errorDto.getMessage());
		final String code = "semi-1111";
		final String message = "<Mensaje para semi-1111 no encontrado>";
		errorDto = new ErrorDto(code);
		assertNotNull(errorDto.getCode());
		assertNotNull(errorDto.getMessage());
		assertEquals(code.toString(), errorDto.getCode());
		assertEquals(message, errorDto.getMessage());
	}

	@Test
	void testErrorDto4() {
		ErrorDto errorDto = new ErrorDto();
		assertNull(errorDto.getCode());
		assertNull(errorDto.getMessage());
		final String code = CommonErrors.ERROR_AUTH0000;
		final String message = "El usuario no tiene autorización";
		errorDto = new ErrorDto(code.toString());
		assertNotNull(errorDto.getCode());
		assertNotNull(errorDto.getMessage());
		assertEquals(code.toString(), errorDto.getCode());
		assertEquals(message, errorDto.getMessage());
	}

	@Test
	void testErrorDto5() {
		ErrorDto errorDto = new ErrorDto();
		assertNull(errorDto.getCode());
		assertNull(errorDto.getMessage());
		final String code = CommonErrors.ERROR_VALI0001;
		final String param = "id";
		final String message = String.format("El campo %s no puede ser nulo", param);
		errorDto = new ErrorDto(code, (Object) param);
		assertNotNull(errorDto.getCode());
		assertNotNull(errorDto.getMessage());
		assertEquals(code.toString(), errorDto.getCode());
		assertEquals(message, errorDto.getMessage());
	}

}
