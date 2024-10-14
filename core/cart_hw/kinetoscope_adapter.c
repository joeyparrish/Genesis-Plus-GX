// Kinetoscope: A Sega Genesis Video Player
//
// Copyright (c) 2024 Joey Parrish
//
// See MIT License in LICENSE.txt

// Adapter between Kinetoscope emulation and Genesis Plus GX.

#include "kinetoscope/emulator-patches/kinetoscope.c"

#include "kinetoscope_adapter.h"
#include "shared.h"

void kinetoscope_adapter_reset() {
  uint8_t* sram_buffer = (uint8_t*)kinetoscope_init();

  // 0x20 here represents 2MB in the map.  Each "unit" of the memory map is
  // 64kB.  We map each of these units to the corresponding offset in
  // sram_buffer.
  for (int i = 0x20; i < 0x40; ++i) {
    m68k.memory_map[i].base = sram_buffer;

    m68k.memory_map[i].read8 = NULL;
    m68k.memory_map[i].read16 = NULL;
    m68k.memory_map[i].write8 = m68k_unused_8_w;
    m68k.memory_map[i].write16 = m68k_unused_16_w;

    zbank_memory_map[i].read = NULL;
    zbank_memory_map[i].write = zbank_unused_w;

    sram_buffer += (64 << 10);  // 64kB
  }
}

void kinetoscope_adapter_write(unsigned int address, unsigned int data) {
  // The Kinetoscope emulator expects only the low 8 bits of this address.
  address &= 0xff;
  kinetoscope_write_16((uint32_t)address, NULL, (uint16_t)data);
}

unsigned int kinetoscope_adapter_read(unsigned int address) {
  // The Kinetoscope emulator expects only the low 8 bits of this address.
  address &= 0xff;
  return (unsigned int)kinetoscope_read_16((uint32_t)address, NULL);
}
