package org.gjs.java.common.util;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.security.DigestInputStream;
import java.security.MessageDigest;

import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.exception.GjsException;

/**
 * The Class CryptoUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Función para calcular el hash de una secuencia de bytes en base a diferentes algoritmos.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class CryptoUtil {

    /**
     * Clase no instanciable.
     */
    private CryptoUtil() {
        throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
    }

    /**
     * Hash.
     *
     * @param bytes
     *            the bytes
     * @param algorithm
     *            the algorithm: SHA, MD2, MD5, SHA-256, SHA-384...
     * @return the string
     * @throws GjsException
     *             the semilla util exception
     */
    public static String hash(byte[] bytes, String algorithm) throws GjsException {
        MessageDigest messageDigest;
        try {
            messageDigest = MessageDigest.getInstance(algorithm);
        } catch (final Exception e) {
            throw new GjsException(e);
        }

        try {
            final InputStream inputStream = new ByteArrayInputStream(bytes);
            try (DigestInputStream dis = new DigestInputStream(inputStream, messageDigest)) {
                while (dis.read() != -1) {
                    // empty loop to clear the data
                }
                messageDigest = dis.getMessageDigest();
            }
        } catch (

        final Exception e) {
            throw new GjsException(e);
        }
        // bytes to hex
        final StringBuilder result = new StringBuilder();
        for (final byte b : messageDigest.digest()) {
            result.append(String.format("%02x", b));
        }
        return result.toString();
    }

}
