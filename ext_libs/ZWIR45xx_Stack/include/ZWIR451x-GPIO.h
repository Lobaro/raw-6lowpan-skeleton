/** **************************************************************************
 *
 *  Copyright (c) 2013 Zentrum Mikroelektronik Dresden AG
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
 *  \file   ZWIR451x-GPIO.h
 *  \brief  Type and function declarations for GPIO Access.
 *
 *****************************************************************************/

 
#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#include <stdbool.h>

/** *************************************************************************
 *  Enumeration of module pins accessible from application code
 *
 ** *************************************************************************/
#ifdef _ZWIR4512AC2_
typedef
  enum {
    ZWIR_Pin1  = 0x00000080,    // PA7
    ZWIR_Pin2  = 0x00000040,    // PA6
    ZWIR_Pin3  = 0x00000020,    // PA5
    ZWIR_Pin4  = 0x00000010,    // PA4
    ZWIR_Pin5  = 0x00000008,    // PA3
    ZWIR_Pin6  = 0x00000004,    // PA2
    ZWIR_Pin7  = 0x00000002,    // PA1
    ZWIR_Pin8  = 0x00000001,    // PA0
    ZWIR_Pin9  = 0x20000000,    // PC13
    ZWIR_Pin13 = 0x00000400,    // PA10
    ZWIR_Pin14 = 0x00000200,    // PA9
    ZWIR_Pin17 = 0x40000000,    // PC14
    ZWIR_Pin18 = 0x80000000,    // PC15
    ZWIR_Pin19 = 0x00000800,    // PA11
    ZWIR_Pin20 = 0x00001000,    // PA12
    ZWIR_Pin21 = 0x00080000,    // PB3  (Alternative Function)
    ZWIR_Pin22 = 0x00002000,    // PA13 (Alternative Function)
    ZWIR_Pin23 = 0x00008000,    // PA15 (Alternative Function)
    ZWIR_Pin24 = 0x00004000,    // PA14 (Alternative Function)
    ZWIR_Pin25 = 0x00800000,    // PB7
    ZWIR_Pin26 = 0x00400000     // PB6
  } ZWIR_GPIO_Pin_t;
#else
# ifdef _ZWIR4512AC1_
typedef
  enum {
    ZWIR_Pin1  = 0x00000080,    // PA7
    ZWIR_Pin2  = 0x00000040,    // PA6
    ZWIR_Pin3  = 0x00000020,    // PA5
    ZWIR_Pin4  = 0x00000010,    // PA4
    ZWIR_Pin5  = 0x00000008,    // PA3
    ZWIR_Pin6  = 0x00000004,    // PA2
    ZWIR_Pin7  = 0x00000002,    // PA1
    ZWIR_Pin8  = 0x00000001,    // PA0
    ZWIR_Pin9  = 0x20000000,    // PC13
    ZWIR_Pin12 = 0x00000400,    // PA10
    ZWIR_Pin13 = 0x00000200,    // PA9
    ZWIR_Pin16 = 0x00000800,    // PA11
    ZWIR_Pin17 = 0x00001000,    // PA12
    ZWIR_Pin19 = 0x00080000,    // PB3  (Alternative Function)
    ZWIR_Pin20 = 0x00002000,    // PA13 (Alternative Function)
    ZWIR_Pin21 = 0x00008000,    // PA15 (Alternative Function)
    ZWIR_Pin22 = 0x00004000,    // PA14 (Alternative Function)
    ZWIR_Pin23 = 0x00800000,    // PB7
    ZWIR_Pin24 = 0x00400000     // PB6
  } ZWIR_GPIO_Pin_t;
# else
typedef enum { __undefined } ZWIR_GPIO_Pin_t;
#  warning Processor type must be specified through #define directive - please define _ZWIR4512AC1_ or _ZWRI4512AC2_
# endif
#endif

/** *************************************************************************
 *  Enumeration GPIO driving strengths
 ** *************************************************************************/
typedef
  enum {
    ZWIR_GPIO_dsLow    = 0x02,
    ZWIR_GPIO_dsMedium = 0x01,
    ZWIR_GPIO_dsHigh   = 0x03
  } ZWIR_GPIO_DriverStrength_t;

/** *************************************************************************
 *  Enumeration of GPIO output modes
 ** *************************************************************************/
typedef
  enum {
    ZWIR_GPIO_omPushPull             = 0x00,
    ZWIR_GPIO_omOpenDrain            = 0x04,
    ZWIR_GPIO_omAlternativePushPull  = 0x08,
    ZWIR_GPIO_omAlternativeOpenDrain = 0x0c
  } ZWIR_GPIO_OutputMode_t;

