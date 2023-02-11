/*
 * Library to access the Apple Partition Map (APM) volume system
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

#if !defined( _LIBVSAPM_H )
#define _LIBVSAPM_H

#include <libvsapm/codepage.h>
#include <libvsapm/definitions.h>
#include <libvsapm/error.h>
#include <libvsapm/extern.h>
#include <libvsapm/features.h>
#include <libvsapm/types.h>

#include <stdio.h>

#if defined( LIBVSAPM_HAVE_BFIO )
#include <libbfio.h>
#endif

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBVSAPM_EXTERN \
const char *libvsapm_get_version(
             void );

/* Returns the access flags for reading
 */
LIBVSAPM_EXTERN \
int libvsapm_get_access_flags_read(
     void );

/* Returns the access flags for reading and writing
 */
LIBVSAPM_EXTERN \
int libvsapm_get_access_flags_read_write(
     void );

/* Returns the access flags for writing
 */
LIBVSAPM_EXTERN \
int libvsapm_get_access_flags_write(
     void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_get_codepage(
     int *codepage,
     libvsapm_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_set_codepage(
     int codepage,
     libvsapm_error_t **error );

/* Determines if a volume contains an Apple Partition Map (APM) signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_check_volume_signature(
     const char *filename,
     libvsapm_error_t **error );

#if defined( LIBVSAPM_HAVE_WIDE_CHARACTER_TYPE )

/* Determines if a volume contains an Apple Partition Map (APM) signature
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_check_volume_signature_wide(
     const wchar_t *filename,
     libvsapm_error_t **error );

#endif /* defined( LIBVSAPM_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSAPM_HAVE_BFIO )

/* Determines if a volume contains an Apple Partition Map (APM) signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libvsapm_error_t **error );

#endif /* defined( LIBVSAPM_HAVE_BFIO ) */

/* -------------------------------------------------------------------------
 * Notify functions
 * ------------------------------------------------------------------------- */

/* Sets the verbose notification
 */
LIBVSAPM_EXTERN \
void libvsapm_notify_set_verbose(
      int verbose );

/* Sets the notification stream
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_notify_set_stream(
     FILE *stream,
     libvsapm_error_t **error );

/* Opens the notification stream using a filename
 * The stream is opened in append mode
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_notify_stream_open(
     const char *filename,
     libvsapm_error_t **error );

/* Closes the notification stream if opened using a filename
 * Returns 0 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_notify_stream_close(
     libvsapm_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBVSAPM_EXTERN \
void libvsapm_error_free(
      libvsapm_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_error_fprint(
     libvsapm_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_error_sprint(
     libvsapm_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_error_backtrace_fprint(
     libvsapm_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * The end-of-string character is not included in the return value
 * Returns the number of printed characters if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_error_backtrace_sprint(
     libvsapm_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Volume functions
 * ------------------------------------------------------------------------- */

/* Creates a volume
 * Make sure the value volume is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_volume_initialize(
     libvsapm_volume_t **volume,
     libvsapm_error_t **error );

/* Frees a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_volume_free(
     libvsapm_volume_t **volume,
     libvsapm_error_t **error );

/* Signals a volume to abort its current activity
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_volume_signal_abort(
     libvsapm_volume_t *volume,
     libvsapm_error_t **error );

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_volume_open(
     libvsapm_volume_t *volume,
     const char *filename,
     int access_flags,
     libvsapm_error_t **error );

#if defined( LIBVSAPM_HAVE_WIDE_CHARACTER_TYPE )

/* Opens a volume
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_volume_open_wide(
     libvsapm_volume_t *volume,
     const wchar_t *filename,
     int access_flags,
     libvsapm_error_t **error );

#endif /* defined( LIBVSAPM_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( LIBVSAPM_HAVE_BFIO )

/* Opens a volume using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_volume_open_file_io_handle(
     libvsapm_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvsapm_error_t **error );

#endif /* defined( LIBVSAPM_HAVE_BFIO ) */

/* Closes a volume
 * Returns 0 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_volume_close(
     libvsapm_volume_t *volume,
     libvsapm_error_t **error );

/* Retrieves the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_volume_get_bytes_per_sector(
     libvsapm_volume_t *volume,
     uint32_t *bytes_per_sector,
     libvsapm_error_t **error );

/* Sets the number of bytes per sector
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_volume_set_bytes_per_sector(
     libvsapm_volume_t *volume,
     uint32_t bytes_per_sector,
     libvsapm_error_t **error );

/* Retrieves the number of partitions
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_volume_get_number_of_partitions(
     libvsapm_volume_t *volume,
     int *number_of_partitions,
     libvsapm_error_t **error );

/* Retrieves a specific partition
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_volume_get_partition_by_index(
     libvsapm_volume_t *volume,
     int partition_index,
     libvsapm_partition_t **partition,
     libvsapm_error_t **error );

/* -------------------------------------------------------------------------
 * Partition functions
 * ------------------------------------------------------------------------- */

/* Frees a partition
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_partition_free(
     libvsapm_partition_t **partition,
     libvsapm_error_t **error );

/* Retrieves the ASCII encoded string of the partition name
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_partition_get_name_string(
     libvsapm_partition_t *partition,
     char *string,
     size_t string_size,
     libvsapm_error_t **error );

/* Retrieves the ASCII encoded string of the partition type
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_partition_get_type_string(
     libvsapm_partition_t *partition,
     char *string,
     size_t string_size,
     libvsapm_error_t **error );

/* Retrieves the partition status flags
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_partition_get_status_flags(
     libvsapm_partition_t *partition,
     uint32_t *status_flags,
     libvsapm_error_t **error );

/* Retrieves the partition offset relative to the start of the volume
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_partition_get_volume_offset(
     libvsapm_partition_t *partition,
     off64_t *volume_offset,
     libvsapm_error_t **error );

/* Reads (partition) data at the current offset into a buffer
 * Returns the number of bytes read or -1 on error
 */
LIBVSAPM_EXTERN \
ssize_t libvsapm_partition_read_buffer(
         libvsapm_partition_t *partition,
         void *buffer,
         size_t buffer_size,
         libvsapm_error_t **error );

/* Reads (partition) data at a specific offset
 * Returns the number of bytes read or -1 on error
 */
LIBVSAPM_EXTERN \
ssize_t libvsapm_partition_read_buffer_at_offset(
         libvsapm_partition_t *partition,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libvsapm_error_t **error );

/* Seeks a certain offset of the (partition) data
 * Returns the offset if seek is successful or -1 on error
 */
LIBVSAPM_EXTERN \
off64_t libvsapm_partition_seek_offset(
         libvsapm_partition_t *partition,
         off64_t offset,
         int whence,
         libvsapm_error_t **error );

/* Retrieves the current offset
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_partition_get_offset(
     libvsapm_partition_t *partition,
     off64_t *offset,
     libvsapm_error_t **error );

/* Retrieves the partition size
 * Returns 1 if successful or -1 on error
 */
LIBVSAPM_EXTERN \
int libvsapm_partition_get_size(
     libvsapm_partition_t *partition,
     size64_t *size,
     libvsapm_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSAPM_H ) */

