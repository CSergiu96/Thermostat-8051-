/**************************************************************************\
****************************************************************************
**                                                                        **
**		                                                                  **
**		FILENAME :        MENU.h                                          **
** 	                                                                      **
**  	DESCRIPTION :                                                     **
**  	      Header file for MENU.c									  **
**  	                                                                  **
**		INCLUDES:                                                         **
**					Util.h                                                **
**																		  **
**  	CONNECTION VARIABLES :                                            **
**  				-                                             		  **
**                                                                        **
**  	FUNCTIONS PROTOTYPES:                                             **
**                                                                        **
**				 void SM_Init(void);                                      **
**				 void SM_Idle(void);                                      **
**				 void SM_Menu(void);                                      **
**				 void SM_Set_Temp(void);                                  **
**				 void SM_View_Set(void);                                  **
**				 void MENU_display(void);                                 **
**  	                                                                  **
**  	MACROS:                                                           **
**				 -                                                        **
**  	                                                                  **
**  	DEFINES:														  **
**			  NO_STATES 6												  **
**  	                                                                  **
**  	STRUCTURES:														  **
**				MENU_date												  **
**  	    MENU_state                                                	  **
**				STATE_machine_type                                        **
**  	                                                                  **
**  	AUTHOR :    Sergiu Cuciurean        START DATE :    5 Jan 2018    **
**                                                                        **
**                                                                        **
****************************************************************************
\**************************************************************************/

/***************************\
*                           *
*		 DEFINES            *
*                           *
\***************************/
#define NO_STATES 6

/***************************\
*                           *
*	     STRUCTURES         *
*                           *
\***************************/
typedef struct
{
	int day;
	int month;
	int year;	
}MENU_date;

typedef enum
{
	STATE_INIT,
	STATE_IDLE,
	STATE_MENU,
	STATE_1_SET_TEMP,
	STATE_2_VIEW_SET,
	STATE_3_RESET
}MENU_state;

typedef struct
{
	MENU_state state;
	void (*func)(void);
}STATE_machine_type;

/***************************\
*                           *
*	FUNCTIONS PROTOTYPES	*
*                           *
\***************************/
void SM_Init(void);
void SM_Idle(void);
void SM_Menu(void);
void SM_Set_Temp(void);
void SM_View_Set(void);
void MENU_-display(void);

