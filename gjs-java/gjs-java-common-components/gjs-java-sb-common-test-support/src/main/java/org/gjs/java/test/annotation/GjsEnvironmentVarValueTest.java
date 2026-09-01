package org.gjs.java.test.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;
import java.util.Optional;
import java.util.regex.Pattern;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ConditionEvaluationResult;
import org.junit.jupiter.api.extension.ExecutionCondition;
import org.junit.jupiter.api.extension.ExtendWith;
import org.junit.jupiter.api.extension.ExtensionContext;
import org.junit.platform.commons.support.AnnotationSupport;

/**
 * Test que solo se ejecuta si una variable de entorno casa con un patron.
 *
 * Anotacion de test de la libreria Gjs
 *
 * Gemela de {@link GjsPropertyValueTest}, pero mirando el entorno del proceso en lugar de las propiedades de sistema, y
 * con su propia ExecutionCondition por el mismo motivo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Target({ ElementType.METHOD, ElementType.ANNOTATION_TYPE })
@Retention(RetentionPolicy.RUNTIME)
@Test
@ExtendWith(GjsEnvironmentVarValueTest.Condicion.class)
public @interface GjsEnvironmentVarValueTest {

	/**
	 * @return nombre de la variable de entorno
	 */
	String named();

	/**
	 * @return expresion regular que debe casar con el valor de la variable
	 */
	String matches();

	/**
	 * Decide si el test se ejecuta, a partir de los valores de la propia anotacion.
	 */
	class Condicion implements ExecutionCondition {

		@Override
		public ConditionEvaluationResult evaluateExecutionCondition(ExtensionContext context) {
			final Optional<GjsEnvironmentVarValueTest> anotacion = AnnotationSupport
					.findAnnotation(context.getElement(), GjsEnvironmentVarValueTest.class);
			if (anotacion.isEmpty()) {
				return ConditionEvaluationResult.enabled("Sin @GjsEnvironmentVarValueTest");
			}

			final String nombre = anotacion.get().named();
			final String patron = anotacion.get().matches();
			final String valor = System.getenv(nombre);

			if (valor == null) {
				return ConditionEvaluationResult.disabled(String.format("La variable %s no esta definida", nombre));
			}
			if (Pattern.matches(patron, valor)) {
				return ConditionEvaluationResult.enabled(String.format("%s = %s, casa con %s", nombre, valor, patron));
			}
			return ConditionEvaluationResult
					.disabled(String.format("%s = %s, no casa con %s", nombre, valor, patron));
		}
	}

}
