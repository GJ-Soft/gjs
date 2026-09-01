package org.gjs.java.test.mock.jwt;

import java.net.URI;
import java.security.cert.X509Certificate;
import java.util.List;
import java.util.Map;

import org.gjs.java.test.exception.DeprecatedException;

import io.jsonwebtoken.JwtBuilder;
import io.jsonwebtoken.JwtBuilder.BuilderHeader;
import io.jsonwebtoken.lang.NestedCollection;
import io.jsonwebtoken.security.PublicJwk;

/**
 * The Class MockBuilderHeader.
 *
 * Clase de datos de la librería Gjs
 *
 * Mock de un BuilderHeader.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockBuilderHeader implements BuilderHeader {

    /** The jwt builder. */
    private final JwtBuilder jwtBuilder;

    /**
     * Instantiates a new mock builder header.
     *
     * @param jwtBuilder
     *            the jwt builder
     */
    public MockBuilderHeader(MockJwtBuilder jwtBuilder) {
        this.jwtBuilder = jwtBuilder;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JweHeaderMutator#agreementPartyUInfo(byte[]) */

    @Override
    public BuilderHeader agreementPartyUInfo(byte[] info) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JweHeaderMutator#agreementPartyUInfo(java.lang.String) */

    @Override
    public BuilderHeader agreementPartyUInfo(String info) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JweHeaderMutator#agreementPartyVInfo(byte[]) */

    @Override
    public BuilderHeader agreementPartyVInfo(byte[] info) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JweHeaderMutator#agreementPartyVInfo(java.lang.String) */

    @Override
    public BuilderHeader agreementPartyVInfo(String info) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.JweHeaderMutator#pbes2Count(int) */

    @Override
    public BuilderHeader pbes2Count(int count) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ProtectedHeaderMutator#critical() */

    @Override
    public NestedCollection<String, BuilderHeader> critical() {
        return null;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ProtectedHeaderMutator#jwk(io.jsonwebtoken.security.PublicJwk) */

    @Override
    public BuilderHeader jwk(PublicJwk<?> jwk) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ProtectedHeaderMutator#jwkSetUrl(java.net.URI) */

    @Override
    public BuilderHeader jwkSetUrl(URI uri) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ProtectedHeaderMutator#keyId(java.lang.String) */

    @Override
    public BuilderHeader keyId(String kid) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ProtectedHeaderMutator#setKeyId(java.lang.String) */

    @Override
    public BuilderHeader setKeyId(String kid) {
        throw new DeprecatedException("setKeyId");
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.ProtectedHeaderMutator#setAlgorithm(java.lang.String) */

    @Override
    public BuilderHeader setAlgorithm(String alg) {
        throw new DeprecatedException("setAlgorithm");
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.HeaderMutator#type(java.lang.String) */

    @Override
    public BuilderHeader type(String typ) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.HeaderMutator#contentType(java.lang.String) */

    @Override
    public BuilderHeader contentType(String cty) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.HeaderMutator#setType(java.lang.String) */

    @Override
    public BuilderHeader setType(String typ) {
        throw new DeprecatedException("setType");
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.HeaderMutator#setContentType(java.lang.String) */

    @Override
    public BuilderHeader setContentType(String cty) {
        throw new DeprecatedException("setContentType");
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.HeaderMutator#setCompressionAlgorithm(java.lang.String) */

    @Override
    public BuilderHeader setCompressionAlgorithm(String zip) {
        throw new DeprecatedException("setCompressionAlgorithm");
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.lang.MapMutator#delete(java.lang.Object) */

    @Override
    public BuilderHeader delete(String key) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.lang.MapMutator#empty() */

    @Override
    public BuilderHeader empty() {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.lang.MapMutator#add(java.lang.Object, java.lang.Object) */

    @Override
    public BuilderHeader add(String key, Object value) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.lang.MapMutator#add(java.util.Map) */

    @Override
    public BuilderHeader add(Map<? extends String, ? extends Object> m) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.security.X509Mutator#x509Url(java.net.URI) */

    @Override
    public BuilderHeader x509Url(URI uri) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.security.X509Mutator#x509Chain(java.util.List) */

    @Override
    public BuilderHeader x509Chain(List<X509Certificate> chain) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.security.X509Mutator#x509Sha1Thumbprint(byte[]) */

    @Override
    public BuilderHeader x509Sha1Thumbprint(byte[] thumbprint) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.security.X509Mutator#x509Sha256Thumbprint(byte[]) */

    @Override
    public BuilderHeader x509Sha256Thumbprint(byte[] thumbprint) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.security.X509Builder#x509Sha1Thumbprint(boolean) */

    @Override
    public BuilderHeader x509Sha1Thumbprint(boolean enable) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.security.X509Builder#x509Sha256Thumbprint(boolean) */

    @Override
    public BuilderHeader x509Sha256Thumbprint(boolean enable) {
        return this;
    }

    /* (non-Javadoc)
     *
     * @see io.jsonwebtoken.lang.Conjunctor#and() */

    @Override
    public JwtBuilder and() {
        return jwtBuilder;
    }

}
