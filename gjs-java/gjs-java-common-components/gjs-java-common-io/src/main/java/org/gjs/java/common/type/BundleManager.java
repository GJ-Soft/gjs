package org.gjs.java.common.type;

import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Objects;
import java.util.ResourceBundle;
import java.util.concurrent.ConcurrentHashMap;

import org.apache.commons.lang3.StringUtils;
import org.gjs.java.common.constant.CommonIoConstants;
import org.gjs.java.common.util.BundleUtils;
import org.gjs.java.common.util.MDCUtils;
import org.gjs.java.common.util.ValidationUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * The Class BundleManager.
 *
 * Clase de utilidades generales de la librería Gjs
 *
 * Gestor de ResourceBundle para acceder a literales con gestión multi-idioma.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public class BundleManager {

	/** The Constant logger. */
	private static final Logger logger = LoggerFactory.getLogger(BundleManager.class);

	/** The bundles. */
	private final List<ResourceBundle> bundles;

	/** The multilaguage bundles. */
	private final Map<String, List<ResourceBundle>> multilaguageBundles;

	/**
	 * Instantiates a new bundle manager.
	 */
	public BundleManager() {
		bundles = new ArrayList<>();
		multilaguageBundles = new ConcurrentHashMap<>();
	}

	/**
	 * Instantiates a new bundle manager.
	 *
	 * @param bundle the bundle
	 */
	public BundleManager(ResourceBundle bundle) {
		this();
		addBundle(bundle);
	}

	/**
	 * Instantiates a new bundle manager.
	 *
	 * @param bundle the bundle
	 */
	public BundleManager(String bundle) {
		this(ResourceBundle.getBundle(bundle));
	}

	/**
	 * Adds the bundle.
	 *
	 * @param bundle the bundle
	 */
	public void addBundle(ResourceBundle bundle) {
		if (Objects.nonNull(bundle)) {
			final String localeText = BundleUtils.getLocalePart(bundle.getBaseBundleName());
			final Locale locale = ValidationUtils.validateLocale(localeText);
			if (Objects.isNull(locale)) {
				bundles.add(0, bundle);
			} else {
				if (!multilaguageBundles.containsKey(locale.toString())) {
					multilaguageBundles.put(locale.toString(), new ArrayList<>());
				}
				multilaguageBundles.get(locale.toString()).add(bundle);
			}
		}
	}

	/**
	 * Adds the bundle.
	 *
	 * @param bundle the bundle
	 */
	public void addBundle(String bundle) {
		addBundle(ResourceBundle.getBundle(bundle));
	}

	/**
	 * Checks if is multilanguage.
	 *
	 * @return true, if is multilanguage
	 */
	public boolean isMultilanguage() {
		return (multilaguageBundles.size() > 0);
	}

	/**
	 * Gets the message.
	 *
	 * @param key the key
	 * @return the message
	 */
	public String getMessage(String key) {
		return findMessage(key);
	}

	/**
	 * Gets the message.
	 *
	 * @param key    the key
	 * @param params the params
	 * @return the message
	 */
	public String getMessage(String key, Object... params) {
		String message = null;
		final String template = findMessage(key);
		if (Objects.nonNull(template)) {
			message = formatMessage(template, params);
		}
		return message;
	}

	/**
	 * Find message.
	 *
	 * @param key the key
	 * @return the string
	 */
	private String findMessage(String key) {
		Locale locale = null;
		if (isMultilanguage()) {
			locale = (Locale) MDCUtils.load(CommonIoConstants.MDC_LOCALE, Locale.class);
		}
		return findMessage(locale, key);
	}

	/**
	 * Gets the message.
	 *
	 * @param locale the locale
	 * @param key    the key
	 * @return the message
	 */
	public String getMessage(Locale locale, String key) {
		return findMessage(locale, key);
	}

	/**
	 * Gets the message.
	 *
	 * @param locale the locale
	 * @param key    the key
	 * @param params the params
	 * @return the message
	 */
	public String getMessage(Locale locale, String key, Object... params) {
		String message = null;
		final String template = findMessage(locale, key);
		if (Objects.nonNull(template)) {
			message = formatMessage(template, params);
		}
		return message;
	}

	/**
	 * Find message.
	 *
	 * @param locale the locale
	 * @param key    the key
	 * @return the string
	 */
	private String findMessage(Locale locale, String key) {
		String message = null;
		if (!StringUtils.isAllBlank(key)) {
			for (final ResourceBundle bundle : selectBundles(locale)) {
				if (bundle.keySet().contains(key)) {
					message = bundle.getString(key);
					break;
				}
			}
			if (Objects.isNull(message)) {
				logger.warn("No se ha definido un literal para {}", key);
			}
		}
		return message;
	}

	/**
	 * Select bundles.
	 *
	 * @param locale the locale
	 * @return the list
	 */
	private List<ResourceBundle> selectBundles(Locale locale) {
		List<ResourceBundle> listBundles = this.bundles;
		if (Objects.nonNull(locale) && this.multilaguageBundles.containsKey(locale.toString())) {
			listBundles = multilaguageBundles.get(locale.toString());
		}
		return listBundles;
	}

	/**
	 * Format message.
	 *
	 * @param template the template
	 * @param params   the params
	 * @return the string
	 */
	private String formatMessage(String template, Object... params) {
		String message = template;
		if (Objects.nonNull(template)) {
			int i = 0;
			while (template.contains("{}")) {
				template = StringUtils.replace(template, "{}", String.format("{%s}", i), 1);
				i = i + 1;
			}
			try {
				message = MessageFormat.format(template, params);
			} catch (final IllegalArgumentException e) {
				logger.warn("No se ha podido formatear el mensaje: {}", e.getMessage());
			}
		}
		return message;
	}

}
