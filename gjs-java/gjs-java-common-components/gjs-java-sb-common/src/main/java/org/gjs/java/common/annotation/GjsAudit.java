package org.gjs.java.common.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * The Interface GjsAudit.
 *
 * Anotación de la librería Gjs
 *
 * Anotación para incluir un método en la auditoría de tiempos. Los métodos de
 * fachadas y servicios ya están incluidos sin necesidad de la anotación.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface GjsAudit {

}
