package org.gjs.java.common.util;

import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.lang.management.MemoryMXBean;
import java.lang.management.MemoryPoolMXBean;
import java.lang.management.MemoryUsage;
import java.util.List;

import org.gjs.java.common.constant.CommonBaseConstants;

import com.sun.management.HotSpotDiagnosticMXBean;

/**
 * The Class JvmUtils.
 *
 * Clase de utilidades generales de la libreria Gjs
 *
 * Informacion sobre la maquina virtual en marcha: memoria del heap, del non-heap y de cada pool.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public final class JvmUtils {

	/** Separacion entre bloques del informe. */
	private static final String SEPARATOR = "\n\n\n";

	/** Etiqueta de la memoria usada. */
	private static final String USED = "Used:      ";

	/** Etiqueta de la memoria comprometida. */
	private static final String COMMITTED = "Committed: ";

	/**
	 * Clase no instanciable.
	 */
	private JvmUtils() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

	public static String jvmInfo() {
		StringBuilder sb = new StringBuilder();

		Runtime runtime = Runtime.getRuntime();

		long maxMemory = runtime.maxMemory(); // -Xmx
		long totalMemory = runtime.totalMemory(); // memoria actual del heap
		long freeMemory = runtime.freeMemory(); // libre dentro del heap actual
		long usedMemory = totalMemory - freeMemory;

		appendMb(sb, "Max heap (-Xmx):   ", maxMemory);
		appendMb(sb, "Total heap actual: ", totalMemory);
		appendMb(sb, "Libre:             ", freeMemory);
		appendMb(sb, "Usada:             ", usedMemory);
		sb.append(SEPARATOR);

		MemoryMXBean memBean = ManagementFactory.getMemoryMXBean();

		MemoryUsage heapUsage = memBean.getHeapMemoryUsage();
		MemoryUsage nonHeapUsage = memBean.getNonHeapMemoryUsage();

		sb.append("=== HEAP ===\n");
		appendUsage(sb, heapUsage);
		sb.append(SEPARATOR);

		sb.append("=== NON-HEAP (Metaspace, etc.) ===\n");
		appendMb(sb, USED, nonHeapUsage.getUsed());
		appendMb(sb, COMMITTED, nonHeapUsage.getCommitted());
		sb.append(SEPARATOR);

		List<MemoryPoolMXBean> pools = ManagementFactory.getMemoryPoolMXBeans();

		for (MemoryPoolMXBean pool : pools) {
			sb.append("Pool: ").append(pool.getName()).append(" [").append(pool.getType()).append("]\n");
			MemoryUsage usage = pool.getUsage();
			appendMb(sb, "  Used:  ", usage.getUsed());
			appendMb(sb, "  Max:   ", usage.getMax());
		}
		sb.append(SEPARATOR);

		for (MemoryPoolMXBean pool : ManagementFactory.getMemoryPoolMXBeans()) {
			if (pool.getName().toLowerCase().contains("metaspace")) {
				sb.append("=== ").append(pool.getName()).append(" ===\n");
				appendUsage(sb, pool.getUsage());
			}
		}
		sb.append(SEPARATOR);

		HotSpotDiagnosticMXBean diagBean;
		try {
			diagBean = ManagementFactory.newPlatformMXBeanProxy(ManagementFactory.getPlatformMBeanServer(),
					"com.sun.management:type=HotSpotDiagnostic", HotSpotDiagnosticMXBean.class);

			// Consultar flags específicos
			sb.append("MaxHeapSize: ").append(diagBean.getVMOption("MaxHeapSize")).append('\n');
			sb.append("InitialHeapSize: ").append(diagBean.getVMOption("InitialHeapSize")).append('\n');
			sb.append("UseG1GC: ").append(diagBean.getVMOption("UseG1GC")).append('\n');
			sb.append(SEPARATOR);
		} catch (IOException e) {
			// Sin el bean de diagnostico de HotSpot (otra JVM): el informe va sin esos flags.
		}
		return sb.toString();
	}

	/**
	 * Añade una linea con la etiqueta y el valor en MB.
	 *
	 * @param sb       el informe
	 * @param etiqueta la etiqueta, ya alineada
	 * @param bytes    el valor en bytes; -1 si no esta definido
	 */
	private static void appendMb(StringBuilder sb, String etiqueta, long bytes) {
		sb.append(etiqueta).append(toMB(bytes)).append(" MB\n");
	}

	/**
	 * Añade las lineas de un uso de memoria: init, used, committed y max.
	 *
	 * @param sb    el informe
	 * @param usage el uso de memoria
	 */
	private static void appendUsage(StringBuilder sb, MemoryUsage usage) {
		appendMb(sb, "Init:      ", usage.getInit());
		appendMb(sb, USED, usage.getUsed());
		appendMb(sb, COMMITTED, usage.getCommitted());
		appendMb(sb, "Max:       ", usage.getMax()); // -1 = sin límite
	}

	static long toMB(long bytes) {
		return bytes == -1 ? -1 : bytes / 1024 / 1024;
	}

}
