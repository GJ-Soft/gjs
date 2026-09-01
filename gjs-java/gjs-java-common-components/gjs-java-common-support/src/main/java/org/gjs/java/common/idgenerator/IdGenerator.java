package org.gjs.java.common.idgenerator;

/**
 * The Interface IdGenerator.
 *
 * Interfaz de la librería Gjs
 *
 * Interfaz que debe implementar un generador de identificadores para las clases mock de gestión de datos.
 *
 * @param <T>
 *            la clase del identificador a generar
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public interface IdGenerator<T> {

    /**
     * Generate.
     *
     * @return the t
     */
    T generate();
}
