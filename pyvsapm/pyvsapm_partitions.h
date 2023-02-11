/*
 * Python object definition of the sequence and iterator object of partitions
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

#if !defined( _PYVSAPM_PARTITIONS_H )
#define _PYVSAPM_PARTITIONS_H

#include <common.h>
#include <types.h>

#include "pyvsapm_libvsapm.h"
#include "pyvsapm_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pyvsapm_partitions pyvsapm_partitions_t;

struct pyvsapm_partitions
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pyvsapm_partitions_type_object;

PyObject *pyvsapm_partitions_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pyvsapm_partitions_init(
     pyvsapm_partitions_t *sequence_object );

void pyvsapm_partitions_free(
      pyvsapm_partitions_t *sequence_object );

Py_ssize_t pyvsapm_partitions_len(
            pyvsapm_partitions_t *sequence_object );

PyObject *pyvsapm_partitions_getitem(
           pyvsapm_partitions_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pyvsapm_partitions_iter(
           pyvsapm_partitions_t *sequence_object );

PyObject *pyvsapm_partitions_iternext(
           pyvsapm_partitions_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYVSAPM_PARTITIONS_H ) */

