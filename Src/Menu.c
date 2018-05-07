/**************************************************************************\
****************************************************************************
**                                                                        **
**		                                                                  **
**		FILENAME :        Menu.c                                          **
** 	                                                                      **
**  	DESCRIPTION :                                                     **
**  	      File containing menu state machine						  **
**  	                                                                  **
**  	GLOBAL VARIABLES :                                                **
**  				int MENU_Selection           				          **
**		      int ADC_temperature          				                  **
**		      int MENU_Delete_flag          				              **
**		                                    				  			  **
**  	EXTERNAL VARIABLES :                                              **
**  				int threshTemp                                        **
**		                                                                  **
**  	PUBLIC FUNCTIONS :                                                **
**				 void SM_Init(void)                                       **
**				 void SM_Idle(void)                                       **
**				 void SM_Menu(void)                                       **
**				 void SM_Set_Temp(void)                                   **
**				 void SM_View_Set(void)                                   **
**				 void MENU_display(void)                  	              **
**  	                                                                  **
**  	NOTES :                                                           **
**  	     - 															  **
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
#include <Inc/Menu.h>
#include <Inc/LCD.h>

/***************************\
*                           *
*		 STRUCTURES         *
*                           *
\***************************/
STATE_machine_type STATE_machine[NO_STATES] = 
{
	{ STATE_INIT				, SM_Init 		},
	{	STATE_IDLE				, SM_Idle 		},
	{	STATE_MENU				, SM_Menu 		},
	{	STATE_1_SET_TEMP		, SM_Set_Temp	 },
	{	STATE_2_VIEW_SET		, SM_View_Set	},
	{	STATE_3_RESET			, SM_Init 		}
};

MENU_state M_State = STATE_INIT;

/***************************\
*                           *
*	 EXTERNAL VARIABLES     *
*                           *
\***************************/
extern int threshTemp;

