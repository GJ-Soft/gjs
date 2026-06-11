#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))

from unittest.mock import patch, MagicMock

from ${package}.client.${capitalizedName}Client import ${capitalizedName}Client
from ${package}.models.Models import ServerStatus




def test_get_server_status_ok():
    client = ${capitalizedName}Client(protocol="http", hostname="localhost", port="8000")

    fake_json = {
        "status": "OK",
        "date-time": "2026-03-22T09:50:00Z"
    }

    mock_response = MagicMock()
    mock_response.json.return_value = fake_json
    mock_response.raise_for_status.return_value = None

    mock_httpx_client = MagicMock()
    mock_httpx_client.get.return_value = mock_response

    mock_context_manager = MagicMock()
    mock_context_manager.__enter__.return_value = mock_httpx_client

    with patch("${package}.client.${capitalizedName}Client.httpx.Client", return_value=mock_context_manager):
        result = client.get_server_status()

    assert isinstance(result, ServerStatus)
    assert result.status == "OK"
    assert str(result.date_time) == "2026-03-22 09:50:00+00:00"
    mock_httpx_client.get.assert_called_once_with("http://${host}:${port}/status")