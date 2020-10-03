
#include "../../includes/definitions.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/TIM0_PWM/TIM0_PWM.h"
#include "CAR.h"

void CAR_INIT()
{

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

}

void CAR_FORWARD(){
	DIO_WRITE_BIT(PORT_B, M1_F, HIGH);
	DIO_WRITE_BIT(PORT_B, M1_B, LOW);
	DIO_WRITE_BIT(PORT_B, M2_F, HIGH);
	DIO_WRITE_BIT(PORT_B, M2_B, LOW);
}

void CAR_BACKWARD(){
	DIO_WRITE_BIT(PORT_B, M1_F, LOW);
	DIO_WRITE_BIT(PORT_B, M1_B, HIGH);
	DIO_WRITE_BIT(PORT_B, M2_F, LOW);
	DIO_WRITE_BIT(PORT_B, M2_B, HIGH);
}

void CAR_LEFT(){
	
	DIO_WRITE_BIT(PORT_B, M1_F, HIGH);
	DIO_WRITE_BIT(PORT_B, M1_B, LOW);
	DIO_WRITE_BIT(PORT_B, M2_F, LOW);
	DIO_WRITE_BIT(PORT_B, M2_B, HIGH);
}

void CAR_RIGHT(){
	
	DIO_WRITE_BIT(PORT_B, M1_F, LOW);
	DIO_WRITE_BIT(PORT_B, M1_B, HIGH);
	DIO_WRITE_BIT(PORT_B, M2_F, HIGH);
	DIO_WRITE_BIT(PORT_B, M2_B, LOW);
}

void CAR_STOP(){
	
	PWM_STOP();
	DIO_WRITE_BIT(PORT_B, EN1 , LOW);
	DIO_WRITE_BIT(PORT_B, EN2 , LOW);
}


void CAR_MOTORS_ON(){
	DIO_WRITE_BIT(PORT_B, EN1 , HIGH);
	DIO_WRITE_BIT(PORT_B, EN2 , HIGH);
}

void CAR_MOTORS_OFF(){
	DIO_WRITE_BIT(PORT_B, EN1 , LOW);
	DIO_WRITE_BIT(PORT_B, EN2 , LOW);
}
