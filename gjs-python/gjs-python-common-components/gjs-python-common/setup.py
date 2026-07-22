#!/usr/bin/env python
# -*- coding: utf-8 -*-

from setuptools import find_packages, setup

setup(
    name='gjs-python-common',
    version='1.0.0-RC.2',
    description='Project Gjs-python-common in language Python',
    author='GJ Software',
    author_email='gjsoft@gmx.es',
    python_requires='>=3.6.0',
    package_dir={'': 'src/main/python'},
    packages=find_packages(where='src/main/python'),
    install_requires=[],
    license='MIT',
)
