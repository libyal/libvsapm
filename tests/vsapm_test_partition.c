/*
 * Library partition type test program
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_SYS_TIME_H )
#include <sys/time.h>
#endif

#include <time.h>

#include "vsapm_test_functions.h"
#include "vsapm_test_getopt.h"
#include "vsapm_test_libbfio.h"
#include "vsapm_test_libcerror.h"
#include "vsapm_test_libvsapm.h"
#include "vsapm_test_macros.h"
#include "vsapm_test_memory.h"
#include "vsapm_test_rwlock.h"

#include "../libvsapm/libvsapm_io_handle.h"
#include "../libvsapm/libvsapm_partition.h"
#include "../libvsapm/libvsapm_partition_map_entry.h"

#if defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT )
#include "../libvsapm/libvsapm_volume.h"
#endif

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make vsapm_test_partition generate verbose output
#define VSAPM_TEST_PARTITION_VERBOSE
 */

#define VSAPM_TEST_PARTITION_READ_BUFFER_SIZE	4096

#if !defined( LIBVSAPM_HAVE_BFIO )

LIBVSAPM_EXTERN \
int libvsapm_check_volume_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBVSAPM_EXTERN \
int libvsapm_volume_open_file_io_handle(
     libvsapm_volume_t *volume,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libvsapm_error_t **error );

#endif /* !defined( LIBVSAPM_HAVE_BFIO ) */

/* Creates and opens a source volume
 * Returns 1 if successful or -1 on error
 */
