package org.gjs.java.common.comparator;

import java.util.Comparator;
import java.util.Date;
import java.util.Objects;

import org.gjs.java.common.util.ConditionUtils;

/**
 * The Class DateComparatorDesc.
 *
 * Clase de datos de la librería Gjs
 *
 * Comparador para ordenar fechas de forma descendente.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class DateComparatorDesc implements Comparator<Date> {

    /* (non-Javadoc)
     *
     * @see java.util.Comparator#compare(java.lang.Object, java.lang.Object) */

    @Override
    public int compare(Date o1, Date o2) {
        int res = -1;
        if (ConditionUtils.allAreTrue(Objects.isNull(o1), Objects.isNull(o2))) {
            res = 0;
        } else if (Objects.isNull(o2)) {
            res = 1;
        } else if (Objects.isNull(o1)) {
            res = -1;
        } else {
            res = o2.compareTo(o1);
        }
        return res;
    }

}
