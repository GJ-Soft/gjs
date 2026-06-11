#set( $symbol_pound = '#' )
#set( $symbol_dollar = '$' )
#set( $symbol_escape = '\' )
#set( $capitalizedName = $shortName.substring(0,1).toUpperCase() + $shortName.substring(1))
#set( $infoGroup = $groupId)
#set( $infoArtifact = $artifactId)
#set( $infoVersion = $version)
#set( $pythonVersion = $version.replace("SNAPSHOT", "DEV"))
${symbol_pound}!/usr/bin/env python
${symbol_pound} -*- coding: utf-8 -*-

from setuptools import find_packages, setup

setup(
    name='${infoArtifact}',
    version='${pythonVersion}',
    description='Project ${capitalizedName} in language Python',
    author='${author}',
    author_email='${authorMail}',
    python_requires='>=3.6.0',
    package_dir={'': 'src/main/python'},
    packages=find_packages(where='src/main/python'),
    install_requires=[],
    license='MIT',
)
