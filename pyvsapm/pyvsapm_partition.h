/*
 * Python object wrapper of libvsapm_partition_t
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

#if !defined( _PYVSAPM_PARTITION_H )
#define _PYVSAPM_PARTITION_H

#include <common.h>
#include <types.h>

#include "pyvsapm_libvsapm.h"
#include "pyvsapm_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvsapm_partition pyvsapm_partition_t;

struct pyvsapm_partition
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvsapm partition
	 */
	libvsapm_partition_t *partition;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pyvsapm_partition_object_methods[];
extern PyTypeObject pyvsapm_partition_type_object;

PyObject *pyvsapm_partition_new(
           libvsapm_partition_t *partition,
           PyObject *parent_object );

int pyvsapm_partition_init(
     pyvsapm_partition_t *pyvsapm_partition );

void pyvsapm_partition_free(
      pyvsapm_partition_t *pyvsapm_partition );

PyObject *pyvsapm_partition_get_name_string(
           pyvsapm_partition_t *pyvsapm_partition,
           PyObject *arguments );

PyObject *pyvsapm_partition_get_type_string(
           pyvsapm_partition_t *pyvsapm_partition,
           PyObject *arguments );

PyObject *pyvsapm_partition_get_volume_offset(
           pyvsapm_partition_t *pyvsapm_partition,
           PyObject *arguments );

PyObject *pyvsapm_partition_get_status_flags(
           pyvsapm_partition_t *pyvsapm_partition,
           PyObject *arguments );

PyObject *pyvsapm_partition_read_buffer(
           pyvsapm_partition_t *pyvsapm_partition,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsapm_partition_read_buffer_at_offset(
           pyvsapm_partition_t *pyvsapm_partition,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsapm_partition_seek_offset(
           pyvsapm_partition_t *pyvsapm_partition,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsapm_partition_get_offset(
           pyvsapm_partition_t *pyvsapm_partition,
           PyObject *arguments );

PyObject *pyvsapm_partition_get_size(
           pyvsapm_partition_t *pyvsapm_partition,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSAPM_PARTITION_H ) */

