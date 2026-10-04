package org.gjs.java.common.dto;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.math.BigInteger;
import java.util.List;
import java.util.Set;

import org.gjs.java.test.BaseUnitTest;
import org.junit.jupiter.api.Test;

@SuppressWarnings("rawtypes")
public class SetDtoTest extends BaseUnitTest<SetDto> {

	@Test
	void testEmptyOnCreation() {
		final SetDto<String> dto = new SetDto<>();
		assertTrue(dto.getContenido().isEmpty());
	}

	@Test
	void testNaturalOrder() {
		final SetDto<String> dto = new SetDto<>();
		dto.getContenido().add("c");
		dto.getContenido().add("a");
		dto.getContenido().add("b");
		assertEquals(List.of("a", "b", "c"), List.copyOf(dto.getContenido()));
		logger.info(dto.toString());
	}

	@Test
	void testDuplicatesIgnored() {
		final SetDto<String> dto = new SetDto<>();
		assertTrue(dto.getContenido().add("a"));
		assertFalse(dto.getContenido().add("a"));
		assertEquals(1, dto.getContenido().size());
	}

	/**
	 * Con un DTO de la librería: el orden es el de su compareTo, que en
	 * DBSequenceDto es el nombre de la secuencia.
	 */
	@Test
	void testDtoOrder() {
		final SetDto<DBSequenceDto> dto = new SetDto<>();
		dto.getContenido().add(new DBSequenceDto("SEQ_C"));
		dto.getContenido().add(new DBSequenceDto("SEQ_A"));
		dto.getContenido().add(new DBSequenceDto("SEQ_B"));
		assertEquals(List.of("SEQ_A", "SEQ_B", "SEQ_C"),
				dto.getContenido().stream().map(DBSequenceDto::getSequenceName).toList());
	}

	/**
	 * Un TreeSet decide los duplicados por compareTo, no por equals: dos
	 * secuencias con el mismo nombre cuentan como una aunque difieran en lo demás.
	 */
	@Test
	void testDtoDuplicatesByCompareTo() {
		final SetDto<DBSequenceDto> dto = new SetDto<>();
		final DBSequenceDto first = new DBSequenceDto("SEQ_A");
		final DBSequenceDto second = new DBSequenceDto("SEQ_A");
		second.setMaxValue(BigInteger.TEN);
		assertTrue(dto.getContenido().add(first));
		assertFalse(dto.getContenido().add(second));
		assertEquals(1, dto.getContenido().size());
	}

	/**
	 * getContenido devuelve el conjunto del DTO, no una copia: es la forma de
	 * llenarlo, porque el campo es final y no tiene setter.
	 */
	@Test
	void testContentIsLive() {
		final SetDto<String> dto = new SetDto<>();
		final Set<String> content = dto.getContenido();
		content.add("a");
		assertEquals(1, dto.getContenido().size());
	}

	@Test
	void testNoSetter() {
		assertThrows(NoSuchMethodException.class, () -> SetDto.class.getMethod("setContenido", Set.class));
	}

	@Test
	void testNullElementRejected() {
		final SetDto<String> dto = new SetDto<>();
		assertThrows(NullPointerException.class, () -> dto.getContenido().add(null));
	}

	/**
	 * Con un DTO de entidad. EntityDto implementa Comparable<EntityDto<?>>, no
	 * Comparable<AvisoDto>: con el limite T extends Comparable<T> esto no compilaba.
	 */
	@Test
	void testEntityDto() {
		final SetDto<AvisoDto> dto = new SetDto<>();
		final AvisoDto segundo = new AvisoDto();
		segundo.setId(2L);
		final AvisoDto primero = new AvisoDto();
		primero.setId(1L);
		dto.getContenido().add(segundo);
		dto.getContenido().add(primero);
		assertEquals(List.of(1L, 2L), dto.getContenido().stream().map(AvisoDto::getId).toList());
	}

}
