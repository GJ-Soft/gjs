package org.gjs.java.test.sample.model;

import java.io.Serializable;
import java.util.Objects;

import jakarta.persistence.Column;
import jakarta.persistence.Embeddable;
import lombok.Getter;
import lombok.Setter;

/**
 * The Class SamplePK.
 *
 * Clase de datos de ejemplo de la librería Gjs
 *
 * Clave primaria compuesta de ejemplo, formada por los identificadores de las dos entidades que relaciona.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
@Embeddable
public class SamplePK implements Serializable {

	/**
	 *
	 */
	private static final long serialVersionUID = 1L;

	@Column(name = "SAMPLE_ID", insertable = false, updatable = false)
	private long sampleId;

	@Column(name = "OTHER_ID", insertable = false, updatable = false)
	private long otherId;

	public SamplePK() {
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#hashCode()
	 */

	@Override
	public int hashCode() {
		return Objects.hash(sampleId, otherId);
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
		if (obj == null) {
			return false;
		}
		if (!(obj instanceof SamplePK)) {
			return false;
		}
		final SamplePK other = (SamplePK) obj;
		return sampleId == other.sampleId && otherId == other.otherId;
	}

	/*
	 * (non-Javadoc)
	 *
	 * @see java.lang.Object#toString()
	 */

	@Override
	public String toString() {
		return "SamplePK [sampleId=" + sampleId + ", otherId=" + otherId + "]";
	}

}
