package org.gjs.java.common.util;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.math.BigDecimal;
import java.sql.Timestamp;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.AbstractCollection;
import java.util.AbstractSet;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

import org.apache.commons.lang3.exception.ExceptionUtils;
import org.gjs.java.common.test.utils.AssertionUtils;
import org.gjs.java.common.type.FieldInfo;
import org.gjs.java.common.util.DateUtils;
import org.gjs.java.common.util.ReflectionUtils;
import org.gjs.java.test.BaseClassTest;
import org.gjs.java.test.samples.annotation.SampleAnnotation;
import org.gjs.java.test.samples.dto.SampleEntityDto;
import org.gjs.java.test.samples.pojos.ISample;
import org.gjs.java.test.samples.pojos.SampleAllTypesPojo;
import org.gjs.java.test.samples.pojos.SampleAnnotationClass;
import org.gjs.java.test.samples.pojos.SampleAnnotationField;
import org.gjs.java.test.samples.pojos.SampleArraysPojo;
import org.gjs.java.test.samples.pojos.SampleBoolean;
import org.gjs.java.test.samples.pojos.SampleCollectionsPojo;
import org.gjs.java.test.samples.pojos.SampleDerivedPojo;
import org.gjs.java.test.samples.pojos.SampleInterfaceDerivedPojo;
import org.gjs.java.test.samples.pojos.SampleInterfacePojo;
import org.gjs.java.test.samples.pojos.SampleLocalDatePojo;
import org.gjs.java.test.samples.pojos.SampleManagedArraysPojo;
import org.gjs.java.test.samples.pojos.SamplePojo;
import org.gjs.java.test.samples.pojos.SamplePojoClone;
import org.gjs.java.test.samples.pojos.SamplePojoConstructor;
import org.gjs.java.test.samples.pojos.SamplePojoFilter;
import org.gjs.java.test.samples.pojos.SamplePojoNativeClass;
import org.gjs.java.test.samples.pojos.SamplePojoNoUpdatables;
import org.gjs.java.test.samples.pojos.SamplePojoWithoutDefaultConstructor;
import org.gjs.java.test.samples.pojos.SampleWithoutMethodsPojo;
import org.gjs.java.test.samples.pojos.SampleWrapperPojo;
import org.junit.jupiter.api.Test;

class ReflectionUtilsTest extends BaseClassTest<ReflectionUtils> {

