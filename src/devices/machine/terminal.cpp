// license:BSD-3-Clause
// copyright-holders:Miodrag Milanovic
#include "emu.h"
#include "machine/terminal.h"
#include "screen.h"
#include "speaker.h"

#define KEYBOARD_TAG "keyboard"

/***************************************************************************
    IMPLEMENTATION
***************************************************************************/

static const uint8_t terminal_font[256*16] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x92, 0x44, 0x92, 0x44, 0x92, 0x44, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x3e, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xf0, 0x80, 0xe0, 0x80, 0x9e, 0x10, 0x1c, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x78, 0x80, 0x80, 0x78, 0x3c, 0x22, 0x3c, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x80, 0x80, 0xf8, 0x3e, 0x20, 0x3c, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x38, 0x44, 0x44, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x10, 0x10, 0xfe, 0x10, 0x10, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x88, 0xc8, 0xa8, 0x98, 0x88, 0x20, 0x20, 0x20, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x88, 0x88, 0x50, 0x20, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x10, 0x10, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x10, 0x10, 0xff, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x10, 0x10, 0x1f, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x10, 0x10, 0xf0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x10, 0x10, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xff, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x02, 0x08, 0x20, 0x80, 0x20, 0x08, 0x02, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x20, 0x08, 0x02, 0x08, 0x20, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xfe, 0x24, 0x24, 0x24, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x02, 0x04, 0xfe, 0x10, 0xfe, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x1c, 0x22, 0x20, 0xf8, 0x20, 0x78, 0xa6, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x24, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x48, 0x48, 0xfc, 0x48, 0xfc, 0x48, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x10, 0x7c, 0x90, 0x7c, 0x12, 0x7c, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xc2, 0xc4, 0x08, 0x10, 0x20, 0x46, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x70, 0x88, 0x88, 0x70, 0x8a, 0x84, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x18, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x20, 0x10, 0x08, 0x08, 0x08, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x44, 0x28, 0xfe, 0x28, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x10, 0x10, 0xfe, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x78, 0x84, 0x02, 0x1c, 0x60, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfe, 0x04, 0x08, 0x1c, 0x02, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x08, 0x18, 0x28, 0x48, 0xfe, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfe, 0x80, 0xbc, 0xc2, 0x02, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x3c, 0x42, 0x80, 0xbc, 0xc2, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfe, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x7c, 0x82, 0x82, 0x7c, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x78, 0x84, 0x86, 0x7a, 0x02, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x30, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x02, 0x08, 0x20, 0x80, 0x20, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xfe, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x20, 0x08, 0x02, 0x08, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x7c, 0x82, 0x0c, 0x10, 0x10, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x7c, 0x82, 0x8a, 0x92, 0x9c, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x10, 0x28, 0x44, 0x82, 0xfe, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfc, 0x42, 0x42, 0x7c, 0x42, 0x42, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x3c, 0x42, 0x80, 0x80, 0x80, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xf8, 0x44, 0x42, 0x42, 0x42, 0x44, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfe, 0x80, 0x80, 0xf8, 0x80, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfe, 0x80, 0x80, 0xf8, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x3c, 0x42, 0x80, 0x80, 0x8e, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x82, 0x82, 0x82, 0xfe, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x7c, 0x10, 0x10, 0x10, 0x10, 0x10, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x0e, 0x04, 0x04, 0x04, 0x04, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x82, 0x8c, 0xb0, 0xc0, 0xb0, 0x8c, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x82, 0xc6, 0xaa, 0x92, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x82, 0xc2, 0xa2, 0x92, 0x8a, 0x86, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x7c, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfc, 0x82, 0x82, 0xfc, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x7c, 0x82, 0x82, 0x82, 0x8a, 0x84, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfc, 0x82, 0x82, 0xfc, 0x88, 0x84, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x7c, 0x82, 0x80, 0x7c, 0x02, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfe, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x82, 0x82, 0x44, 0x44, 0x28, 0x28, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x82, 0x82, 0x82, 0x92, 0x92, 0xaa, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x82, 0x44, 0x28, 0x10, 0x28, 0x44, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x82, 0x44, 0x28, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfe, 0x04, 0x08, 0x10, 0x20, 0x40, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x3c, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x10, 0x28, 0x44, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x30, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7c, 0x02, 0x7e, 0x82, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x80, 0xbc, 0xc2, 0x82, 0xc2, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3c, 0x42, 0x80, 0x40, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x02, 0x02, 0x7a, 0x86, 0x82, 0x86, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7c, 0x82, 0xfe, 0x80, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x1c, 0x22, 0x20, 0xf8, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7c, 0x84, 0x84, 0x7c, 0x04, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x80, 0xbc, 0xc2, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x10, 0x00, 0x30, 0x10, 0x10, 0x10, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x04, 0x00, 0x04, 0x04, 0x04, 0x04, 0x84, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x80, 0x88, 0x90, 0xe0, 0x88, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xc4, 0xaa, 0x92, 0x92, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xbc, 0xc2, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xbc, 0xc2, 0xc2, 0xbc, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7a, 0x86, 0x86, 0x7a, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x9c, 0x62, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x7c, 0x80, 0x7c, 0x02, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x84, 0x84, 0x84, 0x84, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x82, 0x82, 0x44, 0x28, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x82, 0x82, 0x92, 0xaa, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x84, 0x48, 0x30, 0x48, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x84, 0x84, 0x8c, 0x74, 0x04, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xfe, 0x04, 0x18, 0x20, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x0e, 0x10, 0x10, 0x60, 0x10, 0x10, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xe0, 0x10, 0x10, 0x0c, 0x10, 0x10, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x62, 0x92, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

