package org.gjs.java.common.dto;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.fail;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.constant.CommonErrors;
import org.gjs.java.common.dto.ValidationErrorDto;
import org.gjs.java.common.util.JsonUtils;
import org.gjs.java.test.BaseUnitTest;
import org.gjs.java.test.util.AssertionUtils;
import org.junit.jupiter.api.Test;

import tools.jackson.core.JacksonException;

public class ValidationErrorDtoTest extends BaseUnitTest<ValidationErrorDto> {

	@Test
	void testErrorDto1() {
		String code = CommonErrors.ERROR_VALI0001;
		String message = "El campo {0} no puede ser nulo";
		ValidationErrorDto errorDto = new ValidationErrorDto(code);
		assertNotNull(errorDto.getCode());
		assertNotNull(errorDto.getMessage());
		assertEquals(code.toString(), errorDto.getCode());
		assertEquals(message, errorDto.getMessage());

		message = "El campo id no puede ser nulo";
		errorDto = new ValidationErrorDto(code, "id");
		assertNotNull(errorDto.getCode());
		assertNotNull(errorDto.getMessage());
		assertEquals(code.toString(), errorDto.getCode());
		assertEquals(message, errorDto.getMessage());

		code = CommonErrors.ERROR_VALI0001;
		message = "El campo id no puede ser nulo";
		errorDto = new ValidationErrorDto(code, "id");
		assertNotNull(errorDto.getCode());
		assertNotNull(errorDto.getMessage());
		assertEquals(code.toString(), errorDto.getCode());
		assertEquals(message, errorDto.getMessage());

		try {
			final String json = JsonUtils.objectToJson(errorDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches("\\{\"code\":\"vali-0001\",\"message\":\"El campo id no puede ser nulo\"\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

	@Test
	void testErrorDto2() {
		String code = CommonErrors.ERROR_VALI0001;
		String message = "El campo {0} no puede ser nulo";
		ValidationErrorDto errorDto = new ValidationErrorDto(code);
		assertNotNull(errorDto.getCode());
		assertNotNull(errorDto.getMessage());
		assertEquals(code.toString(), errorDto.getCode());
		assertEquals(message, errorDto.getMessage());

		message = "El campo id no puede ser nulo";
		errorDto = new ValidationErrorDto(code, "id");
		assertNotNull(errorDto.getCode());
		assertNotNull(errorDto.getMessage());
		assertEquals(code.toString(), errorDto.getCode());
		assertEquals(message, errorDto.getMessage());

		code = CommonErrors.ERROR_VALI0001;
		message = "El campo id no puede ser nulo";
		errorDto = new ValidationErrorDto(code, "id", "0");
		assertNotNull(errorDto.getCode());
		assertNotNull(errorDto.getMessage());
		assertEquals(code.toString(), errorDto.getCode());
		assertEquals(message, errorDto.getMessage());

		try {
			final String json = JsonUtils.objectToJson(errorDto);
			assertNotNull(json);
			logger.info("JSON={}", json);
			AssertionUtils.assertMatches("\\{\"code\":\"vali-0001\",\"message\":\"El campo id no puede ser nulo\"\\}",
					json);
		} catch (final JacksonException e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion producida");
		}
	}

}
