/*
 * Debug functions
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

#include "libvsapm_debug.h"
#include "libvsapm_libbfio.h"
#include "libvsapm_libcerror.h"
#include "libvsapm_libcnotify.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the partition status flags
 */
void libvsapm_debug_print_partition_status_flags(
      uint32_t partition_status_flags )
{
	if( ( partition_status_flags & 0x00000001UL ) != 0 )
	{
		libcnotify_printf(
		 "\tIs valid\n" );
	}
	if( ( partition_status_flags & 0x00000002UL ) != 0 )
	{
		libcnotify_printf(
		 "\tIs allocated\n" );
	}
	if( ( partition_status_flags & 0x00000004UL ) != 0 )
	{
		libcnotify_printf(
		 "\tIn use\n" );
	}
	if( ( partition_status_flags & 0x00000008UL ) != 0 )
	{
		libcnotify_printf(
		 "\tContains boot information\n" );
	}
	if( ( partition_status_flags & 0x00000010UL ) != 0 )
	{
		libcnotify_printf(
		 "\tIs readable\n" );
	}
	if( ( partition_status_flags & 0x00000020UL ) != 0 )
	{
		libcnotify_printf(
		 "\tIs writeable\n" );
	}
	if( ( partition_status_flags & 0x00000040UL ) != 0 )
	{
		libcnotify_printf(
		 "\tPosition independent boot code\n" );
	}

	if( ( partition_status_flags & 0x00000100UL ) != 0 )
	{
		libcnotify_printf(
		 "\tContains chain-compatible driver\n" );
	}
	if( ( partition_status_flags & 0x00000200UL ) != 0 )
	{
		libcnotify_printf(
		 "\tContains real driver\n" );
	}
	if( ( partition_status_flags & 0x00000400UL ) != 0 )
	{
		libcnotify_printf(
		 "\tContains chain driver\n" );
	}

	if( ( partition_status_flags & 0x40000000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tAutomatic mount at startup\n" );
	}
	if( ( partition_status_flags & 0x80000000UL ) != 0 )
	{
		libcnotify_printf(
		 "\tIs startup partition\n" );
	}
}

/* Prints the read offsets
 * Returns 1 if successful or -1 on error
 */
int libvsapm_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "libvsapm_debug_print_read_offsets";
	off64_t offset        = 0;
	size64_t size         = 0;
	int number_of_offsets = 0;
	int offset_iterator   = 0;

	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_number_of_offsets_read(
	     file_io_handle,
	     &number_of_offsets,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of offsets read.",
		 function );

		return( -1 );
	}
	libcnotify_printf(
	 "Offsets read:\n" );

	for( offset_iterator = 0;
	     offset_iterator < number_of_offsets;
	     offset_iterator++ )
	{
		if( libbfio_handle_get_offset_read(
		     file_io_handle,
		     offset_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset: %d.",
			 function,
			 offset_iterator );

			return( -1 );
		}
		libcnotify_printf(
		 "%08" PRIi64 " ( 0x%08" PRIx64 " ) - %08" PRIi64 " ( 0x%08" PRIx64 " ) size: %" PRIi64 "\n",
		 offset,
		 offset,
		 offset + (off64_t) size,
		 offset + (off64_t) size,
		 size );
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