generic_terminal_device::generic_terminal_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, unsigned w, unsigned h)
	: device_t(mconfig, type, tag, owner, clock)
	, m_io_term_conf(*this, "TERM_CONF")
	, m_width(w)
	, m_height(h)
	, m_buffer()
	, m_x_pos(0)
	, m_framecnt(0)
	, m_y_pos(0)
	, m_bell_timer(nullptr)
	, m_beeper(*this, "beeper")
	, m_keyboard_cb(*this)
{
}

generic_terminal_device::generic_terminal_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: generic_terminal_device(mconfig, GENERIC_TERMINAL, tag, owner, clock, TERMINAL_WIDTH, TERMINAL_HEIGHT)
{
}

void generic_terminal_device::scroll_line()
{
	memmove(m_buffer.get(), m_buffer.get() + m_width, (m_height - 1) * m_width);
	memset(m_buffer.get() + (m_width * (m_height - 1)), 0x20, m_width);
}

void generic_terminal_device::write_char(uint8_t data)
{
	m_buffer[m_y_pos*m_width+m_x_pos] = data;
	m_x_pos++;
	if (m_x_pos >= m_width)
	{
		m_x_pos = 0;
		m_y_pos++;
		if (m_y_pos >= m_height)
		{
			scroll_line();
			m_y_pos = m_height-1;
		}
	}
}

void generic_terminal_device::clear()
{
	std::fill_n(m_buffer.get(), m_width * m_height, 0x20);
	m_x_pos = 0;
	m_y_pos = 0;
}

