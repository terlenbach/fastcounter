#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "structmember.h"

typedef struct {
    PyObject_HEAD
    int value;
} ccounter;

static void ccounter_dealloc(ccounter* self) {
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject* ccounter_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    ccounter* self = (ccounter*)type->tp_alloc(type, 0);

    if (self != NULL) {
        self->value = 0;
    }

    return (PyObject*)self;
}

static int ccounter_init(ccounter* self, PyObject* args, PyObject* kwds) {
    static char* kwlist[] = {"value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|i", kwlist, &self->value)) {
        return -1;
    }

    return 0;
}

static PyMemberDef ccounter_members[] = {
    {"value", T_INT, offsetof(ccounter, value), 0,
     "ccounter value"},
    {NULL}
};

static PyObject* ccounter_increment_safe(ccounter* self, PyObject* Py_UNUSED(ignored)) {
    self->value++;
    Py_RETURN_NONE;
}

static PyMethodDef ccounter_methods[] = {
    {"increment_safe", (PyCFunction)ccounter_increment_safe, METH_NOARGS,
     "Increment the value by one"
    },
    {NULL}
};

static PyTypeObject ccounterType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "ccounter",
    .tp_doc = "ccounter",
    .tp_basicsize = sizeof(ccounter),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = ccounter_new,
    .tp_init = (initproc) ccounter_init,
    .tp_dealloc = (destructor) ccounter_dealloc,
    .tp_members = ccounter_members,
    .tp_methods = ccounter_methods,
};

static PyModuleDef ccountermodule = {
    PyModuleDef_HEAD_INIT,
    .m_name = "ccounter",
    .m_doc = "Counter holder with a safe increment method",
    .m_size = -1,
};

PyMODINIT_FUNC PyInit_ccounter(void) {
    PyObject* m = NULL;
    if (PyType_Ready(&ccounterType) < 0) {
        return NULL;
    }

    m = PyModule_Create(&ccountermodule);
    if (m == NULL) {
        return NULL;
    }

    Py_INCREF(&ccounterType);
    if (PyModule_AddObject(m, "ccounter", (PyObject *) &ccounterType) < 0) {
        Py_DECREF(&ccounterType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}