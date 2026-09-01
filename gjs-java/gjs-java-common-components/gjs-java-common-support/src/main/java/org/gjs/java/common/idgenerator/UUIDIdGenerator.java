package org.gjs.java.common.idgenerator;

import java.util.UUID;

/**
 * The Class UUIDIdGenerator.
 *
 * Clase de datos de la librería Gjs
 *
 * Generador de identificadores cadena UUID.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class UUIDIdGenerator implements IdGenerator<String> {

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.mock.IdGenerator#generate() */

    @Override
    public String generate() {
        return UUID.randomUUID().toString();
    }

}
