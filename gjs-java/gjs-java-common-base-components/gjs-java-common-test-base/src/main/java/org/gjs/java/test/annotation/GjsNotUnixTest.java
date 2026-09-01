package org.gjs.java.test.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.DisabledOnOs;
import org.junit.jupiter.api.condition.OS;

/**
 * Test que se ejecuta en todas partes menos sobre Unix. Complementario de {@link GjsUnixTest}: la lista de sistemas es
 * la misma, de modo que cada sistema cae en una de las dos y solo en una.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Target({ ElementType.METHOD, ElementType.ANNOTATION_TYPE })
@Retention(RetentionPolicy.RUNTIME)
@Test
@DisabledOnOs({ OS.AIX, OS.FREEBSD, OS.LINUX, OS.OPENBSD, OS.SOLARIS })
public @interface GjsNotUnixTest {

}
