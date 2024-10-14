// Kinetoscope: A Sega Genesis Video Player
//
// Copyright (c) 2024 Joey Parrish
//
// See MIT License in LICENSE.txt

// Adapter between Kinetoscope emulation and Genesis Plus GX.

#ifndef _KINETOSCOPE_ADAPTER_H_
#define _KINETOSCOPE_ADAPTER_H_

extern void kinetoscope_adapter_reset(void);
extern void kinetoscope_adapter_write(unsigned int address, unsigned int data);
extern unsigned int kinetoscope_adapter_read(unsigned int address);

#endif
