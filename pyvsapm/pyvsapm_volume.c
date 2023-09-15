/*
 * Python object wrapper of libvsapm_volume_t
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvsapm_error.h"
#include "pyvsapm_file_object_io_handle.h"
#include "pyvsapm_libbfio.h"
#include "pyvsapm_libcerror.h"
#include "pyvsapm_libvsapm.h"
#include "pyvsapm_partition.h"
#include "pyvsapm_partitions.h"
#include "pyvsapm_python.h"
#include "pyvsapm_unused.h"
#include "pyvsapm_volume.h"

#if !defined( LIBVSAPM_HAVE_BFIO )

LIBVSAPM_EXTERN \
int libvsapm_volume_open_file_io_handle(
     libvsapm_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvsapm_error_t **error );

#endif /* !defined( LIBVSAPM_HAVE_BFIO ) */

PyMethodDef pyvsapm_volume_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pyvsapm_volume_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the volume to abort the current activity." },

	{ "open",
	  (PyCFunction) pyvsapm_volume_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a volume." },

	{ "open_file_object",
	  (PyCFunction) pyvsapm_volume_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a volume using a file-like object." },

	{ "close",
	  (PyCFunction) pyvsapm_volume_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a volume." },

	{ "get_bytes_per_sector",
	  (PyCFunction) pyvsapm_volume_get_bytes_per_sector,
	  METH_NOARGS,
	  "get_bytes_per_sector() -> Integer\n"
	  "\n"
	  "Retrieves the number of bytes per sector." },

	{ "get_number_of_partitions",
	  (PyCFunction) pyvsapm_volume_get_number_of_partitions,
	  METH_NOARGS,
	  "get_number_of_partitions() -> Integer\n"
	  "\n"
	  "Retrieves the number of partitions." },

	{ "get_partition",
	  (PyCFunction) pyvsapm_volume_get_partition,
	  METH_VARARGS | METH_KEYWORDS,
	  "get_partition(partition_index) -> Object\n"
	  "\n"
	  "Retrieves the partition specified by the index." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvsapm_volume_object_get_set_definitions[] = {

	{ "bytes_per_sector",
	  (getter) pyvsapm_volume_get_bytes_per_sector,
	  (setter) 0,
	  "The number of bytes per sector.",
	  NULL },

	{ "number_of_partitions",
	  (getter) pyvsapm_volume_get_number_of_partitions,
	  (setter) 0,
	  "The number of partitions.",
	  NULL },

	{ "partitions",
	  (getter) pyvsapm_volume_get_partitions,
	  (setter) 0,
	  "The partitions.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvsapm_volume_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvsapm.volume",
	/* tp_basicsize */
	sizeof( pyvsapm_volume_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvsapm_volume_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyvsapm volume object (wraps libvsapm_volume_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyvsapm_volume_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvsapm_volume_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyvsapm_volume_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Initializes a volume object
 * Returns 0 if successful or -1 on error
 */
int pyvsapm_volume_init(
     pyvsapm_volume_t *pyvsapm_volume )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsapm_volume_init";

	if( pyvsapm_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	/* Make sure libvsapm volume is set to NULL
	 */
	pyvsapm_volume->volume         = NULL;
	pyvsapm_volume->file_io_handle = NULL;

	if( libvsapm_volume_initialize(
	     &( pyvsapm_volume->volume ),
	     &error ) != 1 )
	{
		pyvsapm_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize volume.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a volume object
 */
void pyvsapm_volume_free(
      pyvsapm_volume_t *pyvsapm_volume )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvsapm_volume_free";
	int result                  = 0;

	if( pyvsapm_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvsapm_volume );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyvsapm_volume->file_io_handle != NULL )
	{
		if( pyvsapm_volume_close(
		     pyvsapm_volume,
		     NULL ) == NULL )
		{
			return;
		}
	}
	if( pyvsapm_volume->volume != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libvsapm_volume_free(
		          &( pyvsapm_volume->volume ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvsapm_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libvsapm volume.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	ob_type->tp_free(
	 (PyObject*) pyvsapm_volume );
}

/* Signals the volume to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsapm_volume_signal_abort(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments PYVSAPM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsapm_volume_signal_abort";
	int result               = 0;

	PYVSAPM_UNREFERENCED_PARAMETER( arguments )

	if( pyvsapm_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsapm_volume_signal_abort(
	          pyvsapm_volume->volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsapm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsapm_volume_open(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	const char *filename_narrow = NULL;
	static char *function       = "pyvsapm_volume_open";
	static char *keyword_list[] = { "filename", "mode", NULL };
	char *mode                  = NULL;
	int result                  = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	if( pyvsapm_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pyvsapm_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type Unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 3
		filename_wide = (wchar_t *) PyUnicode_AsWideCharString(
		                             string_object,
		                             NULL );
#else
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libvsapm_volume_open_wide(
		          pyvsapm_volume->volume,
		          filename_wide,
		          LIBVSAPM_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

#if PY_MAJOR_VERSION >= 3 && PY_MINOR_VERSION >= 3
		PyMem_Free(
		 filename_wide );
#endif
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pyvsapm_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert Unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
		                   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libvsapm_volume_open(
		          pyvsapm_volume->volume,
		          filename_narrow,
		          LIBVSAPM_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result != 1 )
		{
			pyvsapm_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pyvsapm_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
		                   string_object );
#else
		filename_narrow = PyString_AsString(
		                   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = libvsapm_volume_open(
		          pyvsapm_volume->volume,
		          filename_narrow,
		          LIBVSAPM_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvsapm_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open volume.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Opens a volume using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsapm_volume_open_file_object(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvsapm_volume_open_file_object";
	static char *keyword_list[] = { "file_object", "mode", NULL };
	char *mode                  = NULL;
	int result                  = 0;

	if( pyvsapm_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "read" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing read attribute.",
		 function );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_HasAttrString(
	          file_object,
	          "seek" );

	if( result != 1 )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported file object - missing seek attribute.",
		 function );

		return( NULL );
	}
	if( pyvsapm_volume->file_io_handle != NULL )
	{
		pyvsapm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: invalid volume - file IO handle already set.",
		 function );

		return( NULL );
	}
	if( pyvsapm_file_object_initialize(
	     &( pyvsapm_volume->file_io_handle ),
	     file_object,
	     &error ) != 1 )
	{
		pyvsapm_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsapm_volume_open_file_io_handle(
	          pyvsapm_volume->volume,
	          pyvsapm_volume->file_io_handle,
	          LIBVSAPM_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsapm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open volume.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pyvsapm_volume->file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( pyvsapm_volume->file_io_handle ),
		 NULL );
	}
	return( NULL );
}

/* Closes a volume
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsapm_volume_close(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments PYVSAPM_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsapm_volume_close";
	int result               = 0;

	PYVSAPM_UNREFERENCED_PARAMETER( arguments )

	if( pyvsapm_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsapm_volume_close(
	          pyvsapm_volume->volume,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		pyvsapm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close volume.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pyvsapm_volume->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pyvsapm_volume->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvsapm_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free libbfio file IO handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the number of bytes per sector
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsapm_volume_get_bytes_per_sector(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments PYVSAPM_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsapm_volume_get_bytes_per_sector";
	uint32_t value_32bit     = 0;
	int result               = 0;

	PYVSAPM_UNREFERENCED_PARAMETER( arguments )

	if( pyvsapm_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsapm_volume_get_bytes_per_sector(
	          pyvsapm_volume->volume,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsapm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of bytes per sector.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the number of partitions
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsapm_volume_get_number_of_partitions(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments PYVSAPM_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsapm_volume_get_number_of_partitions";
	int number_of_partitions = 0;
	int result               = 0;

	PYVSAPM_UNREFERENCED_PARAMETER( arguments )

	if( pyvsapm_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsapm_volume_get_number_of_partitions(
	          pyvsapm_volume->volume,
	          &number_of_partitions,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsapm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of partitions.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) number_of_partitions );
#else
	integer_object = PyInt_FromLong(
	                  (long) number_of_partitions );
#endif
	return( integer_object );
}

/* Retrieves a specific partition by index
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsapm_volume_get_partition_by_index(
           PyObject *pyvsapm_volume,
           int partition_index )
{
	PyObject *partition_object      = NULL;
	libcerror_error_t *error        = NULL;
	libvsapm_partition_t *partition = NULL;
	static char *function           = "pyvsapm_volume_get_partition_by_index";
	int result                      = 0;

	if( pyvsapm_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsapm_volume_get_partition_by_index(
	          ( (pyvsapm_volume_t *) pyvsapm_volume )->volume,
	          partition_index,
	          &partition,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsapm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve partition: %d.",
		 function,
		 partition_index );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	partition_object = pyvsapm_partition_new(
	                    partition,
	                    pyvsapm_volume );

	if( partition_object == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create partition object.",
		 function );

		goto on_error;
	}
	return( partition_object );

on_error:
	if( partition != NULL )
	{
		libvsapm_partition_free(
		 &partition,
		 NULL );
	}
	return( NULL );
}

/* Retrieves a specific partition
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsapm_volume_get_partition(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *partition_object  = NULL;
	static char *keyword_list[] = { "partition_index", NULL };
	int partition_index         = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "i",
	     keyword_list,
	     &partition_index ) == 0 )
	{
		return( NULL );
	}
	partition_object = pyvsapm_volume_get_partition_by_index(
	                    (PyObject *) pyvsapm_volume,
	                    partition_index );

	return( partition_object );
}

/* Retrieves a sequence and iterator object for the partitions
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsapm_volume_get_partitions(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments PYVSAPM_ATTRIBUTE_UNUSED )
{
	PyObject *sequence_object = NULL;
	libcerror_error_t *error  = NULL;
	static char *function     = "pyvsapm_volume_get_partitions";
	int number_of_partitions  = 0;
	int result                = 0;

	PYVSAPM_UNREFERENCED_PARAMETER( arguments )

	if( pyvsapm_volume == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid volume.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsapm_volume_get_number_of_partitions(
	          pyvsapm_volume->volume,
	          &number_of_partitions,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsapm_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve number of partitions.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	sequence_object = pyvsapm_partitions_new(
	                   (PyObject *) pyvsapm_volume,
	                   &pyvsapm_volume_get_partition_by_index,
	                   number_of_partitions );

	if( sequence_object == NULL )
	{
		pyvsapm_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to create sequence object.",
		 function );

		return( NULL );
	}
	return( sequence_object );
}

