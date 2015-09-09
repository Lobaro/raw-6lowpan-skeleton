/** **************************************************************************
 *
 *  Copyright (c) 2011 Zentrum Mikroelektronik Dresden AG
 *
 *  This software is property of Zentrum Mikroelektronik Dresden AG (ZMD AG)
 *  and is protected under national and international laws. Any information
 *  and documentation delivered with this software shall exclusively be used
 *  in combination with ZMD AG products and may not be distributed at any
 *  time nor may it be rented or in any other way made available unless
 *  expressly authorized by ZMD AG. It is strictly prohibited to modify the
 *  software or documentation, to disassemble, reverse engineer or decompile
 *  the software or separate any part thereof. Copies may only be made by
 *  users expressly authorized by ZMD AG.
 *  
 *  Unless otherwise agreed upon under a separate agreement, ZMD AG shall not
 *  be liable for any damages arising out of defects resulting from delivered
 *  hard- and software, non-observance of instructions or misuse, abuse or use
 *  under abnormal conditions in connection with the ZWIR4512. To the extent
 *  permitted by law ZMD AG hereby expressly disclaims and user expressly
 *  waives any and all claims and warranties, whether express, implied or
 *  statutory, including, without limitation, implied warranties of
 *  merchantability and of fitness for a particular purpose, statutory
 *  warranty of non-infringement and other warranty that may arise by reason
 *  of usage of trade, custom or course of dealing.
 *
 *
 *  \file   ZWIR451x-Devkit.h
 *  \brief  Define core functions and types for the ZWIR451x Devkit
 * 
 ** ***************************************************************************/
 

#ifndef __ZWIR451x_DEVKIT__H__
#define __ZWIR451x_DEVKIT__H__

#include <stdbool.h>


//! Set LED 1 state 
void  ZWIR_SetLED1 ( bool  state );
//! Get LED 1 state
bool  ZWIR_GetLED1 ( void );
//! Toggle LED 1 state
void  ZWIR_ToggleLED1 ( void );

//! Set LED 2 state 
void  ZWIR_SetLED2 ( bool  state );
//! Get LED 2 state
bool  ZWIR_GetLED2 ( void );
//! Toggle LED 2 state
void  ZWIR_ToggleLED2 ( void );

//! Set LED 3 state 
void  ZWIR_SetLED3 ( bool  state );
//! Get LED 3 state
bool  ZWIR_GetLED3 ( void );
//! Toggle LED 3 state
void  ZWIR_ToggleLED3 ( void );

//! Set LED 4 state 
void  ZWIR_SetLED4 ( bool  state );
//! Get LED 4 state
bool  ZWIR_GetLED4 ( void );
//! Toggle LED 4 state
void  ZWIR_ToggleLED4 ( void );

//! Get Push-Button 1 Status
bool  ZWIR_GetButton1 ( void );

//! Get Push-Button 2 Status
bool  ZWIR_GetButton2 ( void );


#endif // __ZWIR451x__H__
