#!/usr/bin/env python
# -*- coding: utf-8 -*-

from setuptools import find_packages, setup


# Maven resuelve este token al copiar setup.py a target/classes, que es desde
# donde se ejecuta 'pip install .'. El original del módulo conserva el token a
# propósito: el pom es la única fuente de la versión.
#
# Es 'gjs.python.version', no 'project.version': la nomenclatura de los
# artefactos Python no admite SNAPSHOT, y el parent lo traduce a -DEV.
VERSION = '${gjs.python.version}'

if VERSION[ :1 ] == '$':
    raise RuntimeError(
        'setup.py no tiene versión: hay que ejecutarlo sobre la copia filtrada '
        'que Maven deja en target/classes, no sobre el original del módulo.'
    )


setup(
    name='gjs-python-common',
    version=VERSION,
    description='Project Gjs-python-common in language Python',
    author='GJ Software',
    author_email='gjsoft@gmx.es',
    python_requires='>=3.10',
    package_dir={'': 'src/main/python'},
    packages=find_packages(where='src/main/python'),
    install_requires=[
        'pydantic',
        'pyyaml',
        'requests',
    ],
    license='MIT',
)
