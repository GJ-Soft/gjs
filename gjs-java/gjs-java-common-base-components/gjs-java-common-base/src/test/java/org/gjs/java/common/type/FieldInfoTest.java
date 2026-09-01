package org.gjs.java.common.type;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertInstanceOf;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.lang.reflect.Field;
import java.lang.reflect.ParameterizedType;
import java.util.List;
import java.util.Set;

import org.gjs.java.test.BaseClassTest;
import org.gjs.java.test.samples.pojos.SampleCollectionsPojo;
import org.gjs.java.test.samples.pojos.SamplePojo;
import org.junit.jupiter.api.Test;

class FieldInfoTest extends BaseClassTest<FieldInfo> {

	@Test
	void testConstructorPorDefecto() throws NoSuchFieldException {
		final FieldInfo info = new FieldInfo();
		assertNull(info.getField());
		assertNull(info.getClazz());
		assertNull(info.getGenericClass());
		assertFalse(info.isFromGenericClass());

		final Field campo = SamplePojo.class.getDeclaredField("nombre");
		info.setField(campo);
		info.setClazz(String.class);
		assertEquals(campo, info.getField());
		assertEquals(String.class, info.getClazz());
		assertFalse(info.isFromGenericClass());
	}

	@Test
	void testConstructorSinGenerico() throws NoSuchFieldException {
		final Field campo = SamplePojo.class.getDeclaredField("id");
		final FieldInfo info = new FieldInfo(campo, long.class);

		assertEquals(campo, info.getField());
		assertEquals(long.class, info.getClazz());
		assertNull(info.getGenericClass());
		assertFalse(info.isFromGenericClass());
	}

	@Test
	void testConstructorConGenerico() throws NoSuchFieldException {
		final Field campo = SampleCollectionsPojo.class.getDeclaredField("ids");
		final FieldInfo info = new FieldInfo(campo, List.class, campo.getGenericType());

		assertEquals(campo, info.getField());
		assertEquals(List.class, info.getClazz());
		assertTrue(info.isFromGenericClass());

		final ParameterizedType generico = assertInstanceOf(ParameterizedType.class, info.getGenericClass());
		assertEquals(Long.class, generico.getActualTypeArguments()[0]);
	}

	@Test
	void testGenericoAsignadoYRetirado() throws NoSuchFieldException {
		final Field campo = SampleCollectionsPojo.class.getDeclaredField("nombres");
		final FieldInfo info = new FieldInfo(campo, Set.class);
		assertFalse(info.isFromGenericClass());

		info.setGenericClass(campo.getGenericType());
		assertTrue(info.isFromGenericClass());

		info.setGenericClass(null);
		assertFalse(info.isFromGenericClass());
	}

}
