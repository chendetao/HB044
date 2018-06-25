#ifndef _SPI_H___
#define _SPI_H___

#include "nrf_gpio.h"
#include "Board.h"

#define CS_FONT_ENABLE() nrf_gpio_pin_clear(FONT_SPI_CS_PIN)
#define CS_FONT_DISABLE()  nrf_gpio_pin_set(FONT_SPI_CS_PIN)

extern void font_init_spi_pin(void);
extern void spi_config( NRF_SPI_Type *spi, int scl, int mosi, int miso);

#endif
