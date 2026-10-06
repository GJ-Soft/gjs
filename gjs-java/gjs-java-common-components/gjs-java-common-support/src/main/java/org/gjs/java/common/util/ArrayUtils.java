package org.gjs.java.common.util;

import java.util.Arrays;
import java.util.Objects;
import java.util.Set;
import java.util.stream.IntStream;
import java.util.stream.LongStream;

import org.gjs.java.common.constant.CommonBaseConstants;

/**
 * The Class ArrayUtils.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Algunas funciones de ayuda para el tratamiento de vectores o arrays.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class ArrayUtils {

    /**
     * Clase no instanciable.
     */
    private ArrayUtils() {
        throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
    }

    /**
     * Resize.
     *
     * @param <T>
     *            the generic type
     * @param array
     *            the array
     * @param length
     *            the length
     * @return the t[]
     */
    @SuppressWarnings("unchecked")
    public static <T> T[] resize(Object array, int length) {
        T[] newArray = null;
        if (array.getClass().isArray()) {
            newArray = resize((T[]) array, length);
        }
        return newArray;
    }

    /**
     * Resize.
     *
     * @param <T>
     *            the generic type
     * @param array
     *            the array
     * @param length
     *            the length
     * @return the t[]
     */
    public static <T> T[] resize(T[] array, int length) {
        T[] newArray = null;
        if (Objects.nonNull(array)) {
            newArray = Arrays.copyOf(array, length);
        }
        return newArray;
    }

    /**
     * Resize.
     *
     * @param array
     *            the array
     * @param length
     *            the length
     * @return the short[]
     */
    public static short[] resize(short[] array, int length) {
        short[] newArray = null;
        if (Objects.nonNull(array)) {
            newArray = Arrays.copyOf(array, length);
        }
        return newArray;
    }

    /**
     * Resize.
     *
     * @param array
     *            the array
     * @param length
     *            the length
     * @return the int[]
     */
    public static int[] resize(int[] array, int length) {
        int[] newArray = null;
        if (Objects.nonNull(array)) {
            newArray = Arrays.copyOf(array, length);
        }
        return newArray;
    }

    /**
     * Resize.
     *
     * @param array
     *            the array
     * @param length
     *            the length
     * @return the long[]
     */
    public static long[] resize(long[] array, int length) {
        long[] newArray = null;
        if (Objects.nonNull(array)) {
            newArray = Arrays.copyOf(array, length);
        }
        return newArray;
    }

    /**
     * Resize.
     *
     * @param array
     *            the array
     * @param length
     *            the length
     * @return the float[]
     */
    public static float[] resize(float[] array, int length) {
        float[] newArray = null;
        if (Objects.nonNull(array)) {
            newArray = Arrays.copyOf(array, length);
        }
        return newArray;
    }

    /**
     * Resize.
     *
     * @param array
     *            the array
     * @param length
     *            the length
     * @return the double[]
     */
    public static double[] resize(double[] array, int length) {
        double[] newArray = null;
        if (Objects.nonNull(array)) {
            newArray = Arrays.copyOf(array, length);
        }
        return newArray;
    }

    /**
     * Resize.
     *
     * @param array
     *            the array
     * @param length
     *            the length
     * @return the boolean[]
     */
    public static boolean[] resize(boolean[] array, int length) {
        boolean[] newArray = null;
        if (Objects.nonNull(array)) {
            newArray = Arrays.copyOf(array, length);
        }
        return newArray;
    }

    /**
     * Resize.
     *
     * @param array
     *            the array
     * @param length
     *            the length
     * @return the byte[]
     */
    public static byte[] resize(byte[] array, int length) {
        byte[] newArray = null;
        if (Objects.nonNull(array)) {
            newArray = Arrays.copyOf(array, length);
        }
        return newArray;
    }

    /**
     * Resize.
     *
     * @param array
     *            the array
     * @param length
     *            the length
     * @return the char[]
     */
    public static char[] resize(char[] array, int length) {
        char[] newArray = null;
        if (Objects.nonNull(array)) {
            newArray = Arrays.copyOf(array, length);
        }
        return newArray;
    }

    /**
     * Contains.
     *
     * @param <T>
     *            the generic type
     * @param array
     *            the array
     * @param value
     *            the value
     * @return true, if successful
     */
    public static <T> boolean contains(T[] array, T value) {
        boolean res = false;
        if (ConditionUtils.allAreTrue(Objects.nonNull(array), Objects.nonNull(value))) {
            final Set<T> set = Set.of(array);
            res = set.contains(value);
        }
        return res;
    }

    /**
     * Contains.
     *
     * @param array
     *            the array
     * @param value
     *            the value
     * @return true, if successful
     */
    public static boolean contains(short[] array, short value) {
        boolean res = false;
        if (Objects.nonNull(array)) {
            res = org.apache.commons.lang3.ArrayUtils.contains(array, value);
        }
        return res;
    }

    /**
     * Contains.
     *
     * @param array
     *            the array
     * @param value
     *            the value
     * @return true, if successful
     */
    public static boolean contains(int[] array, int value) {
        boolean res = false;
        if (Objects.nonNull(array)) {
            res = IntStream.of(array).anyMatch(x -> x == value);
        }
        return res;
    }

    /**
     * Contains.
     *
     * @param array
     *            the array
     * @param value
     *            the value
     * @return true, if successful
     */
    public static boolean contains(long[] array, long value) {
        boolean res = false;
        if (Objects.nonNull(array)) {
            res = LongStream.of(array).anyMatch(x -> x == value);
        }
        return res;
    }

    /**
     * Contains.
     *
     * @param array
     *            the array
     * @param value
     *            the value
     * @return true, if successful
     */
    public static boolean contains(float[] array, float value) {
        boolean res = false;
        if (Objects.nonNull(array)) {
            res = org.apache.commons.lang3.ArrayUtils.contains(array, value);
        }
        return res;
    }

    /**
     * Contains.
     *
     * @param array
     *            the array
     * @param value
     *            the value
     * @return true, if successful
     */
    public static boolean contains(double[] array, double value) {
        boolean res = false;
        if (Objects.nonNull(array)) {
            res = org.apache.commons.lang3.ArrayUtils.contains(array, value);
        }
        return res;
    }

    /**
     * Contains.
     *
     * @param array
     *            the array
     * @param value
     *            the value
     * @return true, if successful
     */
    public static boolean contains(boolean[] array, boolean value) {
        boolean res = false;
        if (Objects.nonNull(array)) {
            res = org.apache.commons.lang3.ArrayUtils.contains(array, value);
        }
        return res;
    }

    /**
     * Contains.
     *
     * @param array
     *            the array
     * @param value
     *            the value
     * @return true, if successful
     */
    public static boolean contains(char[] array, char value) {
        boolean res = false;
        if (Objects.nonNull(array)) {
            res = org.apache.commons.lang3.ArrayUtils.contains(array, value);
        }
        return res;
    }

    /**
     * Contains.
     *
     * @param array
     *            the array
     * @param value
     *            the value
     * @return true, if successful
     */
    public static boolean contains(byte[] array, byte value) {
        boolean res = false;
        if (Objects.nonNull(array)) {
            res = org.apache.commons.lang3.ArrayUtils.contains(array, value);
        }
        return res;
    }

}
