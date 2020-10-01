/*
 * Timer_driver.c
 *
 * Created: 8/27/2020 4:06:42 PM
 * Author : Esraa

 */ 
#include "../../MCAL/TIM0/interrupt.h"
#include "../../includes/types.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../MCAL/TIM0/TIM0.h"

#define  CLOCK_INTERNAL 1000000 // 1MHZ
/************************************************************************/
/*
max time 0.000256 >> no prescaler
max time 0.002048 >> 8-pre
max time 0.011776 >> 64-pre
max time 0.065536 >> 256-pre
max time 0.262144 >> 1024-pre   
time count = required delay / clock time -1   
clock time = 1/prescaler        
                                                        */
/************************************************************************/




float   max_freq;
float   max_time;
float  new_freq ;
uint32_t total_ovrf=0;
float time_1_ovrf=0;
float n_f =0;
float time_1_tick=0;


void SET_prescaler( uint16_t pre)
{
	if(pre == Prescaler_off_)
	{
		_TCCR0_ |=0;
	}
	else if(pre == Prescaler_1_)
	{
		_TCCR0_ |= 1;
		
	}
	else if(pre == Prescaler_8_)
	{
		_TCCR0_ |=2;
	}
	else if(pre == Prescaler_64_)
	{
		_TCCR0_ |=3;
	}
	else if(pre == Prescaler_256_)
	{
		_TCCR0_ |=4;
	}
	else if(pre == Prescaler_1024_)
	{	
		_TCCR0_ |=5;
	}
}

float Calculate_max_time (float PREASCLER)
{
	float result;
	new_freq = CLOCK_INTERNAL/PREASCLER;
	max_time = (1/new_freq)*256;
	result = max_time;	
	return result;
	
}
/*******************************************************/

uint16_t calculte_total_ovf(float DELAY)
{

	time_1_ovrf=Calculate_max_time (Prescaler_1024_);//
	total_ovrf=DELAY/time_1_ovrf;//
	return total_ovrf;
}
uint8_t calculat_num_ticks(float DELAY)
{	  
	float total_time_ovrf;
	float TICKs;
	total_time_ovrf=total_ovrf*time_1_ovrf;
	TICKs=DELAY-total_time_ovrf;
	TICKs=TICKs/time_1_tick;
	return TICKs;
}

void Timer_Stop()
{
	_TIFR_ |= (1<<_TOV0_);
	SET_prescaler(Prescaler_off_);
}
void wait_ovf()
{
	while((_TIFR_&(1<<_TOV0_))!=1);
}

void OVF_delay(float delay)
{			
		    uint8_t tick;
		    uint32_t overFlows;
			overFlows=calculte_total_ovf(delay);
			tick = calculat_num_ticks(delay);
	
			for(uint8_t count = 0 ; count < overFlows ; count++)
			{
					if(count==0){SET_prescaler(Prescaler_1024_);}
					
					_TCNT0_=0;	
					wait_ovf();
					Timer_Stop();
					
			}
			
			_TCNT0_=0;
			_TCNT0_=255-tick;
			SET_prescaler(Prescaler_1024_);
			wait_ovf();
			Timer_Stop();
			

}


/***************** init********************************/
void Timer_MODEs(uint8_t T_mode)
{
	if(T_mode==MODE0)
	{
		_TCCR0_ &=~((1<<_WGM00_)|(1<<_WGM01_));
	}
	else if (T_mode==MODE1)
	{
		_TCCR0_ |= (1<<_WGM01_);
		_TCCR0_ &= !(1<<_WGM00_);
	}
	else if(T_mode==MODE2)
	{
		_TCCR0_ |= (1<<_WGM00_);
		_TCCR0_ &= !(1<<_WGM01_);		
	}
	else if(T_mode==Fast_PWM)
	{
		_TCCR0_ |=(1<< _WGM00_)|(1<< _WGM01_);
	}

}

void T_COM_non_PWM(uint8_t C_mode)
{
	if (C_mode==COM_NORMAL)
	{
		_TCCR0_ &=~((1<<_COM00_)|(1<<_COM01_));// clear
	}
	else if(C_mode==COM_Toggel)
	{
		_TCCR0_ |=(1<<_COM00_);
		_TCCR0_ &= !(1<<_COM01_);

	}
	else if (C_mode==COM_Clear)
	{
		_TCCR0_ |= (1<<_COM01_);
		_TCCR0_ &= !(1<<_COM00_);
	
	}
	else if (C_mode==COM_Set)
	{
		_TCCR0_ |=(1<< _COM01_)|(1<< _COM00_);// set
	
	}
}
/**************************************************/
void DELAYms(float delay)
{
	delay=delay/1000;
	if((Calculate_max_time(Prescaler_1_))>=delay)
	{
		_TCNT0_= 255-((CLOCK_INTERNAL*delay));
		SET_prescaler(Prescaler_1_);
		wait_ovf();
		Timer_Stop();
		
	}
	
	else if((Calculate_max_time(Prescaler_8_))>=delay)
	{
		
		_TCNT0_= 255-((CLOCK_INTERNAL*delay)/Prescaler_8_);
		SET_prescaler(Prescaler_8_);
		wait_ovf();
		Timer_Stop();
		
	}
	else if((Calculate_max_time(Prescaler_64_))>=delay)
	{
		_TCNT0_= 255-((CLOCK_INTERNAL*delay)/Prescaler_64_);
		SET_prescaler(Prescaler_64_);
		wait_ovf();
		Timer_Stop();
		
	}
	
	else if((Calculate_max_time(Prescaler_256_))>=delay)
	{
		_TCNT0_= 255-((CLOCK_INTERNAL*delay)/Prescaler_256_);
		SET_prescaler(Prescaler_256_);
		wait_ovf();
		Timer_Stop();
		
	}
	else if((Calculate_max_time(Prescaler_1024_))>=delay)
	{
		
		_TCNT0_= 255-((CLOCK_INTERNAL*delay)/Prescaler_1024_);
		SET_prescaler(Prescaler_1024_);
		wait_ovf();
		Timer_Stop();
		
	}
	else if ((Calculate_max_time(Prescaler_1024_))<delay)
	{
		OVF_delay(delay);
		
	}
}