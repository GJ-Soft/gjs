package org.gjs.java.test.annotation;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.lang.annotation.Annotation;
import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.util.Arrays;
import java.util.List;
import java.util.regex.Pattern;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.DisabledOnOs;
import org.junit.jupiter.api.condition.EnabledIfSystemProperty;
import org.junit.jupiter.api.condition.EnabledOnOs;
import org.junit.jupiter.api.condition.OS;

class GjsAnnotationsTest {

	private static final List<Class<? extends Annotation>> TODAS = List.of(GjsMacTest.class, GjsNotUnixTest.class,
			GjsUnixLikePathTest.class, GjsUnixTest.class, GjsWindowsLikePathTest.class, GjsWindowsTest.class);

	/*
	 * Sin retencion RUNTIME JUnit no llega a verlas, y el metodo anotado no se ejecuta ni se salta: simplemente no
	 * existe como test. Es la comprobacion que sostiene a todas las demas.
	 */
	@Test
	void testRetencionEnTiempoDeEjecucion() {
		for (final Class<? extends Annotation> anotacion : TODAS) {
			final Retention retencion = anotacion.getAnnotation(Retention.class);
			assertNotNull(retencion, anotacion.getSimpleName() + " no declara @Retention");
			assertEquals(RetentionPolicy.RUNTIME, retencion.value(), anotacion.getSimpleName());
		}
	}

	@Test
	void testAplicablesAMetodos() {
		for (final Class<? extends Annotation> anotacion : TODAS) {
			final Target destino = anotacion.getAnnotation(Target.class);
			assertNotNull(destino, anotacion.getSimpleName() + " no declara @Target");
			assertTrue(Arrays.asList(destino.value()).contains(ElementType.METHOD), anotacion.getSimpleName());
		}
	}

	@Test
	void testSonTest() {
		for (final Class<? extends Annotation> anotacion : TODAS) {
			assertTrue(anotacion.isAnnotationPresent(Test.class), anotacion.getSimpleName() + " no es un @Test");
		}
	}

	@Test
	void testWindowsYMac() {
		assertArrayEquals(new OS[] { OS.WINDOWS }, GjsWindowsTest.class.getAnnotation(EnabledOnOs.class).value());
		assertArrayEquals(new OS[] { OS.MAC }, GjsMacTest.class.getAnnotation(EnabledOnOs.class).value());
	}

	/*
	 * Unix y NotUnix tienen que ser complementarias: misma lista de sistemas, una habilitando y la otra deshabilitando.
	 * Asi cada sistema cae en una de las dos y solo en una.
	 */
	@Test
	void testUnixYNoUnixSonComplementarias() {
		final OS[] enUnix = GjsUnixTest.class.getAnnotation(EnabledOnOs.class).value();
		final OS[] fueraDeUnix = GjsNotUnixTest.class.getAnnotation(DisabledOnOs.class).value();

		assertArrayEquals(enUnix, fueraDeUnix);
		assertTrue(Arrays.asList(enUnix).contains(OS.LINUX));
		assertFalse(Arrays.asList(enUnix).contains(OS.WINDOWS));
	}

	@Test
	void testSeparadoresDeRuta() {
		final String unix = GjsUnixLikePathTest.class.getAnnotation(EnabledIfSystemProperty.class).matches();
		final String windows = GjsWindowsLikePathTest.class.getAnnotation(EnabledIfSystemProperty.class).matches();

		assertTrue(Pattern.compile(unix).matcher("/").matches());
		assertFalse(Pattern.compile(unix).matcher("\\").matches());

		assertTrue(Pattern.compile(windows).matcher("\\").matches());
		assertFalse(Pattern.compile(windows).matcher("/").matches());
	}

	@Test
	void testMiranLaPropiedadCorrecta() {
		final String unix = GjsUnixLikePathTest.class.getAnnotation(EnabledIfSystemProperty.class).named();
		final String windows = GjsWindowsLikePathTest.class.getAnnotation(EnabledIfSystemProperty.class).named();

		assertEquals("file.separator", unix);
		assertEquals("file.separator", windows);
	}

}
