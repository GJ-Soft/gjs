package org.gjs.java.test.util;

import java.util.List;
import java.util.Objects;

import org.apache.commons.collections4.CollectionUtils;
import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.util.ConditionUtils;

import com.openpojo.validation.Validator;
import com.openpojo.validation.ValidatorBuilder;
import com.openpojo.validation.test.Tester;

/**
 * The Class PojoUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Algunas funciones de ayuda para la implementación de los test Pojos
 * automatizados.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class PojoUtils {

	/**
	 * Clase no instanciable.
	 */
	private PojoUtils() {
		throw new IllegalStateException("Utility class");
	}

	/**
	 * Test pojo.
	 *
	 * @param tester        the tester
	 * @param packageToTest the package to test
	 */
	public static void testPojo(Tester tester, String packageToTest) {
		if (ConditionUtils.allAreTrue(Objects.nonNull(tester), !StringUtils.isAllBlank(packageToTest))) {
			final Validator validator = ValidatorBuilder.create().with(tester).build();
			validator.validate(packageToTest);
		}
	}

	/**
	 * Test pojo.
	 *
	 * @param testers       the testers
	 * @param packageToTest the package to test
	 */
	public static void testPojo(List<Tester> testers, String packageToTest) {
		if (ConditionUtils.allAreTrue(!CollectionUtils.isEmpty(testers), !StringUtils.isAllBlank(packageToTest))) {
			ValidatorBuilder validatorBuilder = ValidatorBuilder.create();
			for (final Tester tester : testers) {
				validatorBuilder = validatorBuilder.with(tester);
			}
			final Validator validator = validatorBuilder.build();
			validator.validate(packageToTest);
		}
	}

}
