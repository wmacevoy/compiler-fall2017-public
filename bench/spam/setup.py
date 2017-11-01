from distutils.core import setup, Extension
 
ext = Extension('spam', sources=['spammodule.c'])
 
setup(name='foo', version='1.0', description='Test description', ext_modules=[ext])
