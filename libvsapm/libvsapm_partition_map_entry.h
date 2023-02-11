/*
 * Partition map entry functions
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

#if !defined( _LIBVSAPM_PARTITION_MAP_ENTRY_H )
#define _LIBVSAPM_PARTITION_MAP_ENTRY_H

#include <common.h>
#include <types.h>

#include "libvsapm_libbfio.h"
#include "libvsapm_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsapm_partition_map_entry libvsapm_partition_map_entry_t;

struct libvsapm_partition_map_entry
{
	/* The number of entries
	 */
	uint32_t number_of_entries;

	/* The sector number
	 */
	uint32_t sector_number;

	/* The number of sectors
	 */
	uint32_t number_of_sectors;

	/* The name
	 */
	uint8_t name[ 33 ];

	/* The name length
	 */
	size_t name_length;

	/* The type
	 */
	uint8_t type[ 33 ];

	/* The type length
	 */
	size_t type_length;

	/* The status flags
	 */
	uint32_t status_flags;
};

int libvsapm_partition_map_entry_initialize(
     libvsapm_partition_map_entry_t **partition_map_entry,
     libcerror_error_t **error );

int libvsapm_partition_map_entry_free(
     libvsapm_partition_map_entry_t **partition_map_entry,
     libcerror_error_t **error );

int libvsapm_partition_map_entry_read_data(
     libvsapm_partition_map_entry_t *partition_map_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int libvsapm_partition_map_entry_read_file_io_handle(
     libvsapm_partition_map_entry_t *partition_map_entry,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libvsapm_partition_map_entry_get_sector_number(
     libvsapm_partition_map_entry_t *partition_map_entry,
     uint32_t *sector_number,
     libcerror_error_t **error );

int libvsapm_partition_map_entry_get_number_of_sectors(
     libvsapm_partition_map_entry_t *partition_map_entry,
     uint32_t *number_of_sectors,
     libcerror_error_t **error );

int libvsapm_partition_map_entry_get_name_string(
     libvsapm_partition_map_entry_t *partition_map_entry,
     char *string,
     size_t string_size,
     libcerror_error_t **error );

int libvsapm_partition_map_entry_get_type_string(
     libvsapm_partition_map_entry_t *partition_map_entry,
     char *string,
     size_t string_size,
     libcerror_error_t **error );

int libvsapm_partition_map_entry_get_status_flags(
     libvsapm_partition_map_entry_t *partition_map_entry,
     uint32_t *status_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSAPM_PARTITION_MAP_ENTRY_H ) */

