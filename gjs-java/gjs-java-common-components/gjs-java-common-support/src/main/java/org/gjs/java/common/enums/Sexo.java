package org.gjs.java.common.enums;

import java.util.Arrays;
import java.util.Set;
import java.util.TreeSet;

/**
 * The Enum Sexo.
 *
 * Enumerado de la librería Gjs
 *
 * Tipos de sexo.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public enum Sexo {

    /** The varon. */
    VARON("hombre", "V", "masculino", "macho", "caballero", "señor", "señorito", "chico", "muchacho", "esposo",
            "marido"),
    /** The hembra. */
    HEMBRA("mujer", "H", "femina", "hembra", "dama", "señora", "señorita", "chica", "muchacha", "esposa");

    /** The nombre. */
    private String nombre;

    /** The acronimo. */
    private String acronimo;

    /** The sinonimos. */
    private Set<String> sinonimos;

    /**
     * Instantiates a new sexo.
     *
     * @param nombre
     *            the nombre
     * @param acronimo
     *            the acronimo
     */
    Sexo(String nombre, String acronimo) {
        this.nombre = nombre;
        this.acronimo = acronimo;
        sinonimos = new TreeSet<>();
        sinonimos.add(acronimo);
        sinonimos.add(nombre);
    }

    /**
     * Instantiates a new sexo.
     *
     * @param nombre
     *            the nombre
     * @param acronimo
     *            the acronimo
     * @param sinonimos
     *            the sinonimos
     */
    Sexo(String nombre, String acronimo, String... sinonimos) {
        this(nombre, acronimo);
        this.sinonimos.addAll(Arrays.asList(sinonimos));
    }

    /**
     * Gets the nombre.
     *
     * @return the nombre
     */
    public String getNombre() {
        return nombre;
    }

    /**
     * Gets the acronimo.
     *
     * @return the acronimo
     */
    public String getAcronimo() {
        return acronimo;
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Enum#toString() */

    @Override
    public String toString() {
        return acronimo;
    }

    /**
     * Gets the.
     *
     * @param texto
     *            the texto
     * @return the sexo
     */
    public static Sexo get(String texto) {
        Sexo res = null;
        for (final Sexo type : Sexo.values()) {
            if (type.sinonimos.stream().anyMatch(s -> s.equalsIgnoreCase(texto))) {
                res = type;
                break;
            }
        }
        return res;
    }

}
