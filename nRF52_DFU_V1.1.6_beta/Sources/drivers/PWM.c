#include "PWM.h"
#include "nrf_drv_pwm.h"
#include "nrf_drv_config.h"
#include "app_util_platform.h"
#include "Board.h"

#define PWM_REF_LCD_BACKLIGHT_PIN LCD_PWR

nrf_drv_pwm_t m_pwm0 = NRF_DRV_PWM_INSTANCE(0);
nrf_pwm_values_individual_t m_demo1_seq_values;

nrf_pwm_sequence_t const m_demo1_seq = {
	.values.p_individual = &m_demo1_seq_values,
	.length = NRF_PWM_VALUES_LENGTH(m_demo1_seq_values),
	.repeats = 0,
	.end_delay = 0,
};

nrf_drv_pwm_config_t const pwm_config = 
{
	.output_pins = {
		PWM_REF_LCD_BACKLIGHT_PIN | NRF_DRV_PWM_PIN_INVERTED,
	},
	.irq_priority = APP_IRQ_PRIORITY_LOW,
	.base_clock = NRF_PWM_CLK_1MHz,
	.count_mode = NRF_PWM_MODE_UP,
	.top_value = 1000,
	.load_mode = NRF_PWM_LOAD_INDIVIDUAL,
	.step_mode = NRF_PWM_STEP_AUTO,
};

#include "nrf_delay.h"
#include "nrf_gpio.h"

void pwm_init(void)
{
	nrf_drv_pwm_init(&m_pwm0, &pwm_config, NULL);

#if 0    
	nrf_gpio_cfg(
            PWM_REF_LCD_BACKLIGHT_PIN,
            NRF_GPIO_PIN_DIR_OUTPUT,
            NRF_GPIO_PIN_INPUT_DISCONNECT,
            NRF_GPIO_PIN_PULLUP,
            NRF_GPIO_PIN_S0S1,
            NRF_GPIO_PIN_NOSENSE);
	nrf_gpio_pin_clear(PWM_REF_LCD_BACKLIGHT_PIN);    
#endif
}

void pwm_duty_set(int val)
{
	m_demo1_seq_values.channel_0 = val;
}

void pwm_start(void)
{
	nrf_drv_pwm_simple_playback(&m_pwm0,&m_demo1_seq,1,NRF_DRV_PWM_FLAG_LOOP);
    
//    nrf_gpio_pin_clear(PWM_REF_LCD_BACKLIGHT_PIN);    
}

void pwm_stop(void)
{
	nrf_drv_pwm_stop(&m_pwm0,true);	
    
//    nrf_gpio_pin_set(PWM_REF_LCD_BACKLIGHT_PIN);    
}

