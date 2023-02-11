/*
 * Library sector_data type test program
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "vsapm_test_functions.h"
#include "vsapm_test_libbfio.h"
#include "vsapm_test_libcerror.h"
#include "vsapm_test_libvsapm.h"
#include "vsapm_test_macros.h"
#include "vsapm_test_memory.h"
#include "vsapm_test_unused.h"

#include "../libvsapm/libvsapm_sector_data.h"

#if defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT )

/* Tests the libvsapm_sector_data_initialize function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_sector_data_initialize(
     void )
{
	libcerror_error_t *error            = NULL;
	libvsapm_sector_data_t *sector_data = NULL;
	int result                          = 0;

#if defined( HAVE_VSAPM_TEST_MEMORY )
	int number_of_malloc_fail_tests     = 1;
	int number_of_memset_fail_tests     = 1;
	int test_number                     = 0;
#endif

	/* Test regular cases
	 */
	result = libvsapm_sector_data_initialize(
	          &sector_data,
	          512,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "sector_data",
	 sector_data );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libvsapm_sector_data_free(
	          &sector_data,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "sector_data",
	 sector_data );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libvsapm_sector_data_initialize(
	          NULL,
	          512,
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

	sector_data = (libvsapm_sector_data_t *) 0x12345678UL;

	result = libvsapm_sector_data_initialize(
	          &sector_data,
	          512,
	          &error );

	sector_data = NULL;

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libvsapm_sector_data_initialize(
	          &sector_data,
	          0,
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

	result = libvsapm_sector_data_initialize(
	          &sector_data,
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

#if defined( HAVE_VSAPM_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libvsapm_sector_data_initialize with malloc failing
		 */
		vsapm_test_malloc_attempts_before_fail = test_number;

		result = libvsapm_sector_data_initialize(
		          &sector_data,
		          512,
		          &error );

		if( vsapm_test_malloc_attempts_before_fail != -1 )
		{
			vsapm_test_malloc_attempts_before_fail = -1;

			if( sector_data != NULL )
			{
				libvsapm_sector_data_free(
				 &sector_data,
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
			 "sector_data",
			 sector_data );

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
		/* Test libvsapm_sector_data_initialize with memset failing
		 */
		vsapm_test_memset_attempts_before_fail = test_number;

		result = libvsapm_sector_data_initialize(
		          &sector_data,
		          512,
		          &error );

		if( vsapm_test_memset_attempts_before_fail != -1 )
		{
			vsapm_test_memset_attempts_before_fail = -1;

			if( sector_data != NULL )
			{
				libvsapm_sector_data_free(
				 &sector_data,
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
			 "sector_data",
			 sector_data );

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
	if( sector_data != NULL )
	{
		libvsapm_sector_data_free(
		 &sector_data,
		 NULL );
	}
	return( 0 );
}

/* Tests the libvsapm_sector_data_free function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_sector_data_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libvsapm_sector_data_free(
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

/* Tests the libvsapm_sector_data_read_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int vsapm_test_sector_data_read_file_io_handle(
     void )
{
	uint8_t test_data[ 512 ];

	libbfio_handle_t *file_io_handle    = NULL;
	libcerror_error_t *error            = NULL;
	libvsapm_sector_data_t *sector_data = NULL;
	int result                          = 0;

	/* Initialize test
	 */
	result = libvsapm_sector_data_initialize(
	          &sector_data,
	          512,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NOT_NULL(
	 "sector_data",
	 sector_data );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize file IO handle
	 */
	result = vsapm_test_open_file_io_handle(
	          &file_io_handle,
	          test_data,
	          512,
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

	/* Test error cases
	 */
	result = libvsapm_sector_data_read_file_io_handle(
	          NULL,
	          file_io_handle,
	          0,
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

	result = libvsapm_sector_data_read_file_io_handle(
	          sector_data,
	          NULL,
	          0,
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

	result = libvsapm_sector_data_read_file_io_handle(
	          sector_data,
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

	/* Clean up file IO handle
	 */
	result = vsapm_test_close_file_io_handle(
	          &file_io_handle,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO test data too small */

	/* Clean up
	 */
	result = libvsapm_sector_data_free(
	          &sector_data,
	          &error );

	VSAPM_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	VSAPM_TEST_ASSERT_IS_NULL(
	 "sector_data",
	 sector_data );

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
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	if( sector_data != NULL )
	{
		libvsapm_sector_data_free(
		 &sector_data,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc VSAPM_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] VSAPM_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc VSAPM_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] VSAPM_TEST_ATTRIBUTE_UNUSED )
#endif
{
	VSAPM_TEST_UNREFERENCED_PARAMETER( argc )
	VSAPM_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT )

	VSAPM_TEST_RUN(
	 "libvsapm_sector_data_initialize",
	 vsapm_test_sector_data_initialize );

	VSAPM_TEST_RUN(
	 "libvsapm_sector_data_free",
	 vsapm_test_sector_data_free );

	VSAPM_TEST_RUN(
	 "libvsapm_sector_data_read_file_io_handle",
	 vsapm_test_sector_data_read_file_io_handle );

#endif /* defined( __GNUC__ ) && !defined( LIBVSAPM_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

