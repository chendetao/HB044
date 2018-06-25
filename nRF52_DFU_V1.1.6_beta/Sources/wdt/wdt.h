#ifndef __WDOG__H
#define __WDOG__H

#define MY_WDT_CONFIG_ENABLE 1


void WDT_Init(void);
void WDT_Feed(void);

#endif
