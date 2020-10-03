
<<<<<<< HEAD:carFinalProject/carFinalProject/ECUAL/REMOTE.c
<<<<<<< HEAD:carFinalProject/carFinalProject/ECUAL/REMOTE.c
#include "../includes/definitions.h"
#include "../MCAL/DIO/DIO.h"
#include "../MCAL/TIM0/TIM0.h"
#include "../MCAL/TIM0_PWM/TIM0_PWM.h"
#include "../ECUAL/CAR.h"
=======
=======
>>>>>>> parent of 4ca6b43... -:carFinalProject/carFinalProject/ECUAL/REMOTE/REMOTE.c
#include "../../includes/definitions.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/TIM0_PWM/TIM0_PWM.h"
#include "../CAR/CAR.h"
<<<<<<< HEAD:carFinalProject/carFinalProject/ECUAL/REMOTE.c
>>>>>>> parent of 621282a... ..:carFinalProject/carFinalProject/ECUAL/REMOTE/REMOTE.c
=======
>>>>>>> parent of 4ca6b43... -:carFinalProject/carFinalProject/ECUAL/REMOTE/REMOTE.c
#include "REMOTE.h"

extern float freq;
extern int duty, direction, count;

void REMOTE_INIT(){

// Enable pin pull-ups for all connected push-buttons

DIO_INIT_BIT(PORT_A, LEFT_B, INPUT);
DIO_INIT_BIT(PORT_A, RIGHT_B, INPUT);
DIO_INIT_BIT(PORT_A, MOVE_STOP_B, INPUT);
DIO_INIT_BIT(PORT_A, CHNG_SPD_DIR_B, INPUT);

DIO_WRITE_BIT(PORT_A, LEFT_B, HIGH);
DIO_WRITE_BIT(PORT_A, RIGHT_B, HIGH);
DIO_WRITE_BIT(PORT_A, MOVE_STOP_B, HIGH);
DIO_WRITE_BIT(PORT_A, CHNG_SPD_DIR_B, HIGH);

}


void REMOTE_MOVE(){
	
	if(direction == 1){
		CAR_FORWARD();
	}
	else if(direction == 2){
		CAR_BACKWARD();
	}
	TIM0_PWM_start(duty, freq);
}

void REMOTE_LEFT(){
	
	CAR_LEFT();
	TIM0_PWM_start(DUTY_30, freq);
}

void REMOTE_RIGHT(){
	
	CAR_RIGHT();
	TIM0_PWM_start(DUTY_30, freq);
}

void REMOTE_G(){
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

int REMOTE_MOVE_PRESSED(){
	return !DIO_READ_BIT(PORT_A, MOVE_STOP_B);
}

int REMOTE_LEFT_PRESSED(){
	return !DIO_READ_BIT(PORT_A, LEFT_B);
}

int REMOTE_RIGHT_PRESSED(){
	return !DIO_READ_BIT(PORT_A, RIGHT_B);
}

int REMOTE_G_PRESSED(){
	return !DIO_READ_BIT(PORT_A, CHNG_SPD_DIR_B);
}