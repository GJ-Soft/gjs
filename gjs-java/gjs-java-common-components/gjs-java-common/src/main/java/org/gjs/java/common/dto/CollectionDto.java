package org.gjs.java.common.dto;

import java.util.Collection;
import java.util.Objects;
import java.util.Set;
import java.util.TreeSet;

import com.fasterxml.jackson.annotation.JsonTypeInfo;

import lombok.Getter;
import lombok.Setter;

/**
 * The Class CollectionDto.
 *
 * Clase de datos de la librería Gjs
 *
 * Clase DTO genérica para almacenar una colección de objetos del tipo que sean.
 *
 * @param <T>
 *            la clase de objetos
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
@Getter
@Setter
public class CollectionDto<T> extends BaseDto {

    /** The Constant serialVersionUID. */
    private static final long serialVersionUID = -3197941037365727105L;

    /** The contenido. */
    @JsonTypeInfo(use = JsonTypeInfo.Id.CLASS, include = JsonTypeInfo.As.PROPERTY, property = "@class")
    private final transient Set<T> contenido;

    /**
     * Instantiates a new collection dto.
     */
    public CollectionDto() {
        contenido = new TreeSet<>();
    }

    /**
     * Instantiates a new collection dto.
     *
     * @param contenido
     *            the contenido
     */
    public CollectionDto(Collection<T> contenido) {
        this();
        if (Objects.nonNull(contenido)) {
            this.contenido.addAll(contenido);
        }
    }
}
