package org.gjs.java.common.dto;

import java.io.Serializable;
import java.util.Objects;

import org.apache.commons.lang3.builder.ToStringBuilder;
import org.apache.commons.lang3.builder.ToStringStyle;
import org.gjs.java.common.util.ConditionUtils;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class Credentials.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase para almacenar datos de credenciales de usuario.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
public class Credentials implements Serializable {

	/**
	 *
	 */
	private static final long serialVersionUID = -4638043376071570861L;

	/** The login. */
	private String login;

	/** The password. */
	private String password;

	/** The key. */
	private String key;

	/**
	 * Instantiates a new credentials.
	 */
	public Credentials() {
		// No hace nada
	}

	/**
	 * Instantiates a new credentials.
	 *
	 * @param login    the login
	 * @param password the password
	 */
	public Credentials(String login, String password) {
		this.login = login;
		this.password = password;
	}

	/**
	 * Instantiates a new credentials.
	 *
	 * @param login    the login
	 * @param password the password
	 * @param key      the key
	 */
	public Credentials(String login, String password, String key) {
		this.login = login;
		this.password = password;
		this.key = key;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#hashCode()
	 */

	@Override
	public int hashCode() {
		return Objects.hash(key, login, password);
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#equals(java.lang.Object)
	 */

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if (!(obj instanceof final Credentials other)) {
			return false;
		}
		return ConditionUtils.allAreTrue(Objects.equals(key, other.key), Objects.equals(login, other.login),
				Objects.equals(password, other.password));
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return new ToStringBuilder(this, ToStringStyle.SHORT_PREFIX_STYLE).append("login", login)
				.append("password", Objects.nonNull(password) ? "XXX" : "null")
				.append("key", Objects.nonNull(key) ? "XXX" : "null").toString();
	}

}
