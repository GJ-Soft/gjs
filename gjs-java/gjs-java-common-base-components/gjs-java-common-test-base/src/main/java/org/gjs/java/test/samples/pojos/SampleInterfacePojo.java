package org.gjs.java.test.samples.pojos;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleInterfacePojo.
 *
 * Clase de ejemplo de la librería Gjs
 *
 * Pojo que implementa ISample.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
public class SampleInterfacePojo implements ISample {

    private long id;
    private String nombre;

    @Override
    public boolean isValid() {
        return (id > 0);
    }

}
