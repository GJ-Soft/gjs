package org.gjs.java.test.samples.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * The Interface SampleAnotation.
 *
 * Anotación de la librería Gjs
 *
 * Anotación para incluir un método en la auditoría de tiempos. Los métodos de
 * fachadas y servicios ya están incluidos sin necesidad de la anotación.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Target({ ElementType.TYPE, ElementType.FIELD })
@Retention(RetentionPolicy.RUNTIME)
public @interface SampleAnnotation {

}
