package org.gjs.java.test.samples.pojos;

import java.time.LocalDate;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleLocalDatePojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo con un único campo LocalDate.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleLocalDatePojo {

    private LocalDate localDate;

    public SampleLocalDatePojo() {
    }

    public SampleLocalDatePojo(LocalDate localDate) {
        this.localDate = localDate;
    }

    @Override
    public String toString() {
        return "SampleLocalDatePojo [localDate="
                + localDate
                + "]";
    }

}
