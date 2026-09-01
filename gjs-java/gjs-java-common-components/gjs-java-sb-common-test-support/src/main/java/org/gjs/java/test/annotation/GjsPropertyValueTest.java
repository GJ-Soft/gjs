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
 * Test que solo se ejecuta si una propiedad de sistema casa con un patron.
 *
 * Anotacion de test de la libreria Gjs
 *
 * No delega en EnabledIfSystemProperty de JUnit porque las condiciones de JUnit leen los valores declarados en la
 * meta-anotacion, no los de la anotacion compuesta: el @AliasFor de Spring no llega hasta ahi. Por eso trae su propia
 * ExecutionCondition.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Target({ ElementType.METHOD, ElementType.ANNOTATION_TYPE })
@Retention(RetentionPolicy.RUNTIME)
@Test
@ExtendWith(GjsPropertyValueTest.Condicion.class)
public @interface GjsPropertyValueTest {

	/**
	 * @return nombre de la propiedad de sistema
	 */
	String named();

	/**
	 * @return expresion regular que debe casar con el valor de la propiedad
	 */
	String matches();

	/**
	 * Decide si el test se ejecuta, a partir de los valores de la propia anotacion.
	 */
	class Condicion implements ExecutionCondition {

		@Override
		public ConditionEvaluationResult evaluateExecutionCondition(ExtensionContext context) {
			final Optional<GjsPropertyValueTest> anotacion = AnnotationSupport.findAnnotation(context.getElement(),
					GjsPropertyValueTest.class);
			if (anotacion.isEmpty()) {
				return ConditionEvaluationResult.enabled("Sin @GjsPropertyValueTest");
			}

			final String nombre = anotacion.get().named();
			final String patron = anotacion.get().matches();
			final String valor = System.getProperty(nombre);

			if (valor == null) {
				return ConditionEvaluationResult.disabled(String.format("La propiedad %s no esta definida", nombre));
			}
			if (Pattern.matches(patron, valor)) {
				return ConditionEvaluationResult.enabled(String.format("%s = %s, casa con %s", nombre, valor, patron));
			}
			return ConditionEvaluationResult
					.disabled(String.format("%s = %s, no casa con %s", nombre, valor, patron));
		}
	}

}
