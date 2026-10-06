package org.gjs.java.test;

import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.fail;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.test.tester.BaseTester;
import org.gjs.java.test.util.PojoUtils;
import org.junit.jupiter.api.Test;

/**
 * The Class AbstractTesterUnitTest.
 *
 * Clase abstracta funcional de la librería Gjs
 *
 * Clase abstracta base para todos los test unitarios de testers particulares de la librería Gjs
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 * @param <T>
 *            clase tester a testear (que extienda de BaseTester)
 */
public abstract class AbstractTesterUnitTest<T extends BaseTester> extends BaseUnitTest<T> {

    /** Mensaje de fallo de una prueba que lanza una excepcion. */
    private static final String MSG_ERROR = "Se ha producido un error";

    /**
     * Gets the package to test ok.
     *
     * @return the package to test ok
     */
    protected abstract String getPackageToTestOk();

    /**
     * Gets the package to test ko.
     *
     * @return the package to test ko
     */
    protected abstract String getPackageToTestKo();

    /**
     * Creates the tester.
     *
     * @param stopOnError
     *            the stop on error
     * @return the base tester
     */
    protected abstract BaseTester createTester(boolean stopOnError);

    /**
     * Test tester 1.
     */
    @Test
    public void testTester1() {
        try {
            final BaseTester tester = createTester(true);
            PojoUtils.testPojo(tester, getPackageToTestOk());

        } catch (final Exception e) {
            logger.error(ExceptionUtils.getStackTrace(e));
            fail(MSG_ERROR);
        }
    }

    /**
     * Test tester 2.
     */
    @Test
    public void testTester2() {
        try {
            final BaseTester tester = createTester(true);
            PojoUtils.testPojo(tester, getPackageToTestKo());
            fail("Deberia haber fallado");

        } catch (final AssertionError e) {
            assertNotNull(e.getMessage());
        } catch (final Exception e) {
            logger.error(ExceptionUtils.getStackTrace(e));
            fail(MSG_ERROR);
        }
    }

    /**
     * Test tester 3.
     */
    @Test
    public void testTester3() {
        try {
            final BaseTester tester = createTester(false);
            PojoUtils.testPojo(tester, getPackageToTestKo());

        } catch (final AssertionError e) {
            logger.error(ExceptionUtils.getStackTrace(e));
            fail("En este modo los errores deberian ser un warning en el log");
        } catch (final Exception e) {
            logger.error(ExceptionUtils.getStackTrace(e));
            fail(MSG_ERROR);
        }
    }

}
