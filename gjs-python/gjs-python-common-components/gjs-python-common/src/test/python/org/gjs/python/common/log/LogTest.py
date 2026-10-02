# LogTest.py
"""
Tests unitarios para Log.
"""

import logging
from logging.handlers import RotatingFileHandler
from pathlib import Path

import pytest

from org.gjs.python.common.log import Log


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def gjsHandlers() -> list:
    """
    Handlers del logger raíz puestos por Log.

    pytest inyecta los suyos (LogCaptureHandler) en el mismo logger, así que
    se filtran por su módulo de origen.
    """
    return [
        handler for handler in logging.getLogger().handlers
        if type(handler).__module__.startswith("logging")
    ]


def logFile(handler: logging.Handler) -> Path:
    """Ruta resuelta del fichero que escribe un handler de fichero."""
    return Path(handler.baseFilename).resolve()


# ---------------------------------------------------------------------------
# Fixture
# ---------------------------------------------------------------------------

@pytest.fixture(autouse=True)
def cleanLogging():
    """Quita del logger raíz lo que añada Log y restaura el nivel."""
    root = logging.getLogger()
    previous = list(root.handlers)
    level = root.level

    Log._logConfigured = False
    yield

    for handler in list(root.handlers):
        if handler not in previous:
            root.removeHandler(handler)
            handler.close()

    root.setLevel(level)
    Log._logConfigured = False


# ---------------------------------------------------------------------------
# configureConsole
# ---------------------------------------------------------------------------

class TestConfigureConsole:
    """Tests para Log.configureConsole()."""

    def testAddsAConsoleHandler(self):
        """Debe dejar un handler de consola en el logger raíz."""
        assert Log.configureConsole() is True

        handlers = gjsHandlers()
        assert len(handlers) == 1
        assert isinstance(handlers[0], logging.StreamHandler)

    def testHandlerHasTheFormatter(self):
        """
        Regresión: se configuraba el formato sobre un handler y se añadía otro
        distinto, sin formato.
        """
        Log.configureConsole()

        handler = gjsHandlers()[0]
        assert handler.formatter is not None
        assert handler.formatter._fmt == Log.LOG_FORMAT

    def testMarksAsConfigured(self):
        """Regresión: configureConsole() nunca marcaba el logging configurado."""
        assert Log.isConfigured() is False
        Log.configureConsole()
        assert Log.isConfigured() is True

    def testIsIdempotent(self):
        """Una segunda llamada no debe añadir otro handler."""
        Log.configureConsole()
        assert Log.configureConsole() is False
        assert len(gjsHandlers()) == 1

    def testSetsTheLevel(self):
        """El nivel pedido debe llegar al logger raíz."""
        Log.configureConsole(logging.DEBUG)
        assert logging.getLogger().level == logging.DEBUG


# ---------------------------------------------------------------------------
# configure
# ---------------------------------------------------------------------------

class TestConfigure:
    """Tests para Log.configure()."""

    def testWritesTheLogIntoTheGivenDirectory(self, tmp_path):
        """
        Regresión: 'directory' se recibía y no se usaba, así que el fichero
        acababa en el directorio de trabajo.
        """
        directory = tmp_path / "logs"

        assert Log.configure(directory, "miapp", console=False) is True

        handlers = [h for h in gjsHandlers() if isinstance(h, RotatingFileHandler)]
        assert len(handlers) == 1
        assert logFile(handlers[0]).parent == directory.resolve()
        assert logFile(handlers[0]).name == "miapp.log"

    def testCreatesTheDirectory(self, tmp_path):
        """El directorio de logs se crea si no existe."""
        directory = tmp_path / "no" / "existe"
        Log.configure(directory, "miapp", console=False)
        assert directory.is_dir()

    def testConsoleFalseAddsOnlyTheFileHandler(self, tmp_path):
        """Sin consola sólo debe quedar el handler de fichero."""
        Log.configure(tmp_path / "logs", "miapp", console=False)

        handlers = gjsHandlers()
        assert len(handlers) == 1
        assert isinstance(handlers[0], RotatingFileHandler)

    def testConsoleTrueAddsBothHandlers(self, tmp_path):
        """Con consola deben quedar los dos handlers."""
        Log.configure(tmp_path / "logs", "miapp", console=True)
        assert len(gjsHandlers()) == 2

    def testIsIdempotent(self, tmp_path):
        """Regresión: 'logConfigured = true' sin 'global' nunca surtía efecto."""
        assert Log.configure(tmp_path / "logs", "miapp", console=False) is True
        assert Log.isConfigured() is True
        assert Log.configure(tmp_path / "logs", "otra", console=False) is False
        assert len(gjsHandlers()) == 1

    def testDefaultAppName(self, tmp_path):
        """
        Regresión: appName venía anotado 'str | "application"' en lugar de
        llevar 'application' como valor por defecto.
        """
        Log.configure(tmp_path / "logs", console=False)
        assert logFile(gjsHandlers()[0]).name == "application.log"

    def testAcceptsAStringDirectory(self, tmp_path):
        """El directorio debe poder darse como cadena."""
        directory = tmp_path / "logs"
        assert Log.configure(str(directory), "miapp", console=False) is True
        assert directory.is_dir()


