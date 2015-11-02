/*Comhghall McKeating
	C++ with Python embedded.*/

#include <Python.h>

int main(int argc, char *argv[]){
	PyObject *pName, *pModule, *pDict, *pFunc, *pValue;

	if(argc < 3){
		printf("ERROR: Insufficient number of arguments.\n");
		return 1;
	}
	
	Py_Initialize();
	PySys_SetArgv(argc, argv);
	pName = PyString_FromString(argv[1]);	
	pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);
	pFunc = PyDict_GetItemString(pDict, argv[2]);

	if(PyCallable_Check(pFunc)){
		PyObject_CallObject(pFunc, NULL);
	}

	else{
		PyErr_Print();
	}

	Py_DECREF(pModule);
	Py_DECREF(pName);
	Py_Finalize();

	return 0;
}
