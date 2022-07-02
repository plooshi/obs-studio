/******************************************************************************
    Copyright (C) 2022 by Hugh Bailey <obs.jim@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#pragma once

#include "util/c99defs.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT bool obs_hevc_keyframe(const uint8_t *data, size_t size);
EXPORT void obs_extract_hevc_headers(const uint8_t *packet, size_t size,
				     uint8_t **new_packet_data,
				     size_t *new_packet_size,
				     uint8_t **header_data, size_t *header_size,
				     uint8_t **sei_data, size_t *sei_size);

enum {
	OBS_HEVC_NAL_PRIORITY_DISPOSABLE = 0,
	OBS_HEVC_NAL_PRIORITY_LOW = 1,
	OBS_HEVC_NAL_PRIORITY_HIGH = 2,
	OBS_HEVC_NAL_PRIORITY_HIGHEST = 3,
};
// NALU start codes are taken from HM 16.24 reference implementation
// https://vcgit.hhi.fraunhofer.de/jvet/HM/-/blob/master/source/Lib/TLibCommon/TypeDef.h
typedef enum {
	// Coded slice segment of a non-TSA, non-STSA trailing picture
	NAL_UNIT_CODED_SLICE_TRAIL_N = 0,
	NAL_UNIT_CODED_SLICE_TRAIL_R, // 1
	// Coded slice segment of a TSA picture
	NAL_UNIT_CODED_SLICE_TSA_N, // 2
	NAL_UNIT_CODED_SLICE_TSA_R, // 3
	// Coded slice segment of an STSA picture
	NAL_UNIT_CODED_SLICE_STSA_N, // 4
	NAL_UNIT_CODED_SLICE_STSA_R, // 5
	// Coded slice segment of a RADL picture
	NAL_UNIT_CODED_SLICE_RADL_N, // 6
	NAL_UNIT_CODED_SLICE_RADL_R, // 7
	NAL_UNIT_CODED_SLICE_RASL_N, // 8
	NAL_UNIT_CODED_SLICE_RASL_R, // 9

	// 10-15 are reserved

	// Coded slice segment of a BLA picture
	NAL_UNIT_CODED_SLICE_BLA_W_LP = 16,
	NAL_UNIT_CODED_SLICE_BLA_W_RADL, // 17
	NAL_UNIT_CODED_SLICE_BLA_N_LP,   // 18
	// Coded slice segment of an IDR picture
	NAL_UNIT_CODED_SLICE_IDR_W_RADL, // 19
	NAL_UNIT_CODED_SLICE_IDR_N_LP,   // 20
	// Coded slice segment of a CRA picture
	NAL_UNIT_CODED_SLICE_CRA,     // 21
	NAL_UNIT_RESERVED_IRAP_VCL22, // 22
	NAL_UNIT_RESERVED_IRAP_VCL23, // 23

	// 22-31 are reserved

	// 32-40 are non-VCL units
	//
	// Start of Video parameter set
	NAL_UNIT_VPS = 32,
	// Start of Sequence parameter set
	NAL_UNIT_SPS, // 33
	// Start of Picture parameter set
	NAL_UNIT_PPS, // 34
	// Other non-VCL units
	NAL_UNIT_ACCESS_UNIT_DELIMITER, // 35
	NAL_UNIT_EOS,                   // 36
	NAL_UNIT_EOB,                   // 37
	NAL_UNIT_FILLER_DATA,           // 38
	// Start of Supplemental enhancement information
	NAL_UNIT_PREFIX_SEI, // 39
	NAL_UNIT_SUFFIX_SEI, // 40

	NAL_UNIT_INVALID = 64,
} nal_unit_type;

#ifdef __cplusplus
}
#endif