# ---------------------------------------------------------------------------
# configureFromFile
# ---------------------------------------------------------------------------

class TestConfigureFromFile:
    """Tests para Log.configureFromFile()."""

    def testReadsAYamlFile(self, tmp_path):
        """
        Regresión: se comparaba path.suffix ('.yml') con 'yml', así que la rama
        YAML no se tomaba nunca y siempre se caía en fileConfig.
        """
        f = tmp_path / "logging.yml"
        f.write_text("version: 1\nroot:\n  level: WARNING\n", encoding="utf-8")

        assert Log.configureFromFile(f) is True
        assert logging.getLogger().level == logging.WARNING

    def testAcceptsYamlExtension(self, tmp_path):
        """La extensión .yaml también debe tomar la rama YAML."""
        f = tmp_path / "logging.yaml"
        f.write_text("version: 1\nroot:\n  level: ERROR\n", encoding="utf-8")

        assert Log.configureFromFile(f) is True
        assert logging.getLogger().level == logging.ERROR

    def testMissingFileReturnsFalse(self, tmp_path):
        """Un fichero que no existe no configura nada y no lanza."""
        assert Log.configureFromFile(tmp_path / "no_existe.yml") is False
        assert Log.isConfigured() is False

    def testMarksAsConfigured(self, tmp_path):
        """Regresión: configureFromFile() nunca marcaba el logging configurado."""
        f = tmp_path / "logging.yml"
        f.write_text("version: 1\nroot:\n  level: INFO\n", encoding="utf-8")

        Log.configureFromFile(f)
        assert Log.isConfigured() is True

    def testIsIdempotent(self, tmp_path):
        """Una segunda llamada no vuelve a configurar."""
        f = tmp_path / "logging.yml"
        f.write_text("version: 1\nroot:\n  level: INFO\n", encoding="utf-8")

        assert Log.configureFromFile(f) is True
        assert Log.configureFromFile(f) is False


# ---------------------------------------------------------------------------
# reset
# ---------------------------------------------------------------------------

class TestReset:
    """Tests para Log.reset()."""

    def testRemovesTheHandlersAndClearsTheFlag(self, tmp_path):
        """reset() debe dejar el logger raíz limpio y sin configurar."""
        root = logging.getLogger()
        previous = list(root.handlers)

        Log.configure(tmp_path / "logs", "miapp", console=True)
        assert Log.isConfigured() is True

        Log.reset()
        try:
            assert root.handlers == []
            assert Log.isConfigured() is False
        finally:
            # Devolvemos los handlers que pytest tenía puestos.
            for handler in previous:
                root.addHandler(handler)

    def testAllowsReconfiguring(self, tmp_path):
        """Tras reset() se puede volver a configurar."""
        root = logging.getLogger()
        previous = list(root.handlers)

        Log.configureConsole()
        Log.reset()
        try:
            assert Log.configure(tmp_path / "logs", "miapp", console=False) is True
        finally:
            for handler in previous:
                root.addHandler(handler)
