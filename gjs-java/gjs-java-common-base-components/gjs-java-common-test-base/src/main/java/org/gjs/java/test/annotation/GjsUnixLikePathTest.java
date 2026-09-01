package org.gjs.java.test.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.EnabledIfSystemProperty;

/**
 * Test que solo se ejecuta cuando el separador de rutas es la barra ( / ). Mira el separador, no el sistema: en Cygwin
 * sobre Windows lo que manda es como se forman las rutas.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Target({ ElementType.METHOD, ElementType.ANNOTATION_TYPE })
@Retention(RetentionPolicy.RUNTIME)
@Test
@EnabledIfSystemProperty(named = "file.separator", matches = "/")
public @interface GjsUnixLikePathTest {

}
