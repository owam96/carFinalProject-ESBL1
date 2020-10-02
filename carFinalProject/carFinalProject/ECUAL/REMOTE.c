
#include "../includes/definitions.h"
#include "../MCAL/DIO/DIO.h"

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