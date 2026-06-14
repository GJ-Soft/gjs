package org.gjs.java.common.encoder;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.gjs.java.common.encoder.GjsPasswordEncoder;
import org.gjs.java.test.BaseUnitTest;
import org.junit.jupiter.api.Test;
import org.springframework.security.crypto.password.Pbkdf2PasswordEncoder;

public class GjsPasswordEncoderTest extends BaseUnitTest<GjsPasswordEncoder> {

	@Test
	public void testGjsPasswordEncoder1() {
		final GjsPasswordEncoder encoder = new GjsPasswordEncoder(null);
		assertFalse(encoder.isValid());
		final String plain = "T3mp0r4l";
		String encrypted = encoder.encode(plain);
		assertNull(encrypted);
		encrypted = "3ce15cc3117c25d73d8c5a11afd0fad9a9e989d4b4ee68ae818057547d74234679f823a38a8d258c";
		assertFalse(encoder.matches(plain, encrypted));
	}

	@Test
	public void testGjsPasswordEncoder2() {
		final GjsPasswordEncoder encoder = new GjsPasswordEncoder(
				Pbkdf2PasswordEncoder.defaultsForSpringSecurity_v5_8());
		assertTrue(encoder.isValid());
		String encrypted = encoder.encode(null);
		assertNull(encrypted);
		final String plain = "T3mp0r4l";
		encrypted = encoder.encode(plain);
		assertNotNull(encrypted);
		logger.debug("{} : {}", plain, encrypted);
		assertTrue(encoder.matches(plain, encrypted));
		assertFalse(encoder.matches(null, null));
		assertFalse(encoder.matches(plain, null));
		assertFalse(encoder.matches(null, encrypted));
		assertFalse(encoder.matches(plain, "abcvddde"));
		assertFalse(encoder.matches(plain,
				"3ce15cc3117c25d73d8c5a11afd0fad9a9e989d4b5ee68ae818057547d74234679f823a38a8d258c"));
		assertFalse(encoder.matches("abcvddde", encrypted));
	}

	@Test
	public void testGjsPasswordEncoder3() {
		final GjsPasswordEncoder encoder = new GjsPasswordEncoder(null);
		assertFalse(encoder.isValid());
		final String plain = "Semilla1";
		String encrypted = encoder.encode(plain);
		assertNull(encrypted);
		encrypted = "3f8d43651e2755cfde168aafebf332df16bac4c8f04e5461905f8a538f753660382cbce2937515a3";
		assertFalse(encoder.matches(plain, encrypted));
	}

	@Test
	public void testGjsPasswordEncoder4() {
		final GjsPasswordEncoder encoder = new GjsPasswordEncoder(null);
		assertFalse(encoder.isValid());
		final String plain = "Semilla1_1";
		String encrypted = encoder.encode(plain);
		assertNull(encrypted);
		encrypted = "bbf83a39fca6cef7a5ae43d7d4710eccc648d7b7219ad2fc8e91d90d45012e21a8b915f30d3b86af";
		assertFalse(encoder.matches(plain, encrypted));
	}

}
