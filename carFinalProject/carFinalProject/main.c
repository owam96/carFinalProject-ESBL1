
#include "includes/types.h"
#include "includes/registers.h"
#include "includes/definitions.h"
#include "MCAL/DIO/DIO.h"
#include "MCAL/TIM0/TIM0.h"
#include "MCAL/TIM0_PWM/TIM0_PWM.h"
#include "MCAL/TIM0/interrupt.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "ECUAL/CAR/CAR.h"
#include "APP/APP.h"
=======
#include "ECUAL/CAR.h"
#include "ECUAL/REMOTE.h"
>>>>>>> parent of e4935ad... ..

=======
#include "ECUAL/CAR/CAR.h"
#include "APP/APP.h"
>>>>>>> parent of 621282a... ..
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
<<<<<<< HEAD
		CAR_MOTORS_ON();
=======
		DIO_WRITE_BIT(PORT_B, EN1 , HIGH);
		DIO_WRITE_BIT(PORT_B, EN2 , HIGH);
>>>>>>> parent of e4935ad... ..
=======
		CAR_MOTOR_ON();
>>>>>>> parent of 621282a... ..
		_TCNT0_=TON;
		flag=1;
	}
	else
	{
<<<<<<< HEAD
<<<<<<< HEAD

		CAR_MOTORS_OFF();
=======
		DIO_WRITE_BIT(PORT_B, EN1 , LOW);
		DIO_WRITE_BIT(PORT_B, EN2 , LOW);
>>>>>>> parent of e4935ad... ..
=======
		CAR_MOTOR_OFF();
>>>>>>> parent of 621282a... ..
		_TCNT0_= TOFF;
		flag=0;
	}
}