/*
 * Library volume type test program
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

#include "vsapm_test_functions.h"
#include "vsapm_test_getopt.h"
#include "vsapm_test_libbfio.h"
#include "vsapm_test_libcerror.h"
#include "vsapm_test_libvsapm.h"
#include "vsapm_test_macros.h"
#include "vsapm_test_memory.h"
#include "vsapm_test_unused.h"

#if defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT )
#include "../libvsapm/libvsapm_volume.h"
#endif

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make vsapm_test_volume generate verbose output
#define VSAPM_TEST_VOLUME_VERBOSE
 */

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

/* Tests the libvsapm_volume_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_volume_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libvsapm_volume_t *volume       = NULL;
	int result                      = 0;

#if defined( HAVE_VSAPM_TEST_MEMORY )
	int number_of_malloc_fail_tests = 3;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libvsapm_volume_initialize(
	          &volume,
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

	result = libvsapm_volume_free(
	          &volume,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsapm_volume_initialize(
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

	volume = (libvsapm_volume_t *) 0x12345678UL;

	result = libvsapm_volume_initialize(
	          &volume,
	          &error );

	volume = NULL;

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_VSAPM_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvsapm_volume_initialize with malloc failing
		 */
		vsapm_test_malloc_attempts_before_fail = test_number;

		result = libvsapm_volume_initialize(
		          &volume,
		          &error );

		if( vsapm_test_malloc_attempts_before_fail != -1 )
		{
			vsapm_test_malloc_attempts_before_fail = -1;

			if( volume != NULL )
			{
				libvsapm_volume_free(
				 &volume,
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
			 "volume",
			 volume );

			VSAPM_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libvsapm_volume_initialize with memset failing
		 */
		vsapm_test_memset_attempts_before_fail = test_number;

		result = libvsapm_volume_initialize(
		          &volume,
		          &error );

		if( vsapm_test_memset_attempts_before_fail != -1 )
		{
			vsapm_test_memset_attempts_before_fail = -1;

			if( volume != NULL )
			{
				libvsapm_volume_free(
				 &volume,
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
			 "volume",
			 volume );

			VSAPM_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_VSAPM_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( volume != NULL )
	{
		libvsapm_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsapm_volume_free function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_volume_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsapm_volume_free(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsapm_volume_open function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_volume_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libvsapm_volume_t *volume = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = vsapm_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_volume_initialize(
	          &volume,
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

	/* Test open
	 */
	result = libvsapm_volume_open(
	          volume,
	          narrow_source,
	          LIBVSAPM_OPEN_READ,
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
	result = libvsapm_volume_open(
	          NULL,
	          narrow_source,
	          LIBVSAPM_OPEN_READ,
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

	result = libvsapm_volume_open(
	          volume,
	          NULL,
	          LIBVSAPM_OPEN_READ,
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

	result = libvsapm_volume_open(
	          volume,
	          narrow_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libvsapm_volume_open(
	          volume,
	          narrow_source,
	          LIBVSAPM_OPEN_READ,
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

	/* Clean up
	 */
	result = libvsapm_volume_free(
	          &volume,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

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
	if( volume != NULL )
	{
		libvsapm_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libvsapm_volume_open_wide function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_volume_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error  = NULL;
	libvsapm_volume_t *volume = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = vsapm_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_volume_initialize(
	          &volume,
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

	/* Test open
	 */
	result = libvsapm_volume_open_wide(
	          volume,
	          wide_source,
	          LIBVSAPM_OPEN_READ,
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
	result = libvsapm_volume_open_wide(
	          NULL,
	          wide_source,
	          LIBVSAPM_OPEN_READ,
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

	result = libvsapm_volume_open_wide(
	          volume,
	          NULL,
	          LIBVSAPM_OPEN_READ,
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

	result = libvsapm_volume_open_wide(
	          volume,
	          wide_source,
	          -1,
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

	/* Test open when already opened
	 */
	result = libvsapm_volume_open_wide(
	          volume,
	          wide_source,
	          LIBVSAPM_OPEN_READ,
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

	/* Clean up
	 */
	result = libvsapm_volume_free(
	          &volume,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

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
	if( volume != NULL )
	{
		libvsapm_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libvsapm_volume_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_volume_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libvsapm_volume_t *volume        = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
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

	result = libvsapm_volume_initialize(
	          &volume,
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

	/* Test open
	 */
	result = libvsapm_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBVSAPM_OPEN_READ,
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
	result = libvsapm_volume_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBVSAPM_OPEN_READ,
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

	result = libvsapm_volume_open_file_io_handle(
	          volume,
	          NULL,
	          LIBVSAPM_OPEN_READ,
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

	result = libvsapm_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          -1,
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

	/* Test open when already opened
	 */
	result = libvsapm_volume_open_file_io_handle(
	          volume,
	          file_io_handle,
	          LIBVSAPM_OPEN_READ,
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

	/* Clean up
	 */
	result = libvsapm_volume_free(
	          &volume,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
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
	return( 0 );
}

/* Tests the libvsapm_volume_close function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_volume_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsapm_volume_close(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsapm_volume_open and libvsapm_volume_close functions
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_volume_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error  = NULL;
	libvsapm_volume_t *volume = NULL;
	int result                = 0;

	/* Initialize test
	 */
	result = libvsapm_volume_initialize(
	          &volume,
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

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvsapm_volume_open_wide(
	          volume,
	          source,
	          LIBVSAPM_OPEN_READ,
	          &error );
#else
	result = libvsapm_volume_open(
	          volume,
	          source,
	          LIBVSAPM_OPEN_READ,
	          &error );
#endif

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_volume_close(
	          volume,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libvsapm_volume_open_wide(
	          volume,
	          source,
	          LIBVSAPM_OPEN_READ,
	          &error );
#else
	result = libvsapm_volume_open(
	          volume,
	          source,
	          LIBVSAPM_OPEN_READ,
	          &error );
#endif

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_volume_close(
	          volume,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libvsapm_volume_free(
	          &volume,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "volume",
	 volume );

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
	if( volume != NULL )
	{
		libvsapm_volume_free(
		 &volume,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsapm_volume_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_volume_signal_abort(
     libvsapm_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libvsapm_volume_signal_abort(
	          volume,
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
	result = libvsapm_volume_signal_abort(
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsapm_volume_get_bytes_per_sector function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_volume_get_bytes_per_sector(
     libvsapm_volume_t *volume )
{
	libcerror_error_t *error  = NULL;
	uint32_t bytes_per_sector = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libvsapm_volume_get_bytes_per_sector(
	          volume,
	          &bytes_per_sector,
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
	result = libvsapm_volume_get_bytes_per_sector(
	          NULL,
	          &bytes_per_sector,
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

	result = libvsapm_volume_get_bytes_per_sector(
	          volume,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsapm_volume_get_number_of_partitions function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_volume_get_number_of_partitions(
     libvsapm_volume_t *volume )
{
	libcerror_error_t *error = NULL;
	int number_of_partitions = 0;
	int result               = 0;

	/* Test regular cases
	 */
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

	/* Test error cases
	 */
	result = libvsapm_volume_get_number_of_partitions(
	          NULL,
	          &number_of_partitions,
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

	result = libvsapm_volume_get_number_of_partitions(
	          volume,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libvsapm_volume_get_partition_by_index function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_volume_get_partition_by_index(
     libvsapm_volume_t *volume )
{
	libcerror_error_t *error                 = NULL;
	libvsapm_partition_t *partition_by_index = 0;
	int number_of_partitions                 = 0;
	int result                               = 0;

	/* Test regular cases
	 */
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

	if( number_of_partitions == 0 )
	{
		return( 1 );
	}
	result = libvsapm_volume_get_partition_by_index(
	          volume,
	          0,
	          &partition_by_index,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "partition_by_index",
	 partition_by_index );

	result = libvsapm_partition_free(
	          &partition_by_index,
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
	result = libvsapm_volume_get_partition_by_index(
	          NULL,
	          0,
	          &partition_by_index,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "partition_by_index",
	 partition_by_index );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsapm_volume_get_partition_by_index(
	          volume,
	          -1,
	          &partition_by_index,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "partition_by_index",
	 partition_by_index );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsapm_volume_get_partition_by_index(
	          volume,
	          0,
	          NULL,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "partition_by_index",
	 partition_by_index );

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
	libvsapm_volume_t *volume        = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
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
#if defined( HAVE_DEBUG_OUTPUT ) && defined( VSAPM_TEST_VOLUME_VERBOSE )
	libvsapm_notify_set_verbose(
	 1 );
	libvsapm_notify_set_stream(
	 stderr,
	 NULL );
#endif

	VSAPM_TEST_RUN(
	 "libvsapm_volume_initialize",
	 vsapm_test_volume_initialize );

	VSAPM_TEST_RUN(
	 "libvsapm_volume_free",
	 vsapm_test_volume_free );

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
		VSAPM_TEST_RUN_WITH_ARGS(
		 "libvsapm_volume_open",
		 vsapm_test_volume_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		VSAPM_TEST_RUN_WITH_ARGS(
		 "libvsapm_volume_open_wide",
		 vsapm_test_volume_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		VSAPM_TEST_RUN_WITH_ARGS(
		 "libvsapm_volume_open_file_io_handle",
		 vsapm_test_volume_open_file_io_handle,
		 source );

		VSAPM_TEST_RUN(
		 "libvsapm_volume_close",
		 vsapm_test_volume_close );

		VSAPM_TEST_RUN_WITH_ARGS(
		 "libvsapm_volume_open_close",
		 vsapm_test_volume_open_close,
		 source );

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

		VSAPM_TEST_RUN_WITH_ARGS(
		 "libvsapm_volume_signal_abort",
		 vsapm_test_volume_signal_abort,
		 volume );

#if defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT )

		/* TODO: add tests for libvsapm_volume_open_read */

		/* TODO: add tests for libvsapm_volume_read_partition_entries */

#endif /* defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT ) */

		VSAPM_TEST_RUN_WITH_ARGS(
		 "libvsapm_volume_get_bytes_per_sector",
		 vsapm_test_volume_get_bytes_per_sector,
		 volume );

		VSAPM_TEST_RUN_WITH_ARGS(
		 "libvsapm_volume_get_number_of_partitions",
		 vsapm_test_volume_get_number_of_partitions,
		 volume );

		VSAPM_TEST_RUN_WITH_ARGS(
		 "libvsapm_volume_get_partition_by_index",
		 vsapm_test_volume_get_partition_by_index,
		 volume );

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
	}
	if( file_io_handle != NULL )
	{
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

