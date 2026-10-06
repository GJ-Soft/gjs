#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
from unittest.mock import patch, MagicMock

from ${package}.Main import main

def testMainOk(capsys):
    fakeResult = {"status": "OK"}

    with patch("${package}.Main.${capitalizedName}Client") as MockClient:
        instance = MockClient.return_value
        instance.getServerStatus.return_value = fakeResult

        main()

    captured = capsys.readouterr()
    assert "Respuesta recibida" in captured.out
    assert "OK" in captured.out


def testMainError(capsys):
    with patch("${package}.Main.${capitalizedName}Client") as MockClient:
        instance = MockClient.return_value
        instance.getServerStatus.side_effect = Exception("boom")

        main()

    captured = capsys.readouterr()
    assert "Error en la llamada" in captured.out
    assert "boom" in captured.out