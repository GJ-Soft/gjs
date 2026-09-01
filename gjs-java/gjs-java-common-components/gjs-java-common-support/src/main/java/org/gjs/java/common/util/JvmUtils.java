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

		sb.append("Max heap (-Xmx):   " + maxMemory / 1024 / 1024 + " MB\n");
		sb.append("Total heap actual: " + totalMemory / 1024 / 1024 + " MB\n");
		sb.append("Libre:             " + freeMemory / 1024 / 1024 + " MB\n");
		sb.append("Usada:             " + usedMemory / 1024 / 1024 + " MB\n");
		sb.append("\n\n\n");

		MemoryMXBean memBean = ManagementFactory.getMemoryMXBean();

		MemoryUsage heapUsage = memBean.getHeapMemoryUsage();
		MemoryUsage nonHeapUsage = memBean.getNonHeapMemoryUsage();

		sb.append("=== HEAP ===\n");
		sb.append("Init:      " + heapUsage.getInit() / 1024 / 1024 + " MB\n");
		sb.append("Used:      " + heapUsage.getUsed() / 1024 / 1024 + " MB\n");
		sb.append("Committed: " + heapUsage.getCommitted() / 1024 / 1024 + " MB\n");
		sb.append("Max:       " + heapUsage.getMax() / 1024 / 1024 + " MB\n");
		sb.append("\n\n\n");

		sb.append("=== NON-HEAP (Metaspace, etc.) ===\n");
		sb.append("Used:      " + nonHeapUsage.getUsed() / 1024 / 1024 + " MB\n");
		sb.append("Committed: " + nonHeapUsage.getCommitted() / 1024 / 1024 + " MB\n");
		sb.append("\n\n\n");

		List<MemoryPoolMXBean> pools = ManagementFactory.getMemoryPoolMXBeans();

		for (MemoryPoolMXBean pool : pools) {
			sb.append("Pool: " + pool.getName() + " [" + pool.getType() + "]\n");
			MemoryUsage usage = pool.getUsage();
			sb.append("  Used:  " + usage.getUsed() / 1024 / 1024 + " MB\n");
			sb.append("  Max:   " + usage.getMax() / 1024 / 1024 + " MB\n");
		}
		sb.append("\n\n\n");

		for (MemoryPoolMXBean pool : ManagementFactory.getMemoryPoolMXBeans()) {
			if (pool.getName().toLowerCase().contains("metaspace")) {
				MemoryUsage usage = pool.getUsage();

				sb.append("=== " + pool.getName() + " ===\n");
				sb.append("Init:      " + toMB(usage.getInit()) + " MB\n");
				sb.append("Used:      " + toMB(usage.getUsed()) + " MB\n");
				sb.append("Committed: " + toMB(usage.getCommitted()) + " MB\n");
				sb.append("Max:       " + toMB(usage.getMax()) + " MB\n"); // -1 = sin límite
			}
		}
		sb.append("\n\n\n");

		HotSpotDiagnosticMXBean diagBean;
		try {
			diagBean = ManagementFactory.newPlatformMXBeanProxy(ManagementFactory.getPlatformMBeanServer(),
					"com.sun.management:type=HotSpotDiagnostic", HotSpotDiagnosticMXBean.class);

			// Consultar flags específicos
			sb.append("MaxHeapSize: " + diagBean.getVMOption("MaxHeapSize"));
			sb.append("InitialHeapSize: " + diagBean.getVMOption("InitialHeapSize"));
			sb.append("UseG1GC: " + diagBean.getVMOption("UseG1GC"));
			sb.append("\n\n\n");
		} catch (IOException e) {
		}
		return sb.toString();
	}

	static long toMB(long bytes) {
		return bytes == -1 ? -1 : bytes / 1024 / 1024;
	}

}
