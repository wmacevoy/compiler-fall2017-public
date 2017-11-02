from distutils.core import setup, Extension
 
ext = Extension('rand', sources=['randmodule.c'])
 
setup(name='rand', version='1.0', description='clib rand/srand', ext_modules=[ext])
