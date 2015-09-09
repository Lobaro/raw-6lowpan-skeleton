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
 *  \file   ZWIR451x-UART?.h
 *  \brief  Type and function declarations for UART? access.
 *
 *****************************************************************************/



 
#ifndef __UART1_H__
#define __UART1_H__

#include <stdint.h>
#include <stdbool.h>

/** *************************************************************************
 *  UART error code enumeration
 ** *************************************************************************/
typedef
  enum {
    ZWIR_UART1_eOvfl = 0x0210,
    ZWIR_UART1_eParity,
    ZWIR_UART1_eFrame,
    ZWIR_UART1_eNoise
  } ZWIR_UART1_ErrorCode_t;


#ifndef ZWIR_UART_PARAMETER_ENUMS_DEFINED
#define ZWIR_UART_PARAMETER_ENUMS_DEFINED


/** *************************************************************************
 *  UART parity configuration options enumeration
 ** *************************************************************************/
typedef
  enum {
    ZWIR_UART_NoParity   = 0x00,  /**< no parity bit (default)*/
    ZWIR_UART_EvenParity = 0x08,  /**< even parity bit*/
    ZWIR_UART_OddParity  = 0x0c   /**< odd parity bit*/
  } ZWIR_UART_Parity_t;

/** *************************************************************************
 *  UART stop-bit configuration options enumeration
 ** *************************************************************************/
typedef
  enum {
    ZWIR_UART_Stop_1     = 0x00,  /**< 1 stop bit (default)*/
    ZWIR_UART_Stop_0_5   = 0x10,  /**< 0.5 stop bits*/
    ZWIR_UART_Stop_2     = 0x20,  /**< 2 stop bits*/
    ZWIR_UART_Stop_1_5   = 0x30   /**< 1.5 stop bits*/
  } ZWIR_UART_StopBits_t;

/** *************************************************************************
 *  UART flow-control configuration options enumeration
 ** *************************************************************************/
typedef
  enum {
    ZWIR_UART_NoFlowControl = 0x00,  /**< no flow control (default)*/
    ZWIR_UART_HWFlowControl = 0x01   /**< hardware flow control */
  } ZWIR_UART_FlowControl_t;


/** *************************************************************************
 *  Specifies parameter to be changed with ZWIR_UARTx_Configure
 *  \deprecated
 ** *************************************************************************/
typedef
  enum {
    ZWIR_UART_BaudRate,
    ZWIR_UART_Parity,
    ZWIR_UART_StopBits,
    ZWIR_UART_FlowControl
  } ZWIR_UART_Parameter_t;


#endif // ZWIR_UART_PARAMETER_ENUMS_DEFINED


/** *************************************************************************
 *  Definition of function signature required to be used by function that \
 *   shall act as UART receive callback function.
 ** *************************************************************************/
typedef
  void ( * ZWIR_UART_RXCallback_t ) ( void );



/** *************************************************************************
 *  Write a single byte into the transmission buffer
 *  \parameter data  value to be written to the buffer
 *  \return  true if byte was written successfully or false if buffer was full
 ** *************************************************************************/
bool
  ZWIR_UART1_SendByte ( uint8_t  data );

/** *************************************************************************
 *  Write a byte sequence into the transmission buffer
 *  \param data  pointer to the data to be written
 *  \param size  number of bytes to be written
 *  \return  number of bytes that have actually been written
 ** *************************************************************************/
uint16_t
  ZWIR_UART1_Send ( void*     data,  
                    uint16_t  size );

/** *************************************************************************
 *  Read one byte from the receive buffer 
 *  \param data  pointer to a location the read byte is written to
 *  \return  true if a byte has been read or false if the receive buffer was \
             empty
 ** *************************************************************************/
bool
  ZWIR_UART1_ReadByte ( uint8_t*  data );

/** *************************************************************************
 *  Register the callback function to be called when receive data is available
 *  \param callback  function to be called upon reception of data
 ** *************************************************************************/
void
  ZWIR_UART1_SetRXCallback ( ZWIR_UART_RXCallback_t  callback );

/** *************************************************************************
 *  Configure UART settings
 *  \param baudRate  the value determines the UART speed in bits/second
 *  \param parameters  determines the UART configuration - generated by \
                       binary OR'ing of parity, stop and flow-control enums
 ** *************************************************************************/
void
  ZWIR_UART1_Setup ( uint32_t  baudRate,
                     uint8_t   parameters );
                        
/** *************************************************************************
 *  Determine if there are any data left in the transmit buffer
 *  \return  Returns true if the transmission buffer is empty, false otherwise
 ** *************************************************************************/
bool
  ZWIR_UART1_IsTXEmpty ( void );

/** *************************************************************************
 *  Get the byte count that is still available in the transmit buffer
 *  \return  Number of bytes available in the transmit buffer
 ** *************************************************************************/
uint16_t
  ZWIR_UART1_GetAvailableTXBuffer ( void );

/** *************************************************************************
 *  Configure single parameters of the UART
 *  \deprecated
 ** *************************************************************************/
void  __attribute__ (( deprecated ))
  ZWIR_UART1_Configure (  ZWIR_UART_Parameter_t  parameter,
                          uint32_t               value );

// for backward compatibility
static __attribute__ (( deprecated )) ZWIR_UART1_ErrorCode_t const ZWIR_eUART1_Ovfl = ZWIR_UART1_eOvfl;
static __attribute__ (( deprecated )) ZWIR_UART1_ErrorCode_t const ZWIR_eUART1_Parity = ZWIR_UART1_eParity;
static __attribute__ (( deprecated )) ZWIR_UART1_ErrorCode_t const ZWIR_eUART1_Frame = ZWIR_UART1_eFrame;
static __attribute__ (( deprecated )) ZWIR_UART1_ErrorCode_t const ZWIR_eUART1_Noise = ZWIR_UART1_eNoise;


//! Provide a __putchar implementation which can be used by printf.
#define ZWIR_UART1_PRINTF                \
uint8_t                                                   \
__putchar ( uint8_t  c ) {                                \
  while ( !ZWIR_UART1_SendByte ( c ) );  \
  return  c;                                              \
}


#endif // __UART1_H__
