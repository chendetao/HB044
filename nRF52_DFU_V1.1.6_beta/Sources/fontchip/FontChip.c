
#include "FontChip.h"
#include "SPI_HW.h"
#include "SPI.h"
#include "HFMA2Ylib.h"

void EntryDeepSleepMode(void)
{
    CS_FONT_ENABLE(); 
    
    spi_write_byte(NRF_SPI0, 0xB9);
        
    CS_FONT_DISABLE();
}

void ExitDeepSleepMode(void)
{
    CS_FONT_ENABLE();
    
    spi_write_byte(NRF_SPI0, 0xAB);

    CS_FONT_DISABLE();
}

bool font_is_ok(void)
{
	unsigned int GB_CODE;
    
    ExitDeepSleepMode();
	GB_CODE = U2G(0x554a);
    EntryDeepSleepMode();
    
	if ( GB_CODE == 0xb0a1 )
	{
		 return true;
	}
	return false;
}

void Font_init(void)
{
	font_init_spi_pin();
	
	spi_config(NRF_SPI0, FONT_SPI_SCL_PIN, FONT_SPI_MOSI_PIN, FONT_SPI_MISO_PIN);
}

