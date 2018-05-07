/**************************************************************************\
****************************************************************************
**                                                                        **
**		                                                                  **
**		FILENAME :        Util.h                                          **
** 	                                                                      **
**  	DESCRIPTION :                                                     **
**  	      Header file for Util.c									  **
**  	                                                                  **
**		INCLUDES:                                                         **
**					stdio.h                                               **
**          stdlib.h                                                	  **
**          string.h                                                	  **
**          reg51.h                                                 	  **
**																		  **
**  	CONNECTION VARIABLES :                                            **
**  				-                                             		  **
**                                                                        **
**  	FUNCTIONS PROTOTYPES:                                             **
**				  void 					PORT_init(void)                   **
**				  void 					CLOCK_init(void)                  **
**				  void 					delay_ms(unsigned int dly)        **
**				  void 					REL_set(bit mode)                 **
**				  unsigned char KEY_get(void)                             **
**				  int  					ADC_get_value(void)               **
**  	                                                                  **
**  	MACROS:                                                           **
**					ADC_clock()						                      **
**  	                                                                  **
**  	DEFINES:														  **
**					KEY_SELECT 		                                      **
**          KEY_BACK   		                                              **
**          KEY_MENU   		                                              **
**          KEY_UP	   		                                              **
**          KEY_DOWN   		                                              **
**          KEY_NOT_PRESSED                                               **
**                                                                        **
**  	STRUCTURES:														  **
**					-         											  **
**																		  **
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <reg51.h>

/***************************\
*                           *
*		 DEFINES            *
*                           *
\***************************/
#define KEY_SELECT 		  (10 + '0')
#define KEY_BACK   		  (11 + '0')
#define KEY_MENU   		  12
#define KEY_UP	   		  13
#define KEY_DOWN   		  14
#define KEY_NOT_PRESSED	  15

/***************************\
*                           *
*		  MACROS            *
*                           *
\***************************/
#define ADC_clock() CLK = !CLK;

/***************************\
*                           *
*	 FUNCTIONS PROTOTYPES   *
*                           *
\***************************/
void 			PORT_init(void);
void 			CLOCK_init(void);
void 			delay_ms(unsigned int dly);
void 			REL_set(bit mode);
unsigned char	KEY_get(void);
int  				ADC_get_value(void);

