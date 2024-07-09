/*
 * bird.h
 *
 *  Created on: Apr 18, 2024
 *      Author: Shreyas Acharya, BHARATI SOFTWARE
 */

#ifndef INC_PLAYER_H_
#define INC_PLAYER_H_

#include "../../GC9A01A/GC9A01A.h"

void move_player(bsp_lcd_t *hlcd, int y_pos);

static const uint16_t image_data_bird[900] = {
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f3e, 0x9f3e, 0x9f3e, 0x9f3e, 0x9f3e, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f3e, 0x865c, 0x64b8, 0x6417, 0x6c17, 0x4af7, 0x42f7, 0x5c58, 0x865c, 0x9f3e, 0x9f5e, 0x973e, 0x765c, 0x86bd, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x96fd, 0x8e3b, 0x7cb7, 0x7c1a, 0x633d, 0x421d, 0x423e, 0x6b5e, 0x843f, 0x4a7e, 0x2999, 0x4358, 0x863c, 0x96dd, 0xd75e, 0xaedd, 0x8ebd, 0x973e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x861b, 0x8518, 0xd6bc, 0xf7bf, 0xffff, 0xffff, 0xef7f, 0xd6bf, 0xa51f, 0x421f, 0x421f, 0x8c7f, 0x5b3c, 0x755b, 0xaebd, 0xe75d, 0xe77d, 0xc71d, 0x8edd, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x8e7c, 0x8d18, 0xef7e, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffdf, 0xdeff, 0x5aff, 0x215f, 0x95dd, 0x967e, 0x455f, 0xbedd, 0xe75d, 0xe75d, 0xb6fd, 0x86bd, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x96dd, 0x7cf7, 0xe75e, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xe79f, 0x7d5d, 0x6dde, 0x9e7d, 0x75fe, 0x5d9e, 0xc6fd, 0xe75d, 0xef7e, 0xaedd, 0x8efe, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x971e, 0x6476, 0xcf1d, 0xf7ff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd75e, 0xb6fd, 0xaebd, 0x6dde, 0x353f, 0x8e3d, 0x5dbe, 0x65be, 0xd73d, 0xef7e, 0xdf7e, 0x8e9d, 0x971e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x7db9, 0xa61a, 0xdfdf, 0xf7ff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdf7e, 0xb6dd, 0xaebc, 0xa69c, 0xa69c, 0x5dbe, 0x4d7f, 0x9e7d, 0x65df, 0xcf3e, 0x9ebd, 0x86bd, 0x971e, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f3e, 0x7518, 0xcf7e, 0xd7df, 0xe7df, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdedb, 0x8c92, 0x6411, 0x9e1a, 0xa69c, 0xa69c, 0xaebc, 0xa6bd, 0x7e1e, 0xb6fe, 0xc71e, 0x95db, 0x8e9d, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x96fd, 0x8d79, 0xd79f, 0xd7df, 0xdfdf, 0xe7df, 0xffff, 0xffff, 0xffff, 0xf7bf, 0x73d0, 0x9577, 0x7cd4, 0x6c52, 0xae9c, 0xaebd, 0xa63b, 0xc71e, 0xdf7e, 0xefbf, 0xffff, 0xf79e, 0x9d9a, 0x971e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x8e9c, 0x9dda, 0xd7bf, 0xd7df, 0xdfdf, 0xdfdf, 0xdfdf, 0xe7df, 0xe7df, 0xaedd, 0x5b6e, 0x9577, 0x7494, 0x6412, 0x6cdb, 0x21f8, 0xa4b8, 0xf7df, 0xffff, 0xffff, 0xffff, 0xa538, 0x73b4, 0x7d99, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x8e7c, 0x9dfa, 0xd7bf, 0xbefe, 0x74ba, 0x3b58, 0x3b37, 0x74da, 0x7dbb, 0xae9c, 0x8d59, 0x21ee, 0x08b1, 0x009b, 0x001d, 0x101a, 0xbbb3, 0xff5d, 0xffff, 0xffff, 0xffff, 0x8435, 0x7353, 0x6352, 0x9f1d, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x8ebd, 0x95b9, 0xcf3e, 0x3379, 0x03de, 0x045f, 0x041f, 0x041d, 0x1bfc, 0x4338, 0x193a, 0x005e, 0x001f, 0x001f, 0x001f, 0x081d, 0x98aa, 0xfa49, 0xfb6d, 0xfbcf, 0xfc10, 0xe32d, 0xca48, 0xc3e3, 0xc5cb, 0x9e99, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f3e, 0x7d18, 0x8d19, 0x035c, 0x047f, 0x04ff, 0x049f, 0x04bf, 0x04ff, 0x0c5e, 0x11f8, 0x001d, 0x001f, 0x001f, 0x001f, 0x001f, 0x4051, 0xd063, 0xf041, 0xf861, 0xf841, 0xe881, 0xe400, 0xfe60, 0xfe60, 0xddc3, 0xad70, 0x9f3e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x7559, 0x4af3, 0x043d, 0x04bf, 0x04bf, 0x04ff, 0x049f, 0x04bf, 0x04ff, 0x0cdf, 0x1af9, 0x08bb, 0x001f, 0x001f, 0x001f, 0x001e, 0x4050, 0xa886, 0xc883, 0xd083, 0xd2c1, 0xf5e0, 0xfe80, 0xfe80, 0xfe80, 0xf660, 0xb54b, 0x9f1c, 0x9f5e,
	0x9f5e, 0x96fd, 0x3af2, 0x033a, 0x051f, 0x04ff, 0x04bf, 0x051f, 0x04df, 0x04df, 0x051f, 0x04ff, 0x239b, 0x005c, 0x001f, 0x001f, 0x001f, 0x001e, 0x1839, 0x4050, 0x586d, 0xd480, 0xeda0, 0xf5e0, 0xfe60, 0xfe80, 0xfe80, 0xee21, 0xae34, 0x9f3e,
	0x9f3e, 0x9f3e, 0x6d16, 0x0150, 0x045e, 0x053f, 0x051f, 0x051f, 0x051f, 0x051f, 0x051f, 0x051f, 0x0c7d, 0x08db, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001e, 0x001d, 0xc402, 0xf5a0, 0xf5a0, 0xf5c0, 0xf5e0, 0xf600, 0xf600, 0xb50a, 0x9f1d,
	0x7df9, 0x3aac, 0x4b90, 0x5c76, 0x0a34, 0x03dc, 0x047d, 0x045c, 0x045c, 0x043c, 0x043c, 0x043c, 0x02f9, 0x005c, 0x001f, 0x001f, 0x001f, 0x001f, 0x001e, 0x001d, 0x001a, 0x59cd, 0xcc41, 0xcc20, 0xcc00, 0xc422, 0xac27, 0x9d11, 0x9e17, 0x9f3e,
	0x96fd, 0x8e9b, 0x865b, 0x4b6f, 0x5c55, 0x32d4, 0x00f5, 0x00b6, 0x00b6, 0x0096, 0x0096, 0x0076, 0x0037, 0x001a, 0x001c, 0x001c, 0x001c, 0x001b, 0x0019, 0x0018, 0x0017, 0x2154, 0x94d0, 0xb5af, 0xadd1, 0xa656, 0x9efc, 0x9f3e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x7dd9, 0x1947, 0x7557, 0x973e, 0x96fd, 0x6d5a, 0x21b4, 0x0035, 0x0017, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0036, 0x2194, 0x5c57, 0x8ebd, 0x9f1e, 0x9f3e, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x96dd, 0x7dd8, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f3e, 0x971e, 0x7e1b, 0x5c78, 0x3af6, 0x2a15, 0x21b5, 0x2195, 0x21b5, 0x2a15, 0x4316, 0x5c78, 0x7dfb, 0x971e, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f3e, 0x96fe, 0x96fd, 0x96fd, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e

};

