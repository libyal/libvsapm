/*
 * The volume functions
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

#if !defined( _LIBVSAPM_VOLUME_H )
#define _LIBVSAPM_VOLUME_H

#include <common.h>
#include <types.h>

#include "libvsapm_extern.h"
#include "libvsapm_io_handle.h"
#include "libvsapm_libbfio.h"
#include "libvsapm_libcdata.h"
#include "libvsapm_libcerror.h"
#include "libvsapm_libcthreads.h"
#include "libvsapm_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libvsapm_internal_volume libvsapm_internal_volume_t;

struct libvsapm_internal_volume
{
	/* The volume size
	 */
	size64_t size;

	/* The partitions array
	 */
	libcdata_array_t *partitions;

	/* The IO handle
	 */
	libvsapm_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* Value to indicate if bytes per sector was set by library
	 */
	uint8_t bytes_per_sector_set_by_library;

#if defined( HAVE_LIBVSAPM_MULTI_THREAD_SUPPORT )
	/* The read/write lock
	 */
	libcthreads_read_write_lock_t *read_write_lock;
#endif
};

LIBVSAPM_EXTERN \
int libvsapm_volume_initialize(
     libvsapm_volume_t **volume,
     libcerror_error_t **error );

LIBVSAPM_EXTERN \
int libvsapm_volume_free(
     libvsapm_volume_t **volume,
     libcerror_error_t **error );

LIBVSAPM_EXTERN \
int libvsapm_volume_signal_abort(
     libvsapm_volume_t *volume,
     libcerror_error_t **error );

LIBVSAPM_EXTERN \
int libvsapm_volume_open(
     libvsapm_volume_t *volume,
     char const *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBVSAPM_EXTERN \
int libvsapm_volume_open_wide(
     libvsapm_volume_t *volume,
     wchar_t const *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBVSAPM_EXTERN \
int libvsapm_volume_open_file_io_handle(
     libvsapm_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBVSAPM_EXTERN \
int libvsapm_volume_close(
     libvsapm_volume_t *volume,
     libcerror_error_t **error );

int libvsapm_internal_volume_open_read(
     libvsapm_internal_volume_t *internal_volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBVSAPM_EXTERN \
int libvsapm_volume_get_bytes_per_sector(
     libvsapm_volume_t *volume,
     uint32_t *bytes_per_sector,
     libcerror_error_t **error );

LIBVSAPM_EXTERN \
int libvsapm_volume_set_bytes_per_sector(
     libvsapm_volume_t *volume,
     uint32_t bytes_per_sector,
     libcerror_error_t **error );

LIBVSAPM_EXTERN \
int libvsapm_volume_get_number_of_partitions(
     libvsapm_volume_t *volume,
     int *number_of_partitions,
     libcerror_error_t **error );

LIBVSAPM_EXTERN \
int libvsapm_volume_get_partition_by_index(
     libvsapm_volume_t *volume,
     int partition_index,
     libvsapm_partition_t **partition,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSAPM_VOLUME_H ) */

