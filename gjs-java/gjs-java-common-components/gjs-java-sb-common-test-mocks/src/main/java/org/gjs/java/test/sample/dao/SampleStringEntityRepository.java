package org.gjs.java.test.sample.dao;

import org.gjs.java.test.sample.model.SampleStringEntity;
import org.springframework.data.jpa.repository.JpaRepository;

/**
 * The Interface SampleStringEntityRepository.
 *
 * Interfaz de ejemplo de la librería Gjs
 *
 * Repositorio de ejemplo sobre SampleStringEntity, con clave de tipo cadena.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public interface SampleStringEntityRepository extends JpaRepository<SampleStringEntity, String> {

}
