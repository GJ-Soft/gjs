package org.gjs.java.common.data;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.gjs.java.common.data.DataKey;
import org.gjs.java.common.data.ForeignKey;
import org.gjs.java.test.BaseClassTest;
import org.junit.jupiter.api.Test;

class ForeignKeyTest extends BaseClassTest<ForeignKey> {

	@Test
	void testForeignKey1() {
		final ForeignKey key = new ForeignKey();
		assertNull(key.getObjectName());
		key.setObjectName("object");
		assertNotNull(key.getObjectName());
		assertEquals(0, key.countFields());
		assertNotNull(key.getFields());
		assertNotNull(key.getRemoteFields());
		assertEquals(0, key.getFields().size());
		assertEquals(0, key.getRemoteFields().size());
		assertNull(key.getField(0));
		assertNull(key.getRemoteField(0));
		assertEquals("ForeignKey=[Key=[]--Key=[]]", key.toString());
		key.addField("field1");
		assertNotNull(key.getFields());
		assertNotNull(key.getRemoteFields());
		assertEquals(0, key.getFields().size());
		assertEquals(0, key.getRemoteFields().size());
		key.addField("field1", "remote1");
		assertNotNull(key.getField(0));
		assertNotNull(key.getRemoteField(0));
		assertEquals(1, key.countFields());
		assertNotNull(key.getFields());
		assertEquals(1, key.getFields().size());
		assertNotNull(key.getRemoteFields());
		assertEquals(1, key.getRemoteFields().size());
		assertTrue(key.existsField("field1"));
		assertFalse(key.existsField("fieldX"));
		assertFalse(key.existsField(null));
		assertNotNull(key.getField(0));
		assertEquals("field1", key.getField(0));
		assertNotNull(key.getRemoteField(0));
		assertEquals("remote1", key.getRemoteField(0));
		assertEquals("ForeignKey=[Key=[field1]--Key=[remote1]]", key.toString());
		key.addField(null, "remote2");
		assertEquals(1, key.countFields());
		key.addField("field2", null);
		assertEquals(1, key.countFields());
		key.addField("field1", "remote2");
		assertEquals(1, key.countFields());
		// El campo local ya estaba: no entra tampoco el remoto
		assertEquals(1, key.getRemoteFields().size());
		key.addField("field2", "remote2");
		assertEquals(2, key.countFields());
		assertNotNull(key.getField(0));
		assertEquals("field1", key.getField(0));
		assertNotNull(key.getField(1));
		assertEquals("field2", key.getField(1));
		assertNotNull(key.getRemoteField(0));
		assertEquals("remote1", key.getRemoteField(0));
		assertNotNull(key.getRemoteField(1));
		assertEquals("remote2", key.getRemoteField(1));
		assertEquals("ForeignKey=[Key=[field1, field2]--Key=[remote1, remote2]]", key.toString());
		// El remoto ya estaba: no entra tampoco el campo local
		key.addField("field3", "remote1");
		assertEquals(2, key.countFields());
		assertEquals(2, key.getRemoteFields().size());
		assertEquals("ForeignKey=[Key=[field1, field2]--Key=[remote1, remote2]]", key.toString());

		key.clear();
		assertEquals(0, key.countFields());
		assertNotNull(key.getFields());
		assertEquals(0, key.getFields().size());
	}

	@SuppressWarnings("unlikely-arg-type")
	@Test
	void testForeignKey2() {
		final ForeignKey key0 = null;
		final ForeignKey key1 = new ForeignKey();
		key1.addField("field1", "remote1");
		key1.addField("field2", "remote2");
		// Un campo menos
		final ForeignKey key2 = new ForeignKey();
		key2.addField("field1", "remote1");
		// Los mismos pares en el mismo orden
		final ForeignKey key3 = new ForeignKey();
		key3.addField("field1", "remote1");
		key3.addField("field2", "remote2");
		final String key4 = "aye";
		// Los mismos campos locales, pero con los remotos cruzados
		final ForeignKey key5 = new ForeignKey();
		key5.addField("field1", "remote2");
		key5.addField("field2", "remote1");
		// Los mismos pares en otro orden: la comparacion entre claves ajenas es posicional
		final ForeignKey key6 = new ForeignKey();
		key6.addField("field2", "remote2");
		key6.addField("field1", "remote1");
		// Contra una clave simple solo cuentan los campos locales, en cualquier orden
		final DataKey key7 = new DataKey("field2", "field1");
		final DataKey key8 = new DataKey("field1", "field3");
		assertTrue(key1.equals(key1));
		assertFalse(key1.equals(key0));
		assertFalse(key1.equals(key2));
		assertFalse(key2.equals(key1));
		assertTrue(key1.equals(key3));
		assertTrue(key3.equals(key1));
		assertEquals(key1.hashCode(), key3.hashCode());
		assertFalse(key1.equals(key4));
		assertFalse(key1.equals(key5));
		assertFalse(key1.equals(key6));
		assertTrue(key1.equals(key7));
		assertFalse(key1.equals(key8));
	}

	@Test
	void testForeignKey3() {
		final ForeignKey key = new ForeignKey(new DataKey("field1"), new DataKey("field2"));
		assertNull(key.getObjectName());
		assertNotNull(key.getField(0));
		assertNotNull(key.getRemoteField(0));
		assertEquals(1, key.countFields());
		assertNotNull(key.getFields());
		assertEquals(1, key.getFields().size());
		assertNotNull(key.getRemoteFields());
		assertEquals(1, key.getRemoteFields().size());
	}

	@Test
	void testForeignKey4() {
		final ForeignKey key = new ForeignKey("object", new DataKey("field1"), new DataKey("field2"));
		assertNotNull(key.getObjectName());
		assertNotNull(key.getField(0));
		assertNotNull(key.getRemoteField(0));
		assertEquals(1, key.countFields());
		assertNotNull(key.getFields());
		assertEquals(1, key.getFields().size());
		assertNotNull(key.getRemoteFields());
		assertEquals(1, key.getRemoteFields().size());
	}

	/**
	 * Regresion: con una clave nula, key.countFields() se evaluaba igual, como
	 * argumento de ConditionUtils.allAreTrue, y daba NullPointerException.
	 */
	@Test
	void testForeignKeyClaveNula() {
		final ForeignKey key = new ForeignKey(null, new DataKey("field2"));
		assertEquals(0, key.countFields());
		final ForeignKey remote = new ForeignKey(new DataKey("field1"), null);
		assertEquals(0, remote.countFields());
	}

}
