package org.gjs.java.common.enums;

/**
 * The Enum AuditLogType.
 *
 * Enumerado de la librería Gjs
 *
 * Contiene los tipos de registro de auditoría que se escriben en el log. Se una en la auditoría por aspectos.
 *
 * @author Gjs
 * @version 4.0.0
 * @since 3.0.0
 *
 */
public enum AuditLogType {

    /** The begin. */
    BEGIN("INI"),
    /** The end. */
    END("FIN"),
    /** The returns. */
    RETURNS("RET"),
    /** The throws. */
    THROWS("EXC"),
    /** The time warn. */
    TIME_WARN("TMW");

    /** The literal. */
    private String literal;

    /**
     * Instantiates a new audit log type.
     *
     * @param literal
     *            the literal
     */
    AuditLogType(String literal) {
        this.literal = literal;
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Enum#toString() */

    @Override
    public String toString() {
        return literal;
    }
}
