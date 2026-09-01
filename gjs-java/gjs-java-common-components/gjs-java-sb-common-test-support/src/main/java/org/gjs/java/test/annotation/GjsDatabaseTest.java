package org.gjs.java.test.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Inherited;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import org.junit.jupiter.api.parallel.Execution;
import org.junit.jupiter.api.parallel.ExecutionMode;
import org.junit.jupiter.api.parallel.Isolated;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.core.annotation.AliasFor;
import org.springframework.test.context.jdbc.Sql;
import org.springframework.test.context.jdbc.Sql.ExecutionPhase;
import org.springframework.test.context.jdbc.SqlConfig;
import org.springframework.test.context.jdbc.SqlConfig.ErrorMode;
import org.springframework.test.context.jdbc.SqlConfig.TransactionMode;

/**
 * The Interface SemillaDatabaseTest.
 *
 * Anotación de la librería Gjs
 *
 * Anotación para las clase de test unitarios SpringBoot con acceso a datos que necesiten garantizar que el juego de
 * pruebas no se ve afectado por otras clases de test similares.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
@SpringBootTest
@Sql(scripts = {
        "classpath:sql/init-db.sql" }, executionPhase = ExecutionPhase.BEFORE_TEST_CLASS, config = @SqlConfig(transactionMode = TransactionMode.ISOLATED, errorMode = ErrorMode.CONTINUE_ON_ERROR))
/**
 * The Interface GjsDatabaseTest.
 *
 * Anotación de la librería Gjs
 *
 * Marca una clase de test contra base de datos: levanta el contexto de Spring Boot, ejecuta los scripts SQL indicados y aísla la ejecución del resto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Isolated
@Execution(ExecutionMode.SAME_THREAD)
@Inherited
public @interface GjsDatabaseTest {

    /**
     * Classes.
     *
     * @return the class[]
     */
    @AliasFor(annotation = SpringBootTest.class, attribute = "classes")
    Class<?>[] classes() default {};
}
