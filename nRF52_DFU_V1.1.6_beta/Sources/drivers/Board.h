#ifndef __BOARD_H__
#define __BOARD_H__

#define BMA_INT2_PIN        		23
#define BMA_SPI_CS_PIN    			24
#define BMA_SPI_MOSI_PIN    		19   
#define BMA_SPI_MISO_PIN    		20   
#define BMA_SPI_SCL_PIN     		18
#define BMA_POWER_PIN               17
       
#define BUTTON_PIN   				28 

#define MOTOR_PWR_PIN        		 8

#define BAT_DET_ADC_PIN  NRF_SAADC_INPUT_AIN3 /* 5 */
#define BAT_STAT_DET_PIN       		 2
#define BAT_CHARGE_PIN 		     	 7

#define FONT_SPI_CS_PIN    			22
#define FONT_SPI_MOSI_PIN    		19 
#define FONT_SPI_MISO_PIN    		20   
#define FONT_SPI_SCL_PIN     		18

#define HR_PWR_PIN                   4

#define RX_PIN       				(11)
#define TX_PIN       				(8)

#define LCD_SPI_SDA      		    11
#define LCD_SPI_SCL         	    12
#define LCD_SPI_CS  			    15
#define LCD_DC   				    13
#define LCD_RES   				    14
#define LCD_PWR         		    16

#define HRS_SDA_PIN	                29	    
#define HRS_SCL_PIN	                30

#endif
