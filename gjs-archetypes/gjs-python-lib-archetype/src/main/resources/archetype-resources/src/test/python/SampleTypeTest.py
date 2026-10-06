#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
${symbol_pound}
${symbol_pound} Library ${name} 
${symbol_pound}
${symbol_pound} Test for Module SampleType.py
${symbol_pound}

import pytest
from ${package}.SampleType import SampleType


class TestSampleTypeInit:
    """Tests del constructor."""

    def testNombreSeAsignaCorrectamente(self):
        muestra = SampleType("temperatura", 36.6)
        assert muestra.nombre == "temperatura"

    def testValorSeAsignaCorrectamente(self):
        muestra = SampleType("temperatura", 36.6)
        assert muestra.valor == 36.6

    def testValorCero(self):
        muestra = SampleType("vacio", 0.0)
        assert muestra.valor == 0.0

    def testValorNegativo(self):
        muestra = SampleType("deuda", -100.0)
        assert muestra.valor == -100.0


class TestSampleTypeDescribir:
    """Tests del método describir."""

    def testDescribirFormatoCorrecto(self):
        muestra = SampleType("presion", 101.3)
        assert muestra.describir() == "SampleType(nombre='presion', valor=101.3)"

    def testReprCoincideConDescribir(self):
        muestra = SampleType("presion", 101.3)
        assert repr(muestra) == muestra.describir()


class TestSampleTypeIncrementar:
    """Tests del método incrementar."""

    def testIncrementarValorPositivo(self):
        muestra = SampleType("contador", 10.0)
        muestra.incrementar(5.0)
        assert muestra.valor == 15.0

    def testIncrementarValorNegativo(self):
        muestra = SampleType("contador", 10.0)
        muestra.incrementar(-3.0)
        assert muestra.valor == 7.0

    def testIncrementarCeroNoCambiaValor(self):
        muestra = SampleType("contador", 10.0)
        muestra.incrementar(0)
        assert muestra.valor == 10.0

    def testIncrementarVariasVeces(self):
        muestra = SampleType("contador", 0.0)
        muestra.incrementar(1.0)
        muestra.incrementar(2.0)
        muestra.incrementar(3.0)
        assert muestra.valor == 6.0


class TestSampleTypeResetear:
    """Tests del método resetear."""

    def testResetearPoneValorACero(self):
        muestra = SampleType("temperatura", 99.9)
        muestra.resetear()
        assert muestra.valor == 0.0

    def testResetearDesdeCeroSigueEnCero(self):
        muestra = SampleType("temperatura", 0.0)
        muestra.resetear()
        assert muestra.valor == 0.0

    def testResetearNoCambiaElNombre(self):
        muestra = SampleType("temperatura", 50.0)
        muestra.resetear()
        assert muestra.nombre == "temperatura"


class TestSampleTypeIgualdad:
    """Tests del método __eq__."""

    def testDosInstanciasIguales(self):
        a = SampleType("temperatura", 0.0)
        b = SampleType("temperatura", 0.0)
        assert a == b

    def testDistintoNombreNoSonIguales(self):
        a = SampleType("temperatura", 0.0)
        b = SampleType("presion", 0.0)
        assert a != b

    def testDistintoValorNoSonIguales(self):
        a = SampleType("temperatura", 1.0)
        b = SampleType("temperatura", 2.0)
        assert a != b

    def testComparacionConOtroTipoDevuelveNotImplemented(self):
        muestra = SampleType("temperatura", 0.0)
        assert muestra.__eq__("otro tipo") is NotImplemented
