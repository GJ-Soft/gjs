import unittest
from unittest.mock import patch, MagicMock
from ${package}.Main import main

class TestMain(unittest.TestCase):
    @patch('${package}.Main.${capitalizedName}Server')
    def testMainInstantiatesAndStarts(self, MockServer):
        # Crear una instancia simulada
        mockInstance = MockServer.return_value
        
        # Ejecutar main
        main()
        
        # Verificar que se instanció y se llamó al método start
        MockServer.assert_called_once()
        mockInstance.start.assert_called_once()