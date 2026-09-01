package org.gjs.java.test.sample.model;

import jakarta.persistence.EmbeddedId;
import jakarta.persistence.Entity;
import jakarta.persistence.FetchType;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.Table;
import lombok.Getter;
import lombok.Setter;

/**
 * The Class SampleWithPKEntity.
 *
 * Clase de datos de ejemplo de la librería Gjs
 *
 * Entidad de ejemplo con clave primaria compuesta, la de SamplePK, y referencia a las dos entidades que enlaza.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
@Entity
@Table(name = "SAMPLE_WITHPK_ENTITY")
public class SampleWithPKEntity {

	public SampleWithPKEntity() {
	}

	@EmbeddedId
	private SamplePK id;

	// bi-directional many-to-one association to Notificacion
	@ManyToOne(fetch = FetchType.LAZY)
	@JoinColumn(name = "SAMPLE_ID", nullable = false, insertable = false, updatable = false)
	private SampleEntity sample;

	// bi-directional many-to-one association to Usuario
	@ManyToOne(fetch = FetchType.LAZY)
	@JoinColumn(name = "OTHER_ID", nullable = false, insertable = false, updatable = false)
	private OtherEntity other;

	@Override
	public String toString() {
		return "SampleWithPKEntity [id=" + id + "]";
	}

}
