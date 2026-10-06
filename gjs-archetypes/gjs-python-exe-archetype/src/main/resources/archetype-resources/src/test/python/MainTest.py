# MainTest.py
from ${package}.Main import main
import pytest


def testMainEjecucion(capsys):
    # capsys es un "fixture" de pytest que captura lo que sale por pantalla
    main()
# Capturamos la salida
    captured = capsys.readouterr()
    
    # Verificamos que aparezcan las frases que REALMENTE están en tu Main.py
    assert "Este es el ejecutable" in captured.out
    assert "Sistema operativo:" in captured.out
    assert "Versión de Python:" in captured.out