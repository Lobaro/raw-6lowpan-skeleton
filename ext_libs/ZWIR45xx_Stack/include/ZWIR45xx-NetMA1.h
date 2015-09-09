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
 *  \file   ZWIR45xx-6LoWPAN.h
 *  \brief  Define core functions and types for the ZWIR45xx 6LoWPAN API
 * 
 ** ***************************************************************************/


#ifndef __ZWIR45xx_NetMA1_H__
#define __ZWIR45xx_NetMA1_H__

#include <stdint.h>
#include <stdbool.h>

#include <ZWIR45xx-6LoWPAN.h>


/** *************************************************************************
 *  Function for defining the port used by ZMDI's NetMA protocol
 ** *************************************************************************/
void
  ZWIR_NetMA_SetPort ( uint16_t  port );

                              

/** *************************************************************************
 *  Type defining common flags to be used in NetMA packets
 ** *************************************************************************/
typedef
  enum { 
    ZWIR_NetMA_fDevice             = 0x04,
    ZWIR_NetMA_fBridge             = 0x08,
    ZWIR_NetMA_fQueryID            = 0x10,
    ZWIR_NetMA_fHopCountLimitation = 0x20
  } ZWIR_NetMA_Flags_t;

  
/** *************************************************************************
 *  Hop information type used with tracing functionality
 ** *************************************************************************/
typedef
  struct {
    ZWIR_PANAddress_t  address;
    int16_t            linkRSSI;
  } ZWIR_NetMA_HopInfo_t;


/** *************************************************************************
 *  Type defining function signature required by trace callback function.
 ** *************************************************************************/
typedef
  void ( * ZWIR_NetMA_TraceCallback_t ) ( uint8_t                hopCount,
                                          ZWIR_NetMA_HopInfo_t*  hopInfo );


/** *************************************************************************
 *  Function for examination of routes to remote hosts.
 *  \param  addr  The PAN address of the route target
 *  \param  from  The IPv6 address of the route source - use NULL if calling \ 
                  device is the source
 *  \param  callback  pointer to function to be called for results
 ** *************************************************************************/
void
  ZWIR_NetMA_Trace ( ZWIR_PANAddress_t*          addr,
                     ZWIR_IPv6Address_t*         from,
                     ZWIR_NetMA_TraceCallback_t  callback );


/** *************************************************************************
 *  Type defining enumeration of fields for remote parameter requests
 ** *************************************************************************/
typedef
  enum { 
    ZWIR_NetMA_rprfMACAddress      = 0x0100,
    ZWIR_NetMA_rprfFirmwareVersion = 0x0200,
    ZWIR_NetMA_rprfConfig          = 0x0400,
    ZWIR_NetMA_rprfIPv6Addresses   = 0x0800,
    ZWIR_NetMA_rprfTRXStatistics   = 0x1000
  } ZWIR_NetMA_RPRFields_t;

/** *************************************************************************
 *  Structure of remote parameter reply - MAC address field
 ** *************************************************************************/
typedef
  struct __attribute__ (( packed )) {
    uint16_t           panID;
    ZWIR_PANAddress_t  panAddress;
  } ZWIR_NetMA_RemoteMACAddr_t;
  
/** *************************************************************************
 *  Structure of remote parameter reply - IPv6 address field
 ** *************************************************************************/
typedef
  struct __attribute__ (( packed )) {
    uint8_t             count;
    ZWIR_IPv6Address_t  addresses [];
  } ZWIR_NetMA_RemoteIPv6Addr_t;
  
/** *************************************************************************
 *  Structure of remote parameter reply - Settings field
 ** *************************************************************************/
