package org.gjs.java.common.supplier.random;

import java.util.Random;

import org.gjs.java.common.log.LogManager;
import org.gjs.java.common.supplier.GjsSupplier;
import org.gjs.java.common.util.ConditionUtils;
import org.slf4j.LoggerFactory;

/**
 * The class AbstractRandomSupplier.
 *
 * Clase abstracta de datos de la librería Gjs
 *
 * Clase abstracta base para los generadores de datos aleatorios de la librería.
 *
 * @param <T> la clase de datos a generar
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public abstract class AbstractRandomSupplier<T> extends LogManager implements GjsSupplier<T> {

	/** Random. */
	protected final Random random = new Random();

	/** The min size collections. */
	private int minSizeArrays = 1;

	/** The max size collections. */
	private int maxSizeArrays = 5;

	/**
	 * Instantiates a new abstract random supplier.
	 */
	protected AbstractRandomSupplier() {
		// Default Logger
		setLogger(LoggerFactory.getLogger(getClass()));
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.objects.suppliers.Supplier#getMinSizeArrays()
	 */

	@Override
	public int getMinSizeArrays() {
		return minSizeArrays;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.objects.suppliers.Supplier#setMinSizeArrays(int)
	 */

	@Override
	public void setMinSizeArrays(int minSizeArrays) {
		if (ConditionUtils.allAreTrue((minSizeArrays >= 0), (minSizeArrays <= maxSizeArrays))) {
			this.minSizeArrays = minSizeArrays;
		}
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.objects.suppliers.Supplier#getMaxSizeArrays()
	 */

	@Override
	public int getMaxSizeArrays() {
		return maxSizeArrays;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.objects.suppliers.Supplier#setMaxSizeArrays(int)
	 */

	@Override
	public void setMaxSizeArrays(int maxSizeArrays) {
		if (maxSizeArrays >= minSizeArrays) {
			this.maxSizeArrays = maxSizeArrays;
		}
	}

	/**
	 * Creates the array.
	 *
	 * @param size the size
	 * @return the t[]
	 */
	protected abstract T[] createArray(int size);

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.objects.suppliers.Supplier#getArray()
	 */

	@Override
	public T[] getArray() {
		int size = minSizeArrays;
		if (maxSizeArrays > minSizeArrays) {
			// floorMod y no el opuesto del aleatorio, que sigue siendo negativo para
			// Integer.MIN_VALUE y daría un tamaño por debajo del mínimo.
			size = minSizeArrays + Math.floorMod(random.nextInt(), maxSizeArrays - minSizeArrays);
		}
		final T[] array = createArray(size);
		for (int i = 0; i < size; i = i + 1) {
			final T value = get();
			array[i] = value;
		}
		return array;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.objects.suppliers.Supplier#getEmptyArray()
	 */

	@Override
	public T[] getEmptyArray() {
		return createArray(0);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see org.gjs.java.test.objects.suppliers.Supplier#getNullius()
	 */

	@Override
	public T getNullius() {
		return getEmpty();
	}

}
