package org.gjs.java.test.mock.http;

import java.io.IOException;
import java.net.URI;

import org.springframework.http.HttpMethod;
import org.springframework.http.client.ClientHttpRequest;
import org.springframework.http.client.ClientHttpRequestFactory;

/**
 * The Class MockHttpClientRequest.
 *
 * Clase de datos de la librería Gjs
 *
 * Mock de un HttpClientRequestFactory.
 *
 * @author Gjs
 * @version 1.0.0
 * @since 1.0.0
 *
 */
public class MockHttpClientRequestFactory implements ClientHttpRequestFactory {

    /* (non-Javadoc)
     *
     * @see org.springframework.http.client.ClientHttpRequestFactory#createRequest(java.net.URI,
     * org.springframework.http.HttpMethod) */

    @Override
    public ClientHttpRequest createRequest(URI uri, HttpMethod httpMethod) throws IOException {
        return new MockHttpClientRequest(uri, httpMethod);
    }

}
