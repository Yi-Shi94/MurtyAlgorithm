from setuptools import setup, Extension



functions_module = Extension(
    name='MurtyMiller',
    sources=['MurtyAlgorithm/wrapper.cpp'],
    extra_compile_args=["-O3","-fPIC"],
    include_dirs=['/home/users/ps/anaconda3/envs/sy3d/lib/python3.8/site-packages/pybind11/include'],
)


setup (name = 'MurtyMiller',
       version = '1.0',
       description = 'This is a py wrapper for C++ implementation of Murty\'s Algorithm',
       author = 'Yi Shi',
       ext_modules = [functions_module])
