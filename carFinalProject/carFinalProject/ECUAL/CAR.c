
#include "../includes/definitions.h"
#include "../MCAL/DIO/DIO.h"

void CAR_INIT(){

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