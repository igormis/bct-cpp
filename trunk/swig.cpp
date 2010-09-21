#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <Python.h>

/*
 * Converts a gsl_vector* to a Python list.
 */
PyObject* bct::from_gsl(const gsl_vector* v) {
	PyObject* list = PyList_New(v->size);
	for (int i = 0; i < (int)v->size; i++) {
		PyObject* value = PyFloat_FromDouble(gsl_vector_get(v, i));
		PyList_SetItem(list, i, value);
	}
	return list;
}

/*
 * Converts a gsl_matrix* to a Python list of lists.
 */
PyObject* bct::from_gsl(const gsl_matrix* m) {
	PyObject* list = PyList_New(m->size1);
	for (int i = 0; i < (int)m->size1; i++) {
		PyObject* row = PyList_New(m->size2);
		PyList_SetItem(list, i, row);
		for (int j = 0; j < (int)m->size2; j++) {
			PyObject* value = PyFloat_FromDouble(gsl_matrix_get(m, i, j));
			PyList_SetItem(row, j, value);
		}
	}
	return list;
}

/*
 * Converts a double* to a gsl_vector*.
 */
gsl_vector* bct::to_gslv(const double* array, int size) {
	gsl_vector* v = gsl_vector_alloc(size);
	for (int i = 0; i < size; i++) {
		gsl_vector_set(v, i, array[i]);
	}
	return v;
}

/*
 * Converts a double* to a gsl_matrix*.
 */
gsl_matrix* bct::to_gslm(const double* array, int size1, int size2) {
	gsl_matrix* m = gsl_matrix_alloc(size1, size2);
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			gsl_matrix_set(m, i, j, array[i * size2 + j]);
		}
	}
	return m;
}

/*
 * Converts a Python list to a gsl_vector*.
 */
gsl_vector* bct::to_gslv(PyObject* list) {
	int n = PyList_Size(list);
	gsl_vector* v = gsl_vector_alloc(n);
	for (int i = 0; i < n; i++) {
		double value = PyFloat_AsDouble(PyList_GetItem(list, i));
		gsl_vector_set(v, i, value);
	}
	return v;
}

/*
 * Converts a Python list of lists to a gsl_matrix*.
 */
gsl_matrix* bct::to_gslm(PyObject* list) {
	int n_rows = PyList_Size(list);
	int n_cols = PyList_Size(PyList_GetItem(list, 0));
	gsl_matrix* m = gsl_matrix_alloc(n_rows, n_cols);
	for (int i = 0; i < n_rows; i++) {
		PyObject* row = PyList_GetItem(list, i);
		for (int j = 0; j < n_cols; j++) {
			double value = PyFloat_AsDouble(PyList_GetItem(row, j));
			gsl_matrix_set(m, i, j, value);
		}
	}
	return m;
}