static const uint16_t image_data_bird2[900] = {
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f3e, 0x8e7c, 0x64d8, 0x5bf7, 0x63d6, 0x42b6, 0x42f7, 0x5c78, 0x8e7c, 0x9f3e, 0x9f5e, 0x973e, 0x765c, 0x86bd, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x96fe, 0x8e3b, 0x7cb7, 0x7bf9, 0x631c, 0x423d, 0x423e, 0x6b5e, 0x841f, 0x4a7e, 0x2999, 0x4b58, 0x863c, 0x96dd, 0xd73e, 0xb6dd, 0x8edd, 0x973e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x863b, 0x8518, 0xd6dc, 0xf7bf, 0xffff, 0xffff, 0xef7f, 0xd6bf, 0x9cff, 0x39fe, 0x39ff, 0x8c7f, 0x5b3c, 0x6d1b, 0xaebd, 0xdf5d, 0xe75d, 0xc71d, 0x8edd, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x8e7c, 0x8d17, 0xef7e, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffdf, 0xe71f, 0x52bf, 0x215f, 0x95bd, 0x965e, 0x455f, 0xbebd, 0xe75d, 0xe75d, 0xbefd, 0x8edd, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x96dd, 0x7d18, 0xe77e, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xef9f, 0x859d, 0x6dde, 0x965d, 0x75fe, 0x5d9e, 0xc6fd, 0xe75d, 0xe77e, 0xb6dd, 0x8efd, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f3e, 0x6c97, 0xc71d, 0xf7ff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xd75e, 0xb6fd, 0xa69d, 0x6dde, 0x3d3f, 0x8e3d, 0x5dbe, 0x659e, 0xd71d, 0xef7e, 0xe77e, 0x8e9d, 0x971e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x7599, 0x9dba, 0xdfdf, 0xf7ff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdf7e, 0xb6dd, 0xaebc, 0xa69c, 0xa69c, 0x5dbe, 0x4d5f, 0x9e7d, 0x65df, 0xcf3e, 0x9ebd, 0x8ebd, 0x971e, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f3e, 0x74d7, 0xcf7e, 0xd7df, 0xe7df, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xdedb, 0x8c71, 0x63f1, 0x9e1a, 0xa69c, 0xa69c, 0xaebc, 0xa69c, 0x7e1e, 0xb6fe, 0xc71e, 0x95da, 0x8e9c, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x96fd, 0x8db9, 0xd79f, 0xd7df, 0xdfdf, 0xe7df, 0xffff, 0xffff, 0xffff, 0xefbf, 0x6baf, 0x8d56, 0x7cb4, 0x7473, 0xae9c, 0xb6bd, 0xa63b, 0xc71e, 0xdf9e, 0xefbf, 0xffff, 0xf79e, 0x9d9a, 0x96fe, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x8ebd, 0x9e1a, 0xd7bf, 0xd7df, 0xd7df, 0xd7df, 0xdfdf, 0xe7df, 0xe7df, 0xa6bd, 0x530d, 0x9577, 0x7494, 0x6433, 0x649b, 0x2a18, 0xa498, 0xffdf, 0xffff, 0xffff, 0xffff, 0xad79, 0x73b4, 0x7dba, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x8ebc, 0x9e1b, 0xd7bf, 0xd7df, 0xd7df, 0xd7df, 0xd7df, 0xc77f, 0x7e3c, 0xae7c, 0x8519, 0x196d, 0x0070, 0x009a, 0x001d, 0x0819, 0xbb92, 0xff7d, 0xffff, 0xffff, 0xffff, 0x8436, 0x6312, 0x6b72, 0x9f1d, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x96dd, 0x95fa, 0xd7bf, 0xd7df, 0xd7df, 0xd7df, 0xcf9f, 0x657c, 0x1a1a, 0x29da, 0x10fa, 0x003d, 0x001f, 0x001f, 0x001f, 0x081d, 0x98aa, 0xfa49, 0xfb8e, 0xfc10, 0xfc30, 0xe34e, 0xca69, 0xc3e3, 0xc5cb, 0x9eba, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x973e, 0x8558, 0xcf9f, 0xd7df, 0xd7df, 0xd7df, 0x8e3d, 0x1199, 0x0019, 0x0019, 0x001d, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x4051, 0xd063, 0xf041, 0xf861, 0xf841, 0xe881, 0xe400, 0xfe60, 0xfe60, 0xddc3, 0xad90, 0x9f3e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x6d18, 0xa61b, 0xd7df, 0xcf9f, 0x967d, 0x1a7a, 0x0039, 0x0019, 0x0019, 0x001d, 0x001e, 0x001f, 0x001f, 0x001f, 0x001f, 0x001d, 0x4050, 0xa886, 0xc883, 0xd083, 0xcac1, 0xf5e0, 0xfe80, 0xfe80, 0xfe80, 0xfe60, 0xbd6c, 0x9efc, 0x9f5e,
	0x9f5e, 0x971e, 0x53b4, 0x9e3c, 0x655c, 0x19f9, 0x0057, 0x0076, 0x1137, 0x11d8, 0x1a5a, 0x1a9a, 0x19b9, 0x003d, 0x001f, 0x001f, 0x001f, 0x001f, 0x1838, 0x4851, 0x608d, 0xd480, 0xeda0, 0xf5e0, 0xfe60, 0xfe80, 0xfe80, 0xee01, 0xae33, 0x9f3e,
	0x9f5e, 0x971d, 0x6d16, 0x19f1, 0x1157, 0x0935, 0x0a99, 0x141d, 0x0c5e, 0x047f, 0x04df, 0x04ff, 0x0c9e, 0x0979, 0x001f, 0x001f, 0x001f, 0x001f, 0x001f, 0x001e, 0x083c, 0xc422, 0xeda0, 0xed80, 0xeda0, 0xf5c0, 0xf600, 0xf5e0, 0xb54b, 0x9f1d,
	0x7dd8, 0x326b, 0x4b90, 0x5437, 0x0299, 0x03ff, 0x04df, 0x04ff, 0x04ff, 0x04ff, 0x051f, 0x051f, 0x04de, 0x01b9, 0x001f, 0x001f, 0x001f, 0x001f, 0x001e, 0x001d, 0x001a, 0x59cc, 0xcc21, 0xc400, 0xc3e0, 0xc402, 0xb426, 0x9d31, 0x9e59, 0x9f3e,
	0x96fd, 0x8e9b, 0x8e7c, 0x1b39, 0x041f, 0x045f, 0x049f, 0x049f, 0x04bf, 0x04df, 0x051f, 0x051f, 0x0319, 0x0078, 0x001c, 0x001c, 0x001c, 0x001b, 0x0019, 0x0018, 0x0017, 0x2154, 0x94b0, 0xad8f, 0xadd1, 0xa657, 0x9efc, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x7dd9, 0x194a, 0x039d, 0x04df, 0x04ff, 0x04ff, 0x051f, 0x04ff, 0x051f, 0x051f, 0x03ba, 0x0075, 0x0018, 0x0018, 0x0018, 0x0018, 0x0018, 0x0036, 0x2194, 0x5c78, 0x8e9d, 0x9f1e, 0x9f3e, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x96fd, 0x4bd4, 0x039d, 0x045f, 0x049f, 0x049f, 0x04bf, 0x051f, 0x04ff, 0x0c1b, 0x2233, 0x21b5, 0x2195, 0x2195, 0x21f4, 0x3af6, 0x5c78, 0x861b, 0x971e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x96dd, 0x1b18, 0x049f, 0x051f, 0x051f, 0x051f, 0x051f, 0x0c5b, 0x6d7a, 0x971e, 0x96fe, 0x96dd, 0x96fd, 0x973e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f3e, 0x6d5a, 0x0ab7, 0x041e, 0x045f, 0x045f, 0x039b, 0x5cd9, 0x973e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x971e, 0x6d18, 0x3af3, 0x2ab4, 0x32f4, 0x64b8, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f3e, 0x9f3e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e,
	0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e, 0x9f5e

};

#endif /* INC_PLAYER_H_ */
