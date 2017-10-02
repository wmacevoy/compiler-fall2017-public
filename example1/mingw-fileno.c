// https://sourceforge.net/p/mingw/msys2-runtime/ci/607dfebc227d676f29b8eacfa9eb7e39818d0260/tree/newlib/libc/stdio/fileno.c#l59

#if defined(__MINGW32__) || defined(__MINGW64__)

#include <_ansi.h>
#include <stdio.h>
#include "local.h"

int
_DEFUN(fileno, (f),
       FILE * f)
{
  int result;
  CHECK_INIT (_REENT, f);
  _flockfile (f);
  result = __sfileno (f);
  _funlockfile (f);
  return result;
}

#endif