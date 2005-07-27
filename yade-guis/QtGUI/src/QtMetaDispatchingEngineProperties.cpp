/***************************************************************************
 *   Copyright (C) 2004 by Olivier Galizzi                                 *
 *   olivier.galizzi@imag.fr                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "QtMetaDispatchingEngineProperties.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <yade/yade-core/EngineUnit.hpp>
#include <yade/yade-core/Omega.hpp>
#include <yade/yade-lib-multimethods/Indexable.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qimage.h>
#include <qaction.h>

#include <boost/type_traits.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

using namespace boost;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

static const unsigned char image0_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xe0, 0x77, 0x3d, 0xf8, 0x00, 0x00, 0x02,
    0x3f, 0x49, 0x44, 0x41, 0x54, 0x48, 0x89, 0xed, 0x93, 0x4d, 0x48, 0x14,
    0x61, 0x18, 0xc7, 0x7f, 0xef, 0xcc, 0x7e, 0xd9, 0x66, 0x8d, 0xb5, 0x5b,
    0x97, 0xa0, 0x28, 0x28, 0x42, 0x59, 0x08, 0xf1, 0x90, 0x19, 0x28, 0x64,
    0x50, 0x76, 0xb0, 0xe8, 0x16, 0x15, 0xec, 0x21, 0x24, 0x84, 0x0e, 0x1d,
    0xea, 0xd6, 0xa9, 0x82, 0x28, 0x90, 0x3e, 0x48, 0x62, 0xd3, 0xa8, 0x90,
    0x42, 0x48, 0x85, 0xc2, 0xf2, 0x90, 0xeb, 0x16, 0x1d, 0xa2, 0x34, 0xf0,
    0x60, 0x1f, 0xd8, 0x07, 0x92, 0x59, 0x54, 0x3b, 0x91, 0xae, 0xbb, 0x33,
    0x3b, 0xf3, 0x76, 0x30, 0x73, 0x3f, 0x72, 0xb6, 0xa5, 0xab, 0x3f, 0x78,
    0x19, 0x78, 0x3e, 0xfe, 0xff, 0x79, 0x9e, 0x77, 0x06, 0x16, 0x58, 0x60,
    0x96, 0x83, 0xfb, 0xd7, 0xd1, 0xdf, 0xb7, 0xbd, 0xe8, 0x3e, 0xe5, 0x5f,
    0x8a, 0x8e, 0x34, 0x6f, 0xe4, 0x5a, 0x64, 0x0b, 0xe8, 0xd6, 0xbc, 0x35,
    0x1b, 0xca, 0x2b, 0xb9, 0xd2, 0xf9, 0x9c, 0xd6, 0xdb, 0x4f, 0x9d, 0x0d,
    0xca, 0x43, 0x55, 0x5c, 0xbd, 0x35, 0xc0, 0xb6, 0x1d, 0x7b, 0xff, 0xc4,
    0x5a, 0xce, 0x55, 0x41, 0xff, 0x4f, 0xe8, 0xd6, 0xe7, 0x35, 0xb0, 0x6d,
    0x89, 0x69, 0x1a, 0x98, 0x86, 0x91, 0x15, 0x77, 0xe5, 0x16, 0xa6, 0x0c,
    0x13, 0xe1, 0xf6, 0x13, 0x6e, 0x3e, 0x41, 0x75, 0x6d, 0x03, 0x9d, 0x37,
    0x2e, 0x21, 0xbc, 0xd7, 0x01, 0x90, 0xad, 0x0d, 0xc8, 0xf6, 0x03, 0x00,
    0xe8, 0xba, 0x41, 0x34, 0x36, 0x41, 0xcb, 0x85, 0x11, 0x06, 0x62, 0x9f,
    0x91, 0xd2, 0xc6, 0x34, 0x0d, 0xa4, 0x6d, 0x3b, 0x1b, 0x24, 0x93, 0x06,
    0xef, 0x3e, 0x8c, 0xe3, 0xf7, 0xfb, 0xd0, 0x82, 0x6b, 0x38, 0x74, 0xf4,
    0x2c, 0xc3, 0x83, 0x8f, 0xe8, 0xea, 0xb8, 0x88, 0x68, 0xba, 0x07, 0x4d,
    0x20, 0x8f, 0xd7, 0xa3, 0x01, 0x8d, 0xb8, 0x69, 0x0c, 0x57, 0x21, 0x62,
    0x77, 0x91, 0x52, 0x92, 0x36, 0xcd, 0xc2, 0x06, 0x96, 0x65, 0x71, 0xf9,
    0x54, 0x38, 0x0e, 0x68, 0x99, 0x71, 0x55, 0x40, 0x20, 0x10, 0x00, 0x20,
    0x18, 0x19, 0xca, 0xea, 0x09, 0x04, 0x02, 0xfc, 0xf8, 0xf6, 0x31, 0x6a,
    0xa5, 0xcd, 0x3a, 0x5b, 0x4a, 0x67, 0x03, 0x84, 0xa0, 0x7a, 0x75, 0x50,
    0xeb, 0xd9, 0xb7, 0x15, 0x52, 0xe6, 0xcc, 0x49, 0x1a, 0x30, 0x3d, 0x7b,
    0x52, 0x73, 0xcf, 0x44, 0x0a, 0x12, 0x49, 0x48, 0xa4, 0x08, 0x7e, 0x9a,
    0xac, 0x4d, 0x5b, 0x16, 0x52, 0x16, 0x98, 0x40, 0x51, 0x04, 0x48, 0x59,
    0x94, 0x38, 0x53, 0x29, 0x00, 0x6c, 0xcb, 0x42, 0xe6, 0x4c, 0x90, 0xf7,
    0x15, 0x29, 0x42, 0x01, 0x5b, 0x16, 0x27, 0x3e, 0x95, 0x9c, 0x31, 0xb0,
    0xf3, 0x27, 0xc8, 0x37, 0x50, 0x14, 0xb0, 0xed, 0xe2, 0xc4, 0x13, 0xc9,
    0xac, 0x15, 0x3b, 0xae, 0x48, 0x28, 0x82, 0x27, 0xe3, 0x71, 0x3d, 0x18,
    0x79, 0xa8, 0xe5, 0xe6, 0xfe, 0x8e, 0x0a, 0x5e, 0x3f, 0x40, 0x54, 0x55,
    0x5d, 0xa8, 0xae, 0x6c, 0xc9, 0xfc, 0x3b, 0x10, 0x0a, 0xc7, 0xce, 0x74,
    0x95, 0x09, 0x01, 0xcf, 0x1e, 0xf7, 0xf2, 0xa0, 0xa7, 0x8d, 0xf8, 0xd7,
    0x09, 0x00, 0x16, 0xbb, 0x04, 0x93, 0xe9, 0xb9, 0x1d, 0xaf, 0x5a, 0xe1,
    0xe3, 0xfd, 0xeb, 0x3d, 0xb8, 0xb4, 0x0e, 0xd6, 0xae, 0x0f, 0xe1, 0x2b,
    0x59, 0x84, 0xdb, 0xe3, 0x29, 0x3c, 0xc1, 0xd8, 0xe8, 0x30, 0xbd, 0x77,
    0x22, 0xbc, 0x19, 0x19, 0xcc, 0xca, 0x65, 0x8a, 0x03, 0x74, 0x77, 0xd6,
    0xa1, 0xbe, 0x98, 0xb9, 0x60, 0x55, 0x55, 0x29, 0x5d, 0xa2, 0xe1, 0xf1,
    0x7a, 0x9d, 0x0d, 0x46, 0x5f, 0x0e, 0x71, 0xfe, 0xe4, 0xe1, 0xfc, 0x4d,
    0x64, 0xb0, 0xb4, 0xd4, 0x4d, 0xeb, 0xe9, 0x4a, 0x42, 0xcb, 0xfd, 0xe8,
    0x37, 0xbf, 0xff, 0x36, 0x70, 0xe1, 0xf1, 0x96, 0x60, 0x98, 0x86, 0x63,
    0x6f, 0x41, 0x36, 0x57, 0x68, 0x44, 0xdb, 0x6b, 0x48, 0xdc, 0xdf, 0x45,
    0xdb, 0xee, 0x0a, 0xca, 0x7c, 0xf9, 0xbf, 0x52, 0x26, 0xc2, 0x31, 0x9b,
    0x43, 0xfd, 0xa6, 0x65, 0xec, 0xac, 0x59, 0xc9, 0xab, 0xb1, 0x04, 0x7d,
    0xd1, 0x2f, 0xbc, 0xd5, 0xa7, 0xff, 0xeb, 0x65, 0x17, 0x00, 0xe0, 0x17,
    0x23, 0x64, 0x1a, 0x58, 0x23, 0xf6, 0xd0, 0x84, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

static const unsigned char image1_data[] = { 
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
    0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x18,
    0x08, 0x06, 0x00, 0x00, 0x00, 0xe0, 0x77, 0x3d, 0xf8, 0x00, 0x00, 0x03,
    0x5f, 0x49, 0x44, 0x41, 0x54, 0x48, 0x89, 0xed, 0x95, 0x6f, 0x48, 0xdc,
    0x75, 0x1c, 0xc7, 0x5f, 0xf7, 0xbb, 0xfb, 0xdd, 0x9f, 0xdf, 0xfd, 0xee,
    0xee, 0x77, 0x37, 0xef, 0xff, 0x4f, 0x3c, 0x4f, 0xd1, 0x72, 0xa7, 0xe7,
    0xe6, 0x60, 0xb5, 0x3f, 0x6d, 0xb8, 0xd5, 0x5c, 0x44, 0x16, 0x14, 0xb2,
    0xd1, 0xe6, 0x7a, 0x62, 0x24, 0x05, 0x11, 0xb1, 0x07, 0x6b, 0x50, 0x41,
    0x89, 0x0c, 0x59, 0x41, 0x1b, 0x94, 0x0f, 0x22, 0x44, 0xc5, 0xd6, 0x1e,
    0xb4, 0x59, 0x2d, 0xb6, 0xd5, 0xca, 0x68, 0x5b, 0x9b, 0x14, 0xe8, 0xca,
    0xcc, 0x33, 0xd7, 0x9c, 0x49, 0x26, 0xba, 0xb9, 0xd9, 0xbc, 0x3b, 0xcf,
    0x6f, 0x0f, 0xfa, 0x43, 0x5c, 0x37, 0x17, 0xe1, 0x93, 0x60, 0xaf, 0x67,
    0x5f, 0xbe, 0xbc, 0x5f, 0x6f, 0xf8, 0x7c, 0xf8, 0xf2, 0x85, 0xdb, 0xfc,
    0x5f, 0x88, 0x00, 0xbb, 0x15, 0x55, 0x3b, 0x64, 0x92, 0xcd, 0x4d, 0x80,
    0x04, 0x54, 0x02, 0xca, 0x92, 0xd8, 0xef, 0x88, 0xad, 0xba, 0xb4, 0xf7,
    0xc0, 0x19, 0xd1, 0xf6, 0xc9, 0x9c, 0xb8, 0x77, 0x47, 0x8b, 0x30, 0x99,
    0x95, 0x8f, 0x2b, 0xd6, 0xd5, 0x65, 0x42, 0xd1, 0xca, 0x61, 0xa0, 0x62,
    0xb1, 0xac, 0x71, 0x91, 0xbb, 0xd2, 0x3f, 0xc2, 0x17, 0x37, 0x6e, 0xac,
    0xde, 0xb3, 0x7c, 0xf5, 0x83, 0x4a, 0xcf, 0x97, 0x03, 0xf8, 0xf5, 0x12,
    0x22, 0xf9, 0xfe, 0xc2, 0xba, 0x86, 0x66, 0x83, 0xe4, 0x2a, 0x73, 0x5f,
    0x9b, 0x1e, 0xdb, 0x79, 0x65, 0x62, 0xe4, 0x34, 0x70, 0x31, 0x97, 0xc4,
    0x70, 0x13, 0x79, 0x64, 0xcd, 0xfa, 0xcd, 0xa7, 0xe3, 0x55, 0xeb, 0x83,
    0xef, 0xb4, 0xbf, 0xd1, 0x5f, 0xd7, 0xb8, 0xbf, 0x3c, 0x58, 0x58, 0xc5,
    0x5c, 0xc6, 0x8c, 0x2c, 0xcb, 0xa4, 0x93, 0x37, 0x98, 0xcf, 0x2c, 0xa0,
    0xd8, 0x55, 0x84, 0x58, 0xa0, 0xa3, 0x65, 0xc7, 0x6c, 0xa2, 0xff, 0x54,
    0x00, 0xb8, 0x9e, 0x2d, 0x32, 0xe5, 0x90, 0x9b, 0x82, 0x7a, 0xf4, 0xd0,
    0xae, 0xdd, 0xed, 0xc1, 0xc9, 0xab, 0x49, 0x1e, 0xf5, 0x6f, 0x29, 0xf7,
    0x78, 0x03, 0x5c, 0x99, 0x9d, 0x43, 0xd7, 0xf3, 0x30, 0xcb, 0x32, 0x26,
    0xa3, 0x84, 0x24, 0x19, 0x10, 0xc0, 0xf0, 0xc0, 0x79, 0x46, 0x13, 0xbd,
    0x49, 0xc0, 0x9f, 0xab, 0x20, 0xd7, 0x88, 0x74, 0x5f, 0xc1, 0x8a, 0x26,
    0x83, 0x3b, 0x6e, 0x4c, 0x67, 0x0c, 0x04, 0x43, 0x3a, 0xaa, 0xc3, 0x81,
    0x1e, 0x0a, 0xa0, 0xa9, 0x16, 0x34, 0xbb, 0x11, 0xa7, 0x5d, 0xc2, 0x61,
    0x93, 0x50, 0xad, 0x12, 0xdf, 0x0e, 0x7c, 0x87, 0x23, 0xb4, 0xd2, 0x36,
    0x3d, 0x3e, 0xf8, 0xd8, 0xdc, 0xec, 0x54, 0x2b, 0x30, 0x77, 0xab, 0x82,
    0xab, 0xd3, 0x13, 0x23, 0x97, 0x0d, 0x26, 0x5b, 0xed, 0xaa, 0xb5, 0x5b,
    0xf1, 0xb8, 0xdd, 0x2c, 0x73, 0xd9, 0xd0, 0xec, 0x70, 0xfe, 0x54, 0x3b,
    0x47, 0x3b, 0xf7, 0x51, 0x5c, 0x1a, 0x27, 0x12, 0xf6, 0xa0, 0x58, 0x40,
    0x0f, 0xe4, 0x51, 0x14, 0x8d, 0x10, 0x08, 0xf8, 0x6c, 0x67, 0x3f, 0x7b,
    0xff, 0x03, 0xe0, 0xd2, 0x62, 0x23, 0x72, 0x02, 0xcf, 0x04, 0xc2, 0x85,
    0xb5, 0xcb, 0xab, 0x36, 0x91, 0x18, 0x1a, 0xa2, 0x66, 0xd3, 0x3a, 0x34,
    0x15, 0xde, 0xdc, 0xf7, 0x74, 0xf2, 0x48, 0xd7, 0xc1, 0x7a, 0xc0, 0x19,
    0xdf, 0x50, 0xdf, 0x5a, 0x56, 0x52, 0x80, 0xa6, 0xca, 0x38, 0x6d, 0x4e,
    0xc2, 0x7e, 0x27, 0xa3, 0x83, 0xf6, 0x9c, 0x23, 0x97, 0xb2, 0xce, 0xd5,
    0x3b, 0x9f, 0x6a, 0x7e, 0xa9, 0xe3, 0xc3, 0xa1, 0x95, 0x81, 0xfc, 0x32,
    0x4a, 0x8a, 0xf2, 0xd1, 0x54, 0x98, 0xf8, 0xb1, 0x8f, 0x23, 0x5d, 0x07,
    0x9b, 0x80, 0x6e, 0x6f, 0x28, 0xda, 0x58, 0x10, 0x2d, 0x85, 0x85, 0x14,
    0x0e, 0x2b, 0x18, 0xc5, 0x2c, 0x9f, 0x9f, 0x78, 0x97, 0x8f, 0xde, 0x6b,
    0x4b, 0x03, 0xa3, 0xd9, 0x05, 0xd9, 0x8d, 0x32, 0x6a, 0x11, 0xdd, 0x9f,
    0x0e, 0x52, 0x76, 0x67, 0x29, 0x3e, 0xcd, 0x88, 0x6a, 0x85, 0xbe, 0xd1,
    0x01, 0x80, 0x80, 0x96, 0xa7, 0x7f, 0xf1, 0xf0, 0xae, 0x17, 0x2b, 0x53,
    0xb3, 0xbf, 0xa0, 0x7b, 0xc3, 0x58, 0x64, 0x78, 0xab, 0xa3, 0x95, 0x17,
    0x9e, 0x7f, 0xf6, 0x09, 0xe0, 0x30, 0x30, 0x75, 0xab, 0x82, 0x19, 0xe9,
    0xc6, 0x65, 0x7c, 0xde, 0xb5, 0xd8, 0xad, 0x46, 0x14, 0x0b, 0x28, 0x66,
    0xa8, 0xde, 0x5c, 0xc3, 0x03, 0xf5, 0x2f, 0x3f, 0xe9, 0x0d, 0x46, 0x71,
    0xbb, 0x1d, 0x6c, 0xa8, 0xca, 0xc7, 0x66, 0xfd, 0x3d, 0xaa, 0xb9, 0xdd,
    0x98, 0xcd, 0x96, 0xbb, 0x52, 0xa9, 0x64, 0x6b, 0xb6, 0x1c, 0xfe, 0xb9,
    0xe4, 0x91, 0xfe, 0xde, 0x93, 0xce, 0xf9, 0x74, 0xea, 0xee, 0xd1, 0xb1,
    0x71, 0x34, 0x97, 0x93, 0xa8, 0xee, 0xc1, 0xe3, 0xb4, 0x52, 0x53, 0xbd,
    0x9a, 0xd2, 0x88, 0x97, 0xfb, 0xee, 0xa9, 0xc0, 0xb7, 0xcc, 0xf5, 0x57,
    0x20, 0x5e, 0x51, 0x4e, 0xef, 0xb9, 0xb3, 0xc5, 0x3f, 0x0c, 0x27, 0x5e,
    0x07, 0x52, 0xd9, 0x05, 0xd9, 0x3b, 0x58, 0xc8, 0x64, 0x32, 0xaf, 0x24,
    0xbe, 0x39, 0x93, 0x9c, 0x37, 0x28, 0x8c, 0xff, 0x34, 0x8e, 0xc9, 0x08,
    0x46, 0x09, 0x54, 0xc5, 0x42, 0x49, 0x51, 0x18, 0xab, 0xc5, 0x4c, 0x3a,
    0x9d, 0xa6, 0xab, 0xe3, 0x6d, 0xd2, 0xc9, 0x6b, 0x74, 0xb4, 0xb5, 0x72,
    0xe2, 0xf8, 0xb1, 0xe7, 0xc8, 0xf1, 0x06, 0x6e, 0x86, 0xea, 0x0d, 0x15,
    0x7f, 0xd5, 0xb0, 0xb7, 0x53, 0xf4, 0xf4, 0x27, 0xc5, 0xe0, 0x98, 0x10,
    0x3d, 0xe7, 0x12, 0xe2, 0xc2, 0xf7, 0x3f, 0x8b, 0xc9, 0x19, 0x21, 0x26,
    0x67, 0x84, 0xa8, 0x7d, 0xe8, 0x91, 0x69, 0xa0, 0x21, 0x16, 0x8b, 0x8d,
    0xd8, 0x6c, 0xb6, 0xe6, 0x7f, 0x2b, 0xfe, 0x3b, 0x9e, 0x60, 0xb8, 0xb0,
    0xb7, 0xb3, 0xfb, 0x6b, 0x71, 0xf4, 0x64, 0x9f, 0x88, 0x96, 0xc4, 0xc4,
    0xe3, 0x8d, 0x7b, 0xc4, 0xe4, 0x4c, 0x46, 0x4c, 0xcd, 0x24, 0x45, 0xcd,
    0xd6, 0xfb, 0x2f, 0xfc, 0x17, 0x69, 0x36, 0x8a, 0x2c, 0x9b, 0x5f, 0xf5,
    0xf9, 0x43, 0xc7, 0x81, 0xed, 0xb1, 0xf2, 0x15, 0xd7, 0xf7, 0xbf, 0x76,
    0x40, 0x6c, 0xdb, 0xb6, 0xfd, 0x57, 0x97, 0xcb, 0xd5, 0xb2, 0x14, 0x05,
    0xd9, 0x54, 0x00, 0x6b, 0x58, 0xaa, 0x3f, 0xe0, 0x36, 0x7f, 0xf2, 0x1b,
    0x3f, 0xdf, 0x11, 0x2b, 0xed, 0xf0, 0x53, 0x0d, 0x00, 0x00, 0x00, 0x00,
    0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

QtMetaDispatchingEngineProperties::QtMetaDispatchingEngineProperties(QWidget* parent,  const char*name ) : QtGeneratedMetaDispatchingEngineProperties( parent, name )
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

QtMetaDispatchingEngineProperties::QtMetaDispatchingEngineProperties(shared_ptr<MetaDispatchingEngine>& mde, QWidget* parent,  const char* name ) 
	: QtGeneratedMetaDispatchingEngineProperties( parent, name )
{
	dimension = mde->getDimension();
	
	for(int i=0;i<dimension;i++)
		baseClasses.push_back(mde->getBaseClassType(i));

	baseClasses.push_back(mde->getEngineUnitType());
	
	metaEngine = mde;

	QImage img;
	img.loadFromData( image0_data, sizeof( image0_data ), "PNG" );
	image0 = img;

	img.loadFromData( image1_data, sizeof( image1_data ), "PNG" );
	image1 = img;

	buildDynlibList();

	engineUnitFrame = new QFrame();

	engineUnitParameters.clear();
	cbs.clear();

	vector<vector<string> > functorNames = mde->getFunctorNames();

	for(int i=0;i<functorNames.size() ;i++)
	{
		pbAddClicked();
		for(int j=0;j<functorNames[i].size();j++)
			((QComboBox*)cbs[i][j])->setCurrentText(functorNames[i][j]);
		engineUnitParameters.back() = mde->findFunctorArguments(functorNames[i].back());
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

QtMetaDispatchingEngineProperties::~QtMetaDispatchingEngineProperties()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void QtMetaDispatchingEngineProperties::showEvent( QShowEvent * )
{
	adjustSize();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void QtMetaDispatchingEngineProperties::buildDynlibList()
{

	inheritedClasses.resize(baseClasses.size());

	map<string,DynlibDescriptor>::const_iterator di    = Omega::instance().getDynlibsDescriptor().begin();
	map<string,DynlibDescriptor>::const_iterator diEnd = Omega::instance().getDynlibsDescriptor().end();
	for(;di!=diEnd;++di)
	{
		shared_ptr<Factorable> f = ClassFactory::instance().createShared((*di).first);

		if (dynamic_pointer_cast<EngineUnit>(f))
		{
			if (Omega::instance().isInheritingFrom((*di).first,metaEngine->getEngineUnitType()))
				inheritedClasses.back().push_back((*di).first);
		}
		else if (dynamic_pointer_cast<Indexable>(f))
		{
			for(unsigned int i=0;i<baseClasses.size()-1;i++)
			{
				if (Omega::instance().isInheritingFrom((*di).first,metaEngine->getBaseClassType(i)))
					inheritedClasses[i].push_back((*di).first);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void QtMetaDispatchingEngineProperties::pbAddClicked()
{
	vector<QWidget*> v;

	for(int i=0;i<=dimension;i++)
	{	
		QComboBox * cb = new QComboBox( FALSE, centralFrame);
    		cb->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, cb->sizePolicy().hasHeightForWidth() ) );
		cb->show();

		for(unsigned int j=0;j<inheritedClasses[i].size();j++)
			cb->insertItem(inheritedClasses[i][j]);

		v.push_back(cb);
	}

	string pbName = "pbRemove";
	static int num = 0;
	num++;
	pbName += lexical_cast<string>(num);

	QPushButton * pbRemove = new QPushButton( centralFrame,pbName.c_str());
	pbRemove->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, pbRemove->sizePolicy().hasHeightForWidth() ) );
	pbRemove->setPixmap( image0 );
	pbRemove->show();
	connect( pbRemove, SIGNAL( clicked() ), this, SLOT( pbRemoveClicked() ) );

	v.push_back(pbRemove);

	pbName = "pbSerialization";
	pbName += lexical_cast<string>(num);
	QPushButton * pbSerialization = new QPushButton( centralFrame,pbName.c_str());
	pbSerialization->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, 0, 0, pbSerialization->sizePolicy().hasHeightForWidth() ) );
	pbSerialization->setPixmap( image1 );
	pbSerialization->show();
	connect( pbSerialization, SIGNAL( clicked() ), this, SLOT( pbSerializationClicked() ) );

	v.push_back(pbSerialization);

	cbs.push_back(v);

	engineUnitParameters.push_back(shared_ptr<EngineUnit>());

	// if no attributes are registered then the button to open the serialization frame is not enabled
	shared_ptr<EngineUnit> eu = dynamic_pointer_cast<EngineUnit>(ClassFactory::instance().createShared(((QComboBox*)v[v.size()-3])->currentText()));
	eu->registerAttributes();
	v.back()->setEnabled(eu->getArchives().size()!=0);

	for(unsigned int j=0;j<v.size();j++)
		centralFrameLayout->addWidget( v[j], cbs.size()-1, j );

	adjustSize();

}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void QtMetaDispatchingEngineProperties::pbRemoveClicked()
{
	QPushButton * pb = (QPushButton*)(this->sender());
	vector<vector<QWidget*> >::iterator cbsi    = cbs.begin();
	vector<vector<QWidget*> >::iterator cbsiEnd = cbs.end();adjustSize();

	vector<shared_ptr<EngineUnit> >::iterator eui    = engineUnitParameters.begin();

	for( ; cbsi!=cbsiEnd; ++cbsi,++eui)
	{
		QPushButton * tmppb = (QPushButton*)(*cbsi)[dimension+1];
		if (tmppb->name()==pb->name())
		{
    			for(unsigned int i=0;i<(*cbsi).size();i++)
			{
    				centralFrameLayout->remove((*cbsi)[i]);
				(*cbsi)[i]->hide();
			}
			cbs.erase(cbsi);
			engineUnitParameters.erase(eui);
			adjustSize();
			return;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void QtMetaDispatchingEngineProperties::pbSerializationClicked()
{

	QPushButton * pb = (QPushButton*)(this->sender());

	string name;
	shared_ptr<EngineUnit> eu;

	vector<vector<QWidget*> >::iterator cbsi    = cbs.begin();
	vector<vector<QWidget*> >::iterator cbsiEnd = cbs.end();
	vector<shared_ptr<EngineUnit> >::iterator eui    = engineUnitParameters.begin();
	for( ; cbsi!=cbsiEnd; ++cbsi,++eui)
	{
		QPushButton * tmppb = (QPushButton*)(*cbsi)[dimension+2];
		if (tmppb->name()==pb->name())
		{
			QComboBox *  cb = (QComboBox*)((*cbsi)[dimension]);
			const char * str = cb->currentText();
			name = str;

			if ((*eui)==shared_ptr<EngineUnit>() || (*eui)!=shared_ptr<EngineUnit>() && (*eui)->getClassName()!=name)
				*eui = shared_ptr<EngineUnit>(dynamic_pointer_cast<EngineUnit>(ClassFactory::instance().createShared(name)));
			eu = *eui;
		}
	}

	guiGen.setResizeHeight(true);
	guiGen.setResizeWidth(true);
	guiGen.setShift(10,20);
	guiGen.setShowButtons(true);

	QWidget * parent   = this->parentWidget()->parentWidget();

	delete engineUnitFrame;
	engineUnitFrame = new QFrame(parent);
	engineUnitFrame->setCaption(name);

	guiGen.buildGUI(eu,engineUnitFrame);
	engineUnitFrame->show();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

void QtMetaDispatchingEngineProperties::pbOkClicked()
{

	metaEngine->clear();

	vector<vector<QWidget*> >::iterator cbsi    = cbs.begin();
	vector<vector<QWidget*> >::iterator cbsiEnd = cbs.end();
	vector<shared_ptr<EngineUnit> >::iterator eui    = engineUnitParameters.begin();
	for( ; cbsi!=cbsiEnd; ++cbsi,++eui)
	{
		string baseClass1 = ((QComboBox*)(*cbsi)[0])->currentText();
		if (metaEngine->getDimension()==1)
		{			
			string baseFunctor = ((QComboBox*)(*cbsi)[1])->currentText();
			if (*eui!=shared_ptr<EngineUnit>())
				metaEngine->add(baseClass1, baseFunctor,*eui);
			else
				metaEngine->add(baseClass1, baseFunctor);
		}
		else if (metaEngine->getDimension()==2)
		{
			string baseClass2 = ((QComboBox*)(*cbsi)[1])->currentText();
			string baseFunctor = ((QComboBox*)(*cbsi)[2])->currentText();
			if (*eui!=shared_ptr<EngineUnit>())
				metaEngine->add(baseClass1, baseClass2, baseFunctor,*eui);
			else
				metaEngine->add(baseClass1, baseClass2, baseFunctor);
		}
	}

	close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
