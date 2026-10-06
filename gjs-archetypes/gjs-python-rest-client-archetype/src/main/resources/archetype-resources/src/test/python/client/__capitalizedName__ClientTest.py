#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))

from unittest.mock import patch, MagicMock

from ${package}.client.${capitalizedName}Client import ${capitalizedName}Client
from ${package}.models.Models import ServerStatus




def testGetServerStatusOk():
    client = ${capitalizedName}Client(protocol="http", hostname="localhost", port="8000")

    fakeJson = {
        "status": "OK",
        "date-time": "2026-03-22T09:50:00Z"
    }

    mockResponse = MagicMock()
    mockResponse.json.return_value = fakeJson
    mockResponse.raise_for_status.return_value = None

    mockHttpxClient = MagicMock()
    mockHttpxClient.get.return_value = mockResponse

    mockContextManager = MagicMock()
    mockContextManager.__enter__.return_value = mockHttpxClient

    with patch("${package}.client.${capitalizedName}Client.httpx.Client", return_value=mockContextManager):
        result = client.getServerStatus()

    assert isinstance(result, ServerStatus)
    assert result.status == "OK"
    assert str(result.date_time) == "2026-03-22 09:50:00+00:00"
    mockHttpxClient.get.assert_called_once_with("http://${host}:${port}/status")