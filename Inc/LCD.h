/**************************************************************************\
****************************************************************************
**                                                                        **
**																		  **
**		FILENAME :        LCD.h											  **
** 	                                                                      **
**  	DESCRIPTION :                                                     **
**  	      Header file for LCD.c										  **
**  	                                                                  **
**		INCLUDES:                                                         **
**					Util.h                                                **
**																		  **
**  	CONNECTION VARIABLES                                              **
**  				sbit RS = P1^2                                        **
**					sbit EN = P1^3                                        **
**					sbit REL  = P1^1                                      **
**                                                                        **
**  	FUNCTIONS PROTOTYPES:                                             **
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
**  	MACROS:                                                           **
**					-                                                     **
**  	                                                                  **
**  	DEFINES:														  **
**					-													  **
**  	                                                                  **
**  	STRUCTURES:														  **
**					-													  **
**  	                                                                  **
**  	AUTHOR :    Sergiu Cuciurean        START DATE :    5 Jan 2018    **
**                                                                        **
**                                                                        **
****************************************************************************
\**************************************************************************/

/***************************\
*                           *
*	     INCLUDES           *
*                           *
\***************************/
#include <Inc/Util.h>

/***************************\
*                           *
*	DEFINED CONNECTIONS     *
*                           *
\***************************/
sbit RS = P1^2;
sbit EN = P1^3;
sbit REL  = P1^1;

/***************************\
*                           *
*	FUNCTIONS PROTOTYPES	*
*                           *
\***************************/
void LCD_pulse_enable(void);
void LCD_write_cmd(char);
void LCD_init(void);
void LCD_return_home(void);
void LCD_write_data(char);
void LCD_write_string(char*);
void LCD_write_int(int);
void LCD_set_cursor_line(int);
void LCD_set_cursor_position(int, int);
void LCD_clear_line(int);
void LCD_clear_display(void);
void LCD_display_idle_menu(void);

