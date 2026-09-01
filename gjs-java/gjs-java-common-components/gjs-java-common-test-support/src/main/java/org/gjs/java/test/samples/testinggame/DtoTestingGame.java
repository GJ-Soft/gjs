package org.gjs.java.test.samples.testinggame;

import org.gjs.java.common.supplier.AbstractObjectSupplier;
import org.gjs.java.common.supplier.ObjectSupplierManager;
import org.gjs.java.test.samples.dto.SampleEntityDto;
import org.gjs.java.test.samples.dto.SampleWithFKEntityDto;
import org.slf4j.Logger;

/**
 * The Class DtoTestingGame.
 *
 * Clase funcional de la librería Gjs
 *
 * Juego de suministradores para los DTO de ejemplo: entrega instancias pobladas y vacías de SampleEntityDto y de SampleWithFKEntityDto.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class DtoTestingGame extends ObjectSupplierManager {

	static class SampleEntityDtoSupplier extends AbstractObjectSupplier<SampleEntityDto> {
		public SampleEntityDtoSupplier(ObjectSupplierManager manager) {
			super(SampleEntityDto.class.getCanonicalName(), manager);
		}

		@Override
		protected SampleEntityDto[] createArray(int size) {
			return new SampleEntityDto[size];
		}

	}

	static class SampleWithFKEntityDtoSupplier extends AbstractObjectSupplier<SampleWithFKEntityDto> {
		public SampleWithFKEntityDtoSupplier(ObjectSupplierManager manager) {
			super(SampleWithFKEntityDto.class.getCanonicalName(), manager);
		}

		@Override
		protected SampleWithFKEntityDto[] createArray(int size) {
			return new SampleWithFKEntityDto[size];
		}

	}

	SampleEntityDtoSupplier SampleEntityDtoSupplier = null;
	SampleWithFKEntityDtoSupplier SampleWithFKEntityDtoSupplier = null;

	public DtoTestingGame() {
		this(null);
	}

	public DtoTestingGame(Logger logger) {
		super(logger);
		SampleEntityDtoSupplier = new SampleEntityDtoSupplier(this);
		SampleWithFKEntityDtoSupplier = new SampleWithFKEntityDtoSupplier(this);

		SampleEntityDtoSupplier.setLogger(logger);
		SampleWithFKEntityDtoSupplier.setLogger(logger);
	}

	public SampleEntityDto getSampleEntityDto() {
		return SampleEntityDtoSupplier.get();
	}

	public SampleWithFKEntityDto getSampleWithFKEntityDto() {
		return SampleWithFKEntityDtoSupplier.get();
	}

	public SampleEntityDto getEmptySampleEntityDto() {
		return SampleEntityDtoSupplier.getEmpty();
	}

	public SampleWithFKEntityDto getEmptySampleWithFKEntityDto() {
		return SampleWithFKEntityDtoSupplier.getEmpty();
	}

}
