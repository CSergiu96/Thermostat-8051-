/**************************************************************************\
****************************************************************************
**                                                                        **
**		                                                                  **
**		FILENAME :        Util.c                                          **
** 	                                                                      **
**  	DESCRIPTION :                                                     **
**  	      File contains multiple device initializers, timer interrupt **
**					functions and value getters							  **
**  	                                                                  **
**  	GLOBAL VARIABLES :                                                **
**  				int 		currentTemp                               **
**		                                                                  **
**  	EXTERNAL VARIABLES :                                              **
**  				int 		threshTemp                                **
**		                                                                  **
**  	PUBLIC FUNCTIONS :                                                **
**                                                                        **
**				 void 		LCD_pulse_enable(void)                        **
**         void 		LCD_write_cmd(char)                               **
**         void 		LCD_init(void)                                    **
**         void 		LCD_return_home(void)                             **
**         void 		LCD_write_data(char)                              **
**         void 		LCD_write_string(char*)                           **
**         void 		LCD_write_int(int)                                **
**         void 		LCD_set_cursor_line(int)                          **
**         void 		LCD_set_cursor_position(int, int)                 **
**         void 		LCD_clear_line(int)                               **
**  	     void 		LCD_clear_display(void)                           **
**  	     void 		LCD_display_idle_menu(void)                       **
**  	                                                                  **
**  	NOTES :                                                           **
**  	     The LCD connection pins are defined in "LCD.h"               **
**  	                                                                  **
**  	AUTHOR :    Sergiu Cuciurean        START DATE :    5 Jan 2018    **
**                                                                        **
**                                                                        **
****************************************************************************
\**************************************************************************/

/***************************\
*                           *
*		  INCLUDES			*
*                           *
\***************************/
#include <Inc/Util.h>
#include <Inc/LCD.h>

/***************************\
*                           *
*		GLOBAL VARIABLES    *
*                           *
\***************************/
int currentTemp = 20;		//	Value setted by the continous ADC read

/***************************\
*                           *
*    EXTERNAL VARIABLES     *
*                           *
\***************************/
extern int threshTemp;	//	User defined temperature treshold

