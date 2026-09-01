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
 * The Class SampleStringEntity.
 *
 * Clase de datos de ejemplo de la librería Gjs
 *
 * Entidad de ejemplo con la clave primaria de tipo cadena.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@Getter
@Setter
@Entity
@Table(name = "SAMPLE_STRING_ENTITY")
public class SampleStringEntity {

    @Id
    @Column(length = 10)
    private String id;

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

    public SampleStringEntity() {
    }

    @Override
    public String toString() {
        return "SampleEntity [id=" + id + ", nombre=" + nombre + ", descripcion=" + descripcion + ", fechaAlta="
                + fechaAlta + ", fechaBaja=" + fechaBaja + ", activo=" + activo + "]";
    }

}
