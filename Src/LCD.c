/**************************************************************************\
****************************************************************************
**                                                                        **
**		                                                                  **
**		FILENAME :        LCD.c                                           **
** 	                                                                      **
**  	DESCRIPTION :                                                     **
**  	      File used to manipulate the 16x2 LCD connected to the uC.   **
**  	                                                                  **
**  	GLOBAL VARIABLES :                                                **
**  				int 		threshTemp                                **
**		                                                                  **
**  	EXTERNAL VARIABLES :                                              **
**  				int 		currentTemp                               **
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
*		 INCLUDES           *
*                           *
\***************************/
#include <Inc/LCD.h>
#include <Inc/Util.h>

/***************************\
*                           *
*	  GLOBAL VARIABLES      *
*                           *
\***************************/
int threshTemp = 20; 		//	User defined temperature treshold

/***************************\
*                           *
*	 EXTERNAL VARIABLES     *
*                           *
\***************************/
extern int currentTemp;	//	Value setted by the continous ADC read

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_pulse_enable                                                **
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
void LCD_pulse_enable(void)
{
   EN  = 1;				// set EN pin to HIGH
   delay_ms(1);		// wait
   EN  = 0;       // set EN pin to LOW
   delay_ms(1);		// wait
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_write_cmd                                              	  **
**                                                                        **
**	DESCRIPTION: This function confirms that the current LCD			  **
**						   command is correctly written and executes it	  **
**                                                                        **
**	PARAMETERS: char c                                                    **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void LCD_write_cmd(char c)
{
   RS = 0;             	//  make RS Pin to Low for command
   P1 &= 0x0F;         	// 	make P2.4 to P2.7 zero
   P1 |= (c&0xF0);     	// 	write Upper nibble of Data
   LCD_pulse_enable(); 	//	confirm
   P1 &= 0x0F;         	// 	make P2.4 to P2.7 zero
   P1 |= ((c<<4)&0xF0);	// 	write Lower nibble of Data
   LCD_pulse_enable(); 	//	confirm
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_init                                              	  	  **
**                                                                        **
**	DESCRIPTION: This function initializes the LCD display in 			  **
**							 4-bit data transmission mode				  **
**                                                                        **
**	PARAMETERS: -                                                 	      **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void LCD_init(void)
{
	 delay_ms(100);		// 	wait
   P1 &= 0x0F;          // 	make P2.4 to P2.7 zero
   P1 |= (0x30&0xF0);   // 	write 0x30
   LCD_pulse_enable();  //	confirm
   delay_ms(50);		// 	wait
   P1 &= 0x0F;          // 	make P2.4 to P2.7 zero
   P1 |= (0x30&0xF0);   // 	write 0x30
   LCD_pulse_enable();  //	confirm
   delay_ms(2);			// 	wait
   P1 &= 0x0F;          // 	make P2.4 to P2.7 zero
   P1 |= (0x30&0xF0);   // 	write 0x30
   LCD_pulse_enable();  //	confirm
   delay_ms(4);			// 	wait
   P1 &= 0x0F;          // 	make P2.4 to P2.7 zero
   P1 |= (0x20&0xF0);   // 	write 0x20
   LCD_pulse_enable();  // 	confirm
   delay_ms(4);			//  wait
   LCD_write_cmd(0x28); //	function set
   LCD_write_cmd(0x0c); //	display on,cursor off,blink off
   LCD_write_cmd(0x01); //	clear display
   LCD_write_cmd(0x06); //	entry mode, set increment
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_return_home                                              	  **
**                                                                        **
**	DESCRIPTION: This function sets the cursor position to home			  **
**                                                                        **
**	PARAMETERS: -                                               	   	  **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void LCD_return_home(void)     
{
  LCD_write_cmd(0x02);
    delay_ms(10);
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_write_data                                              	  **
**                                                                        **
**	DESCRIPTION: This function writes one character on the LCD			  **
**                                                                        **
**	PARAMETERS: char t                                                    **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void LCD_write_data(char t)
{
   RS = 1;             	//  make RS Pin to High for Data
   P1 &= 0x0F;          //  make P2.4 to P2.7 zero
   P1 |= (t&0xF0);      // 	write Upper nibble of data
   LCD_pulse_enable();  // 	confirm
   P1 &= 0x0F;          //  make P2.4 to P2.7 zero
   P1 |= ((t<<4)&0xF0); //  write Lower nibble of data
   LCD_pulse_enable();	//  confirm
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_write_string                                                **
**                                                                        **
**	DESCRIPTION: This function writes on the LCD display the 			  **
**				 tring passed as parameter, character by character		  **
**                                                                        **
**	PARAMETERS: char*s                                             	      **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void LCD_write_string(char*s)
{
		while(*s)									
			LCD_write_data(*s++);//	write Data untill end of line is occured
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_write_int                                        			  **
**                                                                        **
**	DESCRIPTION: This function writes an 2 digit integer on the LCD		  **
**                                                                        **
**	PARAMETERS: int number                                            	  **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void LCD_write_int(int number)
{
	if(number >= 10)						//	parameter check
		LCD_write_data(number / 10 + '0');	//	write first digit
	LCD_write_data(number % 10 + '0');		//	write last digit 
	LCD_write_data(' ');					//	clear the next position 
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_set_cursor_line                                             **
**                                                                        **
**	DESCRIPTION: This function sets the cursor line depending			  **
**							 on the parameter passed as argument		  **
**                                                                        **
**	PARAMETERS: int line                                            	  **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void LCD_set_cursor_line(int line)
{
	if(line == 1)					//	parameter check
		LCD_write_cmd((char)0x80);	//	set to line 1
	else if(line == 2)				// 	parameter check
		LCD_write_cmd((char)0xC0);	//	set to line 2
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_set_cursor_position                                         **
**                                                                        **
**	DESCRIPTION: This function sets the cursor line and position		  **
**				 depending on the parameters passed as arguments		  **
**                                                                        **
**	PARAMETERS: int pos													  **
**							int line                                      **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void LCD_set_cursor_position(int pos, int line)
{
	LCD_set_cursor_line(line);		//	set line
	while(pos--)					//	shift to right until position is reached
		LCD_write_cmd(0x14);
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_clear_line                                        		  **
**                                                                        **
**	DESCRIPTION: This function clears the specified LCD line			  **
**                                                                        **
**	PARAMETERS: int line                                            	  **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void LCD_clear_line(int line)
{
	LCD_set_cursor_line(line);					//	set line
	LCD_write_string("                ");		//	fill line with spaces
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_clear_display                                        		  **
**                                                                        **
**	DESCRIPTION: This function clears the LCD display					  **
**                                                                        **
**	PARAMETERS: -                                               	  	  **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void LCD_clear_display(void)
{
	   LCD_write_cmd(0x01); 		//	clear display
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: LCD_display_idle_menu                                        	  **
**                                                                        **
**	DESCRIPTION: This function displays the welcome window with the		  **
**				 current temperature value and tip on how to open the	  **
**				 thermostat menu										  **
**                                                                        **
**	PARAMETERS: -                                               	  	  **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void LCD_display_idle_menu(void)
{
	int rotate;
	char string[] = "Press MENU button to enter setup";
	
	rotate = 0;
	while(rotate <= strlen(string) - 16)			//	keep scrooling if there
	{												//is more text to be shown
		LCD_write_string("Temp:           ");		
		LCD_set_cursor_position(strlen("Temp: "),1);//	display the current temp
		LCD_write_int(currentTemp);	
		if(threshTemp > currentTemp)				//	display central status
		{
			LCD_write_string("Heating");
			REL = 1;
		}
		else
		{
			LCD_write_string("Idle   ");
			REL = 0;
		}
		if(KEY_get() == KEY_MENU)					//	listen for key press and
			break;									//stop if menu key is pressed
		LCD_set_cursor_position(0,2);
		LCD_write_string(string + rotate++);		//	rotate the string
		delay_ms(400);								//	wait
	}
	delay_ms(500);									//	wait
}

