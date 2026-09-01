package org.gjs.java.common.jpa;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertSame;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.HashMap;
import java.util.Map;

import org.gjs.java.common.type.DataObject;
import org.gjs.java.test.BaseUnitTest;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.data.repository.CrudRepository;

class BaseRepositoryWrapperTest extends BaseUnitTest<BaseRepositoryWrapper> {

	private static final Logger loggerDePrueba = LoggerFactory.getLogger(BaseRepositoryWrapperTest.class);

	/** Clave primaria compuesta, para el caso de id complejo. */
	public static class ClaveCompuesta {

		private Long uno;
		private String dos;

		public Long getUno() {
			return uno;
		}

		public String getDos() {
			return dos;
		}
	}

	/** Entidad de usar y tirar. */
	public static class Entidad {

		private Long id;

		public Long getId() {
			return id;
		}
	}

	/** Concreta minima: el wrapper deja abstractos el repositorio y las dependencias. */
	private static class WrapperDePrueba<ID> extends BaseRepositoryWrapper<Entidad, ID> {

		WrapperDePrueba(Class<ID> pk) {
			super(Entidad.class, pk, loggerDePrueba);
		}

		WrapperDePrueba(Class<ID> pk, String dataFile) {
			super(Entidad.class, pk, dataFile, loggerDePrueba);
		}

		@Override
		public CrudRepository<Entidad, ID> getRepository() {
			return null;
		}

		@Override
		protected void loadDependencies() {
			// sin dependencias que cargar
		}

		@Override
		protected boolean isFieldToTranslate(String field) {
			return false;
		}

		@Override
		protected void resolveDependecies(DataObject dataObj, Entidad obj) {
			// sin dependencias que resolver
		}
	}

	@Test
	void testConstructor() {
		final WrapperDePrueba<Long> wrapper = new WrapperDePrueba<>(Long.class);

		assertSame(Entidad.class, wrapper.getEntity());
		assertSame(Long.class, wrapper.getPk());
		assertSame(loggerDePrueba, wrapper.getLogger());
		assertFalse(wrapper.isLoaded());
		assertNull(wrapper.getDataFile());
	}

	@Test
	void testConstructorConFichero() {
		final WrapperDePrueba<Long> wrapper = new WrapperDePrueba<>(Long.class, "data/entidades.csv");

		assertEquals("data/entidades.csv", wrapper.getDataFile());
		assertFalse(wrapper.isLoaded());
	}

	/*
	 * complexId es lo unico que el constructor deduce: sale false para las claves que
	 * son tipo primitivo o gestionado, y true para cualquier otra.
	 */
	@Test
	void testClaveSimpleNoEsCompleja() {
		assertFalse(new WrapperDePrueba<>(Long.class).isComplexId());
		assertFalse(new WrapperDePrueba<>(String.class).isComplexId());
	}

	@Test
	void testClaveCompuestaSiEsCompleja() {
		assertTrue(new WrapperDePrueba<>(ClaveCompuesta.class).isComplexId());
	}

	@Test
	void testSetters() {
		final WrapperDePrueba<Long> wrapper = new WrapperDePrueba<>(Long.class);
		final Map<String, String> correspondencias = new HashMap<>();
		correspondencias.put("id_entidad", "id");

		wrapper.setDataFile("data/otro.csv");
		wrapper.setFieldCorrespondencies(correspondencias);

		assertEquals("data/otro.csv", wrapper.getDataFile());
		assertEquals(correspondencias, wrapper.getFieldCorrespondencies());
	}

}
