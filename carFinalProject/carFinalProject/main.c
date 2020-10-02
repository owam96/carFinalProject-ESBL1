
#include "includes/types.h"
#include "MCAL/TIM0/TIM0.h"
#include "MCAL/TIM0_PWM/TIM0_PWM.h"
#include "MCAL/TIM0/interrupt.h"
#include "ECUAL/CAR/CAR.h"
<<<<<<< HEAD
#include "APP/APP.h"
=======
#include "ECUAL/REMOTE/REMOTE.h"
#include "APP/APP.h"

>>>>>>> 3dba2958b7db7affdc2d8367e4bc70c613c6c152
volatile uint8_t flag = 0;

float period;
float TOFF;
float TON;
int direction = 1;
float freq = 51;
int duty = DUTY_30;
int count = 1;

int main(void)
{

	APP_INIT();
	
	
    while (1) 
    {
		
		APP_UPDATE();
		
    }
}

void __vector_11 (void)
{
	if (flag==0)
	{
<<<<<<< HEAD
		CAR_MOTOR_ON();
=======
		CAR_MOTORS_ON();
>>>>>>> 3dba2958b7db7affdc2d8367e4bc70c613c6c152
		_TCNT0_=TON;
		flag=1;
	}
	else
	{
<<<<<<< HEAD
		CAR_MOTOR_OFF();
=======
		CAR_MOTORS_OFF();
>>>>>>> 3dba2958b7db7affdc2d8367e4bc70c613c6c152
		_TCNT0_= TOFF;
		flag=0;
	}
}