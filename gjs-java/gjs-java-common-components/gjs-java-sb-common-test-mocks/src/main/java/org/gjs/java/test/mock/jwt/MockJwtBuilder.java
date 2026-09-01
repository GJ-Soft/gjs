package org.gjs.java.test.mock.jwt;

import java.io.InputStream;
import java.io.OutputStream;
import java.security.Key;
import java.security.Provider;
import java.security.SecureRandom;
import java.util.Date;
import java.util.Map;

import javax.crypto.SecretKey;

import org.gjs.java.common.supplier.random.RandomAlphanumericStringSupplier;

import io.jsonwebtoken.JwtBuilder;
import io.jsonwebtoken.SignatureAlgorithm;
import io.jsonwebtoken.io.CompressionAlgorithm;
import io.jsonwebtoken.io.Encoder;
import io.jsonwebtoken.io.Serializer;
import io.jsonwebtoken.security.AeadAlgorithm;
import io.jsonwebtoken.security.KeyAlgorithm;
import io.jsonwebtoken.security.SecureDigestAlgorithm;

/**
 * The Class MockJwtBuilder.
 *
 * Clase de datos de la librería Gjs
 *
 * Mock de un JwtBuilder.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
@SuppressWarnings("deprecation")
public class MockJwtBuilder implements JwtBuilder {

    /** The supplier. */
    private final RandomAlphanumericStringSupplier supplier = new RandomAlphanumericStringSupplier(1233, false, true);

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ClaimsMutator#setIssuer(java.lang.String) */

    @Override
    public JwtBuilder setIssuer(String iss) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ClaimsMutator#setSubject(java.lang.String) */

    @Override
    public JwtBuilder setSubject(String sub) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ClaimsMutator#setAudience(java.lang.String) */

    @Override
    public JwtBuilder setAudience(String aud) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ClaimsMutator#audience() */

    @Override
    public AudienceCollection<JwtBuilder> audience() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ClaimsMutator#setExpiration(java.util.Date) */

    @Override
    public JwtBuilder setExpiration(Date exp) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ClaimsMutator#setNotBefore(java.util.Date) */

    @Override
    public JwtBuilder setNotBefore(Date nbf) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ClaimsMutator#setIssuedAt(java.util.Date) */

    @Override
    public JwtBuilder setIssuedAt(Date iat) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ClaimsMutator#setId(java.lang.String) */

    @Override
    public JwtBuilder setId(String jti) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#provider(java.security.Provider) */

    @Override
    public JwtBuilder provider(Provider provider) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#random(java.security.SecureRandom) */

    @Override
    public JwtBuilder random(SecureRandom secureRandom) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#header() */

    @Override
    public BuilderHeader header() {
        return new MockBuilderHeader(this);
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#setHeader(java.util.Map) */

    @Override
    public JwtBuilder setHeader(Map<String, ?> map) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#setHeaderParams(java.util.Map) */

    @Override
    public JwtBuilder setHeaderParams(Map<String, ?> params) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#setHeaderParam(java.lang.String, java.lang.Object) */

    @Override
    public JwtBuilder setHeaderParam(String name, Object value) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#setPayload(java.lang.String) */

    @Override
    public JwtBuilder setPayload(String payload) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#content(java.lang.String) */

    @Override
    public JwtBuilder content(String content) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#content(byte[]) */

    @Override
    public JwtBuilder content(byte[] content) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#content(java.io.InputStream) */

    @Override
    public JwtBuilder content(InputStream in) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#content(java.lang.String, java.lang.String) */

    @Override
    public JwtBuilder content(String content, String cty) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#content(byte[], java.lang.String) */

    @Override
    public JwtBuilder content(byte[] content, String cty) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#content(java.io.InputStream, java.lang.String) */

    @Override
    public JwtBuilder content(InputStream content, String cty) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#claims() */

    @Override
    public BuilderClaims claims() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#setClaims(java.util.Map) */

    @Override
    public JwtBuilder setClaims(Map<String, ?> claims) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#addClaims(java.util.Map) */

    @Override
    public JwtBuilder addClaims(Map<String, ?> claims) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#claim(java.lang.String, java.lang.Object) */

    @Override
    public JwtBuilder claim(String name, Object value) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#claims(java.util.Map) */

    @Override
    public JwtBuilder claims(Map<String, ?> claims) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#issuer(java.lang.String) */

    @Override
    public JwtBuilder issuer(String iss) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#subject(java.lang.String) */

    @Override
    public JwtBuilder subject(String sub) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#expiration(java.util.Date) */

    @Override
    public JwtBuilder expiration(Date exp) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#notBefore(java.util.Date) */

    @Override
    public JwtBuilder notBefore(Date nbf) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#issuedAt(java.util.Date) */

    @Override
    public JwtBuilder issuedAt(Date iat) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#id(java.lang.String) */

    @Override
    public JwtBuilder id(String jti) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#signWith(java.security.Key) */

    @Override
    public JwtBuilder signWith(Key key) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#signWith(io.jsonwebtoken.SignatureAlgorithm, byte[]) */

    @Override
    public JwtBuilder signWith(SignatureAlgorithm alg, byte[] secretKey) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#signWith(io.jsonwebtoken.SignatureAlgorithm, java.lang.String) */

    @Override
    public JwtBuilder signWith(SignatureAlgorithm alg, String base64EncodedSecretKey) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#signWith(io.jsonwebtoken.SignatureAlgorithm, java.security.Key) */

    @Override
    public JwtBuilder signWith(SignatureAlgorithm alg, Key key) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#signWith(java.security.Key, io.jsonwebtoken.SignatureAlgorithm) */

    @Override
    public JwtBuilder signWith(Key key, SignatureAlgorithm alg) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#signWith(K, io.jsonwebtoken.security.SecureDigestAlgorithm) */

    @Override
    public <K extends Key> JwtBuilder signWith(K key, SecureDigestAlgorithm<? super K, ?> alg) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#encryptWith(javax.crypto.SecretKey, io.jsonwebtoken.security.AeadAlgorithm) */

    @Override
    public JwtBuilder encryptWith(SecretKey key, AeadAlgorithm enc) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#encryptWith(K, io.jsonwebtoken.security.KeyAlgorithm,
     * io.jsonwebtoken.security.AeadAlgorithm) */

    @Override
    public <K extends Key> JwtBuilder encryptWith(K key, KeyAlgorithm<? super K, ?> keyAlg, AeadAlgorithm enc) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#compressWith(io.jsonwebtoken.io.CompressionAlgorithm) */

    @Override
    public JwtBuilder compressWith(CompressionAlgorithm alg) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#base64UrlEncodeWith(io.jsonwebtoken.io.Encoder) */

    @Override
    public JwtBuilder base64UrlEncodeWith(Encoder<byte[], String> base64UrlEncoder) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#b64Url(io.jsonwebtoken.io.Encoder) */

    @Override
    public JwtBuilder b64Url(Encoder<OutputStream, OutputStream> encoder) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#encodePayload(boolean) */

    @Override
    public JwtBuilder encodePayload(boolean b64) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#serializeToJsonWith(io.jsonwebtoken.io.Serializer) */

    @Override
    public JwtBuilder serializeToJsonWith(Serializer<Map<String, ?>> serializer) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#json(io.jsonwebtoken.io.Serializer) */

    @Override
    public JwtBuilder json(Serializer<Map<String, ?>> serializer) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JwtBuilder#compact() */

    @Override
    public String compact() {
        return supplier.get();
    }

    /* (non-Javadoc)
     *
     * @see java.lang.Object#toString() */

    @Override
    public String toString() {
        return "Mocked JwtBuilder";
    }

}
