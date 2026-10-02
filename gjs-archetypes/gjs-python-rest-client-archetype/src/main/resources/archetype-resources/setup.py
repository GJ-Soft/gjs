#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $infoGroup = $groupId)
#set( $infoArtifact = $artifactId)
#set( $infoVersion = $version)
${symbol_pound}!/usr/bin/env python
${symbol_pound} -*- coding: utf-8 -*-

from setuptools import find_packages, setup

# Es 'gjs.python.version', no 'project.version': la nomenclatura de los
# artefactos Python no admite SNAPSHOT, y el parent lo traduce a -DEV.
VERSION = '${symbol_dollar}{gjs.python.version}'

if VERSION[ :1 ] == '$':
    raise RuntimeError(
        'setup.py no tiene versión: hay que ejecutarlo sobre la copia filtrada '
        'que Maven deja en target/classes, no sobre el original del módulo.'
    )

setup(
    name='${infoArtifact}',
    version=VERSION,
    description='Project Rest Client ${capitalizedName} in language Python',
    author='${author}',
    author_email='${authorMail}',
    python_requires='>=3.10',
    package_dir={'': 'src/main/python'},
    packages=find_packages(where='src/main/python'),
    install_requires=[],
    license='MIT',
)
