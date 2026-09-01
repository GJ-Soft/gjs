package org.gjs.java.test.mock.http;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.URI;
import java.util.Map;
import java.util.Objects;

import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpMethod;
import org.springframework.http.HttpStatus;
import org.springframework.http.client.ClientHttpRequest;
import org.springframework.http.client.ClientHttpResponse;

/**
 * The Class MockHttpClientRequest.
 *
 * Clase de datos de la librería Gjs
 *
 * Mock de un HttpClientRequest.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockHttpClientRequest implements ClientHttpRequest {

    /** The headers. */
    private HttpHeaders headers;

    /** The uri. */
    private URI uri;

    /** The method. */
    private HttpMethod method;

    /** The body. */
    private OutputStream body;

    /**
     * Instantiates a new mock http client request.
     */
    public MockHttpClientRequest() {
    }

    /**
     * Instantiates a new mock http client request.
     *
     * @param uri
     *            the uri
     * @param httpMethod
     *            the http method
     */
    public MockHttpClientRequest(URI uri, HttpMethod httpMethod) {
        this.uri = uri;
        this.method = httpMethod;
        headers = new HttpHeaders();
        body = new ByteArrayOutputStream();
    }

    /* (non-Javadoc)
     *
     * @see org.springframework.http.HttpRequest#getMethod() */

    @Override
    public HttpMethod getMethod() {
        return Objects.nonNull(method) ? method : null;
    }

    /* (non-Javadoc)
     *
     * @see org.springframework.http.HttpRequest#getURI() */

    @Override
    public URI getURI() {
        return uri;
    }

    /* (non-Javadoc)
     *
     * @see org.springframework.http.HttpMessage#getHeaders() */

    @Override
    public HttpHeaders getHeaders() {
        return headers;
    }

    /* (non-Javadoc)
     *
     * @see org.springframework.http.HttpOutputMessage#getBody() */

    @Override
    public OutputStream getBody() throws IOException {
        return body;
    }

    /* (non-Javadoc)
     *
     * @see org.springframework.http.client.ClientHttpRequest#execute() */

    @Override
    public ClientHttpResponse execute() throws IOException {
        return new MockHttpClientResponse(HttpStatus.OK);
    }

    @Override
    public Map<String, Object> getAttributes() {
        // TODO Auto-generated method stub
        return null;
    }

}
