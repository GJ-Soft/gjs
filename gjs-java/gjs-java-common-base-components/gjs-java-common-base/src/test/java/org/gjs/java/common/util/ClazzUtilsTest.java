package org.gjs.java.common.util;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;

import java.lang.reflect.Type;
import java.math.BigDecimal;
import java.util.Date;

import org.gjs.java.common.util.ClazzUtils;
import org.gjs.java.test.BaseClassTest;
import org.gjs.java.test.samples.pojos.SampleGeneric;
import org.gjs.java.test.samples.pojos.SampleMaterialized1;
import org.gjs.java.test.samples.pojos.SamplePojo;
import org.gjs.java.test.samples.type.AllPrimitivesType;
import org.gjs.java.test.samples.type.LombokType;
import org.gjs.java.test.samples.type.WithoutDefaultConstructorType;
import org.junit.jupiter.api.Test;

class ClazzUtilsTest extends BaseClassTest<ClazzUtils> {

	@Test
	void testCreateInstance1() {
		final AllPrimitivesType sample = (AllPrimitivesType) ClazzUtils
				.createInstance("org.gjs.java.test.samples.type.AllPrimitivesType", logger);
		assertNotNull(sample);
	}

	@Test
	void testCreateInstance2() {
		final AllPrimitivesType sample = (AllPrimitivesType) ClazzUtils.createInstance("org.gjs.java.noexiste.Sample",
				logger);
		assertNull(sample);
	}

	@Test
	void testCreateInstance3() {
		final Long sample = (Long) ClazzUtils.createInstance("java.lang.Long", logger);
		assertNotNull(sample);
	}

	@Test
	void testCreateInstance4() {
		final String sample = (String) ClazzUtils.createInstance("java.lang.String", logger);
		assertNotNull(sample);
	}

	@Test
	void testCreateInstance5() {
		final Date sample = (Date) ClazzUtils.createInstance("java.util.Date", logger);
		assertNotNull(sample);
	}

	@Test
	void testCreateInstance6() {
		final BigDecimal sample = (BigDecimal) ClazzUtils.createInstance("java.math.BigDecimal", logger);
		assertNotNull(sample);
	}

	@Test
	void testCreateInstance7() {
		final WithoutDefaultConstructorType sample = (WithoutDefaultConstructorType) ClazzUtils
				.createInstance("org.gjs.java.test.samples.type.WithoutDefaultConstructorType");
		assertNotNull(sample);
	}

	@Test
	void testCreateInstance8() {
		final LombokType sample = (LombokType) ClazzUtils.createInstance("org.gjs.java.test.samples.type.LombokType");
		assertNotNull(sample);
	}

	@Test
	void testCreateArrayInstance1() {
		final String[] strings = (String[]) ClazzUtils.createArrayInstance(String.class.getCanonicalName());
		assertNotNull(strings);
		assertEquals(0, strings.length);
	}

	@Test
	void testCreateArrayInstance2() {
		final AllPrimitivesType[] samples = (AllPrimitivesType[]) ClazzUtils
				.createArrayInstance("org.gjs.java.test.samples.type.AllPrimitivesType", 1, logger);
		assertNotNull(samples);
		assertEquals(1, samples.length);
	}

	@Test
	void testCreateArrayInstance3() {
		final AllPrimitivesType[] sample = (AllPrimitivesType[]) ClazzUtils
				.createArrayInstance("org.gjs.java.noexiste.Sample", 1, logger);
		assertNull(sample);
	}

	@Test
	void testDetGenericSuperclass() {
		Type superclass = ClazzUtils.getGenericSuperclass(SamplePojo.class);
		assertNull(superclass);
		superclass = ClazzUtils.getGenericSuperclass(SampleGeneric.class);
		assertNull(superclass);
		superclass = ClazzUtils.getGenericSuperclass(SampleMaterialized1.class);
		assertNotNull(superclass);
		superclass = ClazzUtils.getGenericSuperclass(String.class);
		assertNull(superclass);
		superclass = ClazzUtils.getGenericSuperclass(Object.class);
		assertNull(superclass);
	}

	@Test
	void testCreateInstancePrimitive1() {
		final Long sample = (Long) ClazzUtils.createInstance("java.lang.Long", logger);
		assertNotNull(sample);
	}

	@Test
	void testCreateInstancePrimitive2() {
		final Long[] sample = (Long[]) ClazzUtils.createArrayInstance("java.lang.Long", 1, logger);
		assertNotNull(sample);
	}

	@Test
	void testCreateInstanceSimple1() {
		final String sample = (String) ClazzUtils.createInstance("java.lang.String", logger);
		assertNotNull(sample);
	}

	@Test
	void testCreateInstanceSimple2() {
		final String[] sample = (String[]) ClazzUtils.createArrayInstance("java.lang.String", 1, logger);
		assertNotNull(sample);
	}

}
