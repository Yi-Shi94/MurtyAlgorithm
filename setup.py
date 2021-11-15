from setuptools import setup, Extension
import pybind11, os


functions_module = Extension(
    name='MurtyMiller',
    sources=['wrapper.cpp'],
    extra_compile_args=["-O3","-fPIC"],
    include_dirs=[os.path.dirname(pybind11.__file__)+'/include'],
)


setup (name = 'MurtyMiller',
       version = '1.0',
       description = 'This is a py wrapper for C++ implementation of Murty\'s Algorithm',
       author = 'Yi Shi',
       ext_modules = [functions_module])
