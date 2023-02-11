/*
 * Error functions
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

#if !defined( _LIBVSAPM_INTERNAL_ERROR_H )
#define _LIBVSAPM_INTERNAL_ERROR_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if !defined( HAVE_LOCAL_LIBVSAPM )
#include <libvsapm/error.h>
#endif

#include "libvsapm_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBVSAPM )

LIBVSAPM_EXTERN \
void libvsapm_error_free(
      libvsapm_error_t **error );

LIBVSAPM_EXTERN \
int libvsapm_error_fprint(
     libvsapm_error_t *error,
     FILE *stream );

LIBVSAPM_EXTERN \
int libvsapm_error_sprint(
     libvsapm_error_t *error,
     char *string,
     size_t size );

LIBVSAPM_EXTERN \
int libvsapm_error_backtrace_fprint(
     libvsapm_error_t *error,
     FILE *stream );

LIBVSAPM_EXTERN \
int libvsapm_error_backtrace_sprint(
     libvsapm_error_t *error,
     char *string,
     size_t size );

#endif /* !defined( HAVE_LOCAL_LIBVSAPM ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSAPM_INTERNAL_ERROR_H ) */

