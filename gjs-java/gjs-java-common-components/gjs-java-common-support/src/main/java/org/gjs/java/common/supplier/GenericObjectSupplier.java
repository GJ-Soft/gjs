package org.gjs.java.common.supplier;

/**
 * The Class GenericObjectSupplier.
 *
 * Clase de datos de la librería Gjs
 *
 * Generador de objetos genéricos de tipo Object.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class GenericObjectSupplier extends AbstractObjectSupplier<Object> {

    /**
     * Instantiates a new generic object supplier.
     *
     * @param className
     *            the class name
     */
    public GenericObjectSupplier(String className) {
        super(className);
        super.setInformAllFields(true);
        super.setInformCollections(true);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.test.objects.suppliers.AbstractRandomSupplier#createArray(int) */

    @Override
    protected Object[] createArray(int size) {
        return new Object[size];
    }

}
