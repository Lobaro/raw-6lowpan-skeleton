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
 *  \file   ZWIR45xx-OTAU.h
 *  \brief  Type and function declarations for ZWIR45xx Over the Air Update
 *
 ** **************************************************************************/


#ifndef __ZWIR45XX_OTAU__H__
#define __ZWIR45XX_OTAU__H__

#include <stdint.h>
#include <stdbool.h>


typedef enum {
  ZWIR_eInvalidVID                = 0x0400,
  ZWIR_eInvalidOTAUInterface      = 0x0401
  
} ZWIR_OTAU_ErrorCode_t;


typedef enum {
  ZWIR_sInvalidPacketHeader      ,
  ZWIR_sUpdateInProgress         ,
  ZWIR_sInvalidPacketCRC         ,
  ZWIR_sUnknownPacketType        ,
  ZWIR_sInvalidFragmentSize      ,
  ZWIR_sInvalidDataPacket        ,
  ZWIR_sFragmentWriteError       ,
  ZWIR_sInvalidCRCPacket         ,
  ZWIR_sCRCWriteError            ,
  ZWIR_sInvalidExecutePacket     ,
  ZWIR_sFirmwareImageVerifyFailed,
                 
  ZWIR_sInitNewFirmwareDone      ,
  ZWIR_sWriteFragmentDone        ,
  ZWIR_sWriteCRCDone             ,
  ZWIR_sFirmwareImageVerifyDone  ,
  ZWIR_sScheduleUpdate           ,
  ZWIR_sStartUpdate              
} ZWIR_OTAU_StatusCode_t;
  
  
bool
  ZWIR_OTAU_Register ( uint16_t  localPort );
  
void
  ZWIR_OTAU_Status ( ZWIR_OTAU_StatusCode_t status );
  
  
  

#endif // __ZWIR45XX_OTAU__H__
