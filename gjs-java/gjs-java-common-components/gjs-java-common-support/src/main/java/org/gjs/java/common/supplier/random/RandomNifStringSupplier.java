package org.gjs.java.common.supplier.random;

/**
 * The Class RandomAlphanumericStringSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generadores de NIF aleatorios.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class RandomNifStringSupplier extends RandomDniStringSupplier {

    /** The Constant NIF_STRING_ASOCIATION. */
    private static final String NIF_STRING_ASOCIATION = "TRWAGMYFPDXBNJZSQVHLCKE";

    /**
     * Instantiates a new random dni string supplier.
     */
    public RandomNifStringSupplier() {
        // No hace nada
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.RandomNumericStringSupplier#get() */

    @Override
    public String get() {
        final String dni = super.get();
        final Integer valueDni = Integer.valueOf(dni);
        return dni.concat(String.valueOf(letterDni(valueDni)));
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
