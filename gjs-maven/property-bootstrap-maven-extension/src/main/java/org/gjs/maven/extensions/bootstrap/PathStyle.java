package org.gjs.maven.extensions.bootstrap;

/**
 * Conversion de rutas entre el estilo de Windows ({@code C:\Desarrollo\Cygwin64})
 * y el de Cygwin ({@code /cygdrive/c/Desarrollo/Cygwin64}).
 *
 * <p>Las conversiones son idempotentes: llevar una ruta al estilo que ya tiene la
 * devuelve intacta (salvo normalizacion de separadores).</p>
 *
 * <p><b>Limite conocido</b>: una ruta posix absoluta que no cuelgue de
 * {@code /cygdrive} (p.ej. {@code /usr/local}) no se puede llevar a Windows sin
 * conocer la raiz de la instalacion de Cygwin, que es justamente el dato que se
 * suele estar calculando. En ese caso se devuelve sin tocar.</p>
 */
final class PathStyle {

	/** Valor de {@code environment.style} que selecciona el estilo Windows. */
	static final String WINDOWS = "windows";

	/** Prefijo bajo el que Cygwin monta las unidades de Windows. */
	private static final String CYGDRIVE = "/cygdrive/";

	private PathStyle() {
	}

	/**
	 * Lleva la ruta al estilo indicado. Cualquier valor distinto de
	 * {@code windows} se interpreta como posix, igual que hace la propiedad
	 * {@code environment.style}.
	 */
	static String to(String style, String path) {
		return WINDOWS.equalsIgnoreCase(style) ? toWindows(path) : toPosix(path);
	}

	/** {@code C:\dir} -&gt; {@code /cygdrive/c/dir}. */
	static String toPosix(String path) {
		if (path == null || path.isEmpty()) {
			return path;
		}
		String slashed = path.replace('\\', '/');
		if (!hasDriveLetter(slashed)) {
			// Ya es posix, o es relativa: basta con el cambio de separador.
			return slashed;
		}
		char drive = Character.toLowerCase(slashed.charAt(0));
		return CYGDRIVE + drive + slashed.substring(2);
	}

	/** {@code /cygdrive/c/dir} -&gt; {@code C:\dir}. */
	static String toWindows(String path) {
		if (path == null || path.isEmpty()) {
			return path;
		}
		if (hasDriveLetter(path.replace('\\', '/'))) {
			// Ya es de Windows: solo normaliza los separadores.
			return path.replace('/', '\\');
		}
		if (hasCygdrivePrefix(path)) {
			char drive = Character.toUpperCase(path.charAt(CYGDRIVE.length()));
			String rest = path.substring(CYGDRIVE.length() + 1);
			return drive + ":" + (rest.isEmpty() ? "\\" : rest.replace('/', '\\'));
		}
		if (path.startsWith("//")) {
			return path.replace('/', '\\'); // UNC
		}
		if (path.charAt(0) == '/') {
			// Posix absoluta fuera de /cygdrive: no es mapeable, se deja igual.
			return path;
		}
		return path.replace('/', '\\'); // relativa
	}

	/** Cierto si la ruta empieza por unidad de Windows con separador: {@code C:/...}. */
	private static boolean hasDriveLetter(String slashed) {
		return slashed.length() >= 3
				&& Character.isLetter(slashed.charAt(0))
				&& slashed.charAt(1) == ':'
				&& slashed.charAt(2) == '/';
	}

	/** Cierto si la ruta es {@code /cygdrive/<letra>} o {@code /cygdrive/<letra>/...}. */
	private static boolean hasCygdrivePrefix(String path) {
		if (!path.regionMatches(true, 0, CYGDRIVE, 0, CYGDRIVE.length())) {
			return false;
		}
		int drive = CYGDRIVE.length();
		if (drive >= path.length() || !Character.isLetter(path.charAt(drive))) {
			return false;
		}
		int after = drive + 1;
		return after == path.length() || path.charAt(after) == '/';
	}
}
