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
 *  \file   ZWIR451x-SPI?.h
 *  \brief  Type and function declarations for SPI? access.
 *
 *****************************************************************************/

 
#ifndef __SPI1_H__
#define __SPI1_H__

#include <stdint.h>
#include <stdbool.h>
#include "ZWIR45xx-6LoWPAN.h"

typedef enum {
  ZWIR_eSPI1_Ovfl = 0x0300,
  ZWIR_eSPI1_Undr
} ZWIR_SPI1_ErrorCode_t;


#ifndef ZWIR_SPI_PARAMETER_ENUMS_DEFINED
#define ZWIR_SPI_PARAMETER_ENUMS_DEFINED

typedef enum {
  ZWIR_SPI_CPHA,
  ZWIR_SPI_CPOL,
  ZWIR_SPI_BaudRate,
  ZWIR_SPI_PendingPin
} ZWIR_SPI_Parameter_t;


#endif // ZWIR_SPI_PARAMETER_ENUMS_DEFINED)

//! Callback function type
typedef  void ( * ZWIR_SPI_RXCallback_t ) ( void );

//! Send single byte over SPI interface
bool  ZWIR_SPI1_SendByte ( uint8_t  data );

//! Send group of bytes over SPI interface
uint8_t  ZWIR_SPI1_Send ( void*  data,  uint16_t  dataSize );

//! Read single byte from SPI interface
bool  ZWIR_SPI1_ReadByte ( uint8_t*  data );

//! Register callback function which is called in case of data reception
void  ZWIR_SPI1_SetRXCallback ( ZWIR_SPI_RXCallback_t  callback );

//! Configure the behavior of the SPI
void  ZWIR_SPI1_Configure ( ZWIR_SPI_Parameter_t  parameter,
                            uint32_t                    value );

bool  ZWIR_SPI1_IsTXEmpty ( void );

uint16_t  ZWIR_SPI1_GetAvailableTXBuffer ( void );

//! Provide a __putchar implementation which can be used by printf.
#define ZWIR_SPI1_PRINTF                \
uint8_t                                  \
__putchar ( uint8_t  c ) {               \
  while ( !ZWIR_SPI1_SendByte ( c ) );  \
}


#endif // __SPI1_H__