int vsapm_test_volume_open_source(
     libvsapm_volume_t **volume,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "vsapm_test_volume_open_source";
	int result            = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
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
	if( libvsapm_volume_initialize(
	     volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize volume.",
		 function );

		goto on_error;
	}
	result = libvsapm_volume_open_file_io_handle(
	          *volume,
	          file_io_handle,
	          LIBVSAPM_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open volume.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *volume != NULL )
	{
		libvsapm_volume_free(
		 volume,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source volume
 * Returns 1 if successful or -1 on error
 */
int vsapm_test_volume_close_source(
     libvsapm_volume_t **volume,
     libcerror_error_t **error )
{
	static char *function = "vsapm_test_volume_close_source";
	int result            = 0;

	if( volume == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid volume.",
		 function );

		return( -1 );
	}
	if( libvsapm_volume_close(
	     *volume,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close volume.",
		 function );

		result = -1;
	}
	if( libvsapm_volume_free(
	     volume,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free volume.",
		 function );

		result = -1;
	}
	return( result );
}

#if defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT )

/* Tests the libvsapm_partition_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_partition_initialize(
     void )
{
	libcerror_error_t *error                            = NULL;
	libvsapm_io_handle_t *io_handle                     = NULL;
	libvsapm_partition_t *partition                     = NULL;
	libvsapm_partition_map_entry_t *partition_map_entry = NULL;
	int result                                          = 0;

#if defined( HAVE_VSAPM_TEST_MEMORY )
	int number_of_malloc_fail_tests                     = 2;
	int number_of_memset_fail_tests                     = 1;
	int test_number                                     = 0;
#endif

	/* Initialize test
	 */
	result = libvsapm_io_handle_initialize(
	          &io_handle,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_partition_map_entry_initialize(
	          &partition_map_entry,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "partition_map_entry",
	 partition_map_entry );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libvsapm_partition_initialize(
	          &partition,
	          io_handle,
	          NULL,
	          partition_map_entry,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_partition_free(
	          &partition,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsapm_partition_initialize(
	          NULL,
	          io_handle,
	          NULL,
	          partition_map_entry,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	partition = (libvsapm_partition_t *) 0x12345678UL;

	result = libvsapm_partition_initialize(
	          &partition,
	          io_handle,
	          NULL,
	          partition_map_entry,
	          &error );

	partition = NULL;

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsapm_partition_initialize(
	          &partition,
	          io_handle,
	          NULL,
	          NULL,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

/* TODO test libvsapm_partition_map_entry_get_size failing */

#if defined( HAVE_VSAPM_TEST_MEMORY )

	/* 1 fail in memory_allocate_structure
	 * 2 fail in libcthreads_read_write_lock_initialize
	 */
	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvsapm_partition_initialize with malloc failing
		 */
		vsapm_test_malloc_attempts_before_fail = test_number;

		result = libvsapm_partition_initialize(
		          &partition,
		          io_handle,
		          NULL,
		          partition_map_entry,
		          &error );

		if( vsapm_test_malloc_attempts_before_fail != -1 )
		{
			vsapm_test_malloc_attempts_before_fail = -1;

			if( partition != NULL )
			{
				libvsapm_partition_free(
				 &partition,
				 NULL );
			}
		}
		else
		{
			VSAPM_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSAPM_TEST_ASSERT_IS_NULL(
			 "partition",
			 partition );

			VSAPM_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	/* 1 fail in memset after memory_allocate_structure
	 */
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libvsapm_partition_initialize with memset failing
		 */
		vsapm_test_memset_attempts_before_fail = test_number;

		result = libvsapm_partition_initialize(
		          &partition,
		          io_handle,
		          NULL,
		          partition_map_entry,
		          &error );

		if( vsapm_test_memset_attempts_before_fail != -1 )
		{
			vsapm_test_memset_attempts_before_fail = -1;

			if( partition != NULL )
			{
				libvsapm_partition_free(
				 &partition,
				 NULL );
			}
		}
		else
		{
			VSAPM_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			VSAPM_TEST_ASSERT_IS_NULL(
			 "partition",
			 partition );

			VSAPM_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_VSAPM_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libvsapm_partition_map_entry_free(
	          &partition_map_entry,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "partition_map_entry",
	 partition_map_entry );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_io_handle_free(
	          &io_handle,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( partition != NULL )
	{
		libvsapm_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_map_entry != NULL )
	{
		libvsapm_partition_map_entry_free(
		 &partition_map_entry,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libvsapm_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsapm_partition_free function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_partition_free(
     void )
{
	libcerror_error_t *error                            = NULL;
	int result                                          = 0;

#if defined( HAVE_VSAPM_TEST_RWLOCK )
	libvsapm_io_handle_t *io_handle                     = NULL;
	libvsapm_partition_t *partition                     = NULL;
	libvsapm_partition_map_entry_t *partition_map_entry = NULL;
#endif

	/* Test error cases
	 */
	result = libvsapm_partition_free(
	          NULL,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSAPM_TEST_RWLOCK )

	/* Initialize test
	 */
	result = libvsapm_io_handle_initialize(
	          &io_handle,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_partition_map_entry_initialize(
	          &partition_map_entry,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "partition_map_entry",
	 partition_map_entry );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_partition_initialize(
	          &partition,
	          io_handle,
	          NULL,
	          partition_map_entry,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test libvsapm_partition_free with pthread_rwlock_destroy failing in libcthreads_read_write_lock_free
	 */
	vsapm_test_pthread_rwlock_destroy_attempts_before_fail = 0;

	result = libvsapm_partition_free(
	          &partition,
	          &error );

	if( vsapm_test_pthread_rwlock_destroy_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_destroy_attempts_before_fail = -1;

		/* Clean up
		 */
		result = libvsapm_partition_free(
		          &partition,
		          &error );

		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "partition",
		 partition );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "partition",
		 partition );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libvsapm_partition_map_entry_free(
	          &partition_map_entry,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "partition_map_entry",
	 partition_map_entry );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_io_handle_free(
	          &io_handle,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* defined( HAVE_VSAPM_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_VSAPM_TEST_RWLOCK )
	if( partition != NULL )
	{
		libvsapm_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_map_entry != NULL )
	{
		libvsapm_partition_map_entry_free(
		 &partition_map_entry,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libvsapm_io_handle_free(
		 &io_handle,
		 NULL );
	}
#endif /* defined( HAVE_VSAPM_TEST_RWLOCK ) */

	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT ) */

/* Tests the libvsapm_partition_get_type_string function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_partition_get_type_string(
     libvsapm_partition_t *partition )
{
	char ascii_string[ 32 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsapm_partition_get_type_string(
	          partition,
	          ascii_string,
	          32,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsapm_partition_get_type_string(
	          NULL,
	          ascii_string,
	          32,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsapm_partition_get_type_string(
	          partition,
	          NULL,
	          32,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsapm_partition_get_type_string(
	          partition,
	          ascii_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSAPM_TEST_RWLOCK )

	/* Test libvsapm_partition_get_type_string with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsapm_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsapm_partition_get_type_string(
	          partition,
	          ascii_string,
	          32,
	          &error );

	if( vsapm_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsapm_partition_get_type_string with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsapm_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsapm_partition_get_type_string(
	          partition,
	          ascii_string,
	          32,
	          &error );

	if( vsapm_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSAPM_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT )

/* Tests the libvsapm_internal_partition_read_buffer_from_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_internal_partition_read_buffer_from_file_io_handle(
     libvsapm_partition_t *partition )
{
	uint8_t buffer[ VSAPM_TEST_PARTITION_READ_BUFFER_SIZE ];

	libcerror_error_t *error          = NULL;
	time_t timestamp                  = 0;
	size64_t partition_size           = 0;
	size64_t remaining_partition_size = 0;
	size_t read_size                  = 0;
	ssize_t read_count                = 0;
	off64_t offset                    = 0;
	off64_t read_offset               = 0;
	int number_of_tests               = 1024;
	int random_number                 = 0;
	int result                        = 0;
	int test_number                   = 0;

	/* Determine size
	 */
	result = libvsapm_partition_get_size(
	          partition,
	          &partition_size,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libvsapm_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_size = VSAPM_TEST_PARTITION_READ_BUFFER_SIZE;

	if( partition_size < VSAPM_TEST_PARTITION_READ_BUFFER_SIZE )
	{
		read_size = (size_t) partition_size;
	}
	read_count = libvsapm_internal_partition_read_buffer_from_file_io_handle(
	              (libvsapm_internal_partition_t *) partition,
	              ( (libvsapm_internal_partition_t *) partition )->file_io_handle,
	              buffer,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) read_size );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( partition_size > 8 )
	{
		/* Set offset to partition_size - 8
		 */
		offset = libvsapm_partition_seek_offset(
		          partition,
		          -8,
		          SEEK_END,
		          &error );

		VSAPM_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 (int64_t) partition_size - 8 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer on partition_size boundary
		 */
		read_count = libvsapm_internal_partition_read_buffer_from_file_io_handle(
		              (libvsapm_internal_partition_t *) partition,
		              ( (libvsapm_internal_partition_t *) partition )->file_io_handle,
		              buffer,
		              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
		              &error );

		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond partition_size boundary
		 */
		read_count = libvsapm_internal_partition_read_buffer_from_file_io_handle(
		              (libvsapm_internal_partition_t *) partition,
		              ( (libvsapm_internal_partition_t *) partition )->file_io_handle,
		              buffer,
		              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
		              &error );

		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Stress test read buffer
	 */
	timestamp = time(
	             NULL );

	srand(
	 (unsigned int) timestamp );

	offset = libvsapm_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	remaining_partition_size = partition_size;

	for( test_number = 0;
	     test_number < number_of_tests;
	     test_number++ )
	{
		random_number = rand();

		VSAPM_TEST_ASSERT_GREATER_THAN_INT(
		 "random_number",
		 random_number,
		 -1 );

		read_size = (size_t) random_number % VSAPM_TEST_PARTITION_READ_BUFFER_SIZE;

#if defined( VSAPM_TEST_PARTITION_VERBOSE )
		fprintf(
		 stdout,
		 "libvsapm_partition_read_buffer: at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIzd "\n",
		 read_offset,
		 read_offset,
		 read_size );
#endif
		read_count = libvsapm_internal_partition_read_buffer_from_file_io_handle(
		              (libvsapm_internal_partition_t *) partition,
		              ( (libvsapm_internal_partition_t *) partition )->file_io_handle,
		              buffer,
		              read_size,
		              &error );

		if( read_size > remaining_partition_size )
		{
			read_size = (size_t) remaining_partition_size;
		}
		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) read_size );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		read_offset += read_count;

		result = libvsapm_partition_get_offset(
		          partition,
		          &offset,
		          &error );

		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSAPM_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 read_offset );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		remaining_partition_size -= read_count;

		if( remaining_partition_size == 0 )
		{
			offset = libvsapm_partition_seek_offset(
			          partition,
			          0,
			          SEEK_SET,
			          &error );

			VSAPM_TEST_ASSERT_EQUAL_INT64(
			 "offset",
			 offset,
			 (int64_t) 0 );

			VSAPM_TEST_ASSERT_IS_NULL(
			 "error",
			 error );

			read_offset = 0;

			remaining_partition_size = partition_size;
		}
	}
	/* Reset offset to 0
	 */
	offset = libvsapm_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libvsapm_internal_partition_read_buffer_from_file_io_handle(
	              NULL,
	              ( (libvsapm_internal_partition_t *) partition )->file_io_handle,
	              buffer,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvsapm_internal_partition_read_buffer_from_file_io_handle(
	              (libvsapm_internal_partition_t *) partition,
	              ( (libvsapm_internal_partition_t *) partition )->file_io_handle,
	              NULL,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvsapm_internal_partition_read_buffer_from_file_io_handle(
	              (libvsapm_internal_partition_t *) partition,
	              ( (libvsapm_internal_partition_t *) partition )->file_io_handle,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT ) */

/* Tests the libvsapm_partition_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_partition_read_buffer(
     libvsapm_partition_t *partition )
{
	uint8_t buffer[ VSAPM_TEST_PARTITION_READ_BUFFER_SIZE ];

	libcerror_error_t *error          = NULL;
	time_t timestamp                  = 0;
	size64_t partition_size           = 0;
	size64_t remaining_partition_size = 0;
	size_t read_size                  = 0;
	ssize_t read_count                = 0;
	off64_t offset                    = 0;
	off64_t read_offset               = 0;
	int number_of_tests               = 1024;
	int random_number                 = 0;
	int result                        = 0;
	int test_number                   = 0;

	/* Determine size
	 */
	result = libvsapm_partition_get_size(
	          partition,
	          &partition_size,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libvsapm_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_size = VSAPM_TEST_PARTITION_READ_BUFFER_SIZE;

	if( partition_size < VSAPM_TEST_PARTITION_READ_BUFFER_SIZE )
	{
		read_size = (size_t) partition_size;
	}
	read_count = libvsapm_partition_read_buffer(
	              partition,
	              buffer,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) read_size );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( partition_size > 8 )
	{
		/* Set offset to partition_size - 8
		 */
		offset = libvsapm_partition_seek_offset(
		          partition,
		          -8,
		          SEEK_END,
		          &error );

		VSAPM_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 (int64_t) partition_size - 8 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer on partition_size boundary
		 */
		read_count = libvsapm_partition_read_buffer(
		              partition,
		              buffer,
		              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
		              &error );

		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond partition_size boundary
		 */
		read_count = libvsapm_partition_read_buffer(
		              partition,
		              buffer,
		              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
		              &error );

		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Stress test read buffer
	 */
	timestamp = time(
	             NULL );

	srand(
	 (unsigned int) timestamp );

	offset = libvsapm_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	remaining_partition_size = partition_size;

	for( test_number = 0;
	     test_number < number_of_tests;
	     test_number++ )
	{
		random_number = rand();

		VSAPM_TEST_ASSERT_GREATER_THAN_INT(
		 "random_number",
		 random_number,
		 -1 );

		read_size = (size_t) random_number % VSAPM_TEST_PARTITION_READ_BUFFER_SIZE;

#if defined( VSAPM_TEST_PARTITION_VERBOSE )
		fprintf(
		 stdout,
		 "libvsapm_partition_read_buffer: at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIzd "\n",
		 read_offset,
		 read_offset,
		 read_size );
#endif
		read_count = libvsapm_partition_read_buffer(
		              partition,
		              buffer,
		              read_size,
		              &error );

		if( read_size > remaining_partition_size )
		{
			read_size = (size_t) remaining_partition_size;
		}
		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) read_size );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		read_offset += read_count;

		result = libvsapm_partition_get_offset(
		          partition,
		          &offset,
		          &error );

		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSAPM_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 read_offset );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		remaining_partition_size -= read_count;

		if( remaining_partition_size == 0 )
		{
			offset = libvsapm_partition_seek_offset(
			          partition,
			          0,
			          SEEK_SET,
			          &error );

			VSAPM_TEST_ASSERT_EQUAL_INT64(
			 "offset",
			 offset,
			 (int64_t) 0 );

			VSAPM_TEST_ASSERT_IS_NULL(
			 "error",
			 error );

			read_offset = 0;

			remaining_partition_size = partition_size;
		}
	}
	/* Reset offset to 0
	 */
	offset = libvsapm_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libvsapm_partition_read_buffer(
	              NULL,
	              buffer,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvsapm_partition_read_buffer(
	              partition,
	              NULL,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvsapm_partition_read_buffer(
	              partition,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSAPM_TEST_RWLOCK )

	/* Test libvsapm_partition_read_buffer with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	vsapm_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libvsapm_partition_read_buffer(
	              partition,
	              buffer,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	if( vsapm_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsapm_partition_read_buffer with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	vsapm_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libvsapm_partition_read_buffer(
	              partition,
	              buffer,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	if( vsapm_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSAPM_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsapm_partition_read_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_partition_read_buffer_at_offset(
     libvsapm_partition_t *partition )
{
	uint8_t buffer[ VSAPM_TEST_PARTITION_READ_BUFFER_SIZE ];

	libcerror_error_t *error          = NULL;
	time_t timestamp                  = 0;
	size64_t partition_size           = 0;
	size64_t remaining_partition_size = 0;
	size_t read_size                  = 0;
	ssize_t read_count                = 0;
	off64_t offset                    = 0;
	off64_t read_offset               = 0;
	int number_of_tests               = 1024;
	int random_number                 = 0;
	int result                        = 0;
	int test_number                   = 0;

	/* Determine size
	 */
	result = libvsapm_partition_get_size(
	          partition,
	          &partition_size,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_size = VSAPM_TEST_PARTITION_READ_BUFFER_SIZE;

	if( partition_size < VSAPM_TEST_PARTITION_READ_BUFFER_SIZE )
	{
		read_size = (size_t) partition_size;
	}
	read_count = libvsapm_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              0,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) read_size );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( partition_size > 8 )
	{
		/* Read buffer on partition_size boundary
		 */
		read_count = libvsapm_partition_read_buffer_at_offset(
		              partition,
		              buffer,
		              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
		              partition_size - 8,
		              &error );

		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond partition_size boundary
		 */
		read_count = libvsapm_partition_read_buffer_at_offset(
		              partition,
		              buffer,
		              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
		              partition_size + 8,
		              &error );

		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Stress test read buffer
	 */
	timestamp = time(
	             NULL );

	srand(
	 (unsigned int) timestamp );

	for( test_number = 0;
	     test_number < number_of_tests;
	     test_number++ )
	{
		random_number = rand();

		VSAPM_TEST_ASSERT_GREATER_THAN_INT(
		 "random_number",
		 random_number,
		 -1 );

		if( partition_size > 0 )
		{
			read_offset = (off64_t) random_number % partition_size;
		}
		read_size = (size_t) random_number % VSAPM_TEST_PARTITION_READ_BUFFER_SIZE;

#if defined( VSAPM_TEST_PARTITION_VERBOSE )
		fprintf(
		 stdout,
		 "libvsapm_partition_read_buffer_at_offset: at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIzd "\n",
		 read_offset,
		 read_offset,
		 read_size );
#endif
		read_count = libvsapm_partition_read_buffer_at_offset(
		              partition,
		              buffer,
		              read_size,
		              read_offset,
		              &error );

		remaining_partition_size = partition_size - read_offset;

		if( read_size > remaining_partition_size )
		{
			read_size = (size_t) remaining_partition_size;
		}
		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) read_size );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		read_offset += read_count;

		result = libvsapm_partition_get_offset(
		          partition,
		          &offset,
		          &error );

		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSAPM_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 read_offset );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	read_count = libvsapm_partition_read_buffer_at_offset(
	              NULL,
	              buffer,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              0,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvsapm_partition_read_buffer_at_offset(
	              partition,
	              NULL,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              0,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvsapm_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              0,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libvsapm_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              -1,
	              &error );

	VSAPM_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSAPM_TEST_RWLOCK )

	/* Test libvsapm_partition_read_buffer_at_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	vsapm_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libvsapm_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              0,
	              &error );

	if( vsapm_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsapm_partition_read_buffer_at_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	vsapm_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libvsapm_partition_read_buffer_at_offset(
	              partition,
	              buffer,
	              VSAPM_TEST_PARTITION_READ_BUFFER_SIZE,
	              0,
	              &error );

	if( vsapm_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSAPM_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT )

/* Tests the libvsapm_internal_partition_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_internal_partition_seek_offset(
     void )
{
	libcerror_error_t *error                            = NULL;
	libvsapm_io_handle_t *io_handle                     = NULL;
	libvsapm_partition_t *partition                     = NULL;
	libvsapm_partition_map_entry_t *partition_map_entry = NULL;
	off64_t offset                                      = 0;
	int result                                          = 0;

	/* Initialize test
	 */
	result = libvsapm_io_handle_initialize(
	          &io_handle,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "io_handle",
	 io_handle );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_partition_map_entry_initialize(
	          &partition_map_entry,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "partition_map_entry",
	 partition_map_entry );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	partition_map_entry->number_of_sectors = 4;

	result = libvsapm_partition_initialize(
	          &partition,
	          io_handle,
	          NULL,
	          partition_map_entry,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "partition",
	 partition );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	offset = libvsapm_internal_partition_seek_offset(
	          (libvsapm_internal_partition_t *) partition,
	          512,
	          SEEK_CUR,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 512 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvsapm_internal_partition_seek_offset(
	          (libvsapm_internal_partition_t *) partition,
	          512,
	          SEEK_CUR,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 1024 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvsapm_internal_partition_seek_offset(
	          (libvsapm_internal_partition_t *) partition,
	          0,
	          SEEK_END,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 2048 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvsapm_internal_partition_seek_offset(
	          (libvsapm_internal_partition_t *) partition,
	          0,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) 0 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libvsapm_internal_partition_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvsapm_internal_partition_seek_offset(
	          (libvsapm_internal_partition_t *) partition,
	          -1,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvsapm_internal_partition_seek_offset(
	          (libvsapm_internal_partition_t *) partition,
	          0,
	          -1,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 (int64_t) offset,
	 (int64_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libvsapm_partition_free(
	          &partition,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "partition",
	 partition );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_partition_map_entry_free(
	          &partition_map_entry,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "partition_map_entry",
	 partition_map_entry );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_io_handle_free(
	          &io_handle,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "io_handle",
	 io_handle );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( partition != NULL )
	{
		libvsapm_partition_free(
		 &partition,
		 NULL );
	}
	if( partition_map_entry != NULL )
	{
		libvsapm_partition_map_entry_free(
		 &partition_map_entry,
		 NULL );
	}
	if( io_handle != NULL )
	{
		libvsapm_io_handle_free(
		 &io_handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT ) */

/* Tests the libvsapm_partition_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_partition_seek_offset(
     libvsapm_partition_t *partition )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	off64_t offset           = 0;

	/* Test regular cases
	 */
	offset = libvsapm_partition_seek_offset(
	          partition,
	          0,
	          SEEK_END,
	          &error );

	VSAPM_TEST_ASSERT_NOT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	size = (size64_t) offset;

	offset = libvsapm_partition_seek_offset(
	          partition,
	          1024,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 1024 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvsapm_partition_seek_offset(
	          partition,
	          -512,
	          SEEK_CUR,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 512 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libvsapm_partition_seek_offset(
	          partition,
	          (off64_t) ( size + 512 ),
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) ( size + 512 ) );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libvsapm_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libvsapm_partition_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvsapm_partition_seek_offset(
	          partition,
	          -1,
	          SEEK_SET,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libvsapm_partition_seek_offset(
	          partition,
	          -1,
	          SEEK_CUR,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	offset = libvsapm_partition_seek_offset(
	          partition,
	          (off64_t) ( -1 * ( size + 1 ) ),
	          SEEK_END,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSAPM_TEST_RWLOCK )

	/* Test libvsapm_partition_seek_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	vsapm_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	offset = libvsapm_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	if( vsapm_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 (int64_t) offset,
		 (int64_t) -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsapm_partition_seek_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	vsapm_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	offset = libvsapm_partition_seek_offset(
	          partition,
	          0,
	          SEEK_SET,
	          &error );

	if( vsapm_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 (int64_t) offset,
		 (int64_t) -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSAPM_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsapm_partition_get_offset function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_partition_get_offset(
     libvsapm_partition_t *partition )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsapm_partition_get_offset(
	          partition,
	          &offset,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsapm_partition_get_offset(
	          NULL,
	          &offset,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsapm_partition_get_offset(
	          partition,
	          NULL,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSAPM_TEST_RWLOCK )

	/* Test libvsapm_partition_get_offset with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsapm_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsapm_partition_get_offset(
	          partition,
	          &offset,
	          &error );

	if( vsapm_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsapm_partition_get_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsapm_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsapm_partition_get_offset(
	          partition,
	          &offset,
	          &error );

	if( vsapm_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSAPM_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsapm_partition_get_size function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_partition_get_size(
     libvsapm_partition_t *partition )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsapm_partition_get_size(
	          partition,
	          &size,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsapm_partition_get_size(
	          NULL,
	          &size,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsapm_partition_get_size(
	          partition,
	          NULL,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSAPM_TEST_RWLOCK )

	/* Test libvsapm_partition_get_size with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	vsapm_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libvsapm_partition_get_size(
	          partition,
	          &size,
	          &error );

	if( vsapm_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libvsapm_partition_get_size with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	vsapm_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libvsapm_partition_get_size(
	          partition,
	          &size,
	          &error );

	if( vsapm_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		vsapm_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_VSAPM_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libvsapm_partition_t *partition  = NULL;
	libvsapm_volume_t *volume        = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int number_of_partitions         = 0;
	int result                       = 0;

	while( ( option = vsapm_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( VSAPM_TEST_PARTITION_VERBOSE )
	libvsapm_notify_set_verbose(
	 1 );
	libvsapm_notify_set_stream(
	 stderr,
	 NULL );
#endif

#if defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT )

	VSAPM_TEST_RUN(
	 "libvsapm_partition_initialize",
	 vsapm_test_partition_initialize );

	VSAPM_TEST_RUN(
	 "libvsapm_partition_free",
	 vsapm_test_partition_free );

#endif /* defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT ) */

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        VSAPM_TEST_ASSERT_IS_NOT_NULL(
	         "file_io_handle",
	         file_io_handle );

	        VSAPM_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        VSAPM_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libvsapm_check_volume_signature_file_io_handle(
		          file_io_handle,
		          &error );

		VSAPM_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		/* Initialize volume for tests
		 */
		result = vsapm_test_volume_open_source(
		          &volume,
		          file_io_handle,
		          &error );

		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSAPM_TEST_ASSERT_IS_NOT_NULL(
		 "volume",
		 volume );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libvsapm_volume_get_number_of_partitions(
		          volume,
		          &number_of_partitions,
		          &error );

		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		if( number_of_partitions > 0 )
		{
			/* Initialize partition for tests
			 */
			result = libvsapm_volume_get_partition_by_index(
			          volume,
			          number_of_partitions - 1,
			          &partition,
			          &error );

			VSAPM_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 1 );

			VSAPM_TEST_ASSERT_IS_NOT_NULL(
			 "partition",
			 partition );

			VSAPM_TEST_ASSERT_IS_NULL(
			 "error",
			 error );

			VSAPM_TEST_RUN_WITH_ARGS(
			 "libvsapm_partition_get_type_string",
			 vsapm_test_partition_get_type_string,
			 partition );

#if defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT )

			VSAPM_TEST_RUN_WITH_ARGS(
			 "libvsapm_internal_partition_read_buffer_from_file_io_handle",
			 vsapm_test_internal_partition_read_buffer_from_file_io_handle,
			 partition );

#endif /* defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT ) */

			VSAPM_TEST_RUN_WITH_ARGS(
			 "libvsapm_partition_read_buffer",
			 vsapm_test_partition_read_buffer,
			 partition );

			VSAPM_TEST_RUN_WITH_ARGS(
			 "libvsapm_partition_read_buffer_at_offset",
			 vsapm_test_partition_read_buffer_at_offset,
			 partition );

#if defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT )

			VSAPM_TEST_RUN(
			 "libvsapm_internal_partition_seek_offset",
			 vsapm_test_internal_partition_seek_offset );

#endif /* defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT ) */

			VSAPM_TEST_RUN_WITH_ARGS(
			 "libvsapm_partition_seek_offset",
			 vsapm_test_partition_seek_offset,
			 partition );

			VSAPM_TEST_RUN_WITH_ARGS(
			 "libvsapm_partition_get_offset",
			 vsapm_test_partition_get_offset,
			 partition );

			VSAPM_TEST_RUN_WITH_ARGS(
			 "libvsapm_partition_get_size",
			 vsapm_test_partition_get_size,
			 partition );

			result = libvsapm_partition_free(
			          &partition,
			          &error );

			VSAPM_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 1 );

			VSAPM_TEST_ASSERT_IS_NULL(
		         "partition",
		         partition );

		        VSAPM_TEST_ASSERT_IS_NULL(
		         "error",
		         error );
		}
		/* Clean up
		 */
		result = vsapm_test_volume_close_source(
		          &volume,
		          &error );

		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "volume",
		 volume );

		VSAPM_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		VSAPM_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		VSAPM_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        VSAPM_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( partition != NULL )
	{
		libvsapm_partition_free(
		 &partition,
		 NULL );
	}
	if( volume != NULL )
	{
		libvsapm_volume_free(
		 &volume,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

