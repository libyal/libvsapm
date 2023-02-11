/*
 * Apple Partition Map (APM) partition map entry definitions
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

#if !defined( _VSAPM_PARTITION_MAP_ENTRY_H )
#define _VSAPM_PARTITION_MAP_ENTRY_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct vsapm_partition_map_entry vsapm_partition_map_entry_t;

struct vsapm_partition_map_entry
{
	/* The signature
	 * Consists of 2 bytes
	 * Contains "PM"
	 */
	uint8_t signature[ 2 ];

	/* Unknown
	 * Consists of 2 bytes
	 */
	uint8_t unknown1[ 2 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];

	/* The start sector
	 * Consists of 4 bytes
	 */
	uint8_t start_sector[ 4 ];

	/* The number of sectors
	 * Consists of 4 bytes
	 */
	uint8_t number_of_sectors[ 4 ];

	/* The name
	 * Consists of 32 bytes
	 */
	uint8_t name[ 32 ];

	/* The type
	 * Consists of 32 bytes
	 */
	uint8_t type[ 32 ];

	/* The data area start sector
	 * Consists of 4 bytes
	 */
	uint8_t data_area_start_sector[ 4 ];

	/* The data area number of sectors
	 * Consists of 4 bytes
	 */
	uint8_t data_area_number_of_sectors[ 4 ];

	/* The status flags
	 * Consists of 4 bytes
	 */
	uint8_t status_flags[ 4 ];

	/* The boot code start sector
	 * Consists of 4 bytes
	 */
	uint8_t boot_code_start_sector[ 4 ];

	/* The boot code number of sectors
	 * Consists of 4 bytes
	 */
	uint8_t boot_code_number_of_sectors[ 4 ];

	/* The boot code address
	 * Consists of 4 bytes
	 */
	uint8_t boot_code_address[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* The boot code entry point
	 * Consists of 4 bytes
	 */
	uint8_t boot_code_entry_point[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* The boot code checksum
	 * Consists of 4 bytes
	 */
	uint8_t boot_code_checksum[ 4 ];

	/* The processor type
	 * Consists of 16 bytes
	 */
	uint8_t processor_type[ 16 ];

	/* Unknown
	 * Consists of 376 bytes
	 */
	uint8_t unknown4[ 376 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _VSAPM_PARTITION_MAP_ENTRY_H ) */

