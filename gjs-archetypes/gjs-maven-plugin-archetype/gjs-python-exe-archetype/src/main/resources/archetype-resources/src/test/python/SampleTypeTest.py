#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
${symbol_pound}
${symbol_pound} Library ${name} 
${symbol_pound}
${symbol_pound} Test for Module SampleType.py
${symbol_pound}

import pytest
from SampleType import SampleType


class TestSampleTypeInit:
    """Tests del constructor."""

    def test_nombre_se_asigna_correctamente(self):
        muestra = SampleType("temperatura", 36.6)
        assert muestra.nombre == "temperatura"

    def test_valor_se_asigna_correctamente(self):
        muestra = SampleType("temperatura", 36.6)
        assert muestra.valor == 36.6

    def test_valor_cero(self):
        muestra = SampleType("vacio", 0.0)
        assert muestra.valor == 0.0

    def test_valor_negativo(self):
        muestra = SampleType("deuda", -100.0)
        assert muestra.valor == -100.0


class TestSampleTypeDescribir:
    """Tests del método describir."""

    def test_describir_formato_correcto(self):
        muestra = SampleType("presion", 101.3)
        assert muestra.describir() == "SampleType(nombre='presion', valor=101.3)"

    def test_repr_coincide_con_describir(self):
        muestra = SampleType("presion", 101.3)
        assert repr(muestra) == muestra.describir()


class TestSampleTypeIncrementar:
    """Tests del método incrementar."""

    def test_incrementar_valor_positivo(self):
        muestra = SampleType("contador", 10.0)
        muestra.incrementar(5.0)
        assert muestra.valor == 15.0

    def test_incrementar_valor_negativo(self):
        muestra = SampleType("contador", 10.0)
        muestra.incrementar(-3.0)
        assert muestra.valor == 7.0

    def test_incrementar_cero_no_cambia_valor(self):
        muestra = SampleType("contador", 10.0)
        muestra.incrementar(0)
        assert muestra.valor == 10.0

    def test_incrementar_varias_veces(self):
        muestra = SampleType("contador", 0.0)
        muestra.incrementar(1.0)
        muestra.incrementar(2.0)
        muestra.incrementar(3.0)
        assert muestra.valor == 6.0


class TestSampleTypeResetear:
    """Tests del método resetear."""

    def test_resetear_pone_valor_a_cero(self):
        muestra = SampleType("temperatura", 99.9)
        muestra.resetear()
        assert muestra.valor == 0.0

    def test_resetear_desde_cero_sigue_en_cero(self):
        muestra = SampleType("temperatura", 0.0)
        muestra.resetear()
        assert muestra.valor == 0.0

    def test_resetear_no_cambia_el_nombre(self):
        muestra = SampleType("temperatura", 50.0)
        muestra.resetear()
        assert muestra.nombre == "temperatura"


class TestSampleTypeIgualdad:
    """Tests del método __eq__."""

    def test_dos_instancias_iguales(self):
        a = SampleType("temperatura", 0.0)
        b = SampleType("temperatura", 0.0)
        assert a == b

    def test_distinto_nombre_no_son_iguales(self):
        a = SampleType("temperatura", 0.0)
        b = SampleType("presion", 0.0)
        assert a != b

    def test_distinto_valor_no_son_iguales(self):
        a = SampleType("temperatura", 1.0)
        b = SampleType("temperatura", 2.0)
        assert a != b

    def test_comparacion_con_otro_tipo_devuelve_not_implemented(self):
        muestra = SampleType("temperatura", 0.0)
        assert muestra.__eq__("otro tipo") is NotImplemented
