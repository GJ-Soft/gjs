package org.gjs.java.test.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.util.Optional;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ConditionEvaluationResult;
import org.junit.jupiter.api.extension.ExecutionCondition;
import org.junit.jupiter.api.extension.ExtendWith;
import org.junit.jupiter.api.extension.ExtensionContext;
import org.junit.platform.commons.support.AnnotationSupport;

/**
 * Test que solo se ejecuta en un rango de versiones de Java.
 *
 * Anotacion de test de la libreria Gjs
 *
 * Los limites son la version mayor ( 17, 21, 25 ) y ambos son inclusivos. Dejar uno a -1 lo deja sin tope por ese lado;
 * dejar los dos equivale a no poner condicion. No delega en EnabledForJreRange de JUnit porque las condiciones de JUnit
 * leen los valores declarados en la meta-anotacion, no los de la anotacion compuesta.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Target({ ElementType.METHOD, ElementType.ANNOTATION_TYPE })
@Retention(RetentionPolicy.RUNTIME)
@Test
@ExtendWith(GjsJavaVersionTest.Condicion.class)
public @interface GjsJavaVersionTest {

	/**
	 * @return version mayor minima, inclusive; -1 para no poner minimo
	 */
	int minVersion() default -1;

	/**
	 * @return version mayor maxima, inclusive; -1 para no poner maximo
	 */
	int maxVersion() default -1;

	/**
	 * Decide si el test se ejecuta, a partir de los valores de la propia anotacion.
	 */
	class Condicion implements ExecutionCondition {

		@Override
		public ConditionEvaluationResult evaluateExecutionCondition(ExtensionContext context) {
			final Optional<GjsJavaVersionTest> anotacion = AnnotationSupport.findAnnotation(context.getElement(),
					GjsJavaVersionTest.class);
			if (anotacion.isEmpty()) {
				return ConditionEvaluationResult.enabled("Sin @GjsJavaVersionTest");
			}

			final int minima = anotacion.get().minVersion();
			final int maxima = anotacion.get().maxVersion();
			final int actual = Runtime.version().feature();

			if (minima != -1 && actual < minima) {
				return ConditionEvaluationResult.disabled(String.format("Java %s, se pedia %s o superior", actual,
						minima));
			}
			if (maxima != -1 && actual > maxima) {
				return ConditionEvaluationResult.disabled(String.format("Java %s, se pedia %s o inferior", actual,
						maxima));
			}
			return ConditionEvaluationResult.enabled(String.format("Java %s, dentro del rango [%s, %s]", actual, minima,
					maxima));
		}
	}

}