/***************************\
*                           *
*	  GLOBAL VARIABLES      *
*                           *
\***************************/
int MENU_Selection;
int ADC_temperature;
int MENU_Delete_flag = 0;

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: MENU_display                                                    **
**                                                                        **
**	DESCRIPTION: Function that runs the funciton corresponding to 		  **
**							 the current state							  **
**                                                                        **
**	PARAMETERS: -									                      **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void MENU_display(void)
{
	if(M_State < NO_STATES)							//	verify the state
		(*STATE_machine[M_State].func)();			//	execute function
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: SM_Init                                                         **
**                                                                        **
**	DESCRIPTION: Clear the LCD, initialize the variables and show		  **
**							 a startup message							  **
**                                                                        **
**	PARAMETERS: -									                      **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void SM_Init(void)
{
	LCD_clear_display();				  //	clear the display
	delay_ms(100);						  //	wait
	LCD_return_home();										 		
	LCD_write_string(" Starting up.");    //	show startup message 
	delay_ms(150);                         	
	LCD_return_home();                     
	LCD_write_string(" Starting up..");    
	delay_ms(150);                         
	LCD_return_home();                     
	LCD_write_string(" Starting up...");   
	delay_ms(150);                         
	LCD_clear_line(1);                     
	threshTemp = 20;                      // 	initialize variables																	 
	M_State = STATE_IDLE;                 // 	switch the state
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: SM_Idle                                                         **
**                                                                        **
**	DESCRIPTION: 	Display general info and wait for menu entry		  **
**                                                                        **
**	PARAMETERS: -									                      **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void SM_Idle(void)
{
	LCD_return_home();                    
	LCD_display_idle_menu();              //	clear the display
	if(KEY_get() != KEY_MENU)             //	read the key
		M_State = STATE_IDLE;               
	else                                  
	{                                     //	enter the menu if condition is met
		LCD_clear_display();                
		MENU_Selection = 1;                 
		M_State = STATE_MENU;             //	switch	state
	}                                     
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: SM_Menu                                                         **
**                                                                        **
**	DESCRIPTION: 	Menu window displaying available commands for 		  **
**	*							the thermostat							  **
**                                                                        **
**	PARAMETERS: -									                      **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void SM_Menu(void)
{
	char key;

	M_State = STATE_MENU;                       //	pre-set state
	LCD_set_cursor_line(1);                   		
	LCD_write_string(" Select with '*'");     	//	display menu hint
	LCD_set_cursor_line(2);                   	
	key = KEY_get();                          	//	read key
	if(key == KEY_UP)                         	//	change menu option
	{                                         	//depending on the pressed key
		MENU_Selection--;                       	
		delay_ms(400);                          	
	}                                         	
	else if(key == KEY_DOWN)                  	
	{                                         	
		MENU_Selection++;                       	
		delay_ms(400);                          	
	}                                         	
	else if (key == KEY_SELECT)               	//	if select is pressed
		M_State = MENU_Selection + 2; 			//	enter the section
	else                                        
	{                                           
		if (MENU_Selection == 0)                  
			MENU_Selection = 3;                     
		else if (MENU_Selection == 4)             
			MENU_Selection = 1;                   
		switch(MENU_Selection)                  //	if not selected
		{                                       //	display section info
			case(1):                                
				LCD_write_string("1:   Set temp   "); 
				break;                                
			case(2):                                
				LCD_write_string("2:View threshold"); 
				break;                                
			case(3):                                
				LCD_write_string("3:    Reset     "); 	
				break;                                
		}                                         
	}                                           
	if(key == KEY_BACK)							 //	if back is pressed
		M_State = STATE_IDLE;                    //	go back to welcome screen
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: SM_Set_Temp                                                     **
**                                                                        **
**	DESCRIPTION: 	Menu window that allows the user to set the			  **
**								temperature threshold for the thermostat  **
**                                                                        **
**	PARAMETERS: -									                      **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void SM_Set_Temp(void)
{
	unsigned char key = KEY_NOT_PRESSED;
	unsigned char setTemp[2];
																											 
	LCD_clear_display();                                 //	clear the display
	LCD_write_string("Press '*' to set");                //	display hint
	LCD_set_cursor_line(2);                              
	LCD_write_string("Set temp to : ");                  
	LCD_set_cursor_position(strlen("Set temp to : "),2); 
	MENU_Delete_flag = 0;                                
	
	readkey:																			
	do 
	{
		key = KEY_get();								// read first key
		if (key == KEY_BACK)
		{
			M_State = STATE_MENU;						
			key = KEY_NOT_PRESSED;						// if back is pressed
			delay_ms(500);								// return to menu
			break;
		}
	}
	while ('0' > key || key > '9');      
	if(M_State != STATE_MENU)
	{
		LCD_write_data(key);							// store the key
		setTemp[1] = key - '0';
		key = KEY_NOT_PRESSED;
		delay_ms(500);
		MENU_Delete_flag = 0;
		readkey2:
		do 
		{
			key = KEY_get();							//	read second key press
			if (key == KEY_BACK)
			break;			
			if (key == KEY_SELECT && !MENU_Delete_flag)
			{
				setTemp[0] = setTemp[1];				// store if it's a digit
				setTemp[1] = 0;
				goto select;
			}
		}
		while ('0' > key || key > '9');
		
		if(key != KEY_BACK)
		{
			LCD_write_data(key);
			setTemp[0] = key - '0';
		}
		else
		{
			LCD_write_cmd(0x10);						//	delete digit if the pressed key
			LCD_write_data(' ');						//is back
			LCD_write_cmd(0x10);
			key = KEY_NOT_PRESSED;
			MENU_Delete_flag = 1;
			delay_ms(500);
			goto readkey;
		}
		do 
		{
			key = KEY_get();
			if (key == KEY_BACK)
			{
				LCD_write_cmd(0x10);					//	delete digit if the pressed key
				LCD_write_data(' ');					//is back
				LCD_write_cmd(0x10);
				key = KEY_NOT_PRESSED;
				MENU_Delete_flag = 1;
				delay_ms(500);
				goto readkey2;
			}
		}
		while (key != KEY_SELECT);
		select:
		LCD_clear_display();
		LCD_set_cursor_line(1);
		if((setTemp[1] * 10 + setTemp[0]) >= 0 &&		//	display set value
			 (setTemp[1] * 10 + setTemp[0]) <= 50)
		{
			LCD_write_string("Temperature set");
			threshTemp = setTemp[1] * 10 + setTemp[0];	// 	set the treshold
			delay_ms(1000);
			M_State = STATE_IDLE;
		}
		else
		{
			LCD_write_string("  Invalid temp");			//	verify for invalid
			delay_ms(1000);								//input
			M_State = STATE_1_SET_TEMP;
		}
	}
}

/**************************************************************************\
****************************************************************************
**                                                                        **
**	NAME: SM_View_Set                                                     **
**                                                                        **
**	DESCRIPTION: 	Menu window that displays the current threshold		  **
**                                                                        **
**	PARAMETERS: -									                      **
**		                                                                  **
**	RETURN: void					                                      **
**           															  **
****************************************************************************
\**************************************************************************/
void SM_View_Set(void)
{
	LCD_clear_display();							//	clear the display
	LCD_set_cursor_line(1);
	LCD_write_string("Current treshold");
	LCD_set_cursor_line(2);
	LCD_write_string("Is set to : ");
	LCD_write_int(threshTemp);						//	display current threshold
	delay_ms(6000);
	M_State = STATE_MENU;							//	switch the menu
}	

