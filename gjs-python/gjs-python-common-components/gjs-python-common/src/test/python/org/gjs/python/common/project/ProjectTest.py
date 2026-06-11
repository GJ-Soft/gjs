# ProjectTest.py
"""
Tests unitarios para Project
"""

import pytest
import importlib
from pathlib import Path
from unittest.mock import patch, MagicMock


# ---------------------------------------------------------------------------
# Project
# ---------------------------------------------------------------------------

class TestProject:
    """Tests para Project.getProjectRoot()."""

    def test_returns_true_when_env_set(self):
        """Debe devolver True cuando MAVEN_TEST_PHASE es 'true'."""
        from org.gjs.python.common.project.Project import Project
        with patch.dict('os.environ', {'MAVEN_TEST_PHASE': 'true'}):
            assert Project.isTestEnvironment() is True

    def test_returns_false_when_env_not_set(self):
        """Debe devolver False cuando MAVEN_TEST_PHASE no está definida."""
        from org.gjs.python.common.project.Project import Project
        with patch.dict('os.environ', {}, clear=True):
            assert Project.isTestEnvironment() is False

    def test_returns_false_when_env_wrong_value(self):
        """Debe devolver False cuando MAVEN_TEST_PHASE tiene otro valor."""
        from org.gjs.python.common.project.Project import Project
        with patch.dict('os.environ', {'MAVEN_TEST_PHASE': 'false'}):
            assert Project.isTestEnvironment() is False

    def test_returns_false_when_env_empty(self):
        """Debe devolver False cuando MAVEN_TEST_PHASE está vacía."""
        from org.gjs.python.common.project.Project import Project
        with patch.dict('os.environ', {'MAVEN_TEST_PHASE': ''}):
            assert Project.isTestEnvironment() is False
