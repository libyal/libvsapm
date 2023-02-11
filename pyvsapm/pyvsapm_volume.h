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

#if !defined( _PYVSAPM_VOLUME_H )
#define _PYVSAPM_VOLUME_H

#include <common.h>
#include <types.h>

#include "pyvsapm_libbfio.h"
#include "pyvsapm_libvsapm.h"
#include "pyvsapm_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvsapm_volume pyvsapm_volume_t;

struct pyvsapm_volume
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The libvsapm volume
	 */
	libvsapm_volume_t *volume;

	/* The libbfio file IO handle
	 */
	libbfio_handle_t *file_io_handle;
};

extern PyMethodDef pyvsapm_volume_object_methods[];
extern PyTypeObject pyvsapm_volume_type_object;

int pyvsapm_volume_init(
     pyvsapm_volume_t *pyvsapm_volume );

void pyvsapm_volume_free(
      pyvsapm_volume_t *pyvsapm_volume );

PyObject *pyvsapm_volume_signal_abort(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments );

PyObject *pyvsapm_volume_open(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsapm_volume_open_file_object(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsapm_volume_close(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments );

PyObject *pyvsapm_volume_get_bytes_per_sector(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments );

PyObject *pyvsapm_volume_get_number_of_partitions(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments );

PyObject *pyvsapm_volume_get_partition_by_index(
           PyObject *pyvsapm_volume,
           int partition_index );

PyObject *pyvsapm_volume_get_partition(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pyvsapm_volume_get_partitions(
           pyvsapm_volume_t *pyvsapm_volume,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSAPM_VOLUME_H ) */

