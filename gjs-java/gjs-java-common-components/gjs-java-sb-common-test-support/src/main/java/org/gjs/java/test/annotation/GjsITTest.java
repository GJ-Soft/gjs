package org.gjs.java.test.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Inherited;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.core.annotation.AliasFor;
import org.springframework.test.context.ActiveProfiles;

/**
 * The Interface SemillaITTest.
 *
 * Anotación de la librería Gjs
 *
 * Anotación para las clase de test IT que obliga a usar el perfil testIT que se conecta directamente a la base de datos
 * Oracle.
 *
 * IMPORTANTE: Es importante en estos test considerar el entorno en el persistence.properties
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@SpringBootTest
@ActiveProfiles("testIT")
@Inherited
public @interface GjsITTest {

    /**
     * Active profiles.
     *
     * @return the string[]
     */
    @AliasFor(annotation = ActiveProfiles.class, attribute = "profiles")
    String[] activeProfiles() default { "testIT" };

    /**
     * Classes.
     *
     * @return the class[]
     */
    @AliasFor(annotation = SpringBootTest.class, attribute = "classes")
    Class<?>[] classes() default {};
}
