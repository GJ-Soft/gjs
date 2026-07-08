package org.gjs.maven.extensions.profile;

import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.HashSet;
import java.util.List;
import java.util.Locale;
import java.util.Properties;
import java.util.Set;

import javax.inject.Inject;

import org.apache.maven.AbstractMavenLifecycleParticipant;
import org.apache.maven.MavenExecutionException;
import org.apache.maven.execution.MavenExecutionRequest;
import org.apache.maven.execution.MavenSession;
import org.apache.maven.project.ProjectBuildingRequest;
import org.codehaus.plexus.logging.Logger;
import org.gjs.maven.extensions.profile.PropertyExpression.Resolver;

/**
 * Extension de nucleo (core extension) que calcula propiedades ANTES de que
 * Maven active los perfiles del reactor y las fija como <em>user properties</em>,
 * de modo que la activacion nativa por &lt;property&gt; las vea en la primera y
 * unica pasada del model building.
 *
 * <p>Con esto se elimina la necesidad de duplicar las mismas condiciones de
 * &lt;activation&gt; en varios perfiles del pom hijo: la propiedad se calcula una
 * sola vez y todos los perfiles la consumen por su nombre.</p>
 *
 * <p>Las propiedades a calcular se describen en un fichero de configuracion
 * (por defecto {@code $MAVEN_HOME/conf/profile-activator.properties}, o el que
 * indique {@code -Dprofile-activator.config=<ruta>}), una por linea, con la forma
 * {@code clave = expresion}. La expresion usa el mini-lenguaje de
 * {@link PropertyExpression}. Si no hay fichero se aplica una regla por defecto
 * ({@code environment.style} / {@code cygwin.style}).</p>
 *
 * <p><b>IMPORTANTE</b>: esta extension DEBE declararse como <i>core extension</i>
 * (en {@code .mvn/extensions.xml} o en {@code $MAVEN_HOME/lib/ext}), NO en
 * {@code <build><extensions>}. Solo las core extensions reciben
 * {@link #afterSessionStart(MavenSession)}, unico hook que se ejecuta antes de
 * leer los POMs del reactor y activar sus perfiles.</p>
 */
public class ProfileActivationPropertyExtension extends AbstractMavenLifecycleParticipant {

	private static final String LOG_PREFIX = "[profile-activator-extension] ";

	/** Propiedad -D para indicar la ruta del fichero de configuracion. */
	private static final String CONFIG_PROPERTY = "profile-activator.config";

	/** Nombre del fichero de configuracion por defecto (en $MAVEN_HOME/conf). */
	private static final String DEFAULT_CONFIG_NAME = "profile-activator.properties";

	@Inject
	private Logger logger;

	@Override
	public void afterSessionStart(MavenSession session) throws MavenExecutionException {

		MavenExecutionRequest request = session.getRequest();

		// User properties de la peticion (incluye las -D) y system properties.
		Properties userProperties = request.getUserProperties();
		Properties systemProperties = request.getSystemProperties();

		// La ProjectBuildingRequest alimenta el ProfileActivationContext de cada
		// proyecto del reactor y de toda su linea de padres.
		ProjectBuildingRequest pbr = request.getProjectBuildingRequest();
		Properties pbrUserProperties = (pbr != null) ? pbr.getUserProperties() : null;

		// Claves ya definidas por el usuario (-D) ANTES de inyectar nada: se respetan.
		Set<String> preset = new HashSet<>(userProperties.stringPropertyNames());

		File config = locateConfig(userProperties, systemProperties);
		if (config != null && config.isFile()) {
			info("usando configuracion " + config.getAbsolutePath());
			applyConfig(config, userProperties, systemProperties, pbrUserProperties, preset);
		} else {
			applyBuiltinDefaults(userProperties, systemProperties, pbrUserProperties, preset);
		}
	}

	/**
	 * Localiza el fichero de configuracion: primero {@code -Dprofile-activator.config},
	 * si no {@code $MAVEN_HOME/conf/profile-activator.properties}.
	 */
	private File locateConfig(Properties userProperties, Properties systemProperties) {
		String override = firstNonBlank(
				userProperties.getProperty(CONFIG_PROPERTY),
				systemProperties.getProperty(CONFIG_PROPERTY),
				System.getProperty(CONFIG_PROPERTY));
		if (override != null) {
			return new File(override);
		}
		String mavenHome = System.getProperty("maven.home");
		if (mavenHome != null && !mavenHome.isEmpty()) {
			return new File(mavenHome, "conf/" + DEFAULT_CONFIG_NAME);
		}
		return null;
	}

