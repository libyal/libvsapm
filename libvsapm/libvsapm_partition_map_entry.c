/*
 * The partition map entry functions
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
#include <byte_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <types.h>

#include "libvsapm_debug.h"
#include "libvsapm_definitions.h"
#include "libvsapm_libcerror.h"
#include "libvsapm_libcnotify.h"
#include "libvsapm_partition_map_entry.h"

#include "vsapm_partition_map_entry.h"

/* Creates a partition map entry
 * Make sure the value partition_map_entry is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libvsapm_partition_map_entry_initialize(
     libvsapm_partition_map_entry_t **partition_map_entry,
     libcerror_error_t **error )
{
	static char *function = "libvsapm_partition_map_entry_initialize";

	if( partition_map_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition map entry.",
		 function );

		return( -1 );
	}
	if( *partition_map_entry != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid partition map entry value already set.",
		 function );

		return( -1 );
	}
	*partition_map_entry = memory_allocate_structure(
	                        libvsapm_partition_map_entry_t );

	if( *partition_map_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create partition map entry.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *partition_map_entry,
	     0,
	     sizeof( libvsapm_partition_map_entry_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear partition map entry.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *partition_map_entry != NULL )
	{
		memory_free(
		 *partition_map_entry );

		*partition_map_entry = NULL;
	}
	return( -1 );
}

/* Frees a partition map entry
 * Returns 1 if successful or -1 on error
 */
int libvsapm_partition_map_entry_free(
     libvsapm_partition_map_entry_t **partition_map_entry,
     libcerror_error_t **error )
{
	static char *function = "libvsapm_partition_map_entry_free";

	if( partition_map_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition map entry.",
		 function );

		return( -1 );
	}
	if( *partition_map_entry != NULL )
	{
		memory_free(
		 *partition_map_entry );

		*partition_map_entry = NULL;
	}
	return( 1 );
}

/* Reads a partition map entry
 * Returns 1 if successful or -1 on error
 */
int libvsapm_partition_map_entry_read_data(
     libvsapm_partition_map_entry_t *partition_map_entry,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "libvsapm_partition_map_entry_read_data";

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
	uint16_t value_16bit  = 0;
#endif

	if( partition_map_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition map entry.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size != sizeof( vsapm_partition_map_entry_t) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: partition map entry data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 sizeof( vsapm_partition_map_entry_t ),
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint32_big_endian(
	 ( (vsapm_partition_map_entry_t *) data )->number_of_entries,
	 partition_map_entry->number_of_entries );

	byte_stream_copy_to_uint32_big_endian(
	 ( (vsapm_partition_map_entry_t *) data )->start_sector,
	 partition_map_entry->sector_number );

	byte_stream_copy_to_uint32_big_endian(
	 ( (vsapm_partition_map_entry_t *) data )->number_of_sectors,
	 partition_map_entry->number_of_sectors );

	if( memory_copy(
	     partition_map_entry->name,
	     ( (vsapm_partition_map_entry_t *) data )->name,
	     32 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy name.",
		 function );

		return( -1 );
	}
	partition_map_entry->name[ 32 ] = 0;

	if( memory_copy(
	     partition_map_entry->type,
	     ( (vsapm_partition_map_entry_t *) data )->type,
	     32 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy type.",
		 function );

		return( -1 );
	}
	partition_map_entry->type[ 32 ] = 0;

	byte_stream_copy_to_uint32_big_endian(
	 ( (vsapm_partition_map_entry_t *) data )->status_flags,
	 partition_map_entry->status_flags );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t: %c%c\n",
		 function,
		 ( (vsapm_partition_map_entry_t *) data )->signature[ 0 ],
		 ( (vsapm_partition_map_entry_t *) data )->signature[ 1 ] );

		byte_stream_copy_to_uint16_big_endian(
		 ( (vsapm_partition_map_entry_t *) data )->unknown1,
		 value_16bit );
		libcnotify_printf(
		 "%s: unknown1\t\t\t: %" PRIu16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: number of entries\t\t: %" PRIu32 "\n",
		 function,
		 partition_map_entry->number_of_entries );

		libcnotify_printf(
		 "%s: start sector number\t\t: %" PRIu32 "\n",
		 function,
		 partition_map_entry->sector_number );

		libcnotify_printf(
		 "%s: number of sectors\t\t: %" PRIu32 "\n",
		 function,
		 partition_map_entry->number_of_sectors );

		libcnotify_printf(
		 "%s: name\t\t\t\t: %s\n",
		 function,
		 partition_map_entry->name );

		libcnotify_printf(
		 "%s: type\t\t\t\t: %s\n",
		 function,
		 partition_map_entry->type );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vsapm_partition_map_entry_t *) data )->data_area_start_sector,
		 value_32bit );
		libcnotify_printf(
		 "%s: data area start sector\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vsapm_partition_map_entry_t *) data )->data_area_number_of_sectors,
		 value_32bit );
		libcnotify_printf(
		 "%s: data area number of sectors\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: status flags\t\t\t: %" PRIu32 "\n",
		 function,
		 partition_map_entry->status_flags );
		libvsapm_debug_print_partition_status_flags(
		 partition_map_entry->status_flags );
		libcnotify_printf(
		 "\n" );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vsapm_partition_map_entry_t *) data )->boot_code_start_sector,
		 value_32bit );
		libcnotify_printf(
		 "%s: boot code start sector\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vsapm_partition_map_entry_t *) data )->boot_code_number_of_sectors,
		 value_32bit );
		libcnotify_printf(
		 "%s: boot code number of sectors\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vsapm_partition_map_entry_t *) data )->boot_code_address,
		 value_32bit );
		libcnotify_printf(
		 "%s: boot code address\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vsapm_partition_map_entry_t *) data )->unknown2,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown2\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vsapm_partition_map_entry_t *) data )->boot_code_entry_point,
		 value_32bit );
		libcnotify_printf(
		 "%s: boot code entry point\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_big_endian(
		 ( (vsapm_partition_map_entry_t *) data )->unknown3,
		 value_32bit );
		libcnotify_printf(
		 "%s: unknown3\t\t\t: %" PRIu32 "\n",
		 function,
		 value_32bit );

		libcnotify_printf(
		 "%s: processor type:\n",
		 function );
		libcnotify_print_data(
		 ( (vsapm_partition_map_entry_t *) data )->processor_type,
		 16,
		 0 );

		libcnotify_printf(
		 "%s: unknown4:\n",
		 function );
		libcnotify_print_data(
		 ( (vsapm_partition_map_entry_t *) data )->unknown4,
		 376,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

/* TODO check for ASCII only */
	partition_map_entry->name_length = narrow_string_length(
	                                    (char *) partition_map_entry->name );

	if( partition_map_entry->name_length >= 32 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid name length value out of bounds.",
		 function );

		return( -1 );
	}
