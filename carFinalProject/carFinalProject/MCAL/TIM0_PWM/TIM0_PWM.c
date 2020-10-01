
#include "../../includes/types.h"
#include "../../MCAL/TIM0/TIM0.h"
#include "../TIM0_PWM/TIM0_PWM.h"
#include "../../MCAL/TIM0/interrupt.h"
#include "../../includes/definitions.h"

extern float TON, TOFF, period;

void dutyCycle(float duty, float freq)
{
	period = 1/freq;
	TON=(period*duty)/100;
	TOFF=period-TON;
	TON= 255-((CLOCK_INTERNAL*TON)/Prescaler_256_);
	TOFF= 255-((CLOCK_INTERNAL*TOFF)/Prescaler_256_);
	SET_prescaler(Prescaler_256_);
	
}