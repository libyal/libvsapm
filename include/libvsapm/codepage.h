/*
 * Codepage definitions for libvsapm
 *
 * Copyright (C) 2009-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBVSAPM_CODEPAGE_H )
#define _LIBVSAPM_CODEPAGE_H

#include <libvsapm/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBVSAPM_CODEPAGES
{
	LIBVSAPM_CODEPAGE_ASCII				= 20127,

	LIBVSAPM_CODEPAGE_ISO_8859_1			= 28591,
	LIBVSAPM_CODEPAGE_ISO_8859_2			= 28592,
	LIBVSAPM_CODEPAGE_ISO_8859_3			= 28593,
	LIBVSAPM_CODEPAGE_ISO_8859_4			= 28594,
	LIBVSAPM_CODEPAGE_ISO_8859_5			= 28595,
	LIBVSAPM_CODEPAGE_ISO_8859_6			= 28596,
	LIBVSAPM_CODEPAGE_ISO_8859_7			= 28597,
	LIBVSAPM_CODEPAGE_ISO_8859_8			= 28598,
	LIBVSAPM_CODEPAGE_ISO_8859_9			= 28599,
	LIBVSAPM_CODEPAGE_ISO_8859_10			= 28600,
	LIBVSAPM_CODEPAGE_ISO_8859_11			= 28601,
	LIBVSAPM_CODEPAGE_ISO_8859_13			= 28603,
	LIBVSAPM_CODEPAGE_ISO_8859_14			= 28604,
	LIBVSAPM_CODEPAGE_ISO_8859_15			= 28605,
	LIBVSAPM_CODEPAGE_ISO_8859_16			= 28606,

	LIBVSAPM_CODEPAGE_KOI8_R			= 20866,
	LIBVSAPM_CODEPAGE_KOI8_U			= 21866,

	LIBVSAPM_CODEPAGE_WINDOWS_874			= 874,
	LIBVSAPM_CODEPAGE_WINDOWS_932			= 932,
	LIBVSAPM_CODEPAGE_WINDOWS_936			= 936,
	LIBVSAPM_CODEPAGE_WINDOWS_949			= 949,
	LIBVSAPM_CODEPAGE_WINDOWS_950			= 950,
	LIBVSAPM_CODEPAGE_WINDOWS_1250			= 1250,
	LIBVSAPM_CODEPAGE_WINDOWS_1251			= 1251,
	LIBVSAPM_CODEPAGE_WINDOWS_1252			= 1252,
	LIBVSAPM_CODEPAGE_WINDOWS_1253			= 1253,
	LIBVSAPM_CODEPAGE_WINDOWS_1254			= 1254,
	LIBVSAPM_CODEPAGE_WINDOWS_1255			= 1255,
	LIBVSAPM_CODEPAGE_WINDOWS_1256			= 1256,
	LIBVSAPM_CODEPAGE_WINDOWS_1257			= 1257,
	LIBVSAPM_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBVSAPM_CODEPAGE_US_ASCII			LIBVSAPM_CODEPAGE_ASCII

#define LIBVSAPM_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBVSAPM_CODEPAGE_ISO_8859_1
#define LIBVSAPM_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBVSAPM_CODEPAGE_ISO_8859_2
#define LIBVSAPM_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBVSAPM_CODEPAGE_ISO_8859_3
#define LIBVSAPM_CODEPAGE_ISO_NORTH_EUROPEAN		LIBVSAPM_CODEPAGE_ISO_8859_4
#define LIBVSAPM_CODEPAGE_ISO_CYRILLIC			LIBVSAPM_CODEPAGE_ISO_8859_5
#define LIBVSAPM_CODEPAGE_ISO_ARABIC			LIBVSAPM_CODEPAGE_ISO_8859_6
#define LIBVSAPM_CODEPAGE_ISO_GREEK			LIBVSAPM_CODEPAGE_ISO_8859_7
#define LIBVSAPM_CODEPAGE_ISO_HEBREW			LIBVSAPM_CODEPAGE_ISO_8859_8
#define LIBVSAPM_CODEPAGE_ISO_TURKISH			LIBVSAPM_CODEPAGE_ISO_8859_9
#define LIBVSAPM_CODEPAGE_ISO_NORDIC			LIBVSAPM_CODEPAGE_ISO_8859_10
#define LIBVSAPM_CODEPAGE_ISO_THAI			LIBVSAPM_CODEPAGE_ISO_8859_11
#define LIBVSAPM_CODEPAGE_ISO_BALTIC			LIBVSAPM_CODEPAGE_ISO_8859_13
#define LIBVSAPM_CODEPAGE_ISO_CELTIC			LIBVSAPM_CODEPAGE_ISO_8859_14

#define LIBVSAPM_CODEPAGE_ISO_LATIN_1			LIBVSAPM_CODEPAGE_ISO_8859_1
#define LIBVSAPM_CODEPAGE_ISO_LATIN_2			LIBVSAPM_CODEPAGE_ISO_8859_2
#define LIBVSAPM_CODEPAGE_ISO_LATIN_3			LIBVSAPM_CODEPAGE_ISO_8859_3
#define LIBVSAPM_CODEPAGE_ISO_LATIN_4			LIBVSAPM_CODEPAGE_ISO_8859_4
#define LIBVSAPM_CODEPAGE_ISO_LATIN_5			LIBVSAPM_CODEPAGE_ISO_8859_9
#define LIBVSAPM_CODEPAGE_ISO_LATIN_6			LIBVSAPM_CODEPAGE_ISO_8859_10
#define LIBVSAPM_CODEPAGE_ISO_LATIN_7			LIBVSAPM_CODEPAGE_ISO_8859_13
#define LIBVSAPM_CODEPAGE_ISO_LATIN_8			LIBVSAPM_CODEPAGE_ISO_8859_14
#define LIBVSAPM_CODEPAGE_ISO_LATIN_9			LIBVSAPM_CODEPAGE_ISO_8859_15
#define LIBVSAPM_CODEPAGE_ISO_LATIN_10			LIBVSAPM_CODEPAGE_ISO_8859_16

#define LIBVSAPM_CODEPAGE_KOI8_RUSSIAN			LIBVSAPM_CODEPAGE_KOI8_R
#define LIBVSAPM_CODEPAGE_KOI8_UKRAINIAN		LIBVSAPM_CODEPAGE_KOI8_U

#define LIBVSAPM_CODEPAGE_WINDOWS_THAI			LIBVSAPM_CODEPAGE_WINDOWS_874
#define LIBVSAPM_CODEPAGE_WINDOWS_JAPANESE		LIBVSAPM_CODEPAGE_WINDOWS_932
#define LIBVSAPM_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBVSAPM_CODEPAGE_WINDOWS_936
#define LIBVSAPM_CODEPAGE_WINDOWS_KOREAN		LIBVSAPM_CODEPAGE_WINDOWS_949
#define LIBVSAPM_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBVSAPM_CODEPAGE_WINDOWS_950
#define LIBVSAPM_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBVSAPM_CODEPAGE_WINDOWS_1250
#define LIBVSAPM_CODEPAGE_WINDOWS_CYRILLIC		LIBVSAPM_CODEPAGE_WINDOWS_1251
#define LIBVSAPM_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBVSAPM_CODEPAGE_WINDOWS_1252
#define LIBVSAPM_CODEPAGE_WINDOWS_GREEK			LIBVSAPM_CODEPAGE_WINDOWS_1253
#define LIBVSAPM_CODEPAGE_WINDOWS_TURKISH		LIBVSAPM_CODEPAGE_WINDOWS_1254
#define LIBVSAPM_CODEPAGE_WINDOWS_HEBREW		LIBVSAPM_CODEPAGE_WINDOWS_1255
#define LIBVSAPM_CODEPAGE_WINDOWS_ARABIC		LIBVSAPM_CODEPAGE_WINDOWS_1256
#define LIBVSAPM_CODEPAGE_WINDOWS_BALTIC		LIBVSAPM_CODEPAGE_WINDOWS_1257
#define LIBVSAPM_CODEPAGE_WINDOWS_VIETNAMESE		LIBVSAPM_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBVSAPM_CODEPAGE_H ) */

