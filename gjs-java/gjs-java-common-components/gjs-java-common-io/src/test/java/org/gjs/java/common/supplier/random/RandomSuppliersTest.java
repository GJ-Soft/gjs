package org.gjs.java.common.supplier.random;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.util.Arrays;
import java.util.Set;
import java.util.TreeSet;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.test.AbstractClassTest;
import org.junit.jupiter.api.Test;

class RandomSuppliersTest extends AbstractClassTest {

	@Override
	protected Class<?> getClazz() {
		return AbstractRandomSupplier.class;
	}

	@Test
	void testRandomSelectedFromFileSupplier() {
		// final Path filePath = currentDir.resolve("data/nombres.txt");
		// logger.info("{}", filePath.toAbsolutePath().toString().replace("\\",
		// "\\\\"));
		final String[] options = { "Juan", "Hermes", "Antonio", "Raimundo", "Dagoberto" };
		final Set<String> setOptions = new TreeSet<>(Arrays.asList(options));

		try {

			final RandomSelectedFromFileSupplier supplier = new RandomSelectedFromFileSupplier("data/nombres.txt");
			for (int i = 0; i < 20; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				logger.debug("Valor generado={}", value);
				assertTrue(setOptions.contains(value));
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomNameSupplier() {
		try {
			final RandomNameSupplier supplier = new RandomNameSupplier();
			for (int i = 0; i < 100; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				logger.debug("Valor generado={}", value);
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomFemaleNameSupplier() {
		try {
			final RandomFemaleNameSupplier supplier = new RandomFemaleNameSupplier();
			final Set<String> obtenidos = tirar(supplier, 50);

			assertFalse(obtenidos.isEmpty());
			assertTrue(obtenidos.size() > 1, "Siempre devolvio el mismo nombre");
			assertNull(supplier.getEmpty());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	@Test
	void testRandomMaleNameSupplier() {
		try {
			final RandomMaleNameSupplier supplier = new RandomMaleNameSupplier();
			final Set<String> obtenidos = tirar(supplier, 50);

			assertFalse(obtenidos.isEmpty());
			assertTrue(obtenidos.size() > 1, "Siempre devolvio el mismo nombre");
			assertNull(supplier.getEmpty());
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	/*
	 * Cada uno lee su fichero: nombresH.txt el de mujer y nombresV.txt el de varon.
	 * Como las dos listas no comparten ningun nombre, que los resultados no se
	 * solapen demuestra que no estan cruzados ni leyendo los dos el mismo fichero.
	 */
	@Test
	void testLosDosNoLeenLoMismo() {
		try {
			final Set<String> mujeres = tirar(new RandomFemaleNameSupplier(), 50);
			final Set<String> varones = tirar(new RandomMaleNameSupplier(), 50);
			logger.debug("Mujeres={}", mujeres);
			logger.debug("Varones={}", varones);

			final Set<String> comunes = new TreeSet<>(mujeres);
			comunes.retainAll(varones);
			assertTrue(comunes.isEmpty(), String.format("Nombres en los dos: %s", comunes));
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

	private Set<String> tirar(RandomSelectedFromFileSupplier supplier, int veces) {
		final Set<String> obtenidos = new TreeSet<>();
		for (int i = 0; i < veces; i = i + 1) {
			final String value = supplier.get();
			assertNotNull(value);
			assertFalse(value.isBlank());
			obtenidos.add(value);
		}
		return obtenidos;
	}

	@Test
	void testRandomSurnameSupplier() {
		try {
			final RandomSurnameSupplier supplier = new RandomSurnameSupplier();
			for (int i = 0; i < 100; i = i + 1) {
				final String value = supplier.get();
				assertNotNull(value);
				logger.debug("Valor generado={}", value);
			}

		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Excepcion inesperada");
		}
	}

}
