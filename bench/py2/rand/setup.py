from distutils.core import setup, Extension
 
ext = Extension('rand', sources=['randmodule.c'])
 
setup(name='rand', version='1.0', description='c rand', ext_modules=[ext])
