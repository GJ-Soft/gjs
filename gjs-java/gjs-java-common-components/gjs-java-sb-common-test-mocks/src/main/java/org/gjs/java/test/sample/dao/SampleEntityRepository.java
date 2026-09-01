package org.gjs.java.test.sample.dao;

import org.gjs.java.test.sample.model.SampleEntity;
import org.springframework.data.jpa.repository.JpaRepository;

/**
 * The Interface SampleEntityRepository.
 *
 * Interfaz de ejemplo de la librería Gjs
 *
 * Repositorio de ejemplo sobre SampleEntity, con clave numérica.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public interface SampleEntityRepository extends JpaRepository<SampleEntity, Long> {

}
