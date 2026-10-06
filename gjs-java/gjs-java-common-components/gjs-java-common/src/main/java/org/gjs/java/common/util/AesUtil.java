package org.gjs.java.common.util;

import java.security.SecureRandom;
import java.util.Arrays;
import java.util.Base64;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import javax.crypto.Cipher;
import javax.crypto.spec.GCMParameterSpec;
import javax.crypto.spec.SecretKeySpec;

import org.apache.commons.lang3.ObjectUtils;
import org.gjs.java.common.constant.CommonBaseConstants;
import org.gjs.java.common.exception.GjsException;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class AesUtil.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Funciones de encriptación/desencriptación AES.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public final class AesUtil {

	/** The Constant encryptionCipher. */
	// IMPORTANTE: A causa de una vulnerabilidad con RSA, usamos el Optimal
	// Asymmetric Encryption Padding (OAEP)
	// private static final String encryptionCipher = "AES";
	private static final String ENCRYPTION_CYPHER = "AES/GCM/NoPadding";

	/** The Constant encryptionKey. */
	private static final String DEFAULT_ENCRYPTION_KEY = "0123456789abcdef";

	/** The Constant IV_LEN. */
	private static final int IV_LEN = 12;

	/** The Constant T_LEN. */
	private static final int T_LEN = 128;

	/** The class lock. */
	private static final Lock CLASS_LOCK = new ReentrantLock();

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(AesUtil.class);

	/**
	 * Clase no instanciable.
	 */
	private AesUtil() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	/**
	 * Encrypt long.
	 *
	 * @param plain the plain
	 * @return the string
	 * @throws GjsException the semilla util exception
	 */
	public static String encryptLong(Long plain) throws GjsException {
		final String plainString = (plain == null) ? null : String.valueOf(plain);
		return AesUtil.encrypt(plainString);
	}

	/**
	 * Encrypt string.
	 *
	 * @param plain the plain
	 * @return the string
	 * @throws GjsException the semilla util exception
	 */
	public static String encryptString(String plain) throws GjsException {
		return AesUtil.encrypt(plain);
	}

	/**
	 * Decrypt long.
	 *
	 * @param encrypted the encrypted
	 * @return the long
	 * @throws GjsException the semilla util exception
	 */
	public static Long decryptLong(String encrypted) throws GjsException {
		final String decrypted = (String) AesUtil.decrypt(encrypted);
		Long longValue = null;
		try {
			longValue = ConversionUtils.longValue(decrypted);
		} catch (final GjsException e) {
			logger.warn(e.getMessage());
		}
		return longValue;
	}

	/**
	 * Decrypt string.
	 *
	 * @param encrypted the encrypted
	 * @return the string
	 * @throws GjsException the semilla util exception
	 */
	public static String decryptString(String encrypted) throws GjsException {
		return (String) AesUtil.decrypt(encrypted);
	}

	/**
	 * Encrypt.
	 *
	 * @param plain the plain
	 * @return the string
	 * @throws GjsException the semilla util exception
	 */
	private static String encrypt(String plain) throws GjsException {
		return encrypt(plain, DEFAULT_ENCRYPTION_KEY);
	}

	/**
	 * Encrypt.
	 *
	 * @param plain         the plain
	 * @param encryptionKey the encryption key
	 * @return the string
	 * @throws GjsException the semilla util exception
	 */
	private static String encrypt(String plain, String encryptionKey) throws GjsException {
		if (ObjectUtils.anyNull(plain, encryptionKey)) {
			return null;
		}
		try {
			final SecureRandom random = SecureRandom.getInstanceStrong();
			final byte[] iv = new byte[IV_LEN];
			random.nextBytes(iv);

			final Cipher cipher = Cipher.getInstance(ENCRYPTION_CYPHER);
			final GCMParameterSpec ivSpec = new GCMParameterSpec(T_LEN, iv);
			final SecretKeySpec key = new SecretKeySpec(encryptionKey.getBytes(), "AES");
			cipher.init(Cipher.ENCRYPT_MODE, key, ivSpec);

			final byte[] ciphertext = cipher.doFinal(plain.getBytes());
			final byte[] encrypted = new byte[iv.length + ciphertext.length];
			System.arraycopy(iv, 0, encrypted, 0, iv.length);
			System.arraycopy(ciphertext, 0, encrypted, iv.length, ciphertext.length);

			// logger.debug("ENCRYPT IV={}", iv);
			// logger.debug("ENCRYPT CIPHER={}", ciphertext);
			// logger.debug("ENCRYPT ENCRYPTED={}", encrypted);
			String encryptedText = Base64.getEncoder().encodeToString(encrypted);
			encryptedText = encryptedText.replace('/', '_');
			return encryptedText;

		} catch (final Exception e) {
			throw new GjsException(e);
		}
	}

	/**
	 * Decrypt.
	 *
	 * @param encrypted the encrypted
	 * @return the object
	 * @throws GjsException the semilla util exception
	 */
	private static Object decrypt(String encrypted) throws GjsException {
		try {
			CLASS_LOCK.lock();
			return decrypt(encrypted, DEFAULT_ENCRYPTION_KEY);
		} finally {
			CLASS_LOCK.unlock();
		}
	}

	/**
	 * Decrypt.
	 *
	 * @param encrypted     the encrypted
	 * @param encryptionKey the encryption key
	 * @return the object
	 * @throws GjsException the semilla util exception
	 */
	private static Object decrypt(String encrypted, String encryptionKey) throws GjsException {
		if (ObjectUtils.anyNull(encrypted, encryptionKey)) {
			return null;
		}
		try {
			encrypted = encrypted.replace('_', '/');
			final byte[] decoded = Base64.getDecoder().decode(encrypted);
			final byte[] iv = Arrays.copyOfRange(decoded, 0, IV_LEN);
			final byte[] ciphertext = Arrays.copyOfRange(decoded, IV_LEN, decoded.length);

			final Cipher cipher = Cipher.getInstance(ENCRYPTION_CYPHER);
			final GCMParameterSpec ivSpec = new GCMParameterSpec(T_LEN, iv);
			final SecretKeySpec key = new SecretKeySpec(encryptionKey.getBytes(), "AES");
			cipher.init(Cipher.DECRYPT_MODE, key, ivSpec);

			// logger.debug("DECRYPT ENCRYPTED={}", decoded);
			// logger.debug("DECRYPT IV={}", iv);
			// logger.debug("DECRYPT CIPHER={}", ciphertext);
			final byte[] decryptedText = cipher.doFinal(ciphertext);
			return new String(decryptedText);
		} catch (final Exception e) {
			throw new GjsException(e);
		}
	}

}
