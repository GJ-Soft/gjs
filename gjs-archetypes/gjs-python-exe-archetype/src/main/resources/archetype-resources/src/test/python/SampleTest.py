#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
${symbol_pound}
${symbol_pound} Library ${name} 
${symbol_pound}
${symbol_pound} Test for Module Sample.py
${symbol_pound}


"""
SampleTest.py - Tests para las funciones sumar y esPar usando pytest
"""

import pytest
from ${package}.Sample import sumar, esPar


class TestSumar:
    """Tests para la función sumar."""

    def testSumaDosPositivos(self):
        assert sumar(3.0, 5.0) == 8.0

    def testSumaDosNegativos(self):
        assert sumar(-2.0, -4.0) == -6.0

    def testSumaPositivoYNegativo(self):
        assert sumar(10.0, -3.0) == 7.0

    def testSumaConCero(self):
        assert sumar(7.0, 0.0) == 7.0

    def testSumaDosCeros(self):
        assert sumar(0.0, 0.0) == 0.0

    def testSumaNumerosDecimales(self):
        assert sumar(1.5, 2.5) == pytest.approx(4.0)

    def testSumaEsConmutativa(self):
        assert sumar(3.0, 7.0) == sumar(7.0, 3.0)


class TestEsPar:
    """Tests para la función esPar."""

    def testNumeroParPositivo(self):
        assert esPar(4) is True

    def testNumeroImparPositivo(self):
        assert esPar(7) is False

    def testCeroEsPar(self):
        assert esPar(0) is True

    def testNumeroParNegativo(self):
        assert esPar(-8) is True

    def testNumeroImparNegativo(self):
        assert esPar(-3) is False

    def testUnoEsImpar(self):
        assert esPar(1) is False

    def testDosEsPar(self):
        assert esPar(2) is True

    @pytest.mark.parametrize("numero", [0, 2, 4, 6, 8, 100])
    def testParesParametrizado(self, numero):
        assert esPar(numero) is True

    @pytest.mark.parametrize("numero", [1, 3, 5, 7, 9, 101])
    def testImparesParametrizado(self, numero):
        assert esPar(numero) is False