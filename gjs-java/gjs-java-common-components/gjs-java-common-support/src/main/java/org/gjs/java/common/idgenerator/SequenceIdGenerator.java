package org.gjs.java.common.idgenerator;

/**
 * The Class SequenceIdGenerator.
 *
 * Clase de datos de la librería Gjs
 *
 * Generador de identificadores enteros secuencial.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class SequenceIdGenerator implements IdGenerator<Long> {

    /** The last. */
    private Long last = Long.valueOf(0);

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.mock.IdGenerator#generate() */

    @Override
    public Long generate() {
        last = last + 1;
        return last;
    }

}
