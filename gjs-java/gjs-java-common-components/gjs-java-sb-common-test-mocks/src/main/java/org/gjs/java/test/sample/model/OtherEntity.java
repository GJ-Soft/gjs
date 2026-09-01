package org.gjs.java.test.sample.model;

import java.util.Date;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Id;
import jakarta.persistence.Table;
import jakarta.persistence.Temporal;
import jakarta.persistence.TemporalType;
import lombok.Getter;
import lombok.Setter;

/**
 * The Class OtherEntity.
 *
 * Clase de datos de ejemplo de la librería Gjs
 *
 * Entidad de ejemplo, hermana de SampleEntity, para las pruebas que necesitan dos tablas distintas.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
@Entity
@Table(name = "OTHER_ENTITY")
public class OtherEntity {

    @Id
    @Column(precision = 10)
    private Long id;

    @Column(name = "NOMBRE", unique = true, nullable = false, length = 50)
    private String nombre;

    @Column(name = "DESCRIPCION", nullable = false, length = 250)
    private String descripcion;

    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "FECHA_ALTA", nullable = false, length = 7)
    private Date fechaAlta;

    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "FECHA_BAJA", length = 7)
    private Date fechaBaja;

    @Column(name = "ACTIVO", nullable = false, precision = 1, scale = 0)
    private Boolean activo;

    public OtherEntity() {
    }

    @Override
    public String toString() {
        return "OtherEntity [id=" + id + ", nombre=" + nombre + ", descripcion=" + descripcion + ", fechaAlta="
                + fechaAlta + ", fechaBaja=" + fechaBaja + ", activo=" + activo + "]";
    }

}
