#!/usr/bin/env python
import setuptools

from distutils.core import setup, Extension
from Cython.Build import cythonize

setuptools.setup(
    setup_requires=["setuptools_scm"],
    use_scm_version=True,
    ext_modules=cythonize("cythoncounter/cythoncounter.pyx") + [Extension('ccounter', sources=['ccounter/ccounter.c'])]
)