void generic_terminal_device::term_write(uint8_t data)
{
	if (data > 0x1f)
	{
		// printable char
		if (data != 0x7f) write_char(data);
	}
	else
	{
		const uint16_t options = m_io_term_conf->read();
		switch(data)
		{
		case 0x07: // bell
			m_beeper->set_state(1);
			m_bell_timer->reset(attotime::from_msec(250));
			break;

		case 0x08: // backspace
			if (m_x_pos) m_x_pos--;
			break;

		case 0x09: // horizontal tab
			m_x_pos = (std::min<uint8_t>)((m_x_pos & 0xf8) + 8, m_width - 1);
			break;

		case 0x0d: // carriage return
			m_x_pos = 0;
			if (!(options & 0x080)) break;
			[[fallthrough]];
		case 0x0a: // linefeed
			m_y_pos++;
			if (m_y_pos >= m_height)
			{
				scroll_line();
				m_y_pos = m_height - 1;
			}
			if (options & 0x040) m_x_pos = 0;
			break;

		case 0x0b: // vertical tab
			if (m_y_pos) m_y_pos--;
			break;

		case 0x0c: // form feed
			clear();
			break;

		case 0x1e: // record separator
			m_x_pos = 0;
			m_y_pos = 0;
			break;
		}
	}
}

/***************************************************************************
    VIDEO HARDWARE
***************************************************************************/
uint32_t generic_terminal_device::update(screen_device &device, bitmap_rgb32 &bitmap, const rectangle &cliprect)
{
	uint16_t const options = m_io_term_conf->read();
	uint16_t const cursor = m_y_pos * m_width + m_x_pos;
	uint16_t sy=0,ma=0;

	uint32_t font_color;
	switch (options & 0x030)
	{
	case 0x010:
		font_color = rgb_t(0xf7, 0xaa, 0x00);
		break;
	case 0x020:
		font_color = rgb_t::white();
		break;
	default:
		font_color = rgb_t(0x00, 0xff, 0x00);
		break;
	}

	m_framecnt++;

	for (uint8_t y = 0; y < m_height; y++)
	{
		for (uint8_t ra = 0; ra < 10; ra++)
		{
			uint32_t *p = &bitmap.pix(sy++);

			for (uint16_t x = ma; x < ma + m_width; x++)
			{
				uint8_t const chr = m_buffer[x];
				uint8_t gfx = terminal_font[(chr << 4) | ra];

				if ((x == cursor) && (options & 0x001)) // at cursor position and want a cursor
				{
					if ((options & 2) || (ra == 9)) // block, or underline & at bottom line
					{
						if ((options & 0x004) && (m_framecnt & 8)) // want blink & time to blink
						{
						}
						else
						{
							if (options & 0x008)
								gfx ^= 0xff; // invert
							else
								gfx |= 0xff; // overwrite
						}
					}
				}

				/* Display a scanline of a character */
				*p++ = (BIT(gfx, 7)) ? font_color : 0;
				*p++ = (BIT(gfx, 6)) ? font_color : 0;
				*p++ = (BIT(gfx, 5)) ? font_color : 0;
				*p++ = (BIT(gfx, 4)) ? font_color : 0;
				*p++ = (BIT(gfx, 3)) ? font_color : 0;
				*p++ = (BIT(gfx, 2)) ? font_color : 0;
				*p++ = (BIT(gfx, 1)) ? font_color : 0;
				*p++ = (BIT(gfx, 0)) ? font_color : 0;
			}
		}
		ma += m_width;
	}
	return 0;
}

void generic_terminal_device::kbd_put(u8 data)
{
	if (m_io_term_conf->read() & 0x100) term_write(data);
	send_key(data);
}

/***************************************************************************
    VIDEO HARDWARE
***************************************************************************/

