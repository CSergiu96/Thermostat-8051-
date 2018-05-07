/**************************************************************************\
****************************************************************************
**                                                                        **
**		                                                                  **
**		FILENAME :        Main.c                                          **
** 	                                                                      **
**  	DESCRIPTION :                                                     **
**  	      File containing main function thar runs at				  **
**			  startup of the uC											  **
**  	                                                                  **
**		                                                                  **
**  	PUBLIC FUNCTIONS :                                                **
**                                                                        **
**				 void main(void)                            			  **
**  	                                                                  **
**  	NOTES :                                                           **
**  	     -															  **
**  	                                                                  **
**  	AUTHOR :    Sergiu Cuciurean        START DATE :    5 Jan 2018    **
**                                                                        **
**                                                                        **
****************************************************************************
\**************************************************************************/


/***************************\
*                           *
*		 INCLUDES           *
*                           *
\***************************/
#include <Inc/Util.h>
#include <Inc/LCD.h>
#include <Inc/Menu.h>

/***************************\
*                           *
*	   MAIN FUNCTION        *
*                           *
\***************************/
void main(void)
{
  	PORT_init();						//	initialize ports to be input/output
  	LCD_init();							//	initialize LCD
	CLOCK_init();						//	initialize timers for ADC clk and read
  	while(1)							//	infinite loop
		MENU_display();					//	continous display of menu
}
