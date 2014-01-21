from distutils.core import setup, Extension
import os

mcradialpy = Extension(
    'mcradialpy',
    define_macros=[('MAJOR_VERSION', '1'), ('MINOR_VERSION', '0')],
    include_dirs=[os.path.abspath('../../../src/lib')],
    libraries=['mcradia', 'm', 'fftw'],
    library_dirs=[os.path.abspath('../gcc'), os.path.abspath('../../../ext_lib')],
    sources=[os.path.abspath('../../../src/bindings/python/mcradialpy.cpp')])

setup(name='MCRADIA Python interface',
      version='1.0',
      description='This is MCRADIA for Python',
      author='O. Chubar, A. Prodi et al.',
      author_email='chubar@bnl.gov, prodi@esrf.fr',
      url='http://github.com/aprodi/mcradia',
      long_description='''
This is MCRADIA for Python.
''',
      ext_modules=[mcradialpy])