void generic_terminal_device::device_add_mconfig(machine_config &config)
{
	screen_device &screen(SCREEN(config, TERMINAL_SCREEN_TAG, SCREEN_TYPE_RASTER));
	screen.set_refresh_hz(50);
	screen.set_vblank_time(ATTOSECONDS_IN_USEC(2500)); /* not accurate */
	screen.set_size(generic_terminal_device::TERMINAL_WIDTH*8, generic_terminal_device::TERMINAL_HEIGHT*10);
	screen.set_visarea(0, generic_terminal_device::TERMINAL_WIDTH*8-1, 0, generic_terminal_device::TERMINAL_HEIGHT*10-1);
	screen.set_screen_update(FUNC(generic_terminal_device::update));

	generic_keyboard_device &keyboard(GENERIC_KEYBOARD(config, KEYBOARD_TAG, 0));
	keyboard.set_keyboard_callback(FUNC(generic_terminal_device::kbd_put));

	SPEAKER(config, "bell").front_center();
	BEEP(config, m_beeper, 2'000);
	m_beeper->add_route(ALL_OUTPUTS, "bell", 0.25);
}

void generic_terminal_device::device_start()
{
	m_buffer = std::make_unique<uint8_t []>(m_width * m_height);
	m_bell_timer = timer_alloc(FUNC(generic_terminal_device::bell_off), this);
	m_keyboard_cb.resolve_safe();
	save_pointer(NAME(m_buffer), m_width * m_height);
	save_item(NAME(m_x_pos));
	save_item(NAME(m_framecnt));
	save_item(NAME(m_y_pos));
}

void generic_terminal_device::device_reset()
{
	m_beeper->set_state(0);
	clear();
	m_framecnt = 0;
}

TIMER_CALLBACK_MEMBER(generic_terminal_device::bell_off)
{
	m_beeper->set_state(0);
}

/*
Char  Dec  Oct  Hex | Char  Dec  Oct  Hex | Char  Dec  Oct  Hex | Char Dec  Oct   Hex
-------------------------------------------------------------------------------------
(nul)   0 0000 0x00 | (sp)   32 0040 0x20 | @      64 0100 0x40 | `      96 0140 0x60
(soh)   1 0001 0x01 | !      33 0041 0x21 | A      65 0101 0x41 | a      97 0141 0x61
(stx)   2 0002 0x02 | "      34 0042 0x22 | B      66 0102 0x42 | b      98 0142 0x62
(etx)   3 0003 0x03 | #      35 0043 0x23 | C      67 0103 0x43 | c      99 0143 0x63
(eot)   4 0004 0x04 | $      36 0044 0x24 | D      68 0104 0x44 | d     100 0144 0x64
(enq)   5 0005 0x05 | %      37 0045 0x25 | E      69 0105 0x45 | e     101 0145 0x65
(ack)   6 0006 0x06 | &      38 0046 0x26 | F      70 0106 0x46 | f     102 0146 0x66
(bel)   7 0007 0x07 | '      39 0047 0x27 | G      71 0107 0x47 | g     103 0147 0x67
(bs)    8 0010 0x08 | (      40 0050 0x28 | H      72 0110 0x48 | h     104 0150 0x68
(ht)    9 0011 0x09 | )      41 0051 0x29 | I      73 0111 0x49 | i     105 0151 0x69
(nl)   10 0012 0x0a | *      42 0052 0x2a | J      74 0112 0x4a | j     106 0152 0x6a
(vt)   11 0013 0x0b | +      43 0053 0x2b | K      75 0113 0x4b | k     107 0153 0x6b
(np)   12 0014 0x0c | ,      44 0054 0x2c | L      76 0114 0x4c | l     108 0154 0x6c
(cr)   13 0015 0x0d | -      45 0055 0x2d | M      77 0115 0x4d | m     109 0155 0x6d
(so)   14 0016 0x0e | .      46 0056 0x2e | N      78 0116 0x4e | n     110 0156 0x6e
(si)   15 0017 0x0f | /      47 0057 0x2f | O      79 0117 0x4f | o     111 0157 0x6f
(dle)  16 0020 0x10 | 0      48 0060 0x30 | P      80 0120 0x50 | p     112 0160 0x70
(dc1)  17 0021 0x11 | 1      49 0061 0x31 | Q      81 0121 0x51 | q     113 0161 0x71
(dc2)  18 0022 0x12 | 2      50 0062 0x32 | R      82 0122 0x52 | r     114 0162 0x72
(dc3)  19 0023 0x13 | 3      51 0063 0x33 | S      83 0123 0x53 | s     115 0163 0x73
(dc4)  20 0024 0x14 | 4      52 0064 0x34 | T      84 0124 0x54 | t     116 0164 0x74
(nak)  21 0025 0x15 | 5      53 0065 0x35 | U      85 0125 0x55 | u     117 0165 0x75
(syn)  22 0026 0x16 | 6      54 0066 0x36 | V      86 0126 0x56 | v     118 0166 0x76
(etb)  23 0027 0x17 | 7      55 0067 0x37 | W      87 0127 0x57 | w     119 0167 0x77
(can)  24 0030 0x18 | 8      56 0070 0x38 | X      88 0130 0x58 | x     120 0170 0x78
(em)   25 0031 0x19 | 9      57 0071 0x39 | Y      89 0131 0x59 | y     121 0171 0x79
(sub)  26 0032 0x1a | :      58 0072 0x3a | Z      90 0132 0x5a | z     122 0172 0x7a
(esc)  27 0033 0x1b | ;      59 0073 0x3b | [      91 0133 0x5b | {     123 0173 0x7b
(fs)   28 0034 0x1c | <      60 0074 0x3c | \      92 0134 0x5c | |     124 0174 0x7c
(gs)   29 0035 0x1d | =      61 0075 0x3d | ]      93 0135 0x5d | }     125 0175 0x7d
(rs)   30 0036 0x1e | >      62 0076 0x3e | ^      94 0136 0x5e | ~     126 0176 0x7e
(us)   31 0037 0x1f | ?      63 0077 0x3f | _      95 0137 0x5f | (del) 127 0177 0x7f

*/
INPUT_PORTS_START( generic_terminal )
	PORT_START("TERM_CONF")
	PORT_CONFNAME( 0x001, 0x001, "Cursor"        )
	PORT_CONFSETTING(     0x000, DEF_STR(No)     )
	PORT_CONFSETTING(     0x001, DEF_STR(Yes)    )
	PORT_CONFNAME( 0x002, 0x002, "Type"          )
	PORT_CONFSETTING(     0x000, "Underline"     )
	PORT_CONFSETTING(     0x002, "Block"         )
	PORT_CONFNAME( 0x004, 0x004, "Blinking"      )
	PORT_CONFSETTING(     0x000, DEF_STR(No)     )
	PORT_CONFSETTING(     0x004, DEF_STR(Yes)    )
	PORT_CONFNAME( 0x008, 0x008, "Invert"        )
	PORT_CONFSETTING(     0x000, DEF_STR(No)     )
	PORT_CONFSETTING(     0x008, DEF_STR(Yes)    )
	PORT_CONFNAME( 0x030, 0x000, "Color"         )
	PORT_CONFSETTING(     0x000, "Green"         )
	PORT_CONFSETTING(     0x010, "Amber"         )
	PORT_CONFSETTING(     0x020, "White"         )
	PORT_CONFNAME( 0x040, 0x040, "Auto CR on LF" )
	PORT_CONFSETTING(     0x000, DEF_STR(No)     )
	PORT_CONFSETTING(     0x040, DEF_STR(Yes)    )
	PORT_CONFNAME( 0x080, 0x000, "Auto LF on CR" )
	PORT_CONFSETTING(     0x000, DEF_STR(No)     )
	PORT_CONFSETTING(     0x080, DEF_STR(Yes)    )
	PORT_CONFNAME( 0x100, 0x000, "Local echo"    )
	PORT_CONFSETTING(     0x000, DEF_STR(No)     )
	PORT_CONFSETTING(     0x100, DEF_STR(Yes)    )
INPUT_PORTS_END

ioport_constructor generic_terminal_device::device_input_ports() const
{
	return INPUT_PORTS_NAME(generic_terminal);
}

DEFINE_DEVICE_TYPE(GENERIC_TERMINAL, generic_terminal_device, "generic_terminal", "Generic Terminal")