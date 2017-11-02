// Pulls in the Python API
#include <Python.h>
 
static PyObject * rand_srand(PyObject *self, PyObject *args) {
  PyObject *arg = NULL;
  int seed;

  if (! PyArg_ParseTuple(args, "|O", &arg)) {
    return NULL;
  }

  if (arg != NULL && PyInt_Check(arg) == 1) {
    seed = (int) PyInt_AsLong(arg);
  } else {
    seed = (int) clock();
  }

  srand(seed);

  return Py_BuildValue("");
}

static PyObject * rand_rand(PyObject *self, PyObject *args) {
  int n;
  if (! PyArg_ParseTuple(args, "i", &n)) {
    return NULL;
  }

  int ans = rand() % n;

  return Py_BuildValue("i", ans);
}
 
static PyMethodDef RandMethods[] = {
    {"srand", rand_srand, METH_VARARGS, "srand(seed)"},  
    {"rand", rand_rand, METH_VARARGS, "rand(0..n-1)"},
    {NULL, NULL, 0, NULL}
};
 
void initrand(void) {
    // Module's initialization function
    // Will be called again if you use Python's reload()
 
    PyImport_AddModule("rand");
    Py_InitModule("rand", RandMethods);
}
 
int main(int argc, char *argv[]) {
    Py_SetProgramName(argv[0]);
 
    Py_Initialize();
 
    initrand();
 
    return 0;
}