/** *************************************************************************
 *  Enumeration of GPIO input modes
 ** *************************************************************************/
typedef
  enum {
    ZWIR_GPIO_imAnalog   = 0x00,
    ZWIR_GPIO_imFloating = 0x04,
    ZWIR_GPIO_imPullUp   = 0x18,
    ZWIR_GPIO_imPullDown = 0x08
  } ZWIR_GPIO_InputMode_t;

/** *************************************************************************
 *  Enumeration of GPIO remapping functions
 ** *************************************************************************/
typedef
  enum {
    ZWIR_GPIO_rfSWJ = 0,
  } ZWIR_GPIO_RemapFunction_t;

/** *************************************************************************
 *  Enumeration of GPIO remapping values for JTAG/Serial Wire Debug pins
 ** *************************************************************************/
typedef
  enum {
    ZWIR_GPIO_swjrEnableSWJ  = 1,
    ZWIR_GPIO_swjrSWOnly     = 2,
    ZWIR_GPIO_swjrDisableSWJ = 4
  } ZWIR_GPIO_SWJRemapValue_t;


/** *************************************************************************
 *  High-level function for configuring output pins.
 *  \param pins    a binary OR'ed combination of pin enumerators
 *  \param driver  driving strength of output pin(s)
 *  \param mode    the pin mode (push/pull, open drain, alternative)
 ** *************************************************************************/
void
ZWIR_GPIO_ConfigureAsOutput ( uint32_t                    pins,              
                              ZWIR_GPIO_DriverStrength_t  driver,
                              ZWIR_GPIO_OutputMode_t      mode );

/** *************************************************************************
 *  High-level function for configuring input pins.
 *  \param pins    a binary OR'ed combination of pin enumerators
 *  \param mode    the pin mode (floating, pull-up pull-down, analog)
 ** *************************************************************************/
void
ZWIR_GPIO_ConfigureAsInput ( uint32_t               pins,
                             ZWIR_GPIO_InputMode_t  mode );


/** *************************************************************************
 *  High-level function for reading a single pin.
 *  \param pin    pin enumerator
 *  \return  Returns true if the input level was logical high, false otherwise
 ** *************************************************************************/
bool
ZWIR_GPIO_Read ( ZWIR_GPIO_Pin_t  pin );


/** *************************************************************************
 *  High-level function for reading multiple input pins at the same time.
 *   The bit mask for of the returned value looks like shown below:
 *  For ZWIR4512AC1 devices:
 *         7    6    5    4    3    2    1    0
 *      +----+----+----+----+----+----+----+----+
 *   3  |    |    |  9 |    |    |    |    |    |
 *      +----+----+----+----+----+----+----+----+
 *   2  | 23 | 24 |    |    | 19 |    |    |    |
 *      +----+----+----+----+----+----+----+----+
 *   1  | 21 | 22 | 20 | 17 | 16 | 12 | 13 |    |
 *      +----+----+----+----+----+----+----+----+
 *   0  |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |
 *      +----+----+----+----+----+----+----+----+
 *  For ZWIR4512AC2 devices:
 *         7    6    5    4    3    2    1    0
 *      +----+----+----+----+----+----+----+----+
 *   3  | 18 | 17 |  9 |    |    |    |    |    |
 *      +----+----+----+----+----+----+----+----+
 *   2  | 25 | 26 |    |    | 21 |    |    |    |
 *      +----+----+----+----+----+----+----+----+
 *   1  | 23 | 24 | 22 | 20 | 19 | 13 | 14 |    |
 *      +----+----+----+----+----+----+----+----+
 *   0  |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |
 *      +----+----+----+----+----+----+----+----+
 *  \param pins    a binary OR'ed combination of pin enumerators
 *  \return  Bit mask with 1 set at pin positions read as logical high level
 ** *************************************************************************/
uint32_t
  ZWIR_GPIO_ReadMultiple ( uint32_t  pins );


/** *************************************************************************
 *  High-level function for reading a single pin.
 *  \param pins   a binary OR'ed combination of pin enumerators
 *  \param value  the value to be written to all pins
 ** *************************************************************************/
void
  ZWIR_GPIO_Write ( uint32_t  pins,
                    bool      value );


/** *************************************************************************
 *  Function for remapping of pin functions
 *  \param function  determines the remapping function
 *  \param value     determines the remapping to be applied
 ** *************************************************************************/
void
  ZWIR_GPIO_Remap ( ZWIR_GPIO_RemapFunction_t  function,
                    int32_t                    value );

#endif // __GPIO_H__
