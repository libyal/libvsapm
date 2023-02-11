/*
 * Info handle
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
#include <file_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "info_handle.h"
#include "vsapmtools_libcerror.h"
#include "vsapmtools_libclocale.h"
#include "vsapmtools_libvsapm.h"

#define INFO_HANDLE_NOTIFY_STREAM	stdout

/* Copies a string of a decimal value to a 64-bit value
 * Returns 1 if successful or -1 on error
 */
int vsapmtools_system_string_copy_from_64_bit_in_decimal(
     const system_character_t *string,
     size_t string_size,
     uint64_t *value_64bit,
     libcerror_error_t **error )
{
	static char *function              = "vsapmtools_system_string_copy_from_64_bit_in_decimal";
	size_t string_index                = 0;
	system_character_t character_value = 0;
	uint8_t maximum_string_index       = 20;
	int8_t sign                        = 1;

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
	if( string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( value_64bit == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value 64-bit.",
		 function );

		return( -1 );
	}
	*value_64bit = 0;

	if( string[ string_index ] == (system_character_t) '-' )
	{
		string_index++;
		maximum_string_index++;

		sign = -1;
	}
	else if( string[ string_index ] == (system_character_t) '+' )
	{
		string_index++;
		maximum_string_index++;
	}
	while( string_index < string_size )
	{
		if( string[ string_index ] == 0 )
		{
			break;
		}
		if( string_index > (size_t) maximum_string_index )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_LARGE,
			 "%s: string too large.",
			 function );

			return( -1 );
		}
		*value_64bit *= 10;

		if( ( string[ string_index ] >= (system_character_t) '0' )
		 && ( string[ string_index ] <= (system_character_t) '9' ) )
		{
			character_value = (system_character_t) ( string[ string_index ] - (system_character_t) '0' );
		}
		else
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported character value: %" PRIc_SYSTEM " at index: %d.",
			 function,
			 string[ string_index ],
			 string_index );

			return( -1 );
		}
		*value_64bit += character_value;

		string_index++;
	}
	if( sign == -1 )
	{
		*value_64bit *= (uint64_t) -1;
	}
	return( 1 );
}

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle value already set.",
		 function );

		return( -1 );
	}
	*info_handle = memory_allocate_structure(
	                info_handle_t );

	if( *info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create info handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *info_handle,
	     0,
	     sizeof( info_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear info handle.",
		 function );

		goto on_error;
	}
	if( libvsapm_volume_initialize(
	     &( ( *info_handle )->input_volume ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input handle.",
		 function );

		goto on_error;
	}
	( *info_handle )->bytes_per_sector = 512;
	( *info_handle )->notify_stream    = INFO_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees an info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->input_volume != NULL )
		{
			if( libvsapm_volume_free(
			     &( ( *info_handle )->input_volume ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free input handle.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	info_handle->abort = 1;

	if( info_handle->input_volume != NULL )
	{
		if( libvsapm_volume_signal_abort(
		     info_handle->input_volume,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input handle to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the bytes per sector
 * Returns 1 if successful or -1 on error
 */
int info_handle_set_bytes_per_sector(
     info_handle_t *info_handle,
     const system_character_t *string,
     libcerror_error_t **error )
{
	static char *function = "info_handle_set_bytes_per_sector";
	size_t string_length  = 0;
	uint64_t value_64bit  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	string_length = system_string_length(
	                 string );

	if( vsapmtools_system_string_copy_from_64_bit_in_decimal(
	     string,
	     string_length + 1,
	     &value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy string to 64-bit decimal.",
		 function );

		return( -1 );
	}
	if( ( value_64bit != 512 )
	 && ( value_64bit != 1024 )
	 && ( value_64bit != 2048 )
	 && ( value_64bit != 4096 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unuspported bytes per sector value.",
		 function );

		return( -1 );
	}
	info_handle->bytes_per_sector = (off64_t) value_64bit;

	return( 1 );
}

/* Opens the input
 * Returns 1 if successful or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "info_handle_open_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libvsapm_volume_set_bytes_per_sector(
	     info_handle->input_volume,
	     info_handle->bytes_per_sector,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bytes per sector in input handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libvsapm_volume_open_wide(
	     info_handle->input_volume,
	     filename,
	     LIBVSAPM_OPEN_READ,
	     error ) != 1 )
#else
	if( libvsapm_volume_open(
	     info_handle->input_volume,
	     filename,
	     LIBVSAPM_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes the input
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libvsapm_volume_close(
	     info_handle->input_volume,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input handle.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Prints the partition status flags to the notify stream
 */
void info_handle_partition_status_flags_fprint(
      uint32_t status_flags,
      FILE *notify_stream )
{
	if( ( status_flags & 0x00000001UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs valid\n" );
	}
	if( ( status_flags & 0x00000002UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs allocated\n" );
	}
	if( ( status_flags & 0x00000004UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs in use\n" );
	}
	if( ( status_flags & 0x00000008UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tContains boot information\n" );
	}
	if( ( status_flags & 0x00000010UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs readable\n" );
	}
	if( ( status_flags & 0x00000020UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs writeable\n" );
	}
	if( ( status_flags & 0x00000040UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tBoot code is position independent\n" );
	}

	if( ( status_flags & 0x00000100UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tContains a chain-compatible driver\n" );
	}
	if( ( status_flags & 0x00000200UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tContains a real driver\n" );
	}
	if( ( status_flags & 0x00000400UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tContains a chain driver\n" );
	}

	if( ( status_flags & 0x40000000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tAutomatic mount at startup\n" );
	}
	if( ( status_flags & 0x80000000UL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs startup partition\n" );
	}
	fprintf(
	 notify_stream,
	 "\n" );
}

/* Prints the partition information
 * Returns 1 if successful or -1 on error
 */
int info_handle_partition_fprint(
     info_handle_t *info_handle,
     libvsapm_partition_t *partition,
     libcerror_error_t **error )
{
	char ascii_string[ 32 ];

	static char *function = "info_handle_partition_fprint";
	size64_t size         = 0;
	off64_t volume_offset = 0;
	uint32_t status_flags = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libvsapm_partition_get_type_string(
	     partition,
	     ascii_string,
	     32,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition type string.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tType\t\t\t: %s\n",
	 ascii_string );

	if( libvsapm_partition_get_name_string(
	     partition,
	     ascii_string,
	     32,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition name string.",
		 function );

		return( -1 );
	}
	if( ascii_string[ 0 ] != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tName\t\t\t: %s\n",
		 ascii_string );
	}
	if( libvsapm_partition_get_volume_offset(
	     partition,
	     &volume_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition offset.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tOffset\t\t\t: %" PRIi64 " (0x%08" PRIx64 ")\n",
	 volume_offset,
	 volume_offset );

	if( libvsapm_partition_get_size(
	     partition,
	     &size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition size.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tSize\t\t\t: %" PRIu64 "\n",
	 size );

	if( libvsapm_partition_get_status_flags(
	     partition,
	     &status_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve partition status flags.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tStatus flags\t\t: 0x%08" PRIx32 "\n",
	 status_flags );

	info_handle_partition_status_flags_fprint(
	 status_flags,
	 info_handle->notify_stream );

	return( 1 );
}

/* Prints the partitions information
 * Returns 1 if successful or -1 on error
 */
int info_handle_partitions_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libvsapm_partition_t *partition = NULL;
	static char *function           = "info_handle_partitions_fprint";
	uint32_t bytes_per_sector       = 0;
	int number_of_partitions        = 0;
	int partition_index             = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Apple Partition Map (APM) information:\n" );

	if( libvsapm_volume_get_bytes_per_sector(
	     info_handle->input_volume,
	     &bytes_per_sector,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of bytes per sector.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tBytes per sector\t: %" PRIu32 "\n",
	 bytes_per_sector );

	if( libvsapm_volume_get_number_of_partitions(
	     info_handle->input_volume,
	     &number_of_partitions,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of partitions.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tNumber of partitions\t: %d\n",
	 number_of_partitions );

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	if( number_of_partitions > 0 )
	{
		for( partition_index = 0;
		     partition_index < number_of_partitions;
		     partition_index++ )
		{
			fprintf(
			 info_handle->notify_stream,
			 "Partition: %d\n",
			 partition_index + 1 );

			if( libvsapm_volume_get_partition_by_index(
			     info_handle->input_volume,
			     partition_index,
			     &partition,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve partition: %d.",
				 function,
				 partition_index );

				goto on_error;
			}
			if( info_handle_partition_fprint(
			     info_handle,
			     partition,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print partition: %d information.",
				 function,
				 partition_index );

				goto on_error;
			}
			if( libvsapm_partition_free(
			     &partition,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free partition: %d.",
				 function,
				 partition_index );

				goto on_error;
			}
		}
	}
	return( 1 );

on_error:
	if( partition != NULL )
	{
		libvsapm_partition_free(
		 &partition,
		 NULL );
	}
	return( -1 );
}

