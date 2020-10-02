
#include "includes/types.h"
#include "includes/registers.h"
#include "includes/definitions.h"
#include "MCAL/DIO/DIO.h"
#include "MCAL/TIM0/TIM0.h"
#include "MCAL/TIM0_PWM/TIM0_PWM.h"
#include "MCAL/TIM0/interrupt.h"
#include "ECUAL/CAR.h"
#include "ECUAL/REMOTE.h"

volatile uint8_t flag = 0;

float period;
float TOFF;
float TON;

int main(void)
{
	
	int duty = DUTY_30;
	int direction = 1;
	float freq = 51;
	int count = 1;
	
	REMOTE_INIT();
	
	CAR_INIT();
	
	TIM0_PWM_INIT();
	
	
    while (1) 
    {
		
		while(!DIO_READ_BIT(PORT_A, MOVE_STOP_B)){
			_TIMSK_ |= (1<<_TOIE0_);
			if(direction == 1){
				CAR_FORWARD();
			}
			else if(direction == 2){
				CAR_BACKWARD();
			}
			TIM0_PWM_start(duty, freq);
		}
		
 		TIM0_STOP();
		_TIMSK_ &=~(1<<_TOIE0_);
		CAR_STOP();
		
		while(!DIO_READ_BIT(PORT_A, LEFT_B)){
			_TIMSK_ |= (1<<_TOIE0_);
			CAR_LEFT();
			TIM0_PWM_start(DUTY_30, freq);
		}
		
		TIM0_STOP();
		_TIMSK_ &=~(1<<_TOIE0_);
		CAR_STOP();
		
		while(!DIO_READ_BIT(PORT_A, RIGHT_B)){
			_TIMSK_ |= (1<<_TOIE0_);
			CAR_RIGHT();
			TIM0_PWM_start(DUTY_30, freq);
		}
		
		TIM0_STOP();
		_TIMSK_ &=~(1<<_TOIE0_);
		CAR_STOP();
		
		if(!DIO_READ_BIT(PORT_A, CHNG_SPD_DIR_B)){
			count++;
			if (count == 1){
				duty = DUTY_30;
				direction = FORWARD;
			}
			else if(count == 2){
				duty = DUTY_60;
				direction = FORWARD;
			}
			else if(count == 3){
				duty = DUTY_90;
				direction = FORWARD;
			}
			else if(count == 4){
				duty = DUTY_30;
				direction = BACKWARD;
				count = 0;
			}
			while(!DIO_READ_BIT(PORT_A, CHNG_SPD_DIR_B));
 		}
    }
}

void __vector_11 (void)
{
	if (flag==0)
	{
		DIO_WRITE_BIT(PORT_B, EN1 , HIGH);
		DIO_WRITE_BIT(PORT_B, EN2 , HIGH);
		_TCNT0_=TON;
		flag=1;
	}
	else
	{
		DIO_WRITE_BIT(PORT_B, EN1 , LOW);
		DIO_WRITE_BIT(PORT_B, EN2 , LOW);
		_TCNT0_= TOFF;
		flag=0;
	}
}