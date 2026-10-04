package org.gjs.java.test;

import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.Objects;
import java.util.Set;
import java.util.TreeSet;

import org.apache.commons.lang3.ArrayUtils;
import org.gjs.java.common.util.ConditionUtils;

import io.jsonwebtoken.lang.Arrays;

/**
 * The Class AbstractDataObjectUnitTest.
 *
 * Clase abstracta funcional de la librería Gjs
 *
 * Clase abstracta base para todos los test unitarios de clases que necesiten manejo de datos de la librería Gjs
 *
 * @author Gjs
 * @version 1.0.0
 * @param <T>
 *            clase a testear
 * @since 1.0.0
 */
public abstract class AbstractDataObjectUnitTest<T> extends BaseUnitTest<T> {

    /** The initial data count. */
    protected long initialDataCount;

    // Identificadores registros inmutables:
    /** The id1. */
    protected Long ID1 = Long.valueOf(1);

    /** The cod1. */
    protected String COD1 = "COD1";

    /** The id2. */
    protected Long ID2 = Long.valueOf(2);

    /** The cod2. */
    protected String COD2 = "COD2";

    // Identificadores registros modificables:
    /** The idu1. */
    protected Long IDU1 = Long.valueOf(3);

    /** The codu1. */
    protected String CODU1 = "COD3";

    // Identificadores registros eliminables:
    /** The idd1. */
    protected Long IDD1 = Long.valueOf(4);

    /** The codd1. */
    protected String CODD1 = "COD4";

    // Identificador invalido:
    /** The idko. */
    protected Long IDKO = Long.valueOf(0);

    /** The codko. */
    protected String CODKO = "";

    // Identificador inexistente:
    /** The idne. */
    protected Long IDNE = Long.valueOf(99);

    /** The codne. */
    protected String CODNE = "XXX";

    /** The additional ids. */
    protected Long[] additionalIds;

    /** The additional cods. */
    protected String[] additionalCods;

    /**
     * Instantiates a new abstract data object unit test.
     */
    protected AbstractDataObjectUnitTest() {
    }

    /**
     * Instantiates a new abstract data object unit test.
     *
     * @param testClazz
     *            the test clazz
     */
    protected AbstractDataObjectUnitTest(Class<T> testClazz) {
        super(testClazz);
    }

    /**
     * Load test data.
     *
     * @return the long
     * @throws Exception
     *             the exception
     */
    protected abstract long loadTestData() throws Exception;

    /**
     * Gets the expected.
     *
     * @return the expected
     */
    protected Long[] getExpected() {
        final Long[] expected = new Long[4 + ArrayUtils.getLength(additionalIds)];
        expected[0] = ID1;
        expected[1] = ID2;
        expected[2] = IDU1;
        expected[3] = IDD1;
        for (int i = 0; i < ArrayUtils.getLength(additionalIds); i = i + 1) {
            expected[4 + i] = additionalIds[i];
        }
        return expected;
    }

    /**
     * Gets the cods expected.
     *
     * @return the cods expected
     */
    protected String[] getCodsExpected() {
        final String[] expected = new String[4 + ArrayUtils.getLength(additionalCods)];
        expected[0] = COD1;
        expected[1] = COD2;
        expected[2] = CODU1;
        expected[3] = CODD1;
        for (int i = 0; i < ArrayUtils.getLength(additionalCods); i = i + 1) {
            expected[4 + i] = additionalCods[i];
        }
        return expected;
    }

    protected String[] getOrdererCodsExpected() {
        final String[] expected = getCodsExpected();
        final Set<String> set = new TreeSet<>(Arrays.asList(expected));
        return set.toArray(new String[expected.length]);
    }

    /**
     * Gets the immutable ids.
     *
     * @return the immutable ids
     */
    protected Long[] getImmutableIds() {
        return new Long[] { ID1, ID2 };
    }

    /**
     * Gets the immutable cods.
     *
     * @return the immutable cods
     */
    protected String[] getImmutableCods() {
        return new String[] { COD1, COD2 };
    }

    /**
     * Valid element data count.
     *
     * @return the long
     */
    protected long validElementDataCount() {
        return getExpected().length;
    }

    /**
     * Pre load test data.
     */
    protected void preLoadTestData() {
    }