/***************************\
*                           *
*	DEFINED CONNECTIONS     *
*                           *
\***************************/
sbit CLK  = P1^0;
sbit R1   = P3^0;
sbit R2   = P3^1;
sbit R3   = P3^2;
sbit R4   = P3^3;
sbit MEN  = P0^0;
sbit UP   = P0^1;
sbit DWN  = P0^2;

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: delay_ms                                                        **
**                                                                        **
**	DESCRIPTION: Soft delay												  **
**                                                                        **
**	PARAMETERS: unsigned int delay                                        **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void delay_ms(unsigned int delay)
{
   unsigned int i;
	
   for(;delay>0;delay--)				//	wait
		for(i=122;i>0;i--);    			//	wait
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: CLOCK_init                                                      **
**                                                                        **
**	DESCRIPTION: Initialize timer0 to toggle ADC and					  **
**							 timer1 to cotinous ADC read				  **
**                                                                        **
**	PARAMETERS: -   							                          **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void CLOCK_init(void)
{
	TMOD = (TMOD & 0xF0) | 0x01;  /* set T/C0 mode */
	ET0 = 1;                      /* enable timer 0 interrupts */
	TR0 = 1;                      /* start timer 0 running */
	TMOD = (TMOD & 0x0F) | 0x01;  /* Set Mode (8-bit timer with reload) */
	TH1 = 256 - 100;              /* Reload TL1 to count 100 clocks */
	TL1 = TH1;
	ET1 = 1;                      /* Enable Timer 1 Interrupts */
	TR1 = 1;                      /* Start Timer 1 Running */
	EA = 1;                       /* Global Interrupt Enable */
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: PORT_init                                               		  **
**                                                                        **
**	DESCRIPTION: This function confirms that the current LCD			  **
**						   command is correctly written and executes it	  **
**                                                                        **
**	PARAMETERS: -                                                         **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void PORT_init(void)
{
	
	P0 = 0x00; 				// input pins : MEN, UP, DWN buttons
	P1 = 0x00; 				// output pins : CLK (ADC clock), REL (relay toggle)
							//								RS, E, D[4-7] (LCD control)
	P2 = 0xFF; 				// input pins : OUT[1-8] (ADC read values)
	P3 = 0x00; 				// output pins later defined as input
							//          used for menu keypad
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: KEY_get                                               		  **
**                                                                        **
**	DESCRIPTION: This function toggles all key matrix and returns the	  **
**							 pressed button								  **
**                                                                        **
**	PARAMETERS: -                                                         **
**		                                                                  **
**	RETURN: unsigned char					                              **
**           															  **
****************************************************************************
\**************************************************************************/
unsigned char KEY_get(void)
{
	unsigned char key = 15;
	
	P3 = 0x6F;						//	toggle collum 1 and set key if read
	if(R1==0) {key=1;}	
	if(R2==0) {key=4;}
	if(R3==0) {key=7;}
	if(R4==0) {key=10;}
	P3 = 0x5F;						//	toggle collum 2 and set key if read
	if(R1==0) {key=2;}
	if(R2==0) {key=5;}
	if(R3==0) {key=8;}
	if(R4==0) {key=0;}
	P3 = 0x3F;						//	toggle collum 1 and set key if read
	if(R1==0) {key=3;}
	if(R2==0) {key=6;}
	if(R3==0) {key=9;}
	if(R4==0) {key=11;}
	if(key<12)						//	if a key was pressed set it for return 
		key = key + '0';
	else if(MEN == 1)				//	check if a menu button was pressed
	{
		delay_ms(20);				//	debounce
		if(MEN == 1)
			key = KEY_MENU;			//	set key
	}
	else if(UP == 1)				//	check if a menu button was pressed
	{                     
		delay_ms(20);				//	debounce
		if(UP == 1)
			key = KEY_UP;			//	set key
	}
	else if(DWN == 1)				//	check if a menu button was pressed
	{								
		delay_ms(20);				//	debounce
		if(DWN == 1)        
			key = KEY_DOWN;			//	set key
	}
	delay_ms(20);
	return (key);					//	return pressed key
}	

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: ADC_get_value                                               	  **
**                                                                        **
**	DESCRIPTION: This function returns the current adc value			  **
**                                                                        **
**	PARAMETERS: -                                                         **
**		                                                                  **
**	RETURN: int					                                    	  **
**           															  **
****************************************************************************
\**************************************************************************/
int ADC_get_value(void)
{
	int temp;
	
	temp = (int)P2 *50 / 254; //	aproximated value 							 
	return (temp);			  //converted from raw value
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: timer0_ISR                                               	  	  **
**                                                                        **
**	DESCRIPTION: Timer0 interrupt used for ADC clock generation			  **
**                                                                        **
**	PARAMETERS: -                                                         **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void timer0_ISR (void) interrupt 1
{
	ADC_clock();  		//	toggle adc clock
	TH0 = 0xFD;			//	set reload time as low as possible
}

/**************************************************************************\
****************************************************************************
**                                                                       **
**	NAME: timer1_ISR                                               	  	 **
**                                                                       **
**	DESCRIPTION: Timer1 interrupt used for ADC continous read			 **
**                                                                       **
**	PARAMETERS: -                                                        **
**		                                                                 **
**	RETURN: void					                                     **
**           															 **
****************************************************************************
\**************************************************************************/
void timer1_ISR (void) interrupt 3
{
	TH1 = 256 - 100;              		// 	reload TL1 to count 100 clocks 
	currentTemp = ADC_get_value();		//	read ADC temperature
	if(threshTemp > currentTemp)		//	set relay	accordingly
		REL = 1;
	else
		REL = 0;
}

