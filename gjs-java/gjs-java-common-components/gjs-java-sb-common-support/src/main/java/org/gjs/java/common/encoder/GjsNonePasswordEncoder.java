package org.gjs.java.common.encoder;

import java.util.Objects;

import org.apache.commons.lang3.ObjectUtils;
import org.springframework.security.crypto.password.PasswordEncoder;

/**
 * The Class SemillaNonePasswordEncoder.
 *
 * Clase de datos de la librería Gjs
 *
 * Implementa un PasswordEncoder que no codifica la contraseña. Se usa con SGU, donde la codificación de la constraseña
 * la realiza el sistema SGU.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class GjsNonePasswordEncoder implements PasswordEncoder {

    /**
     * Instantiates a new semilla password encoder.
     */
    public GjsNonePasswordEncoder() {
        // No hace nada
    }

    /* (non-Javadoc)
     *
     * @see org.springframework.security.crypto.password.PasswordEncoder#encode(java.lang.CharSequence) */

    @Override
    public String encode(CharSequence rawPassword) {
        String encrypted = null;
        if (Objects.nonNull(rawPassword)) {
            encrypted = rawPassword.toString();
        }
        return encrypted;
    }

    /* (non-Javadoc)
     *
     * @see org.springframework.security.crypto.password.PasswordEncoder#matches(java.lang.CharSequence,
     * java.lang.String) */

    @Override
    public boolean matches(CharSequence rawPassword, String encodedPassword) {
        boolean res = false;
        if (ObjectUtils.allNotNull(rawPassword, encodedPassword)) {
            res = encodedPassword.equals(rawPassword.toString());
        }
        return res;
    }

    /**
     * Checks if is valid.
     *
     * @return true, if is valid
     */
    public boolean isValid() {
        return true;
    }

}
