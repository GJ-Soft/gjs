package org.gjs.java.common.util;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.fail;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.supplier.GjsSupplier;
import org.gjs.java.test.BaseClassTest;
import org.gjs.java.test.samples.dto.SampleEntityDto;
import org.gjs.java.test.samples.testinggame.DtoTestingGame;
import org.gjs.java.test.supplier.testinggame.TestingGamesSingleton;
import org.gjs.java.test.util.AssertionUtils;
import org.junit.jupiter.api.Test;

class JsonUtilsTest extends BaseClassTest<JsonUtils> {

	private static String JSON_EXAMPLE1 = "{\"id\":989,\"activo\":false,\"descripcion\":\"GQDzByDLcBFFJzdeFUOYaOBQSk9qThZ9qL0R2dZH\",\"nombre\":\"UYKKqd4bsLp6Ez3E54rv8aAYeNNNmPl\"}";

	@Test
	void testJsonToObject() {
		try {
			String json = null;
			SampleEntityDto dto = (SampleEntityDto) JsonUtils.jsonToObject(json, SampleEntityDto.class);
			assertNull(dto);
			json = "";
			dto = (SampleEntityDto) JsonUtils.jsonToObject(json, SampleEntityDto.class);
			assertNull(dto);
			json = "{}";
			dto = (SampleEntityDto) JsonUtils.jsonToObject(json, SampleEntityDto.class);
			assertNotNull(dto);
			logger.debug(ConversionUtils.toString(dto));
			json = JSON_EXAMPLE1;
			dto = (SampleEntityDto) JsonUtils.jsonToObject(json, SampleEntityDto.class);
			assertNotNull(dto);
			logger.debug(ConversionUtils.toString(dto));

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Recibida excepcion");
		}
	}

	@Test
	void testObjectToJson() {
		try {
			SampleEntityDto dto = null;
			String json = JsonUtils.objectToJson(dto);
			assertNull(json);
			dto = ((DtoTestingGame) TestingGamesSingleton.getInstance().getTestingGame("dtos")).getSampleEntityDto();
			json = JsonUtils.objectToJson(dto);
			assertNotNull(json);
			logger.debug(json);
			final SampleEntityDto copiaDto = (SampleEntityDto) JsonUtils.jsonToObject(json, SampleEntityDto.class);
			AssertionUtils.assertEqualsAsWarning(dto, copiaDto, "La copia no es igual", logger);

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Recibida excepcion");
		}
	}

	@Test
	void testSafeObjectToJson() {
		try {
			SampleEntityDto dto = null;
			String json = JsonUtils.safeObjectToJson(dto);
			assertNull(json);
			dto = ((DtoTestingGame) TestingGamesSingleton.getInstance().getTestingGame("dtos")).getSampleEntityDto();
			json = JsonUtils.safeObjectToJson(dto);
			assertNotNull(json);
			logger.debug(json);
			final SampleEntityDto copiaDto = (SampleEntityDto) JsonUtils.jsonToObject(json, SampleEntityDto.class);
			AssertionUtils.assertEqualsAsWarning(dto, copiaDto, "La copia no es igual", logger);

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Recibida excepcion");
		}
	}

	@Test
	void testSafeJsonToObject() {
		try {
			String json = null;
			SampleEntityDto dto = (SampleEntityDto) JsonUtils.safeJsonToObject(json, SampleEntityDto.class);
			assertNull(dto);
			json = "";
			dto = (SampleEntityDto) JsonUtils.safeJsonToObject(json, SampleEntityDto.class);
			assertNull(dto);
			json = "{}";
			dto = (SampleEntityDto) JsonUtils.safeJsonToObject(json, SampleEntityDto.class);
			assertNotNull(dto);
			logger.debug(ConversionUtils.toString(dto));
			json = JSON_EXAMPLE1;
			dto = (SampleEntityDto) JsonUtils.safeJsonToObject(json, SampleEntityDto.class);
			assertNotNull(dto);
			logger.debug(ConversionUtils.toString(dto));

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Recibida excepcion");
		}
	}

	@Test
	void testObjectToAndFromJson1() {
		try {
			for (final Class<?> clazz : TestingGamesSingleton.getInstance().getTestingGame("dtos")
					.getManagedClasses()) {
				logger.info("Test Serializacion JSON de clase : {}", clazz.getCanonicalName());
				final GjsSupplier<?> supplier = TestingGamesSingleton.getInstance().getTestingGame("dtos")
						.findSupplier(clazz.getCanonicalName());
				final Object dto = supplier.getNullius();
				assertNotNull(dto, "El objeto de test se ha generado nulo");
				logger.info("Creado objeto: {}", dto);
				final String json = JsonUtils.objectToJson(dto);
				assertNotNull(json, "El Json se ha generado nulo");
				logger.info("JSON={}", json);
				final Object copiaDto = JsonUtils.jsonToObject(json, clazz);
				assertNotNull(copiaDto, "La copia ha resultado nula");
				AssertionUtils.assertEqualsAsWarning(dto, copiaDto, "La copia no es identica", logger);
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Recibida excepcion");
		}
	}

	@Test
	void testObjectToAndFromJson2() {
		try {
			for (final Class<?> clazz : TestingGamesSingleton.getInstance().getTestingGame("dtos")
					.getManagedClasses()) {
				logger.info("Test Serializacion JSON de clase : {}", clazz.getCanonicalName());
				final GjsSupplier<?> supplier = TestingGamesSingleton.getInstance().getTestingGame("dtos")
						.findSupplier(clazz.getCanonicalName());
				final Object dto = supplier.get();
				assertNotNull(dto, "El objeto de test se ha generado nulo");
				logger.info("Creado objeto: {}", dto);
				final String json = JsonUtils.objectToJson(dto);
				assertNotNull(json, "El Json se ha generado nulo");
				logger.info("JSON={}", json);
				final Object copiaDto = JsonUtils.jsonToObject(json, clazz);
				assertNotNull(copiaDto, "La copia ha resultado nula");
				AssertionUtils.assertEqualsAsWarning(dto, copiaDto, "La copia no es identica", logger);
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Recibida excepcion");
		}
	}

	/*
	 * Regresión: con Jackson 3 el error de lectura es una JacksonException, que no es
	 * IOException; safeJsonToObject sólo capturaba IOException y la dejaba escapar.
	 */
	@Test
	void testSafeJsonToObjectMalformed() {
		assertNull(JsonUtils.safeJsonToObject("{ no es json", SampleEntityDto.class));
	}

}