	/**
	 * Evalua el fichero linea a linea, en orden. Cada valor calculado se inyecta
	 * de inmediato, de modo que las lineas siguientes pueden referenciar las
	 * propiedades ya calculadas.
	 */
	private void applyConfig(File config, Properties userProperties, Properties systemProperties,
			Properties pbrUserProperties, Set<String> preset) throws MavenExecutionException {

		List<String> lines;
		try {
			lines = Files.readAllLines(config.toPath(), StandardCharsets.UTF_8);
		} catch (IOException e) {
			throw new MavenExecutionException("No se pudo leer " + config, e);
		}

		Resolver resolver = resolver(userProperties, systemProperties);

		int number = 0;
		for (String raw : lines) {
			number++;
			String line = raw.trim();
			if (line.isEmpty() || line.charAt(0) == '#') {
				continue;
			}
			int eq = line.indexOf('=');
			if (eq <= 0) {
				throw new MavenExecutionException("Linea " + number + " invalida en "
						+ config.getName() + " (se esperaba 'clave = expresion'): " + line, config);
			}
			String key = line.substring(0, eq).trim();
			String exprSource = line.substring(eq + 1).trim();
			try {
				String value = PropertyExpression.parse(exprSource).evaluate(resolver);
				inject(key, value, userProperties, pbrUserProperties, preset);
			} catch (RuntimeException e) {
				throw new MavenExecutionException("Error evaluando '" + key + "' (linea " + number
						+ " de " + config.getName() + "): " + e.getMessage(), e);
			}
		}
	}

	/**
	 * Regla por defecto cuando no hay fichero de configuracion: calcula
	 * {@code environment.style} (y {@code cygwin.style} en Cygwin) a partir del
	 * SO y de la variable de entorno {@code CYGWIN}.
	 */
	private void applyBuiltinDefaults(Properties userProperties, Properties systemProperties,
			Properties pbrUserProperties, Set<String> preset) {

		String osName = System.getProperty("os.name", "").toLowerCase(Locale.ROOT);
		boolean windows = osName.contains("win");
		boolean cygwin = windows && (System.getenv("CYGWIN") != null);

		String environmentStyle;
		if (cygwin) {
			String cygwinStyle = firstNonBlank(
					userProperties.getProperty("cygwin.style"),
					systemProperties.getProperty("cygwin.style"),
					"posix");
			inject("cygwin.style", cygwinStyle, userProperties, pbrUserProperties, preset);
			// environment.style = ${cygwin.style} (respetando el valor efectivo).
			environmentStyle = userProperties.getProperty("cygwin.style");
		} else if (windows) {
			environmentStyle = "windows";
		} else {
			environmentStyle = "posix";
		}

		inject("environment.style", environmentStyle, userProperties, pbrUserProperties, preset);
	}

	/**
	 * Resolutor de identificadores para el mini-lenguaje: {@code env.X} es una
	 * variable de entorno; cualquier otro nombre es una propiedad existente
	 * (user &gt; system &gt; JVM). Devuelve {@code null} si no existe.
	 */
	private static Resolver resolver(Properties userProperties, Properties systemProperties) {
		return name -> {
			if (name.startsWith("env.")) {
				return System.getenv(name.substring(4));
			}
			String value = userProperties.getProperty(name);
			if (value == null) {
				value = systemProperties.getProperty(name);
			}
			if (value == null) {
				value = System.getProperty(name);
			}
			return value;
		};
	}

	/**
	 * Inyecta una propiedad calculada en las user properties (peticion y
	 * ProjectBuildingRequest), respetando un valor explicito del usuario (-D) y
	 * los valores nulos.
	 */
	private void inject(String name, String value, Properties userProperties,
			Properties pbrUserProperties, Set<String> preset) {

		if (value == null) {
			return;
		}
		if (preset.contains(name)) {
			info("'" + name + "' definida por el usuario, se respeta ("
					+ userProperties.getProperty(name) + ")");
			return;
		}
		userProperties.setProperty(name, value);
		if (pbrUserProperties != null) {
			pbrUserProperties.setProperty(name, value);
		}
		info("propiedad calculada '" + name + "' = '" + value + "'");
	}

	private static String firstNonBlank(String... values) {
		for (String value : values) {
			if (value != null && !value.trim().isEmpty()) {
				return value;
			}
		}
		return null;
	}

	private void info(String message) {
		if (logger != null) {
			logger.info(LOG_PREFIX + message);
		}
	}
}