    /**
     * Post load test data.
     */
    protected void postLoadTestData() {
    }

    /**
     * Clean test data.
     */
    protected void cleanTestData() {
    }

    /**
     * Define expected ids.
     *
     * @param id1
     *            the id 1
     * @param id2
     *            the id 2
     * @param idu1
     *            the idu 1
     * @param idd1
     *            the idd 1
     * @param additional
     *            the additional
     */
    protected void defineExpectedIds(Long id1, Long id2, Long idu1, Long idd1, Long... additional) {
        ID1 = id1;
        ID2 = id2;
        IDU1 = idu1;
        IDD1 = idd1;
        this.additionalIds = additional;
    }

    /**
     * Define inexistent id.
     *
     * @param idne
     *            the idne
     */
    protected void defineInexistentId(Long idne) {
        IDNE = idne;
    }

    /**
     * Define expected max id.
     *
     * @param maxId
     *            the max id
     */
    protected void defineExpectedMaxId(Long maxId) {
        ID1 = Long.valueOf(1);
        ID2 = Long.valueOf(2);
        IDU1 = Long.valueOf(3);
        IDD1 = Long.valueOf(4);
        if (maxId > IDD1) {
            this.additionalIds = new Long[maxId.intValue() - 4];
            for (int i = 5; i <= maxId.intValue(); i = i + 1) {
                additionalIds[i - 5] = Long.valueOf(i);
            }
        } else {
            this.additionalIds = null;
        }
    }

    /**
     * Define expected cods.
     *
     * @param cod1
     *            the cod 1
     * @param cod2
     *            the cod 2
     * @param codu1
     *            the codu 1
     * @param codd1
     *            the codd 1
     * @param additional
     *            the additional
     */
    protected void defineExpectedCods(String cod1, String cod2, String codu1, String codd1, String... additional) {
        COD1 = cod1;
        COD2 = cod2;
        CODU1 = codu1;
        CODD1 = codd1;
        this.additionalCods = additional;
    }

    /**
     * Define inexistent cod.
     *
     * @param codne
     *            the codne
     */
    protected void defineInexistentCod(String codne) {
        CODNE = codne;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.AbstractUnitTest#initialize() */

    @Override
    protected void initialize() throws Exception {
        preLoadTestData();
        initialDataCount = loadTestData();
        logger.info("Cargados los datos. Registros totales={}", initialDataCount);
        assertTrue(initialDataCount >= validElementDataCount(), "Datos de prueba insuficientes para completar el test");
        postLoadTestData();
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.AbstractTest#finalizeTest() */

    @Override
    protected void finalizeTest() {
        cleanTestData();
    }

    /**
     * Checks if is id expected.
     *
     * @param id
     *            the id
     * @return true, if is id expected
     */
    protected boolean isIdExpected(Long id) {
        boolean res = false;
        if (Objects.nonNull(id)) {
            res = ArrayUtils.contains(getExpected(), id);
        }
        return res;
    }

    /**
     * Checks if is cod expected.
     *
     * @param cod
     *            the cod
     * @return true, if is cod expected
     */
    protected boolean isCodExpected(String cod) {
        boolean res = false;
        if (Objects.nonNull(cod)) {
            res = ArrayUtils.contains(getCodsExpected(), cod);
        }
        return res;
    }

    /**
     * Checks if is id expected in order.
     *
     * @param id
     *            the id
     * @param order
     *            the order
     * @return true, if is id expected in order
     */
    protected boolean isIdExpectedInOrder(Long id, int order) {
        boolean res = false;
        if (ConditionUtils.allAreTrue(Objects.nonNull(id), (order >= 0), (order < getExpected().length))) {
            res = getExpected()[order].equals(id);
        }
        return res;
    }

    /**
     * Checks if is cod expected in order.
     *
     * @param cod
     *            the cod
     * @param order
     *            the order
     * @return true, if is cod expected in order
     */
    protected boolean isCodExpectedInOrder(String cod, int order) {
        boolean res = false;
        if (ConditionUtils.allAreTrue(Objects.nonNull(cod), (order >= 0), (order < getExpected().length))) {
            res = getOrdererCodsExpected()[order].equals(cod);
        }
        return res;
    }

}
