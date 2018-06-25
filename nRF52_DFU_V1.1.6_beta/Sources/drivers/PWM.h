#ifndef __PWM_H__
#define __PWM_H__

extern void pwm_init(void);
extern void pwm_duty_set(int val);
extern void pwm_start(void);
extern void pwm_stop(void);

#endif
