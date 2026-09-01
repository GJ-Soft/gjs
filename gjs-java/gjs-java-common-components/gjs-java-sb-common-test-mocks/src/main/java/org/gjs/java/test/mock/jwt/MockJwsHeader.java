package org.gjs.java.test.mock.jwt;

import java.net.URI;
import java.security.cert.X509Certificate;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import io.jsonwebtoken.JwsHeader;
import io.jsonwebtoken.security.PublicJwk;

/**
 * The Class MockJwsHeader.
 *
 * Clase de datos de la librería Gjs
 *
 * Mock de un JwsHeader.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockJwsHeader implements JwsHeader {

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ProtectedHeader#getJwkSetUrl() */

    @Override
    public URI getJwkSetUrl() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ProtectedHeader#getJwk() */

    @Override
    public PublicJwk<?> getJwk() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ProtectedHeader#getKeyId() */

    @Override
    public String getKeyId() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ProtectedHeader#getCritical() */

    @Override
    public Set<String> getCritical() {
        return new TreeSet<>();
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Header#getType() */

    @Override
    public String getType() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Header#getContentType() */

    @Override
    public String getContentType() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Header#getAlgorithm() */

    @Override
    public String getAlgorithm() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.Header#getCompressionAlgorithm() */

    @Override
    public String getCompressionAlgorithm() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#size() */

    @Override
    public int size() {
        return 0;
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#isEmpty() */

    @Override
    public boolean isEmpty() {
        return false;
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#containsKey(java.lang.Object) */

    @Override
    public boolean containsKey(Object key) {
        return false;
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#containsValue(java.lang.Object) */

    @Override
    public boolean containsValue(Object value) {
        return false;
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#get(java.lang.Object) */

    @Override
    public Object get(Object key) {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#put(java.lang.Object, java.lang.Object) */

    @Override
    public Object put(String key, Object value) {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#remove(java.lang.Object) */

    @Override
    public Object remove(Object key) {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#putAll(java.util.Map) */

    @Override
    public void putAll(Map<? extends String, ? extends Object> m) {
        // No hace nada
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#clear() */

    @Override
    public void clear() {
        // No hace nada
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#keySet() */

    @Override
    public Set<String> keySet() {
        return new TreeSet<>();
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#values() */

    @Override
    public Collection<Object> values() {
        return new ArrayList<>();
    }

    /* (non-Javadoc)
     *
     * @see java.util.Map#entrySet() */

    @Override
    public Set<Entry<String, Object>> entrySet() {
        return new TreeSet<>();
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.security.X509Accessor#getX509Url() */

    @Override
    public URI getX509Url() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.security.X509Accessor#getX509Chain() */

    @Override
    public List<X509Certificate> getX509Chain() {
        return new ArrayList<>();
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.security.X509Accessor#getX509Sha1Thumbprint() */

    @Override
    public byte[] getX509Sha1Thumbprint() {
        return new byte[] {};
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.security.X509Accessor#getX509Sha256Thumbprint() */

    @Override
    public byte[] getX509Sha256Thumbprint() {
        return new byte[] {};
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwsHeader#isPayloadEncoded() */

    @Override
    public boolean isPayloadEncoded() {
        return false;
    }

}
