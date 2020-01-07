#!/usr/bin/env python
import setuptools

from distutils.core import setup, Extension

ccounter = Extension('ccounter', sources = ['ccounter/ccounter.c'])

setuptools.setup(
    setup_requires=["setuptools_scm"],
    use_scm_version=True,
    ext_modules = [ccounter]
)
