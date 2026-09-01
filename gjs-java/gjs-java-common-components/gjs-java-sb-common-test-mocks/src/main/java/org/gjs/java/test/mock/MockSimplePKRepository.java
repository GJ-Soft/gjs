package org.gjs.java.test.mock;

import java.io.IOException;

import org.gjs.java.common.idgenerator.IdGenerator;
import org.gjs.java.common.idgenerator.SequenceIdGenerator;
import org.springframework.core.io.Resource;

/**
 * The Class MockSimplePKRepository.
 *
 * Clase de datos de la librería Gjs
 *
 * Implementa un repositorio JPA de datos sencillo en memoria para cualquier
 * clase de objetos cuya clave primaria sea un Long.
 *
 * @param <T> la clase de las entidad
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockSimplePKRepository<T> extends MockRepository<T, Long> {

	/** The id generator. */
	protected IdGenerator<Long> idGenerator = new SequenceIdGenerator();

	/**
	 * Instantiates a new mock simple PK repository.
	 */
	public MockSimplePKRepository() {
	}

	/**
	 * Instantiates a new mock simple PK repository.
	 *
	 * @param resource the resource
	 * @throws IOException Signals that an I/O exception has occurred.
	 */
	public MockSimplePKRepository(Resource resource) throws IOException {
		super(resource);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.mock.MockRepository#autogenerateId()
	 */

	@Override
	protected boolean autogenerateId() {
		return true;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.mock.MockRepository#getGeneratorId()
	 */

	@Override
	protected IdGenerator<Long> getGeneratorId() {
		return idGenerator;
	}

}