typedef
  struct __attribute__ (( packed )) {
    uint16_t  routeTimeout;
    uint16_t  routingTableSize;
    uint16_t  neighborReachableTime;
    uint8_t   neighborCacheSize;
    uint8_t   maxNetfloodHopCount;
    uint8_t   maxSocketCount;
    uint8_t   routeMaxFailCount;
    int8_t    routeRequestMinLinkRSSI;
    uint8_t   routeRequestMinLinkRSSIReduction;
    uint8_t   routeRequestAttempts;
    uint8_t   channel;
    uint8_t   power;
    uint8_t   modulation;
    uint8_t   doDuplicateAddressDetection;
    uint8_t   doRouterSolicitation;
    uint16_t  neighborRetransTime;
  } ZWIR_NetMA_RemoteConfig_t;
  
/** *************************************************************************
 *  Structure of remote parameter reply - Version field
 ** *************************************************************************/
typedef
  struct __attribute (( packed )) {
    uint32_t  vendorID;
    uint16_t  productID;
    uint8_t   firmwareMajorVersion;
    uint8_t   firmwareMinorVersion;
    uint16_t  firmwareVersionExtension;
    uint8_t   libraryMajorVersion;
    uint8_t   libraryMinorVersion;
    uint16_t  libraryVersionExtension;
  } ZWIR_NetMA_RemoteVersion_t;
  
  
/** *************************************************************************
 *  Structure of remote parameter reply - Status field
 ** *************************************************************************/
typedef
  struct {
    uint32_t  txBytes;
    uint32_t  txPackets;
    uint32_t  rxBytes;
    uint32_t  rxPackets;
    uint32_t  txFail;
    uint32_t  dutyCycle;
    uint8_t   channelUtilization 
  } ZWIR_NetMA_RemoteStatus_t;

/** *************************************************************************
 *  Structure being reported as result from a remote parameter request
 ** *************************************************************************/
typedef
  struct {
    ZWIR_NetMA_RemoteMACAddr_t*   macAddr;
    ZWIR_NetMA_RemoteIPv6Addr_t*  ipv6Addr;
    ZWIR_NetMA_RemoteConfig_t*    config;
    ZWIR_NetMA_RemoteVersion_t*   version;
    ZWIR_NetMA_RemoteStatus_t*    status;
  } ZWIR_NetMA_RemoteData_t;
  
/** *************************************************************************
 *  Type defining function signature to be used as callback for in remote \
      parameter requests.
 ** *************************************************************************/
typedef
  void ( *ZWIR_NetMA_RPRCallback_t ) ( ZWIR_NetMA_RPRFields_t          fields,
                                       ZWIR_NetMA_RemoteData_t const*  data );

// internal use only!
typedef
  struct {
    ZWIR_NetMA_RPRFields_t   fields;
    ZWIR_NetMA_Flags_t       flags;
    uint8_t                  responseInterval;
    uint8_t                  queryID;
    uint8_t                  hopCountLimit;
  } _ZWIR_RPROptArgs_t;

// internal use only
typedef
  struct {
    ZWIR_IPv6Address_t  address;
    uint8_t             responseInterval;
    uint8_t             queryID;
    uint8_t             hopCountLimit;
  } _ZWIR_DiscoveryOptArgs_t;

// internal use only
void
  _ZWIR_RemoteParameterRequest ( ZWIR_IPv6Address_t*       address,
                                 ZWIR_NetMA_RPRCallback_t  callback,
                                 _ZWIR_RPROptArgs_t        optionalArguments );
                                 
/** *************************************************************************
 *  Send out a network discovery packet which all nodes must reply to. The
 *   replies are handled by the callback function passed as argument.
 *  \deprecated
 ** *************************************************************************/
void
  ZWIR_DiscoverNetwork ( ZWIR_DiscoveryCallback_t  callback,
                         uint8_t                   responseInterval );
               
/** *************************************************************************
 *  Macro acting as function substitution, providing C++ like default \
     arguments for remote parameter requests.
 ** *************************************************************************/
#define  ZWIR_RemoteParameterRequest(A,C,...) _ZWIR_RemoteParameterRequest ( A, C, (_ZWIR_RPROptArgs_t){__VA_ARGS__} )


#endif // __ZWIR45xx_NetMA1_H__
