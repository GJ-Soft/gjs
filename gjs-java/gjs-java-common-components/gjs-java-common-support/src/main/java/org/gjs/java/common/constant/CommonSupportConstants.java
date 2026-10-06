package org.gjs.java.common.constant;

import ch.qos.logback.classic.Level;

/**
 * The Class CommonSupportConstants.
 */
public final class CommonSupportConstants {

	/** The Constant RESOURCE_MAIL_TEMPLATE. */
	public static final String RESOURCE_MAIL_TEMPLATE = "mail";

	/** The Constant LOG_LEVEL_DEFAULT. */
	public static final Level LOG_LEVEL_DEFAULT = Level.INFO;

	/**
	 * Instantiates a new common support constants.
	 */
	private CommonSupportConstants() {
		throw new IllegalStateException(CommonBaseConstants.MSG_UTILITY_CLASS);
	}

}