	@Test
	void testGetAllMethods() {
		try {
			List<Method> lista = ReflectionUtils.getAllMethods(SamplePojo.class);
			assertNotNull(lista);
			logger.debug("Metodos de la clase : {}", SamplePojo.class.getName());
			for (final Method method : lista) {
				logger.debug("Method: {}", method.getName());
			}
			assertEquals(8, lista.size());

			lista = ReflectionUtils.getAllMethods(SampleDerivedPojo.class);
			assertNotNull(lista);
			logger.debug("Metodos de la clase : {}", SampleDerivedPojo.class.getName());
			for (final Method method : lista) {
				logger.debug("Method: {}", method.getName());
			}
			assertEquals(12, lista.size());

			lista = ReflectionUtils.getAllMethods(SampleWithoutMethodsPojo.class);
			assertNotNull(lista);
			logger.debug("Metodos de la clase : {}", SampleWithoutMethodsPojo.class.getName());
			for (final Method method : lista) {
				logger.debug("Method: {}", method.getName());
			}
			assertEquals(4, lista.size());
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testHasMethod() {
		try {
			assertTrue(ReflectionUtils.hasMethod(SamplePojo.class, "compareTo"));
			assertFalse(ReflectionUtils.hasMethod(SamplePojo.class, "doSomething"));
			assertFalse(ReflectionUtils.hasMethod(SampleWithoutMethodsPojo.class, "compareTo"));
			assertFalse(ReflectionUtils.hasMethod(SampleWithoutMethodsPojo.class, "equals"));
			assertFalse(ReflectionUtils.hasMethod(SampleWithoutMethodsPojo.class, "hashCode"));
			assertFalse(ReflectionUtils.hasMethod(SampleWithoutMethodsPojo.class, "toString"));

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testFindGetter1() {
		try {
			assertNotNull(ReflectionUtils.findGetter(SamplePojo.class, "nombre"));
			assertNotNull(ReflectionUtils.findGetter(SamplePojo.class, "id"));
			assertNull(ReflectionUtils.findGetter(SamplePojo.class, "serialVersionUID"));

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testFindSetter1() {
		try {
			assertNotNull(ReflectionUtils.findSetter(SamplePojo.class, "nombre"));
			assertNotNull(ReflectionUtils.findSetter(SamplePojo.class, "id"));
			assertNull(ReflectionUtils.findSetter(SamplePojo.class, "serialVersionUID"));

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testFindMetod1() {
		try {
			assertNotNull(ReflectionUtils.findMethod(SamplePojo.class, "toString"));
			assertNotNull(ReflectionUtils.findMethod(SamplePojo.class, "equals"));
			assertNull(ReflectionUtils.findMethod(SamplePojo.class, "beWater"));

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testFindField1() {
		try {
			assertNotNull(ReflectionUtils.findField(SamplePojo.class, "nombre"));
			assertNotNull(ReflectionUtils.findField(SamplePojo.class, "id"));
			assertNull(ReflectionUtils.findField(SamplePojo.class, "serialVersionUID"));
			assertNull(ReflectionUtils.findField(SamplePojo.class, "tovarich"));

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testGetAllFields1() {
		try {
			List<FieldInfo> lista = ReflectionUtils.getAllFields(SamplePojo.class);
			assertNotNull(lista);
			logger.debug("Campos de la clase : {}", SamplePojo.class.getName());
			for (final FieldInfo field : lista) {
				logger.debug("Field: {}", field.getField().getName());
			}
			assertEquals(2, lista.size());
			assertEquals("id", lista.get(0).getField().getName());
			assertEquals("nombre", lista.get(1).getField().getName());

			lista = ReflectionUtils.getAllFields(SampleDerivedPojo.class);
			assertNotNull(lista);
			logger.debug("Campos de la clase : {}", SampleDerivedPojo.class.getName());
			for (final FieldInfo field : lista) {
				logger.debug("Field: {}", field.getField().getName());
			}
			assertEquals(4, lista.size());
			assertEquals("id", lista.get(0).getField().getName());
			assertEquals("nombre", lista.get(1).getField().getName());
			assertEquals("activo", lista.get(2).getField().getName());
			assertEquals("codigo", lista.get(3).getField().getName());

			lista = ReflectionUtils.getAllFields(SampleAllTypesPojo.class);
			assertNotNull(lista);
			logger.debug("Campos de la clase : {}", SampleDerivedPojo.class.getName());
			for (final FieldInfo field : lista) {
				logger.debug("Field: {} Primitive={}", field.getField().getName(),
						field.getField().getType().isPrimitive());
			}
			assertEquals(18, lista.size());

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testGetAllGetters1() {
		try {
			List<Method> lista = ReflectionUtils.getAllGetters(SamplePojo.class);
			assertNotNull(lista);
			logger.debug("Getters de la clase : {}", SamplePojo.class.getName());
			for (final Method method : lista) {
				logger.debug("Getter: {}", method.getName());
			}
			assertEquals(2, lista.size());
			assertEquals("getId", lista.get(0).getName());
			assertEquals("getNombre", lista.get(1).getName());

			lista = ReflectionUtils.getAllGetters(SampleDerivedPojo.class);
			assertNotNull(lista);
			logger.debug("Getters de la clase : {}", SampleDerivedPojo.class.getName());
			for (final Method method : lista) {
				logger.debug("Getter: {}", method.getName());
			}
			assertEquals(4, lista.size());
			assertEquals("getId", lista.get(0).getName());
			assertEquals("getNombre", lista.get(1).getName());
			assertEquals("isActivo", lista.get(2).getName());
			assertEquals("getCodigo", lista.get(3).getName());

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testHasField1() {
		try {
			assertFalse(ReflectionUtils.hasField(SamplePojo.class, null));
			assertTrue(ReflectionUtils.hasField(SamplePojo.class, "id"));
			assertTrue(ReflectionUtils.hasField(SamplePojo.class, "nombre"));
			assertFalse(ReflectionUtils.hasField(SamplePojo.class, "beWater"));

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testGetTypeName1() {
		try {
			List<FieldInfo> lista = ReflectionUtils.getAllFields(SamplePojo.class);
			assertNotNull(lista);
			logger.debug("Campos de la clase : {}", SamplePojo.class.getName());
			for (final FieldInfo field : lista) {
				final String typeName = ReflectionUtils.getTypeName(field.getField());
				assertNotNull(typeName);
				logger.debug("Field: {} => {}", field.getField().getName(), typeName);
			}
			lista = ReflectionUtils.getAllFields(SamplePojo.class);
			assertNotNull(lista);
			logger.debug("Campos de la clase : {}", SampleDerivedPojo.class.getName());
			for (final FieldInfo field : lista) {
				final String typeName = ReflectionUtils.getTypeName(field.getField());
				assertNotNull(typeName);
				logger.debug("Field: {} => {}", field.getField().getName(), typeName);
			}
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testSetFieldValue1() {
		try {
			final SamplePojo obj = new SamplePojo();
			final FieldInfo field = ReflectionUtils.findField(SamplePojo.class, "nombre");
			final String value = "NombrE";
			assertNull(obj.getNombre());
			ReflectionUtils.setFieldValue(obj, field.getField(), value);
			assertNotNull(obj.getNombre());
			assertEquals(value, obj.getNombre());

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testGetFieldValue1() {
		try {
			final SamplePojo obj = new SamplePojo();
			final String value = "NombrE";
			obj.setNombre(value);
			final FieldInfo field = ReflectionUtils.findField(SamplePojo.class, "nombre");
			assertNotNull(obj.getNombre());
			final Object res = ReflectionUtils.getFieldValue(obj, field.getField());
			assertNotNull(res);
			assertEquals(value, res);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testSetFieldValue2() {
		try {
			final SamplePojo obj = new SamplePojo();
			final String value = "NombrE";
			assertNull(obj.getNombre());
			ReflectionUtils.setFieldValue(obj, "nombre", value);
			assertNotNull(obj.getNombre());
			assertEquals(value, obj.getNombre());
			ReflectionUtils.setFieldValue(obj, "noexiste", value);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testGetFieldValue2() {
		try {
			final SamplePojo obj = new SamplePojo();
			final String value = "NombrE";
			obj.setNombre(value);
			assertNotNull(obj.getNombre());
			Object res = ReflectionUtils.getFieldValue(obj, "nombre");
			assertNotNull(res);
			assertEquals(value, res);
			res = ReflectionUtils.getFieldValue(obj, "noexiste");
			assertNull(res);
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testGetFieldValue3() {
		try {
			final SamplePojo obj = new SamplePojo();
			final String value = "NombrE";
			obj.setNombre(value);
			assertNotNull(obj.getNombre());
			Method getter = ReflectionUtils.findGetter(obj.getClass(), String.class, "Nombre");
			assertNotNull(getter);
			Object res = ReflectionUtils.getFieldValue(obj, getter);
			assertNotNull(res);
			assertEquals(value, res);
			getter = null;
			res = ReflectionUtils.getFieldValue(obj, getter);
			assertNull(res);
			getter = ReflectionUtils.findGetter(SamplePojoClone.class, String.class, "Nombre");
			res = ReflectionUtils.getFieldValue(obj, getter);
			assertNull(res);
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testSetFieldValue3() {
		try {
			final SampleLocalDatePojo obj = new SampleLocalDatePojo();
			final LocalDate value = LocalDate.now(ZoneId.systemDefault());
			assertNull(obj.getLocalDate());
			ReflectionUtils.setFieldValue(obj, "localDate", value);
			assertNotNull(obj.getLocalDate());
			assertEquals(value, obj.getLocalDate());

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testIsUpdatable1() {
		try {
			final FieldInfo field1 = ReflectionUtils.findField(SamplePojo.class, "nombre");
			assertTrue(ReflectionUtils.isUpdatable(field1.getField()));

			final FieldInfo field2 = ReflectionUtils.findField(SamplePojoNoUpdatables.class, "nombre");
			assertTrue(ReflectionUtils.isUpdatable(field2.getField()));

			final Field field3 = SamplePojoNoUpdatables.class.getDeclaredField("staticValue");
			assertFalse(ReflectionUtils.isUpdatable(field3));

			final FieldInfo field4 = ReflectionUtils.findField(SamplePojoNoUpdatables.class, "finalValue");
			assertTrue(ReflectionUtils.isUpdatable(field4.getField()));

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testFindConstructor1() {
		try {
			assertNull(ReflectionUtils.findConstructor(SamplePojo.class, SamplePojo.class.getCanonicalName()));
			assertNull(ReflectionUtils.findConstructor(SamplePojoConstructor.class, String.class.getCanonicalName()));
			assertNotNull(
					ReflectionUtils.findConstructor(SamplePojoConstructor.class, SamplePojo.class.getCanonicalName()));
			assertNotNull(ReflectionUtils.findConstructor(SamplePojoConstructor.class,
					SamplePojoConstructor.class.getCanonicalName()));

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone1() {
		try {
			final SamplePojoClone obj = new SamplePojoClone();
			obj.setId(1);
			obj.setNombre("NombrE");
			final SamplePojoClone copied = (SamplePojoClone) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			assertEquals(obj.getId(), copied.getId());
			assertEquals(obj.getNombre(), copied.getNombre());

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone2() {
		try {
			final SamplePojoConstructor obj = new SamplePojoConstructor();
			obj.setId(1);
			obj.setNombre("NombrE");
			final SamplePojoConstructor copied = (SamplePojoConstructor) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			assertEquals(obj.getId(), copied.getId());
			assertEquals(obj.getNombre(), copied.getNombre());

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone3() {
		try {
			final String obj1 = "NombrE";
			final String copied1 = (String) ReflectionUtils.clone(obj1);
			assertNotNull(copied1);
			assertEquals(obj1, copied1);

			final BigDecimal obj2 = BigDecimal.TEN;
			final BigDecimal copied2 = (BigDecimal) ReflectionUtils.clone(obj2);
			assertNotNull(copied2);
			assertEquals(obj2, copied2);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone4() {
		try {
			final SamplePojo obj = new SamplePojo();
			obj.setId(1);
			obj.setNombre("NombrE");
			final SamplePojo copied = (SamplePojo) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			logger.debug("Copiado {} a {}", obj, copied);
			assertEquals(obj.getId(), copied.getId());
			assertEquals(obj.getNombre(), copied.getNombre());

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone5() {
		try {
			final SamplePojoNativeClass obj = new SamplePojoNativeClass();
			obj.setId(Long.valueOf(1));
			obj.setNombre("NombrE");
			final SamplePojoNativeClass copied = (SamplePojoNativeClass) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			logger.debug("Copiado {} a {}", obj, copied);
			assertEquals(obj.getId(), copied.getId());
			assertEquals(obj.getNombre(), copied.getNombre());

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone6() {
		try {
			final Date obj1 = new Date();
			final Date copied1 = (Date) ReflectionUtils.clone(obj1);
			assertNotNull(copied1);
			assertEquals(obj1, copied1);

			final LocalDateTime obj2 = LocalDateTime.now(ZoneId.systemDefault());
			final LocalDateTime copied2 = (LocalDateTime) ReflectionUtils.clone(obj2);
			assertNotNull(copied2);
			assertEquals(obj2, copied2);

			final Timestamp obj3 = new Timestamp(obj1.getTime());
			final Timestamp copied3 = (Timestamp) ReflectionUtils.clone(obj3);
			assertNotNull(copied3);
			assertEquals(obj3, copied3);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone7() {
		try {
			List<Long> list = null;
			List<Long> copied = ReflectionUtils.clone(list);
			assertNull(copied);

			list = new LinkedList<>();
			copied = ReflectionUtils.clone(list);
			assertNotNull(copied);
			AssertionUtils.assertCollectionEquals(list, copied, "Lista vacia");

			list.add(Long.valueOf(1));
			list.add(Long.valueOf(2));
			copied = ReflectionUtils.clone(list);
			assertNotNull(copied);
			for (final Long item : copied) {
				logger.debug("Item={}", item);
			}
			AssertionUtils.assertCollectionEquals(list, copied, "Lista llena");

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone8() {
		try {
			Set<Long> set = null;
			Set<Long> copied = ReflectionUtils.clone(set);
			assertNull(copied);

			set = new HashSet<>();
			copied = ReflectionUtils.clone(set);
			assertNotNull(copied);
			AssertionUtils.assertCollectionEquals(set, copied, "Conjunto vacio");

			set.add(Long.valueOf(1));
			set.add(Long.valueOf(2));
			copied = ReflectionUtils.clone(set);
			assertNotNull(copied);
			AssertionUtils.assertCollectionEquals(set, copied, "Conjunto lleno");

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone9() {
		try {
			Map<String, String> map = null;
			Map<String, String> copied = ReflectionUtils.clone(map);
			assertNull(copied);

			map = new TreeMap<>();
			copied = ReflectionUtils.clone(map);
			assertNotNull(copied);
			AssertionUtils.assertCollectionEquals(map, copied, "Mapa vacio");

			map.put("1", "Valor1");
			map.put("2", "Valor2");
			copied = ReflectionUtils.clone(map);
			assertNotNull(copied);
			AssertionUtils.assertCollectionEquals(map, copied, "Conjunto lleno");

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone10() {
		try {
			final List<Long> ids = new ArrayList<>();
			final Set<String> nombres = new TreeSet<>();
			final Map<String, SamplePojo> objetos = new HashMap<>();
			final SampleCollectionsPojo obj = new SampleCollectionsPojo();
			SampleCollectionsPojo copied = (SampleCollectionsPojo) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			AssertionUtils.assertCollectionEquals(obj.getIds(), copied.getIds(), "Ids");
			AssertionUtils.assertCollectionEquals(obj.getNombres(), copied.getNombres(),
					"Nombre");
			AssertionUtils.assertCollectionEquals(obj.getObjetos(), copied.getObjetos(),
					"Objetos nulos");

			obj.setIds(ids);
			obj.setNombres(nombres);
			obj.setObjetos(objetos);
			copied = (SampleCollectionsPojo) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			AssertionUtils.assertCollectionEquals(obj.getIds(), copied.getIds(), "Ids");
			AssertionUtils.assertCollectionEquals(obj.getNombres(), copied.getNombres(),
					"Nombre");
			AssertionUtils.assertCollectionEquals(obj.getObjetos(), copied.getObjetos(),
					"Objetos vacios");

			ids.add(Long.valueOf(1));
			ids.add(Long.valueOf(2));
			nombres.add("nombre1");
			objetos.put("key1", new SamplePojo(1, "objeto1"));
			objetos.put("key2", new SamplePojo(1, "objeto2"));
			copied = (SampleCollectionsPojo) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			AssertionUtils.assertCollectionEquals(obj.getIds(), copied.getIds(), "Ids");
			AssertionUtils.assertCollectionEquals(obj.getNombres(), copied.getNombres(),
					"Nombre");
			AssertionUtils.assertCollectionEquals(obj.getObjetos(), copied.getObjetos(),
					"Objetos llenos");

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone11() {
		try {
			final SampleArraysPojo obj = new SampleArraysPojo(new boolean[] {}, new short[] {}, new int[] {},
					new long[] {}, new char[] {}, new double[] {}, new float[] {}, new Boolean[] {}, new Short[] {},
					new Integer[] {}, new Long[] {}, new Character[] {}, new Double[] {}, new Float[] {},
					new String[] {}, new BigDecimal[] {}, new Date[] {}, new byte[] {}, new Byte[] {});
			assertNotNull(obj.getBoolVal());
			assertNotNull(obj.getSiVal());
			assertNotNull(obj.getIntVal());
			assertNotNull(obj.getLonVal());
			assertNotNull(obj.getCarVal());
			assertNotNull(obj.getDouVal());
			assertNotNull(obj.getFloVal());
			assertNotNull(obj.getObVal());
			assertNotNull(obj.getOsiVal());
			assertNotNull(obj.getOiVal());
			assertNotNull(obj.getOlVal());
			assertNotNull(obj.getOcVal());
			assertNotNull(obj.getOdVal());
			assertNotNull(obj.getOfVal());
			assertNotNull(obj.getStrVal());
			assertNotNull(obj.getDecVal());
			assertNotNull(obj.getDatVal());
			assertNotNull(obj.getByVal());
			assertNotNull(obj.getObyVal());
			final SampleArraysPojo copied = (SampleArraysPojo) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			logger.debug("Copiado {} a {}", obj, copied);
			assertNotNull(copied.getBoolVal());
			assertNotNull(copied.getSiVal());
			assertNotNull(copied.getIntVal());
			assertNotNull(copied.getLonVal());
			assertNotNull(copied.getCarVal());
			assertNotNull(copied.getDouVal());
			assertNotNull(copied.getFloVal());
			assertNotNull(copied.getObVal());
			assertNotNull(copied.getOsiVal());
			assertNotNull(copied.getOiVal());
			assertNotNull(copied.getOlVal());
			assertNotNull(copied.getOcVal());
			assertNotNull(copied.getOdVal());
			assertNotNull(copied.getOfVal());
			assertNotNull(copied.getStrVal());
			assertNotNull(copied.getDecVal());
			assertNotNull(copied.getDatVal());
			assertNotNull(copied.getByVal());
			assertNotNull(copied.getObyVal());

			assertEquals(obj.getIntVal().length, copied.getIntVal().length);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone12() {
		try {
			final SampleManagedArraysPojo obj = new SampleManagedArraysPojo(new String[] {}, new Date[] {},
					new BigDecimal[] {});
			assertNotNull(obj.getStrings());
			assertNotNull(obj.getDates());
			assertNotNull(obj.getBigDecimals());
			final SampleManagedArraysPojo copied = (SampleManagedArraysPojo) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			logger.debug("Copiado {} a {}", obj, copied);
			assertNotNull(copied.getStrings());
			assertNotNull(copied.getDates());
			assertNotNull(copied.getDates());

			assertEquals(obj.getStrings().length, copied.getStrings().length);
			assertEquals(obj.getDates().length, copied.getDates().length);
			assertEquals(obj.getDates().length, copied.getDates().length);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone13() {
		try {
			final SampleArraysPojo obj = new SampleArraysPojo(new boolean[] { true }, new short[] { 3 },
					new int[] { 0, 3, 2 }, new long[] { 15, -1 }, new char[] { 'a', 'b' },
					new double[] { -0.01, 2.004 }, new float[] { (float) 0.0 },
					new Boolean[] { Boolean.TRUE, Boolean.FALSE }, new Short[] { Short.valueOf((short) 0) },
					new Integer[] { Integer.valueOf(1) }, new Long[] { Long.valueOf(-4) }, new Character[] {},
					new Double[] {}, new Float[] {}, new String[] { "1", "2" }, new BigDecimal[] { BigDecimal.ONE },
					new Date[] { new Date() }, new byte[] { 0, 1, 0 }, new Byte[] { Byte.valueOf((byte) 1) });
			assertNotNull(obj.getBoolVal());
			assertNotNull(obj.getSiVal());
			assertNotNull(obj.getIntVal());
			assertNotNull(obj.getLonVal());
			assertNotNull(obj.getCarVal());
			assertNotNull(obj.getDouVal());
			assertNotNull(obj.getFloVal());
			assertNotNull(obj.getObVal());
			assertNotNull(obj.getOsiVal());
			assertNotNull(obj.getOiVal());
			assertNotNull(obj.getOlVal());
			assertNotNull(obj.getOcVal());
			assertNotNull(obj.getOdVal());
			assertNotNull(obj.getOfVal());
			assertNotNull(obj.getStrVal());
			assertNotNull(obj.getDecVal());
			assertNotNull(obj.getDatVal());
			assertNotNull(obj.getByVal());
			assertNotNull(obj.getObyVal());
			final SampleArraysPojo copied = (SampleArraysPojo) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			logger.debug("Copiado {} a {}", obj, copied);
			assertNotNull(copied.getBoolVal());
			assertNotNull(copied.getSiVal());
			assertNotNull(copied.getIntVal());
			assertNotNull(copied.getLonVal());
			assertNotNull(copied.getCarVal());
			assertNotNull(copied.getDouVal());
			assertNotNull(copied.getFloVal());
			assertNotNull(copied.getObVal());
			assertNotNull(copied.getOsiVal());
			assertNotNull(copied.getOiVal());
			assertNotNull(copied.getOlVal());
			assertNotNull(copied.getOcVal());
			assertNotNull(copied.getOdVal());
			assertNotNull(copied.getOfVal());
			assertNotNull(copied.getStrVal());
			assertNotNull(copied.getDecVal());
			assertNotNull(copied.getDatVal());
			assertNotNull(copied.getByVal());
			assertNotNull(copied.getObyVal());

			assertEquals(obj.getIntVal().length, copied.getIntVal().length);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone14() {
		try {
			final SampleManagedArraysPojo obj = new SampleManagedArraysPojo(new String[] { "1", "2" },
					new Date[] { DateUtils.yesterday(), DateUtils.today(), DateUtils.tomorrow() },
					new BigDecimal[] { BigDecimal.ZERO, BigDecimal.ONE });
			assertNotNull(obj.getStrings());
			assertNotNull(obj.getDates());
			assertNotNull(obj.getBigDecimals());
			final SampleManagedArraysPojo copied = (SampleManagedArraysPojo) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			logger.debug("Copiado {} a {}", obj, copied);
			assertNotNull(copied.getStrings());
			assertNotNull(copied.getDates());
			assertNotNull(copied.getDates());

			assertEquals(obj.getStrings().length, copied.getStrings().length);
			assertEquals(obj.getDates().length, copied.getDates().length);
			assertEquals(obj.getDates().length, copied.getDates().length);

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone15() {
		try {
			final SampleWrapperPojo obj = new SampleWrapperPojo(1, "NombrE");
			final SampleWrapperPojo copied = (SampleWrapperPojo) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			logger.debug("Copiado {} a {}", obj, copied);
			assertNotNull(copied.getPojo());
			assertEquals(obj.getPojo().getId(), copied.getPojo().getId());
			assertEquals(obj.getPojo().getNombre(), copied.getPojo().getNombre());

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testClone16() {
		try {
			final SampleWrapperPojo obj = new SampleWrapperPojo();
			final SampleWrapperPojo copied = (SampleWrapperPojo) ReflectionUtils.clone(obj);
			assertNotNull(copied);
			logger.debug("Copiado {} a {}", obj, copied);
			assertNull(copied.getPojo());

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testMeetsFilter1() {
		try {
			final SamplePojoFilter obj00 = null;
			final SamplePojoFilter obj0 = new SamplePojoFilter();
			final SamplePojoFilter obj1 = new SamplePojoFilter(Long.valueOf(1), "nombre1", Boolean.TRUE);
			final SamplePojoFilter obj2 = new SamplePojoFilter(Long.valueOf(2), "nombre de test", Boolean.FALSE);
			final SamplePojoFilter obj3 = new SamplePojoFilter(Long.valueOf(3), "test nombre", null);
			final SamplePojoFilter filter00 = null;
			final SamplePojoFilter filter0 = new SamplePojoFilter();
			final SamplePojoFilter filter1 = new SamplePojoFilter(Long.valueOf(1), null, null);
			final SamplePojoFilter filter2 = new SamplePojoFilter(null, "nomb%", null);
			final SamplePojoFilter filter3 = new SamplePojoFilter(null, "%test", null);
			final SamplePojoFilter filter4 = new SamplePojoFilter(null, "%de %", null);
			final SamplePojoFilter filter5 = new SamplePojoFilter(null, null, Boolean.TRUE);

			assertTrue(ReflectionUtils.meetsFilter(obj00, filter00));
			assertTrue(ReflectionUtils.meetsFilter(obj0, filter00));
			assertTrue(ReflectionUtils.meetsFilter(obj1, filter00));
			assertFalse(ReflectionUtils.meetsFilter(obj00, filter0));
			assertTrue(ReflectionUtils.meetsFilter(obj0, filter0));
			assertTrue(ReflectionUtils.meetsFilter(obj1, filter0));

			assertTrue(ReflectionUtils.meetsFilter(obj1, filter1));
			assertFalse(ReflectionUtils.meetsFilter(obj2, filter1));
			assertFalse(ReflectionUtils.meetsFilter(obj3, filter1));
			assertTrue(ReflectionUtils.meetsFilter(obj1, filter2));
			assertTrue(ReflectionUtils.meetsFilter(obj2, filter2));
			assertTrue(ReflectionUtils.meetsFilter(obj3, filter2));
			assertFalse(ReflectionUtils.meetsFilter(obj1, filter3));
			assertTrue(ReflectionUtils.meetsFilter(obj2, filter3));
			assertTrue(ReflectionUtils.meetsFilter(obj3, filter3));
			assertFalse(ReflectionUtils.meetsFilter(obj1, filter4));
			assertTrue(ReflectionUtils.meetsFilter(obj2, filter4));
			assertFalse(ReflectionUtils.meetsFilter(obj3, filter4));
			assertTrue(ReflectionUtils.meetsFilter(obj1, filter5));
			assertFalse(ReflectionUtils.meetsFilter(obj2, filter5));
			assertFalse(ReflectionUtils.meetsFilter(obj3, filter5));
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testMeetsFilter2() {
		try {
			final SamplePojo obj0 = new SamplePojo();
			final SamplePojo obj1 = new SamplePojo(1, "nombre1");
			final SamplePojo obj2 = new SamplePojo(2, "nombre de test");
			final SamplePojo filter0 = new SamplePojo();
			final SamplePojo filter1 = new SamplePojo(1, null);
			final SamplePojo filter2 = new SamplePojo(1, "nomb%");
			final SamplePojo filter3 = new SamplePojo(2, "%test");
			final SamplePojo filter4 = new SamplePojo(2, "nombre1");

			assertTrue(ReflectionUtils.meetsFilter(obj0, filter0));
			assertTrue(ReflectionUtils.meetsFilter(obj1, filter0));

			assertTrue(ReflectionUtils.meetsFilter(obj1, filter1));
			assertTrue(ReflectionUtils.meetsFilter(obj2, filter1));
			assertTrue(ReflectionUtils.meetsFilter(obj1, filter2));
			assertTrue(ReflectionUtils.meetsFilter(obj2, filter2));
			assertFalse(ReflectionUtils.meetsFilter(obj1, filter3));
			assertTrue(ReflectionUtils.meetsFilter(obj2, filter3));
			assertTrue(ReflectionUtils.meetsFilter(obj1, filter4));
			assertFalse(ReflectionUtils.meetsFilter(obj2, filter4));
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testGetId() {
		try {
			final SampleBoolean sample0 = new SampleBoolean();
			final SamplePojo sample1 = new SamplePojo(1, "Test");
			final SamplePojoNativeClass sample2 = new SamplePojoNativeClass(Long.valueOf(1), "Test");
			final SamplePojo sample3 = new SamplePojo();
			final SamplePojoNativeClass sample4 = new SamplePojoNativeClass();

			Object id = ReflectionUtils.getId(sample0, SampleBoolean.class, Long.class);
			assertNull(id);
			id = ReflectionUtils.getId(sample1, SampleBoolean.class, long.class);
			assertNull(id);
			id = ReflectionUtils.getId(sample1, SamplePojo.class, long.class);
			assertNotNull(id);
			assertEquals(1, (long) id);
			id = ReflectionUtils.getId(sample2, SamplePojoNativeClass.class, Long.class);
			assertNotNull(id);
			assertTrue(id instanceof Long);
			assertEquals(Long.valueOf(1), (Long) id);
			id = ReflectionUtils.getId(sample3, SamplePojo.class, long.class);
			assertNotNull(id);
			assertEquals(0, (long) id);
			id = ReflectionUtils.getId(sample4, SamplePojoNativeClass.class, Long.class);
			assertNull(id);
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testSetId() {
		try {
			final SampleBoolean sample0 = new SampleBoolean();
			final SamplePojo sample1 = new SamplePojo(1, "Test");
			final SamplePojoNativeClass sample2 = new SamplePojoNativeClass(Long.valueOf(1), "Test");

			final long id = 9;
			ReflectionUtils.setId(sample0, id, SampleBoolean.class);

			ReflectionUtils.setId(sample1, id, SampleBoolean.class);
			assertEquals(1, sample1.getId());

			ReflectionUtils.setId(sample1, id, SamplePojo.class);
			assertEquals(9, sample1.getId());

			ReflectionUtils.setId(sample2, Long.valueOf(id), SamplePojoNativeClass.class);
			assertNotNull(sample2.getId());
			assertEquals(Long.valueOf(9), sample2.getId());

			ReflectionUtils.setId(sample2, null, SamplePojoNativeClass.class);
			assertNull(sample2.getId());
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testHasAnnotation1() {
		try {
			String annotation = null;
			assertFalse(ReflectionUtils.hasAnnotation(SamplePojo.class, annotation));
			annotation = "xxx";
			assertFalse(ReflectionUtils.hasAnnotation(SamplePojo.class, annotation));
			annotation = SampleAnnotation.class.getCanonicalName();
			assertFalse(ReflectionUtils.hasAnnotation(SamplePojo.class, annotation));
			assertTrue(ReflectionUtils.hasAnnotation(SampleAnnotationClass.class, annotation));
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testHasAnnotation2() {
		try {
			String field = null;
			String annotation = null;
			assertFalse(ReflectionUtils.hasAnnotation(SamplePojo.class, field, annotation));
			field = "xxx";
			assertFalse(ReflectionUtils.hasAnnotation(SamplePojo.class, field, annotation));
			field = "id";
			assertFalse(ReflectionUtils.hasAnnotation(SamplePojo.class, field, annotation));
			annotation = "xxx";
			assertFalse(ReflectionUtils.hasAnnotation(SamplePojo.class, field, annotation));
			annotation = SampleAnnotation.class.getCanonicalName();
			assertFalse(ReflectionUtils.hasAnnotation(SamplePojo.class, field, annotation));
			assertTrue(ReflectionUtils.hasAnnotation(SampleAnnotationField.class, field, annotation));
			field = "nombre";
			assertFalse(ReflectionUtils.hasAnnotation(SampleAnnotationField.class, field, annotation));
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testGetAllClasses1() {
		try {
			List<String> lista = ReflectionUtils.getAllClasses(Object.class);
			assertNotNull(lista);
			assertEquals(1, lista.size());
			assertNotNull(lista.get(0));
			assertEquals(Object.class.getCanonicalName(), lista.get(0));

			lista = ReflectionUtils.getAllClasses(SamplePojo.class);
			assertNotNull(lista);
			logger.debug("Clases de: {}", SamplePojo.class.getName());
			for (final String className : lista) {
				logger.debug("Clase: {}", className);
			}
			assertEquals(1, lista.size());
			assertNotNull(lista.get(0));
			assertEquals(SamplePojo.class.getCanonicalName(), lista.get(0));

			lista = ReflectionUtils.getAllClasses(SampleDerivedPojo.class);
			assertNotNull(lista);
			logger.debug("Clases de: {}", SamplePojo.class.getName());
			for (final String className : lista) {
				logger.debug("Clase: {}", className);
			}
			assertEquals(2, lista.size());
			assertNotNull(lista.get(0));
			assertEquals(SampleDerivedPojo.class.getCanonicalName(), lista.get(0));
			assertNotNull(lista.get(1));
			assertEquals(SamplePojo.class.getCanonicalName(), lista.get(1));
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testGetAllClasses2() {
		try {
			List<String> lista = ReflectionUtils.getAllClasses((String) null);
			assertNotNull(lista);
			assertEquals(0, lista.size());
			lista = ReflectionUtils.getAllClasses("");
			assertNotNull(lista);
			assertEquals(0, lista.size());
			lista = ReflectionUtils.getAllClasses("com.gandalf.Noexiste");
			assertNotNull(lista);
			assertEquals(0, lista.size());

			lista = ReflectionUtils.getAllClasses(Object.class.getCanonicalName());
			assertNotNull(lista);
			assertEquals(1, lista.size());
			assertNotNull(lista.get(0));
			assertEquals(Object.class.getCanonicalName(), lista.get(0));

			lista = ReflectionUtils.getAllClasses(SamplePojo.class.getCanonicalName());
			assertNotNull(lista);
			logger.debug("Clases de: {}", SamplePojo.class.getName());
			for (final String className : lista) {
				logger.debug("Clase: {}", className);
			}
			assertEquals(1, lista.size());
			assertNotNull(lista.get(0));
			assertEquals(SamplePojo.class.getCanonicalName(), lista.get(0));

			lista = ReflectionUtils.getAllClasses(SampleDerivedPojo.class.getCanonicalName());
			assertNotNull(lista);
			logger.debug("Clases de: {}", SamplePojo.class.getName());
			for (final String className : lista) {
				logger.debug("Clase: {}", className);
			}
			assertEquals(2, lista.size());
			assertNotNull(lista.get(0));
			assertEquals(SampleDerivedPojo.class.getCanonicalName(), lista.get(0));
			assertNotNull(lista.get(1));
			assertEquals(SamplePojo.class.getCanonicalName(), lista.get(1));
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testGetAllInterfaces1() {
		try {
			List<String> lista = ReflectionUtils.getAllInterfaces(Object.class);
			assertNotNull(lista);
			assertEquals(0, lista.size());
			lista = ReflectionUtils.getAllInterfaces(SamplePojo.class);
			assertEquals(1, lista.size());
			assertNotNull(lista.get(0));
			assertEquals(Comparable.class.getCanonicalName(), lista.get(0));

			lista = ReflectionUtils.getAllInterfaces(SampleInterfacePojo.class);
			assertNotNull(lista);
			logger.debug("Interfaces de: {}", SampleInterfacePojo.class.getName());
			for (final String className : lista) {
				logger.debug("Interfaces: {}", className);
			}
			assertEquals(1, lista.size());
			assertNotNull(lista.get(0));
			assertEquals(ISample.class.getCanonicalName(), lista.get(0));

			lista = ReflectionUtils.getAllInterfaces(SampleInterfaceDerivedPojo.class);
			assertNotNull(lista);
			logger.debug("Interfaces de: {}", SampleInterfaceDerivedPojo.class.getName());
			for (final String className : lista) {
				logger.debug("Interfaces: {}", className);
			}
			assertEquals(1, lista.size());
			assertNotNull(lista.get(0));
			assertEquals(ISample.class.getCanonicalName(), lista.get(0));
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testGetAllInterfaces2() {
		try {
			List<String> lista = ReflectionUtils.getAllInterfaces((String) null);
			assertNotNull(lista);
			assertEquals(0, lista.size());
			lista = ReflectionUtils.getAllInterfaces("");
			assertNotNull(lista);
			assertEquals(0, lista.size());
			lista = ReflectionUtils.getAllInterfaces("com.gandalf.Noexiste");
			assertNotNull(lista);
			assertEquals(0, lista.size());

			lista = ReflectionUtils.getAllInterfaces(Object.class.getCanonicalName());
			assertNotNull(lista);
			assertEquals(0, lista.size());

			lista = ReflectionUtils.getAllInterfaces(SampleInterfacePojo.class.getCanonicalName());
			assertNotNull(lista);
			assertEquals(1, lista.size());
			assertNotNull(lista.get(0));
			assertEquals(ISample.class.getCanonicalName(), lista.get(0));

			lista = ReflectionUtils.getAllInterfaces(SampleInterfaceDerivedPojo.class.getCanonicalName());
			assertNotNull(lista);
			assertEquals(1, lista.size());
			assertNotNull(lista.get(0));
			assertEquals(ISample.class.getCanonicalName(), lista.get(0));

		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testIsInstanceOf1() {
		try {
			assertFalse(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class, null));
			assertFalse(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class, ""));
			assertFalse(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class, "com.gandalf.Noexiste"));
			assertTrue(ReflectionUtils.isInstanceOf(Object.class, Object.class.getCanonicalName()));
			assertTrue(ReflectionUtils.isInstanceOf(SamplePojo.class, Object.class.getCanonicalName()));
			assertTrue(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class, Object.class.getCanonicalName()));
			assertTrue(ReflectionUtils.isInstanceOf(SamplePojo.class, Object.class.getCanonicalName()));
			assertTrue(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class, SamplePojo.class.getCanonicalName()));
			assertFalse(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class, String.class.getCanonicalName()));
			assertFalse(ReflectionUtils.isInstanceOf(HashSet.class, List.class.getCanonicalName()));
			assertFalse(ReflectionUtils.isInstanceOf(HashSet.class, Set.class.getCanonicalName()));
			assertTrue(ReflectionUtils.isInstanceOf(HashSet.class, AbstractSet.class.getCanonicalName()));
			assertTrue(ReflectionUtils.isInstanceOf(HashSet.class, AbstractCollection.class.getCanonicalName()));
		} catch (final Exception e) {
			logger.error(ExceptionUtils.getStackTrace(e));
			fail("Recibida excepcion");
		}
	}

	@Test
	void testIsInstanceOf2() {
		// try {
		assertFalse(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class.getCanonicalName(), null));
		assertFalse(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class.getCanonicalName(), ""));
		assertFalse(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class.getCanonicalName(), "com.gandalf.Noexiste"));
		assertFalse(ReflectionUtils.isInstanceOf((String) null, Object.class.getCanonicalName()));
		assertFalse(ReflectionUtils.isInstanceOf("", Object.class.getCanonicalName()));
		assertFalse(ReflectionUtils.isInstanceOf("com.gandalf.Noexiste", Object.class.getCanonicalName()));

		assertTrue(ReflectionUtils.isInstanceOf(Object.class.getCanonicalName(), Object.class.getCanonicalName()));
		assertTrue(ReflectionUtils.isInstanceOf(SamplePojo.class.getCanonicalName(), Object.class.getCanonicalName()));
		assertTrue(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class.getCanonicalName(),
				Object.class.getCanonicalName()));
		assertTrue(ReflectionUtils.isInstanceOf(SamplePojo.class.getCanonicalName(), Object.class.getCanonicalName()));
		assertTrue(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class.getCanonicalName(),
				SamplePojo.class.getCanonicalName()));
		assertFalse(ReflectionUtils.isInstanceOf(SampleDerivedPojo.class.getCanonicalName(),
				String.class.getCanonicalName()));
		assertFalse(ReflectionUtils.isInstanceOf(HashSet.class.getCanonicalName(), List.class.getCanonicalName()));
		assertFalse(ReflectionUtils.isInstanceOf(HashSet.class.getCanonicalName(), Set.class.getCanonicalName()));
		assertTrue(
				ReflectionUtils.isInstanceOf(HashSet.class.getCanonicalName(), AbstractSet.class.getCanonicalName()));
		assertTrue(ReflectionUtils.isInstanceOf(HashSet.class.getCanonicalName(),
				AbstractCollection.class.getCanonicalName()));
		// } catch (final Exception e) {
		// logger.error(e.getMessage(), e);
		// fail("Recibida excepcion");
		// }
	}

	@Test
	void testIsInterfaceOf1() {
		try {
			assertFalse(ReflectionUtils.implementsInterface(SamplePojo.class, null));
			assertFalse(ReflectionUtils.implementsInterface(SamplePojo.class, ""));
			assertFalse(ReflectionUtils.implementsInterface(SamplePojo.class, "com.gandalf.Noexiste"));
			assertFalse(ReflectionUtils.implementsInterface(SamplePojo.class, ISample.class.getCanonicalName()));
			assertTrue(
					ReflectionUtils.implementsInterface(SampleInterfacePojo.class, ISample.class.getCanonicalName()));
			assertTrue(ReflectionUtils.implementsInterface(SampleInterfaceDerivedPojo.class,
					ISample.class.getCanonicalName()));
			assertFalse(ReflectionUtils.implementsInterface(HashSet.class, List.class.getCanonicalName()));
			assertTrue(ReflectionUtils.implementsInterface(HashSet.class, Set.class.getCanonicalName()));
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testIsInterfaceOf2() {
		try {
			assertFalse(ReflectionUtils.implementsInterface(SamplePojo.class.getCanonicalName(), null));
			assertFalse(ReflectionUtils.implementsInterface(SamplePojo.class.getCanonicalName(), ""));
			assertFalse(
					ReflectionUtils.implementsInterface(SamplePojo.class.getCanonicalName(), "com.gandalf.Noexiste"));
			assertFalse(ReflectionUtils.implementsInterface(SamplePojo.class.getCanonicalName(),
					ISample.class.getCanonicalName()));
			assertTrue(ReflectionUtils.implementsInterface(SampleInterfacePojo.class.getCanonicalName(),
					ISample.class.getCanonicalName()));
			assertTrue(ReflectionUtils.implementsInterface(SampleInterfaceDerivedPojo.class.getCanonicalName(),
					ISample.class.getCanonicalName()));
			assertFalse(ReflectionUtils.implementsInterface(HashSet.class.getCanonicalName(),
					List.class.getCanonicalName()));
			assertTrue(ReflectionUtils.implementsInterface(HashSet.class.getCanonicalName(),
					Set.class.getCanonicalName()));
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testHasDefaultConstuctor() {
		try {
			assertFalse(ReflectionUtils
					.hasDefaultConstructor(SamplePojoWithoutDefaultConstructor.class.getCanonicalName()));
			assertTrue(ReflectionUtils.hasDefaultConstructor(SamplePojo.class.getCanonicalName()));
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testFillObject1() {
		final SampleEntityDto obj = null;
		final Map<String, Object> values = null;
		try {
			ReflectionUtils.fillObject(obj, values);
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testFillObject2() {
		final SampleEntityDto obj = new SampleEntityDto();
		final Map<String, Object> values = null;
		try {
			ReflectionUtils.fillObject(obj, values);
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testFillObject3() {
		final SampleEntityDto obj = new SampleEntityDto();
		final Map<String, Object> values = new HashMap<>();
		try {
			ReflectionUtils.fillObject(obj, values);
			assertNull(obj.getId());
			assertNull(obj.getNombre());
			assertNull(obj.getActivo());
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

	@Test
	void testFillObject4() {
		final SampleEntityDto obj = new SampleEntityDto();
		final Map<String, Object> values = new HashMap<>();
		values.put("id", Long.valueOf(1));
		values.put("nombre", "Nombre");
		values.put("activo", Boolean.TRUE);
		try {
			ReflectionUtils.fillObject(obj, values);
			assertNotNull(obj.getId());
			assertNotNull(obj.getNombre());
			assertNotNull(obj.getActivo());
			assertEquals(Long.valueOf(1), obj.getId());
			assertEquals("Nombre", obj.getNombre());
			assertEquals(Boolean.TRUE, obj.getActivo());
		} catch (final Exception e) {
			logger.error(e.getMessage(), e);
			fail("Recibida excepcion");
		}
	}

}
