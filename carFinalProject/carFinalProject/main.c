
#include "includes/types.h"
#include "includes/registers.h"
#include "includes/definitions.h"
#include "MCAL/DIO/DIO.h"
#include "MCAL/TIM0/TIM0.h"
#include "MCAL/TIM0_PWM/TIM0_PWM.h"
#include "MCAL/TIM0/interrupt.h"

volatile uint8_t flag = 0;

float period = 0;
float TOFF = 0;
float TON = 0;

int duty = DUTY_30;
int direction = 1;
float freq = 51;

uint8_t ButtonState;
uint8_t Count=0;
uint8_t LastState=0;

int main(void)
{
	
	int count = 1;
	
	// Enable pin pull-ups for all connected push-buttons
	
	DIO_INIT_BIT(PORT_A, LEFT_B, INPUT);
	DIO_INIT_BIT(PORT_A, RIGHT_B, INPUT);
	DIO_INIT_BIT(PORT_A, MOVE_STOP_B, INPUT);
	DIO_INIT_BIT(PORT_A, CHNG_SPD_DIR_B, INPUT);
	
	DIO_WRITE_BIT(PORT_A, LEFT_B, HIGH);
	DIO_WRITE_BIT(PORT_A, RIGHT_B, HIGH);
	DIO_WRITE_BIT(PORT_A, MOVE_STOP_B, HIGH);
	DIO_WRITE_BIT(PORT_A, CHNG_SPD_DIR_B, HIGH);
	
	// Set enable pins as output
	
	DIO_INIT_BIT(PORT_B, EN1, OUTPUT);
	DIO_INIT_BIT(PORT_B, EN2, OUTPUT);
	
	// Set direction control pins as output
	
	DIO_INIT_BIT(PORT_B, M1_B, OUTPUT);
	DIO_INIT_BIT(PORT_B, M1_F, OUTPUT);
	DIO_INIT_BIT(PORT_B, M2_B, OUTPUT);
	DIO_INIT_BIT(PORT_B, M2_F, OUTPUT);
	
	// Set initial direction as forward and initial speed 30%
	
	DIO_WRITE_BIT(PORT_B, M1_F, HIGH);
	DIO_WRITE_BIT(PORT_B, M2_F, HIGH);
	
	// Enable OVF interrupt and global interrupt
	
	Timer_MODEs(MODE0);
	_TIMSK_ |= (1<<_TOIE0_);
	_SREG_ |= (1<<I);
	
	
    while (1) 
    {
		
		while(!DIO_READ_BIT(PORT_A, MOVE_STOP_B)){
			dutyCycle(duty, freq);
		}
		Timer_Stop();
		while(!DIO_READ_BIT(PORT_A, LEFT_B)){
			DIO_WRITE_BIT(PORT_B, M1_F, HIGH);
			DIO_WRITE_BIT(PORT_B, M1_B, LOW);
			DIO_WRITE_BIT(PORT_B, M2_F, LOW);
			DIO_WRITE_BIT(PORT_B, M2_B, HIGH);
			dutyCycle(DUTY_30, freq);
		}
		Timer_Stop();
		while(!DIO_READ_BIT(PORT_A, RIGHT_B)){
			DIO_WRITE_BIT(PORT_B, M1_F, LOW);
			DIO_WRITE_BIT(PORT_B, M1_B, HIGH);
			DIO_WRITE_BIT(PORT_B, M2_F, HIGH);
			DIO_WRITE_BIT(PORT_B, M2_B, LOW);
			dutyCycle(DUTY_30, freq);
		}
		Timer_Stop();
		if(!DIO_READ_BIT(PORT_A, CHNG_SPD_DIR_B)){
			count++;
			if (count == 1){
				duty = DUTY_30;
				direction = 1;
			}
			else if(count == 2){
				duty = DUTY_60;
				direction = 1;
			}
			else if(count == 3){
				duty = DUTY_90;
				direction = 1;
			}
			else if(count == 4){
				duty = DUTY_30;
				direction = 2;
			}
			while(!DIO_READ_BIT(PORT_A, CHNG_SPD_DIR_B));
		}
		
    }
}

