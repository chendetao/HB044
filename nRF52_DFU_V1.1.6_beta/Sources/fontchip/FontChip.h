
#ifndef __FONT_CHIP_H__
#define __FONT_CHIP_H__

#include "FontChip.h"
#include "SPI.h"

extern void EntryDeepSleepMode(void);
extern void ExitDeepSleepMode(void);

extern bool font_is_ok(void);
void Font_init(void);

#endif

