package org.gjs.java.common.supplier;

import org.gjs.java.common.supplier.random.RandomAlphanumericCharSupplier;
import org.gjs.java.common.supplier.random.RandomBooleanSupplier;
import org.gjs.java.common.supplier.random.RandomBytesSupplier;
import org.gjs.java.common.supplier.random.RandomDoubleSupplier;
import org.gjs.java.common.supplier.random.RandomFloatSupplier;
import org.gjs.java.common.supplier.random.RandomIntegerSupplier;
import org.gjs.java.common.supplier.random.RandomLongSupplier;
import org.gjs.java.common.supplier.random.RandomShortSupplier;

/**
 * The Class PrimitiveObjectSupplierBattery.
 *
 * Clase de datos de la librería Gjs
 *
 * Generador de objetos aleatorios para todos las clases de datos incluidas en el enumerado PrimitiveType de tipos
 * primitivos.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class PrimitiveObjectSupplierBattery {

    /** The long supplier. */
    private final GjsSupplier<Long> longSupplier = new RandomLongSupplier();

    /** The int supplier. */
    private final GjsSupplier<Integer> intSupplier =
            new RandomIntegerSupplier(Integer.valueOf(0), Integer.valueOf(1000));

    /** The int supplier. */
    private final GjsSupplier<Short> shortSupplier =
            new RandomShortSupplier(Short.valueOf((short) 0), Short.valueOf((short) 1000));

    /** The boolean supplier. */
    private final GjsSupplier<Boolean> booleanSupplier = new RandomBooleanSupplier();

    /** The float supplier. */
    private final GjsSupplier<Float> floatSupplier = new RandomFloatSupplier();

    /** The double supplier. */
    private final GjsSupplier<Double> doubleSupplier = new RandomDoubleSupplier();

    /** The char supplier. */
    private final GjsSupplier<Character> charSupplier = new RandomAlphanumericCharSupplier();

    /** The bytes supplier. */
    private final GjsSupplier<Byte[]> bytesSupplier = new RandomBytesSupplier(20, false, false);

    /** The bytes supplier. */
    private final GjsSupplier<Byte[]> byteSupplier = new RandomBytesSupplier(1, false, true);

    /**
     * Instantiates a new primitive object supplier battery.
     */
    public PrimitiveObjectSupplierBattery() {
        // No hace nada
    }

    /**
     * Random long.
     *
     * @return random value
     */
    public Long randomLong() {
        return longSupplier.get();
    }

    /**
     * Random int.
     *
     * @return random value
     */
    public Integer randomInt() {
        return intSupplier.get();
    }

    /**
     * Random short.
     *
     * @return random value
     */
    public Short randomShort() {
        return shortSupplier.get();
    }

    /**
     * Random boolean.
     *
     * @return random value
     */
    public Boolean randomBoolean() {
        return booleanSupplier.get();
    }

    /**
     * Random float.
     *
     * @return random value
     */
    public Float randomFloat() {
        return floatSupplier.get();
    }

    /**
     * Random double.
     *
     * @return random value
     */
    public Double randomDouble() {
        return doubleSupplier.get();
    }

    /**
     * Random char.
     *
     * @return random value
     */
    public Character randomChar() {
        return charSupplier.get();
    }

    /**
     * Random bytes.
     *
     * @return random value
     */
    public Byte[] randomBytes() {
        return bytesSupplier.get();
    }

    /**
     * Random byte.
     *
     * @return random value
     */
    public Byte randomByte() {
        return byteSupplier.get()[0];
    }

    /**
     * Random long.
     *
     * @return random value
     */
    public Long emptyLong() {
        return longSupplier.getEmpty();
    }

    /**
     * Random int.
     *
     * @return random value
     */
    public Integer emptyInt() {
        return intSupplier.getEmpty();
    }

    /**
     * Random short.
     *
     * @return random value
     */
    public Short emptyShort() {
        return shortSupplier.getEmpty();
    }

    /**
     * Random boolean.
     *
     * @return random value
     */
    public Boolean emptyBoolean() {
        return booleanSupplier.getEmpty();
    }

    /**
     * Random float.
     *
     * @return random value
     */
    public Float emptyFloat() {
        return floatSupplier.getEmpty();
    }

    /**
     * Random double.
     *
     * @return random value
     */
    public Double emptyDouble() {
        return doubleSupplier.getEmpty();
    }

    /**
     * Random char.
     *
     * @return random value
     */
    public Character emptyChar() {
        return charSupplier.getEmpty();
    }

    /**
     * Random bytes.
     *
     * @return random value
     */
    public Byte[] emptyBytes() {
        return bytesSupplier.getEmpty();
    }

    /**
     * Random byte.
     *
     * @return random value
     */
    public Byte emptyByte() {
        return Byte.valueOf((byte) 0);
    }

    /**
     * Random Array long.
     *
     * @return randomArray value
     */
    public Long[] randomArrayLong() {
        return longSupplier.getArray();
    }

    /**
     * Random Array int.
     *
     * @return randomArray value
     */
    public Integer[] randomArrayInt() {
        return intSupplier.getArray();
    }

    /**
     * Random Array short.
     *
     * @return randomArray value
     */
    public Short[] randomArrayShort() {
        return shortSupplier.getArray();
    }

    /**
     * Random Array boolean.
     *
     * @return randomArray value
     */
    public Boolean[] randomArrayBoolean() {
        return booleanSupplier.getArray();
    }

    /**
     * Random Array float.
     *
     * @return randomArray value
     */
    public Float[] randomArrayFloat() {
        return floatSupplier.getArray();
    }

    /**
     * Random Array double.
     *
     * @return randomArray value
     */
    public Double[] randomArrayDouble() {
        return doubleSupplier.getArray();
    }

    /**
     * Random Array char.
     *
     * @return randomArray value
     */
    public Character[] randomArrayChar() {
        return charSupplier.getArray();
    }

    /**
     * Random Array bytes.
     *
     * @return randomArray value
     */
    public Byte[][] randomArrayBytes() {
        return bytesSupplier.getArray();
    }

    /**
     * Empty Array long.
     *
     * @return randomArray value
     */
    public Long[] emptyArrayLong() {
        return longSupplier.getEmptyArray();
    }

    /**
     * Empty Array int.
     *
     * @return randomArray value
     */
    public Integer[] emptyArrayInt() {
        return intSupplier.getEmptyArray();
    }

    /**
     * Empty Array short.
     *
     * @return randomArray value
     */
    public Short[] emptyArrayShort() {
        return shortSupplier.getEmptyArray();
    }

    /**
     * Empty Array boolean.
     *
     * @return randomArray value
     */
    public Boolean[] emptyArrayBoolean() {
        return booleanSupplier.getEmptyArray();
    }

    /**
     * Empty Array float.
     *
     * @return randomArray value
     */
    public Float[] emptyArrayFloat() {
        return floatSupplier.getEmptyArray();
    }

    /**
     * Empty Array double.
     *
     * @return randomArray value
     */
    public Double[] emptyArrayDouble() {
        return doubleSupplier.getEmptyArray();
    }

    /**
     * Empty Array char.
     *
     * @return randomArray value
     */
    public Character[] emptyArrayChar() {
        return charSupplier.getEmptyArray();
    }

    /**
     * Empty Array bytes.
     *
     * @return randomArray value
     */
    public Byte[][] emptyArrayBytes() {
        return bytesSupplier.getEmptyArray();
    }

}
