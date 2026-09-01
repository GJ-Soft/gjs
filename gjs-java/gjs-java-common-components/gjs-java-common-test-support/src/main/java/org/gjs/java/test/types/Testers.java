package org.gjs.java.test.types;

import com.openpojo.validation.test.Tester;
import com.openpojo.validation.test.impl.SetterTester;

/**
 * The Class Testers.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase pensada para incluir testers especiales que puedan definirse en las aplicaciones para test Pojos automatizados
 * de clases especiales.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class Testers {

    /** The setter tester. */
    // Todo: ampliar a la customizacion de todos los tipos de testers
    private final Tester setterTester;

    /**
     * Instantiates a new testers.
     */
    public Testers() {
        this(new SetterTester());
    }

    /**
     * Instantiates a new testers.
     *
     * @param setterTester
     *            the setter tester
     */
    public Testers(Tester setterTester) {
        this.setterTester = setterTester;
    }

    /**
     * Gets the setter tester.
     *
     * @return the setter tester
     */
    public Tester getSetterTester() {
        return setterTester;
    }

}
