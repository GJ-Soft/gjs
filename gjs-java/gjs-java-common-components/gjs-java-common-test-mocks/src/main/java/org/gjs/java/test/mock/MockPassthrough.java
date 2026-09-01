package org.gjs.java.test.mock;

/**
 * The Class MockPassthrough.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase pensada para ser extendida por mocks de servicios o fachadas cuando existan alternativas de usa y deba
 * chequearse que se ha pasado por el correcto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockPassthrough {

    /** The checked. */
    private boolean checked;

    /**
     * Inits the.
     */
    public void init() {
        checked = false;
    }

    /**
     * Check.
     */
    protected void check() {
        checked = true;
    }

    /**
     * Checks if is checked.
     *
     * @return true, if is checked
     */
    public boolean isChecked() {
        return checked;
    }

}
