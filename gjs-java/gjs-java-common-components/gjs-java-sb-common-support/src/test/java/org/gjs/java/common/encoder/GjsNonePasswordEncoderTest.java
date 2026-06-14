package org.gjs.java.common.encoder;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.gjs.java.common.encoder.GjsNonePasswordEncoder;
import org.gjs.java.test.BaseUnitTest;
import org.junit.jupiter.api.Test;

public class GjsNonePasswordEncoderTest extends BaseUnitTest<GjsNonePasswordEncoder> {

	@Test
	public void testGjsNonePasswordEncoder() {
		final GjsNonePasswordEncoder encoder = new GjsNonePasswordEncoder();
		String plain = "T3mp0r4l";
		String encrypted = encoder.encode(plain);
		assertNotNull(encrypted);
		assertTrue(encoder.matches(plain, encrypted));
		assertFalse(encoder.matches("Other", encrypted));
		assertFalse(encoder.matches(plain, "Other"));
		assertFalse(encoder.matches(null, null));
		assertFalse(encoder.matches(plain, null));
		assertFalse(encoder.matches(null, encrypted));
		assertEquals(plain, encrypted);
		plain = null;
		encrypted = encoder.encode(plain);
		assertNull(encrypted);
		assertFalse(encoder.matches(plain, encrypted));
	}

}
