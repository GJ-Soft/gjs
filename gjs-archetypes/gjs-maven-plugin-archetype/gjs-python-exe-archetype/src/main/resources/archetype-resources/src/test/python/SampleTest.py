#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
${symbol_pound}
${symbol_pound} Library ${name} 
${symbol_pound}
${symbol_pound} Test for Module Sample.py
${symbol_pound}


"""
test_sample.py - Tests para las funciones sumar y es_par usando pytest
"""

import pytest
from Sample import sumar, es_par


class TestSumar:
    """Tests para la función sumar."""

    def test_suma_dos_positivos(self):
        assert sumar(3.0, 5.0) == 8.0

    def test_suma_dos_negativos(self):
        assert sumar(-2.0, -4.0) == -6.0

    def test_suma_positivo_y_negativo(self):
        assert sumar(10.0, -3.0) == 7.0

    def test_suma_con_cero(self):
        assert sumar(7.0, 0.0) == 7.0

    def test_suma_dos_ceros(self):
        assert sumar(0.0, 0.0) == 0.0

    def test_suma_numeros_decimales(self):
        assert sumar(1.5, 2.5) == pytest.approx(4.0)

    def test_suma_es_conmutativa(self):
        assert sumar(3.0, 7.0) == sumar(7.0, 3.0)


class TestEsPar:
    """Tests para la función es_par."""

    def test_numero_par_positivo(self):
        assert es_par(4) is True

    def test_numero_impar_positivo(self):
        assert es_par(7) is False

    def test_cero_es_par(self):
        assert es_par(0) is True

    def test_numero_par_negativo(self):
        assert es_par(-8) is True

    def test_numero_impar_negativo(self):
        assert es_par(-3) is False

    def test_uno_es_impar(self):
        assert es_par(1) is False

    def test_dos_es_par(self):
        assert es_par(2) is True

    @pytest.mark.parametrize("numero", [0, 2, 4, 6, 8, 100])
    def test_pares_parametrizado(self, numero):
        assert es_par(numero) is True

    @pytest.mark.parametrize("numero", [1, 3, 5, 7, 9, 101])
    def test_impares_parametrizado(self, numero):
        assert es_par(numero) is False