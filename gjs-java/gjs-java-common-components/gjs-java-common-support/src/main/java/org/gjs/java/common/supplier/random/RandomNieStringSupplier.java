package org.gjs.java.common.supplier.random;

/**
 * The Class RandomAlphanumericStringSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de NIE aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomNieStringSupplier extends RandomNumericStringSupplier {

    /** The Constant NIE_NUMERIC_PART_LENGTH. */
    private static final int NIE_NUMERIC_PART_LENGTH = 7;

    /** The Constant NIE_PREFIX_ASOCIATION. */
    private static final String NIE_PREFIX_ASOCIATION = "XYZ";

    /** The Constant NUMERIC_PREFIX_ASOCIATION. */
    private static final String NUMERIC_PREFIX_ASOCIATION = "012";

    /** The Constant NIF_STRING_ASOCIATION. */
    private static final String NIF_STRING_ASOCIATION = "TRWAGMYFPDXBNJZSQVHLCKE";

    /** The index supplier. */
    private final RandomIntegerSupplier indexSupplier;

    /**
     * Instantiates a new random nie string supplier.
     */
    public RandomNieStringSupplier() {
        super(NIE_NUMERIC_PART_LENGTH, false, true);
        indexSupplier = new RandomIntegerSupplier(Integer.valueOf(0),
                Integer.valueOf(NIE_PREFIX_ASOCIATION.length() - 1));
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.RandomNumericStringSupplier#get() */

    @Override
    public String get() {
        final String numericPart = super.get();
        final int index = indexSupplier.get().intValue();
        final char firstLetter = NIE_PREFIX_ASOCIATION.charAt(index);
        final Integer value = Integer
                .valueOf(String.valueOf(NUMERIC_PREFIX_ASOCIATION.charAt(index)).concat(numericPart));
        return String.valueOf(String.valueOf(firstLetter).concat(numericPart).concat(String.valueOf(letterDni(value))));
    }

    /**
     * Letter dni.
     *
     * @param dni
     *            the dni
     * @return the char
     */
    private char letterDni(int dni) {
        return NIF_STRING_ASOCIATION.charAt(dni % 23);
    }

}