/* TODO check for ASCII only */
	partition_map_entry->type_length = narrow_string_length(
	                                    (char *) partition_map_entry->type );

	if( ( partition_map_entry->type_length == 0 )
	 || ( partition_map_entry->type_length >= 32 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid type length value out of bounds.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the partition map entry
 * Returns 1 if successful or -1 on error
 */
int libvsapm_partition_map_entry_read_file_io_handle(
     libvsapm_partition_map_entry_t *partition_map_entry,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t partition_map_entry_data[ sizeof( vsapm_partition_map_entry_t ) ];

	static char *function = "libvsapm_partition_map_entry_read_file_io_handle";
	ssize_t read_count    = 0;

	if( partition_map_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition map entry.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading partition map entry at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              partition_map_entry_data,
	              sizeof( vsapm_partition_map_entry_t ),
	              file_offset,
	              error );

	if( read_count != (ssize_t) sizeof( vsapm_partition_map_entry_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read partition map entry data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		return( -1 );
	}
	if( libvsapm_partition_map_entry_read_data(
	     partition_map_entry,
	     partition_map_entry_data,
	     sizeof( vsapm_partition_map_entry_t ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read partition map entry.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the partition sector number
 * Returns 1 if successful or -1 on error
 */
int libvsapm_partition_map_entry_get_sector_number(
     libvsapm_partition_map_entry_t *partition_map_entry,
     uint32_t *sector_number,
     libcerror_error_t **error )
{
	static char *function = "libvsapm_partition_map_entry_get_sector_number";

	if( partition_map_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition map entry.",
		 function );

		return( -1 );
	}
	if( sector_number == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sector number.",
		 function );

		return( -1 );
	}
	*sector_number = partition_map_entry->sector_number;

	return( 1 );
}

/* Retrieves the partition number of sectors
 * Returns 1 if successful or -1 on error
 */
int libvsapm_partition_map_entry_get_number_of_sectors(
     libvsapm_partition_map_entry_t *partition_map_entry,
     uint32_t *number_of_sectors,
     libcerror_error_t **error )
{
	static char *function = "libvsapm_partition_map_entry_get_number_of_sectors";

	if( partition_map_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition map entry.",
		 function );

		return( -1 );
	}
	if( number_of_sectors == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of sectors.",
		 function );

		return( -1 );
	}
	*number_of_sectors = partition_map_entry->number_of_sectors;

	return( 1 );
}

/* Retrieves the ASCII encoded string of the partition name
 * Returns 1 if successful or -1 on error
 */
int libvsapm_partition_map_entry_get_name_string(
     libvsapm_partition_map_entry_t *partition_map_entry,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	static char *function = "libvsapm_partition_map_entry_get_name_string";

	if( partition_map_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition map entry.",
		 function );

		return( -1 );
	}
	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( ( string_size <= partition_map_entry->name_length )
	 || ( string_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid string size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     string,
	     partition_map_entry->name,
	     partition_map_entry->name_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy name string.",
		 function );

		return( -1 );
	}
	string[ partition_map_entry->name_length ] = 0;

	return( 1 );
}

/* Retrieves the ASCII encoded string of the partition type
 * Returns 1 if successful or -1 on error
 */
int libvsapm_partition_map_entry_get_type_string(
     libvsapm_partition_map_entry_t *partition_map_entry,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	static char *function = "libvsapm_partition_map_entry_get_type_string";

	if( partition_map_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition map entry.",
		 function );

		return( -1 );
	}
	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( ( string_size <= partition_map_entry->type_length )
	 || ( string_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid string size value out of bounds.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     string,
	     partition_map_entry->type,
	     partition_map_entry->type_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy type string.",
		 function );

		return( -1 );
	}
	string[ partition_map_entry->type_length ] = 0;

	return( 1 );
}

/* Retrieves the partition status flags
 * Returns 1 if successful or -1 on error
 */
int libvsapm_partition_map_entry_get_status_flags(
     libvsapm_partition_map_entry_t *partition_map_entry,
     uint32_t *status_flags,
     libcerror_error_t **error )
{
	static char *function = "libvsapm_partition_map_entry_get_status_flags";

	if( partition_map_entry == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid partition map entry.",
		 function );

		return( -1 );
	}
	if( status_flags == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid status flags.",
		 function );

		return( -1 );
	}
	*status_flags = partition_map_entry->status_flags;

	return( 1 );
}

