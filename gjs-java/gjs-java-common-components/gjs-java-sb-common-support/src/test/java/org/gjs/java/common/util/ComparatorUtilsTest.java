package org.gjs.java.common.util;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertNull;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

import org.gjs.java.common.util.ComparatorUtils;
import org.gjs.java.test.BaseClassTest;
import org.gjs.java.test.samples.type.AllPrimitivesType;
import org.junit.jupiter.api.Test;
import org.springframework.data.domain.Sort;

class ComparatorUtilsTest extends BaseClassTest<ComparatorUtils> {

	@Test
	void testConvert1() {
		final AllPrimitivesType AllPrimitivesType1 = new AllPrimitivesType();
		AllPrimitivesType1.setIntVal(1);
		AllPrimitivesType1.setStrVal("AllPrimitivesType1");
		final AllPrimitivesType AllPrimitivesType2 = new AllPrimitivesType();
		AllPrimitivesType2.setIntVal(2);
		AllPrimitivesType2.setStrVal("AllPrimitivesType2");
		final AllPrimitivesType AllPrimitivesType3 = new AllPrimitivesType();
		AllPrimitivesType3.setIntVal(1);
		AllPrimitivesType3.setStrVal("AllPrimitivesType3");
		final List<AllPrimitivesType> list = new ArrayList<>();
		list.add(AllPrimitivesType3);
		list.add(AllPrimitivesType2);
		list.add(AllPrimitivesType1);
		final Sort sort = Sort.by("intVal", "strVal");
		final Comparator<AllPrimitivesType> comparator = ComparatorUtils.convert(sort, AllPrimitivesType.class);
		assertNotNull(comparator);
		assertEquals(-1, comparator.compare(AllPrimitivesType1, AllPrimitivesType2));
		assertEquals(0, comparator.compare(AllPrimitivesType1, AllPrimitivesType1));
		assertEquals(1, comparator.compare(AllPrimitivesType2, AllPrimitivesType3));
		list.sort(comparator);
		assertEquals("AllPrimitivesType1", list.get(0).getStrVal());
		assertEquals("AllPrimitivesType3", list.get(1).getStrVal());
		assertEquals("AllPrimitivesType2", list.get(2).getStrVal());
	}

	@Test
	void testConvert2() {
		try {
			final Sort sort = Sort.by("xxx");
			final Comparator<AllPrimitivesType> comparator = ComparatorUtils.convert(sort, AllPrimitivesType.class);
			assertNotNull(comparator);

		} catch (final Exception ex) {
			assertNull(ex);
		}
	}

}
