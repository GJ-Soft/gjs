package org.gjs.java.test.mock.jwt;

import java.util.Date;
import java.util.HashMap;
import java.util.Set;

import io.jsonwebtoken.Claims;

/**
 * The Class MockClaims.
 *
 * Clase de datos de la librería Gjs
 *
 * Mock de un Claims.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */

public class MockClaims extends HashMap<String, Object> implements Claims {

    /** The Constant serialVersionUID. */
    private static final long serialVersionUID = -71218747532645211L;

    /** The subject. */
    private String subjectValue;

    /** The issued at. */
    private Date issuedAtValue;

    /** The expiration. */
    private Date expirationValue;

    /** The id. */
    private String idValue;

    /** The issuer. */
    private String issuerValue;

    /** The audience. */
    private Set<String> audienceValue;

    /** The notbefore. */
    private Date notBeforeValue;

    /**
     * Instantiates a new mock claims.
     */
    public MockClaims() {
    }

    /**
     * Instantiates a new mock claims.
     *
     * @param subject
     *            the subject
     * @param issuedAt
     *            the issued at
     * @param expiration
     *            the expiration
     */
    public MockClaims(String subject, Date issuedAt, Date expiration) {
        this.subjectValue = subject;
        this.issuedAtValue = issuedAt;
        this.expirationValue = expiration;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Claims#getIssuer() */

    @Override
    public String getIssuer() {
        return issuerValue;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Claims#getSubject() */

    @Override
    public String getSubject() {
        return subjectValue;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Claims#getAudience() */

    @Override
    public Set<String> getAudience() {
        return audienceValue;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Claims#getExpiration() */

    @Override
    public Date getExpiration() {
        return expirationValue;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Claims#getNotBefore() */

    @Override
    public Date getNotBefore() {
        return notBeforeValue;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Claims#getIssuedAt() */

    @Override
    public Date getIssuedAt() {
        return issuedAtValue;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Claims#getId() */

    @Override
    public String getId() {
        return idValue;
    }

    /**
     * Sets the subject.
     *
     * @param subjectValue
     *            the new subject
     */
    public void setSubject(String subjectValue) {
        this.subjectValue = subjectValue;
    }

    /**
     * Sets the issued at.
     *
     * @param issuedAtValue
     *            the new issued at
     */
    public void setIssuedAt(Date issuedAtValue) {
        this.issuedAtValue = issuedAtValue;
    }

    /**
     * Sets the expiration.
     *
     * @param expirationValue
     *            the new expiration
     */
    public void setExpiration(Date expirationValue) {
        this.expirationValue = expirationValue;
    }

    /**
     * Sets the id.
     *
     * @param idValue
     *            the new id
     */
    public void setId(String idValue) {
        this.idValue = idValue;
    }

    /**
     * Sets the issuer.
     *
     * @param issuerValue
     *            the new issuer
     */
    public void setIssuer(String issuerValue) {
        this.issuerValue = issuerValue;
    }

    /**
     * Sets the audience.
     *
     * @param audienceValue
     *            the new audience
     */
    public void setAudience(Set<String> audienceValue) {
        this.audienceValue = audienceValue;
    }

    /**
     * Sets the not before.
     *
     * @param notBeforeValue
     *            the new not before
     */
    public void setNotBefore(Date notBeforeValue) {
        this.notBeforeValue = notBeforeValue;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Claims#get(java.lang.String, java.lang.Class) */

    @SuppressWarnings("unchecked")
    @Override
    public <T> T get(String claimName, Class<T> requiredType) {
        T res = null;
        if (Claims.ISSUER.equals(claimName)) {
            res = (T) issuerValue;
        } else if (Claims.SUBJECT.equals(claimName)) {
            res = (T) subjectValue;
        } else if (Claims.AUDIENCE.equals(claimName)) {
            res = (T) audienceValue;
        } else if (Claims.EXPIRATION.equals(claimName)) {
            res = (T) expirationValue;
        } else if (Claims.NOT_BEFORE.equals(claimName)) {
            res = (T) notBeforeValue;
        } else if (Claims.ISSUED_AT.equals(claimName)) {
            res = (T) issuedAtValue;
        } else if (Claims.ID.equals(claimName)) {
            res = (T) idValue;
        }
        return res;
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.dto.EntidadDto#equals(java.lang.Object) */

    @Override
    public boolean equals(Object o) {
        return super.equals(o);
    }

    /* (non-Javadoc)
     *
     * @see org.gjs.java.dto.EntidadDto#hashCode() */

    @Override
    public int hashCode() {
        return super.hashCode();
    }

}
