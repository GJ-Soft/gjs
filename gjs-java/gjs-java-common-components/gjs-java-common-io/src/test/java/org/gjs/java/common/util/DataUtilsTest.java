package org.gjs.java.common.util;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.time.LocalDate;
import java.time.ZoneId;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import org.gjs.java.test.BaseUnitTest;
import org.gjs.java.test.samples.dto.SampleEntityDto;
import org.junit.jupiter.api.Test;

class DataUtilsTest extends BaseUnitTest<DataUtils> {

	@Test
	void testMakeCsv1() {
		final List<String> columns = null;
		final List<SampleEntityDto> data = null;
		final byte[] csv = DataUtils.makeCsv(data, columns);
		assertNotNull(csv);
		assertEquals(0, csv.length);
	}

	@Test
	void testMakeCsv2() {
		final List<String> columns = new ArrayList<>();
		final List<SampleEntityDto> data = new ArrayList<>();
		final byte[] csv = DataUtils.makeCsv(data, columns);
		assertNotNull(csv);
		assertEquals(0, csv.length);
	}

	@Test
	void testMakeCsv3() {
		final List<String> columns = new ArrayList<>();
		columns.add("nombre");
		final List<SampleEntityDto> data = new ArrayList<>();
		final byte[] csv = DataUtils.makeCsv(data, columns);
		assertNotNull(csv);
		final String text = new String(csv);
		logger.info("Byte stream={}", text);
		assertTrue(csv.length > 0);
	}

	@Test
	void testMakeCsv4() {
		final List<String> columns = new ArrayList<>();
		columns.add("nombre");
		final List<SampleEntityDto> data = new ArrayList<>();
		final SampleEntityDto obj1 = new SampleEntityDto();
		obj1.setId(Long.valueOf(1));
		obj1.setNombre("ROL_1");
		obj1.setActivo(Boolean.TRUE);
		data.add(obj1);
		final byte[] csv = DataUtils.makeCsv(data, columns);
		assertNotNull(csv);
		final String text = new String(csv);
		logger.info("Byte stream={}", text);
		assertTrue(csv.length > 0);
	}

	@Test
	void testMakeCsv5() {
		final List<String> columns = new ArrayList<>();
		columns.add("id");
		columns.add("nombre");
		columns.add("fechaAlta");
		columns.add("activo");
		final List<SampleEntityDto> data = new ArrayList<>();
		final SampleEntityDto obj1 = new SampleEntityDto();
		obj1.setId(Long.valueOf(1));
		obj1.setNombre("ROL_1");
		obj1.setActivo(Boolean.TRUE);
		data.add(obj1);
		final byte[] csv = DataUtils.makeCsv(data, columns);
		assertNotNull(csv);
		final String text = new String(csv);
		logger.info("Byte stream={}", text);
		assertTrue(csv.length > 0);
	}

	@Test
	void testMakeCsv6() {
		final List<String> columns = null;
		final List<Map<String, String>> data = null;
		final Set<String> stringColuns = null;
		final byte[] csv = DataUtils.makeCsv(data, columns, stringColuns);
		assertNotNull(csv);
		assertEquals(0, csv.length);
	}

	@Test
	void testMakeCsv7() {
		final List<String> columns = new ArrayList<>();
		final List<Map<String, String>> data = new ArrayList<>();
		final Set<String> stringColuns = null;
		final byte[] csv = DataUtils.makeCsv(data, columns, stringColuns);
		assertNotNull(csv);
		assertEquals(0, csv.length);
	}

	@Test
	void testMakeCsv8() {
		final List<String> columns = new ArrayList<>();
		columns.add("nombre");
		final List<Map<String, String>> data = new ArrayList<>();
		final Set<String> stringColuns = null;
		final byte[] csv = DataUtils.makeCsv(data, columns, stringColuns);
		assertNotNull(csv);
		final String text = new String(csv);
		logger.info("Byte stream={}", text);
		assertTrue(csv.length > 0);
	}

	@Test
	void testMakeCsv9() {
		final List<String> columns = new ArrayList<>();
		columns.add("nombre");
		final List<Map<String, String>> data = new ArrayList<>();
		final Set<String> stringColuns = null;
		final Map<String, String> obj1 = new HashMap<>();
		obj1.put("id", ConversionUtils.toString(Long.valueOf(1)));
		obj1.put("nombre", "ROL_1");
		obj1.put("fechaAlta", ConversionUtils.toString(LocalDate.now(ZoneId.systemDefault())));
		obj1.put("activo", ConversionUtils.toString(Boolean.TRUE));
		data.add(obj1);
		final byte[] csv = DataUtils.makeCsv(data, columns, stringColuns);
		assertNotNull(csv);
		final String text = new String(csv);
		logger.info("Byte stream={}", text);
		assertTrue(csv.length > 0);
	}

	@Test
	void testMakeCsv10() {
		final List<String> columns = new ArrayList<>();
		final Set<String> stringColuns = new TreeSet<>();
		columns.add("id");
		columns.add("nombre");
		columns.add("fechaAlta");
		columns.add("activo");
		stringColuns.add("nombre");
		final List<Map<String, String>> data = new ArrayList<>();
		final Map<String, String> obj1 = new HashMap<>();
		obj1.put("id", ConversionUtils.toString(Long.valueOf(1)));
		obj1.put("nombre", "ROL_1");
		obj1.put("fechaAlta", ConversionUtils.toString(LocalDate.now(ZoneId.systemDefault())));
		obj1.put("activo", ConversionUtils.toString(Boolean.TRUE));
		data.add(obj1);
		final byte[] csv = DataUtils.makeCsv(data, columns, stringColuns);
		assertNotNull(csv);
		final String text = new String(csv);
		logger.info("Byte stream={}", text);
		assertTrue(csv.length > 0);
	}

}
