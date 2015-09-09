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


#ifndef __ZWIR45xx_6LOWPAN_H__
#define __ZWIR45xx_6LOWPAN_H__

#include <stdbool.h>
#include <stdint.h>



#define ZWIR_LIB_MAJOR_VERSION      1
#define ZWIR_LIB_MINOR_VERSION      10
#define ZWIR_LIB_VERSION_EXTENSION  8315

// ***************************************************************************
/*! Type definition for socket handle.
 */
typedef void*  ZWIR_SocketHandle_t;


// ***************************************************************************
/*! Type for IPv6 addresses.
 */
typedef union {
  uint8_t    u8 [ 16 ];
  uint16_t   u16 [ 8 ];
  uint32_t   u32 [ 4 ];
}  ZWIR_IPv6Address_t;

#define  IPV6_UNSPECIFIED  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
#define  IPV6_ALLNODES { 0xff, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }

#define  IPv6_ALLROUTERS   { 0xff, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 }
// this version of the macro is deprecated!
#define  IPv6_ALLROUTERS   { 0xff, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2 }

#define  IPV6_LINKLOCAL( A7, A6, A5, A4, A3, A2, A1, A0 ) \
  { 0xfe, 0x80, 0, 0, 0, 0, 0, 0, A7, A6, A5, A4, A3, A2, A1, A0 }
// this version of the macro is deprecated!
#define  IPv6_LINKLOCAL( A7, A6, A5, A4, A3, A2, A1, A0 ) \
  { 0xfe, 0x80, 0, 0, 0, 0, 0, 0, A7, A6, A5, A4, A3, A2, A1, A0 }

#define  printIPv6(IP) printf ( "%02x%02x:%02x%02x:%02x%02x"      \
                                ":%02x%02x:%02x%02x:%02x%02x"     \
                                ":%02x%02x:%02x%02x",               \
                                ( IP ) . u8 [  0 ], ( IP ) . u8 [  1 ], \
                                ( IP ) . u8 [  2 ], ( IP ) . u8 [  3 ], \
                                ( IP ) . u8 [  4 ], ( IP ) . u8 [  5 ], \
                                ( IP ) . u8 [  6 ], ( IP ) . u8 [  7 ], \
                                ( IP ) . u8 [  8 ], ( IP ) . u8 [  9 ], \
                                ( IP ) . u8 [ 10 ], ( IP ) . u8 [ 11 ], \
                                ( IP ) . u8 [ 12 ], ( IP ) . u8 [ 13 ], \
                                ( IP ) . u8 [ 14 ], ( IP ) . u8 [ 15 ] )

#define IPV6FRMT "%02x%02x:%02x%02x:%02x%02x:%02x%02x:" \
                 "%02x%02x:%02x%02x:%02x%02x:%02x%02x"
#define IPV6VALUE(IP) ( IP ) . u8 [  0 ], ( IP ) . u8 [  1 ], \
                      ( IP ) . u8 [  2 ], ( IP ) . u8 [  3 ], \
                      ( IP ) . u8 [  4 ], ( IP ) . u8 [  5 ], \
                      ( IP ) . u8 [  6 ], ( IP ) . u8 [  7 ], \
                      ( IP ) . u8 [  8 ], ( IP ) . u8 [  9 ], \
                      ( IP ) . u8 [ 10 ], ( IP ) . u8 [ 11 ], \
                      ( IP ) . u8 [ 12 ], ( IP ) . u8 [ 13 ], \
                      ( IP ) . u8 [ 14 ], ( IP ) . u8 [ 15 ]

#define PANFRMT "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:"
#define PANVALUE(PAN) ( PAN ) [ 0 ], ( PAN ) [ 1 ], \
                      ( PAN ) [ 2 ], ( PAN ) [ 3 ], \
                      ( PAN ) [ 4 ], ( PAN ) [ 5 ], \
                      ( PAN ) [ 6 ], ( PAN ) [ 7 ]


// ***************************************************************************
/*! Type for 8-byte PAN addresses.
 */
typedef
  uint8_t ZWIR_PANAddress_t [8];


// ***************************************************************************
/*! Type for 32-byte Routing table entry.
 */
typedef struct {
    uint8_t data[32];
  }ZWIR_RoutingTableEntry_t;  
  
// ***************************************************************************
/*! Enumeration of selectable physical radio channels.
 */
typedef
  enum {
    ZWIR_eu868      = 0,   /*!< EU channel ( 868.3 MHz ) */
    ZWIR_channel0   = 0,   /*!< EU channel ( 868.3 MHz ) */
    ZWIR_us906      = 1,   /*!< US channel ( 906 MHz ) */
    ZWIR_channel1   = 1,   /*!< US channel ( 906 MHz ) */
    ZWIR_us908      = 2,   /*!< US channel ( 908 MHz ) */
    ZWIR_channel2   = 2,   /*!< US channel ( 908 MHz ) */
    ZWIR_us910      = 3,   /*!< US channel ( 910 MHz ) */
    ZWIR_channel3   = 3,   /*!< US channel ( 910 MHz ) */
    ZWIR_us912      = 4,   /*!< US channel ( 912 MHz ) */
    ZWIR_channel4   = 4,   /*!< US channel ( 912 MHz ) */
    ZWIR_us914      = 5,   /*!< US channel ( 914 MHz ) */
    ZWIR_channel5   = 5,   /*!< US channel ( 914 MHz ) */
    ZWIR_us916      = 6,   /*!< US channel ( 916 MHz ) */
    ZWIR_channel6   = 6,   /*!< US channel ( 916 MHz ) */
    ZWIR_us918      = 7,   /*!< US channel ( 918 MHz ) */
    ZWIR_channel7   = 7,   /*!< US channel ( 918 MHz ) */
    ZWIR_us920      = 8,   /*!< US channel ( 920 MHz ) */
    ZWIR_channel8   = 8,   /*!< US channel ( 920 MHz ) */
    ZWIR_us922      = 9,   /*!< US channel ( 922 MHz ) */
    ZWIR_channel9   = 9,   /*!< US channel ( 922 MHz ) */
    ZWIR_us924      = 10,  /*!< US channel ( 924 MHz ) */
    ZWIR_channel10  = 10,  /*!< US channel ( 924 MHz ) */
    ZWIR_eu865      = 100, /*!< EU channel ( 865.3 MHz ) */
    ZWIR_channel100 = 100, /*!< EU channel ( 865.3 MHz ) */
    ZWIR_eu866      = 101, /*!< EU channel ( 866.3 MHz ) */
    ZWIR_channel101 = 101, /*!< EU channel ( 866.3 MHz ) */
    ZWIR_eu867      = 102, /*!< EU channel ( 867.3 MHz ) */
    ZWIR_channel102 = 102, /*!< EU channel ( 867.3 MHz ) */
    ZWIR_il867      = 20,  /*!< IL channel ( 916 MHz ) */
    ZWIR_channel20  = 20,  /*!< IL channel ( 916 MHz ) */
  } ZWIR_RadioChannel_t;



typedef
  enum {
    ZWIR_mBPSK = 0,  /*!< BPSK modulation */
    ZWIR_mQPSK = 1,  /*!< QPSK modulation */
  } ZWIR_Modulation_t;


// ***************************************************************************
/*! Enumeration of selectable PA control configurations.
 */
typedef
  enum {
    ZWIR_paOff = 0x00,  /*!< PA control off */
    ZWIR_pa2us = 0x10,  /*!< Pa control on with 2us lead time */
    ZWIR_pa4us = 0x11,  /*!< Pa control on with 4us lead time */
    ZWIR_pa6us = 0x12,  /*!< Pa control on with 6us lead time */
    ZWIR_pa8us = 0x13,  /*!< Pa control on with 8us lead time */
  } ZWIR_PAControl_t;

// ***************************************************************************
/*! Enumeration of available processor clock frequencies
 */
typedef
  enum {
    ZWIR_mcu8MHz  = 0,            /*!< 8MHz */
    ZWIR_mcu16MHz = 1,            /*!< 16MHz */
    ZWIR_mcu32MHz = 2,            /*!< 32MHz */
    ZWIR_mcu64MHz = 3,            /*!< 64MHz */
    ZWIR_mcu8MHzLowPower = 4,     /*!< 8MHz with low power optimization */
    ZWIR_mcuUserFrequency = 0xff  /*!< User Frequency settings */
  } ZWIR_MCUFrequency_t;




// ***************************************************************************
/*!  Enumeration of operating modes.
 */
typedef
  enum {
    ZWIR_omNormal  = 0,  /*!< RadioNode operating mode */
    ZWIR_omGateway = 1,  /*!< Gateway operating mode */
    ZWIR_omSniffer = 2   /*!< Sniffer operating mode */
  } ZWIR_OperatingMode_t;


// ***************************************************************************
/*!  Configurable system parameter enumeration.
 */
typedef
  enum {
    ZWIR_spRoutingTableSize,
    ZWIR_spNeighborCacheSize,
    ZWIR_spMaxSocketCount,
    ZWIR_spRouteTimeout,
    ZWIR_spNeighborReachableTime,
    ZWIR_spMaxHopCount,
    ZWIR_spRouteMaxFailCount,
    ZWIR_spRouteRequestMinLinkRSSI,
    ZWIR_spRouteRequestMinLinkRSSIReduction,
    ZWIR_spDoDuplicateAddressDetection,
    ZWIR_spDoRouterSolicitation,
    ZWIR_spRouteRequestAttempts,
    ZWIR_spHeaderCompressionContext1,
    ZWIR_spHeaderCompressionContext2,
    ZWIR_spHeaderCompressionContext3,
    ZWIR_spNeighborRetransTime,
    ZWIR_spDoAddressAutoConfiguration,
    ZWIR_spMobileSleepyDeviceRouting,
    ZWIR_spBadRSSIAcceptCount
  } ZWIR_SystemParameter_t;


// ***************************************************************************
/*!  Type of an UDP callback function
 */
typedef
  void ( * ZWIR_RadioReceiveCallback_t ) ( uint8_t*  data,
                                           uint16_t  size );

// ***************************************************************************
/*!  Type of a timer callback function.
 */
typedef
  void ( * ZWIR_TimeoutCallback_t ) ( void*  data );

// ***************************************************************************
/*!  Type of an application event handler.
 */
typedef
  void ( * ZWIR_AppEventHandler_t ) ( void );

// ***************************************************************************
/*!  Type of a callback function which is called if network discovery
 *    responses are received.
 */
typedef
  void ( * ZWIR_DiscoveryCallback_t ) ( uint8_t              hopCount,
                                        int8_t               rssi,
                                        uint8_t              addrCount,
                                        ZWIR_IPv6Address_t*  addresses );

// ***************************************************************************
/*!  Data type containing the library version information
 */
typedef
  struct {
    int8_t  majorRevision;
    int8_t  minorRevision;
    union {
      int16_t svnRevision;
      struct {
        int16_t  releaseCandidate : 2;
        int16_t  versionExtension : 14;
      };
    };
  } ZWIR_RevisionInfo_t;


typedef
  enum {
    ZWIR_aatNone  = 0x00,
    ZWIR_aatEUI64 = 0x01,
    ZWIR_aatEUI48 = 0x02,
    ZWIR_aatAny   = 0x03
  } ZWIR_AlternativeAddressType_t;

#ifdef __cplusplus
extern "C" {
#endif


// ***************************************************************************
/*! Registers a callback to be called for processing of application events.
 *   When NULL is provided with the handler argument, the event handler is
 *   for the specified event is unregistered.
 *  \param enventId  ID of the event the handler should be registered for
 *  \param handler   Pointer to the function to be called
 */
void
  ZWIR_RegisterAppEventHandler ( uint8_t                 eventId,
                                 ZWIR_AppEventHandler_t  handler );


// ***************************************************************************
/*! Trigger an application event.
 *   The operating system will call the appropriate event handler (to be
 *   registered with ZWIR_RegisterAppEventHandler) after processing of all
 *   higher priority events.
 *  \param enventId  ID of the event to be triggered (0 to 4)
 */
void
  ZWIR_TriggerAppEvent ( uint8_t  eventId );

// ***************************************************************************
/*! Get RSSI value of the last received Frame
 *  \return  RSSI value of the last received packet
 */
int32_t
  ZWIR_GetLastRSSI ( void );

// ***************************************************************************
/*!  Data type containing the transceiver statistic
 */
typedef
  struct {
    uint32_t  txBytes;
    uint32_t  txPackets;
    uint32_t  rxBytes;
    uint32_t  rxPackets;
    uint32_t  txFail;
    uint32_t  dutyCycle;
    uint8_t   channelUtilization;
    uint32_t  txCSMAErrorCount;
    uint32_t  txNoACKCount;
  } ZWIR_TRXStatistic_t;


// ***************************************************************************
/*! Returns transceiver statistic
 */
ZWIR_TRXStatistic_t
  ZWIR_GetTRXStatistic ( void );


// ***************************************************************************
/*! Resets transceiver statistic
 */
void
  ZWIR_ResetTRXStatistic ( void );


// ***************************************************************************
/*! Sends a IP without UDP and IP, but with 6loWPAN header processing
 *
 * \param  dstAddrIPv6 destination address of the packet
 * \param  packet packet to be sent
 * \param  packetLength  byte size of the packet ( including headers )
 * \param  1 if packet was sent successfully, 0 otherwise
 */
bool
  ZWIR_Send6LoWPAN ( ZWIR_PANAddress_t*  dstAddr,
                     uint8_t*            packet,
                     uint16_t            packetLength );


// ***************************************************************************
/*! Returns a random number
 *
 *  \return  random number
 */
int32_t
  ZWIR_Rand ( void );


// ***************************************************************************
/*! Initializes the random number generator and returns a random number
 *
 * \param   seed  Seed for the random number generator
 * \return  random number
 */
int32_t
  ZWIR_SRand ( int32_t  seed );


// ***************************************************************************
/*! Enumeration of available RTC sources
 */
typedef
  enum {
    ZWIR_rIntern = 0,
    ZWIR_rExtern = 1
  } ZWIR_RTCSource_t;


// ***************************************************************************
/*! Sets the RTC source
 *
 * \param   source  RTC source to be selected
 * \return  result:  0 selection failed
 *                   1 selected successfully
 *                   2 source was selected - no changes made
 */
uint8_t
  ZWIR_SelectRTCSource ( ZWIR_RTCSource_t source );


// ***************************************************************************
/*! Returns the current RTC counter value
 *
 * \return  current RTC counter value
 */
uint32_t
  ZWIR_GetRTC ( void );


// ***************************************************************************
/*! Sets the current RTC counter value
 *
 * \param   value  RTC value to be set.
 */
void
  ZWIR_SetRTC ( uint32_t value );


// ***************************************************************************
/*! Enumeration of available power down modes
 */
typedef
  enum {
    ZWIR_pSleep,
    ZWIR_pSleepAfterActivities,
    ZWIR_pStop,
    ZWIR_pStopAfterActivities,
    ZWIR_pStandby,
    ZWIR_pStandbyAfterActivities,
    ZWIR_pCallback,
    ZWIR_pCallbackAfterActivities
  } ZWIR_PowerDownState_t;


// ***************************************************************************
/*! Abort delayed power down modes.
 *  If ZWIR_PowerDown was called with a delayed power down mode and the power
 *   down state was not entered, it will not enter in future after a call to
 *   this function.
 */
void
  ZWIR_AbortPowerDown ( void );


// ***************************************************************************
/*! Enter the given power down mode.
 *
 * \param  powerDownState Power down state to be entered
 * \param  sleepTime      Time units to remain in power down state
 */
void
  ZWIR_PowerDown ( ZWIR_PowerDownState_t  powerDownMode ,
                   uint32_t               sleepTime );


// ***************************************************************************
/*! Set the wakeup source for Sleep, Stop and Standby mode
 *
 * \param  powerDownState power down mode
 * \param  wakeupSource:
 *            Sleep mode:   interrupt mask
 *            Stop mode:    event mask
 *            Standby mode: wakeup pin (0x02) and/or RTC alarm (0x01)
 */
void
  ZWIR_SetWakeupSource ( ZWIR_PowerDownState_t  powerDownMode ,
                         uint64_t               wakeupSource );


// ***************************************************************************
/*! Enumeration of available reset reasons
 */
typedef
  enum __attribute__ (( packed )){
    ZWIR_rPowerOnReset             = 0,
    ZWIR_rStandbyReset             = 1,
    ZWIR_rIndependentWatchdogReset = 2,
    ZWIR_rSoftwareReset            = 3,
    ZWIR_rPinReset                 = 4,
    ZWIR_rWindowWatchdogReset      = 5,
    ZWIR_rLowPowerReset            = 6,
    ZWIR_rUserNetworkReset         = 7,
    ZWIR_rInternalNetworkReset     = 8
  } ZWIR_ResetReason_t;


// ***************************************************************************
/*! Function to switch the transceiver on
 */
void
  ZWIR_TransceiverOn ( void );

// ***************************************************************************
/*! Function to switch the transceiver off
 */
void
  ZWIR_TransceiverOff ( void );


// ***************************************************************************
/*! Controls the clock frequency of the core
 *
 *  \param  mcuFrequency - clock frequency
 */
void
  ZWIR_SetFrequency ( ZWIR_MCUFrequency_t  mcuFrequency );

// ***************************************************************************
/*! Start the callback timer.
 *This function initializes the callback timer.
 *
 *\param timeout  specifies the time to call callback, relative to now
 *\param callback  pointer to the function to be called
 *\param value  pointer to a value which is passed to the timeout handler
 */
void
  ZWIR_StartCallbackTimer ( uint32_t                timeout,
                            ZWIR_TimeoutCallback_t  callback,
                            void*                   data,
                            bool                    continous );


// ***************************************************************************
/*! Stops the callback timer.
 */
void
  ZWIR_StopCallbackTimer ( );


// ***************************************************************************
/*! Set the IP6-Address of the module
 *
 *\param address  Pointer to the IPv6 address to be set for the device
 */
bool
  ZWIR_SetIPv6Address ( ZWIR_IPv6Address_t*  address );


// ***************************************************************************
/*!  Obtain the IPv6 addresses assigned to the interface
 *
 *  \param buf      Pointer to memory IP addresses should be stored in
 *  \param bufSize  Capacity of buf (number of IPv6 addresses to be stored at max)
 *  \return         number of IPv6 addresses stored in buf
 */
uint8_t
  ZWIR_GetIPv6Addresses ( ZWIR_IPv6Address_t*  buf,
                          uint8_t              bufSize );


// ***************************************************************************
/*! Set 64 bit PAN address of the module
 *
 *\param address  Pointer to the PAN address to be set for the device
 */
void
  ZWIR_SetPANAddress ( ZWIR_PANAddress_t*  panAddress );


//*****************************************************************************
/*! Get 64 bit PAN address of module.
 *
 *\return  Pointer to the PAN address of the device
 */
ZWIR_PANAddress_t*
  ZWIR_GetPANAddress ( void );

//*****************************************************************************
/*! Get 64 bit PAN address of module.
 *
 *\return  Pointer to the PAN address of the source device
 */
ZWIR_PANAddress_t*
  ZWIR_GetSourcePANAddress ( void );

//*****************************************************************************
/*! Get 64 bit PAN address of module.
 *
 *\return  Pointer to the PAN address of the destination device
 */
ZWIR_PANAddress_t*
  ZWIR_GetDestinationPANAddress ( void );



// ***************************************************************************
/*! Set 16 bit PAN id of module.
 *
 *\param panId  PAN Id of the module
 */
void
  ZWIR_SetPANId ( uint16_t  panId );


// ***************************************************************************
/*! Get 16 bit PAN id of module.
 *
 */
uint16_t
  ZWIR_GetPANId ( void );


// ***************************************************************************
/*! Set 16 bit PAN id of module for outgoing packets.
 *
 *\param panId  PAN Id of the module
 */
void
  ZWIR_SetDestinationPANId ( uint16_t panID );

// ***************************************************************************
/*! Reset 16 bit PAN id of module for outgoing packets. TX PAN id = PAN id
 *
 */
void
  ZWIR_ResetDestinationPANId ( );


// ***************************************************************************
/*! Switches the physical radio channel of the module.
 *
 * \param radioChannel  Radio channel to be selected
 */
void
  ZWIR_SetChannel ( ZWIR_RadioChannel_t  radioChannel );


// ***************************************************************************
/*! Returns the selected physical radio channel of the module.
 *
 * \param radioChannel  Radio channel to be selected
 */
ZWIR_RadioChannel_t
  ZWIR_GetChannel (  );


// ***************************************************************************
/*! Changes the power amplifier output power.
 *
 * \param power  Power level to be selected
 */
void
  ZWIR_SetTransmitPower ( int  power );


// ***************************************************************************
/*! Returns the selected power amplifier output power.
 *
 * \param power  Power level to be selected
 */
int
  ZWIR_GetTransmitPower ( );


// ***************************************************************************
/*! Changes the modulation of the transceiver.
 *
 * \param modulation  Modulation to be selected
 */
void
  ZWIR_SetModulation ( ZWIR_Modulation_t  modulation );


// ***************************************************************************
/*! Returns the active modulation scheme
 *
 * \param modulation  Modulation to be selected
 */
ZWIR_Modulation_t
  ZWIR_GetModulation ( );


// ***************************************************************************
/*! Changes the PA control of the transceiver.
 *
 * \param pacontrol  PA control to be selected
 */
void
  ZWIR_SetPAControl ( ZWIR_PAControl_t  pacontrol );


// ***************************************************************************
/*! Open a socket for network communication.
 *
 *  \param   remoteAddress  Remote IPv6 address
 *  \param   remotePort  Remote Port
 *  \param   localPort   Local Port
 *  \param   recvCallbackFunction to be called upon reception of data
 *  \return  Non zero value on success, 0 otherwise.
 */
ZWIR_SocketHandle_t
  ZWIR_OpenSocket ( ZWIR_IPv6Address_t*          remoteAddress,
                    uint16_t                     remotePort,
                    uint16_t                     localPort,
                    ZWIR_RadioReceiveCallback_t  recvCallback );


// ***************************************************************************
/*! Closes an open socket.
 *
 * \param portHandle  Handle socket to be closed
 */
void
  ZWIR_CloseSocket ( ZWIR_SocketHandle_t  portHandle );


// ***************************************************************************
/*! Send data as UDP packet.
 *
 * \param socketHandle  Handle of socket to be used for communication
 * \param data          Pointer to data to be sent
 * \param dataLength    Length of data to be sent
 * \return              1 in case of success, 0 otherwise
 */
bool
  ZWIR_SendUDP ( ZWIR_SocketHandle_t  socketHandle,
                 uint8_t*             data,
                 uint16_t             dataLength );


// ***************************************************************************
/*! Send data as UDP packet without opening a socket.
 *
 * \param data              Pointer to data to be sent
 * \param dataLength        Length of data to be sent
 * \param remoteIP6Address  Destination Address
 * \param toPort            Destination Port
 * \return                  1 in case of success, 0 otherwise
 */
bool
  ZWIR_SendUDP2 ( uint8_t*             data,
                  uint16_t             dataLength,
                  ZWIR_IPv6Address_t*  remoteIP6Address,
                  uint16_t             toPort );


// ***************************************************************************
/*! Get the source address of a received packet
 *
 *  \return  A pointer to the packet originators IPv6 address
 */
ZWIR_IPv6Address_t*
  ZWIR_GetPacketSenderAddress ( void );


// ***************************************************************************
/*! Get the destination address of a received packet
 *
 *  \return  A pointer to the packet destination IPv6 address
 */
ZWIR_IPv6Address_t*
  ZWIR_GetPacketDestinationAddress ( void );


// ***************************************************************************
/*! Get the source port of a received packet
 *
 *  \return  Source port of the latest received UDP packet
 */
uint16_t
  ZWIR_GetPacketSenderPort ( void );


// ***************************************************************************
/*! Get the socket the last packet was received on
 *
 *  \return  Socket on which the last UDP packet has been received
 */
ZWIR_SocketHandle_t
  ZWIR_GetPacketRXSocket ( void );



// ***************************************************************************
/*! Get the hop count the last packet has taken
 *
 *  \return  Number of hops taken
 */
uint8_t
  ZWIR_GetPacketHopCount ( void );



// ***************************************************************************
/*!  Disable or enable rebroadcasting of broadcast packets to realize a local
 *   Broadcast
 *
 *\param  value  enable or disable locale broadcast
 *
 */

void
  ZWIR_LocalBroadcast ( uint8_t value );



// ***************************************************************************
/*!  Disable or enable sending broadcast packets that will be rebroadcasted
 *   by nodes with existing multihop routes (repeater) only.
 *
 *\param  value  enable or disable prefering existing repeater
 *
 */

void
  ZWIR_MulticastPreferExistingRepeater ( uint8_t value );



// ***************************************************************************
/*! Return 6loWPAN library revision number
 *
 *  \return ZMD software revision number. Required for each kind of
 *   support request!
 */
ZWIR_RevisionInfo_t
  ZWIR_GetRevision ( void );



// ***************************************************************************
/*!  Set the operating mode of the device.
 *
 *\param  mode  Operating mode of the node.
 *
 *\note This function MUST be called from ZWIR_BootInit! Calling it from
 *  any other place will cause a fatal system error.
 */
void
  ZWIR_SetOperatingMode ( ZWIR_OperatingMode_t         mode,
                          ZWIR_RadioReceiveCallback_t  radioReceiveCallback );


// ***************************************************************************
/*!  Set the transceiver in promiscuous mode.
 *
 *\param  enable  Enable or disable promiscuous mode.
 *
 */
void
  ZWIR_SetPromiscuousMode ( bool  enable );


// ***************************************************************************
/*! Perform full system reset. Configured parameters are reset to the default values.
 */
void
  ZWIR_Reset ( void );

// ***************************************************************************
/*! Performs reset of the network stack. Configured parameters remain unchanged
 */
void
  ZWIR_ResetNetwork ( void );


// ***************************************************************************
/*! Enumeration of error codes possibly generated by the core libraries
 */
typedef
  enum {
    ZWIR_eDADFailed=0x0100,
    ZWIR_eProgExit,
    ZWIR_eReadMACFailed,
    ZWIR_eMemoryExhaustion,
    ZWIR_eHostUnreachable,
    ZWIR_eExtClockPowerDown,
    ZWIR_eRouteFailed
  } ZWIR_ErrorCode_t;


// ***************************************************************************
/*! Allows debugging while controller is in a low power mode
 */
void
  ZWIR_EnableLowPowerDebug (void);

// ***************************************************************************
/*! Hook called in case of an error. Implement this to provide application
 *  specific handling of errors. Return true if the application handled the
 *  error or false to perform default error handling.
 *
 *  \param code  Code of the error causing this call.
 *  \return true if error was handled or false if default handling is required.
 */
bool
  ZWIR_Error ( int  code );

// ***************************************************************************
/*! Declaration of the hook called in in a 10 ms interval.
 *   Implement this in the application code to do something every 10 ms.
 *  \note It is not guaranteed, that each intended instance of this function
 *     is called.
 *  \note The application must not rely on the execution interval of 10ms.
 *     the actual interval may vary.
 */
void
  ZWIR_Main10ms ( void );
// ***************************************************************************
/*! Declaration of the hook called in in a 100 ms interval.
 *   Implement this in the application code to do something every 100 ms.
 *  \note It is not guaranteed, that each intended instance of this function
 *     is called.
 *  \note The application must not rely on the execution interval of 10ms.
 *     the actual interval may vary.
 */
void
  ZWIR_Main100ms ( void );
// ***************************************************************************
/*! Declaration of the hook called in in a 1 s interval.
 *   Implement this in the application code to do something every 1 s.
 *  \note It is not guaranteed, that each intended instance of this function
 *     is called.
 *  \note The application must not rely on the execution interval of 10ms.
 *     the actual interval may vary.
 */
void
  ZWIR_Main1000ms ( void );

// ***************************************************************************
/*! This function is used to configure stack parameters.
 *  \param  parameter  determines which parameter is changed
 *  \param  value      determines the value of the parameter
 */
int32_t
  ZWIR_SetParameter ( ZWIR_SystemParameter_t  parameter,
                      int64_t                 value );

// ***************************************************************************
/*! This function is used to query stack parameters.
 *  \param  parameter  determines which parameter is changed
 *  \return value of the stack parameter requested
 */
int64_t
  ZWIR_GetParameter ( ZWIR_SystemParameter_t  parameter );

// ***************************************************************************
/*! Allocate memory for alternative MAC addresses.
 *  \param  size  determines the maximum number of alternative addresses \
                  supported by the device
 *  \return The function returns 1 if the address list was created successfully \
            or 0 otherwise
 */
bool
  ZWIR_CreateAlternativeAddressList ( uint16_t size );

// ***************************************************************************
/*! Add an alternative MAC addresses.
 *  \param  address  The address to be added to the alternative address list
 *  \param  type     Determines the type of the address
 *  \return The function returns true if the address was added successfully \
            or 0 otherwise
 */
bool
  ZWIR_AddAlternativeAddress ( ZWIR_PANAddress_t*            address,
                               ZWIR_AlternativeAddressType_t type );

// ***************************************************************************
/*! Determines if the requested address is in the alternative address list.
 *  \param  address  The address to be checked
 *  \param  type     The required address type
 *  \return The function returns true if the address was in the alternative \
            address list or 0 otherwise
 */
ZWIR_AlternativeAddressType_t
  ZWIR_IsAlternativeAddress ( ZWIR_PANAddress_t*            address,
                              ZWIR_AlternativeAddressType_t type );




// ***************************************************************************
/*! Returns the last IPv6 address for which address resolution has failed.
 *  \return IPv6 address for which address resolution has failed.
 */
ZWIR_IPv6Address_t*
  ZWIR_GetFailingAddress ( void );


// ***************************************************************************
/*! Returns the routing and neighbour table entry for a given IPv6-Address
 *  \param  IP6Address Specifies the IPv6-Address.
 *  \return Returns a routing and neighbour table entry.
 */
ZWIR_RoutingTableEntry_t
  ZWIR_GetRoutingTableEntry ( ZWIR_IPv6Address_t*	_IP6Address );

  
// ***************************************************************************
/*! Add the given entry to the routing and neighbour table.
 *  \param  routingTableEntry Entry to be added
 *  \return Returns a routing and neighbour table entry.
 */  
void
  ZWIR_RestoreRoutingTableEntry ( ZWIR_RoutingTableEntry_t*	routingTableEntry );  
  
  
// ***************************************************************************
/*! Sets the status of the external clock source.
 *  \param  enabled  Determines whether the external clock is used or not.
 *  \return Returns true if the clock source has been switched successfully.
 */
bool
  ZWIR_ExternalClockEnable ( bool  enabled );

// ***************************************************************************
/*! Hook function that must be implemented for multicast enabled nodes, in order \
     to verify whether the node is part of the specified multicast group or not.
 *  \param  addr    The mutlicast address to be checked.
 *  \return Return true if the node is part of the multicast goup or false otherwise.
 */
bool
  ZWIR_CheckMulticastGroup ( ZWIR_IPv6Address_t const*  addr );


// ***************************************************************************
/*! Hook function which is called during hardware initialization after reset.
 *  \param  reason  Determines the reset-reason for which the function is called.
 */
void
  ZWIR_AppInitHardware ( ZWIR_ResetReason_t   reason );


// ***************************************************************************
/*! Hook function which is called during network initialization after reset.
 *  \param  reason  Determines the reset-reason for which the function is called.
 */
void
  ZWIR_AppInitNetwork ( ZWIR_ResetReason_t   reason );


// ***************************************************************************
/*! Hook function which is called after completion of network initialization.
 *  \param  reason  Determines the reset-reason for which the function is called.
 */
void
  ZWIR_AppInitNetworkDone ( ZWIR_ResetReason_t   reason );



// ***************************************************************************
/*! This type defines the signature that is required by functions intended to be\
     used as hook for processing of packets in gateway mode.
 */
typedef
  uint8_t ( *ZWIR_GatewayOutputFunction_t ) ( uint8_t*            data,
                                              uint16_t            size,
                                              ZWIR_PANAddress_t*  address );


// ***************************************************************************
/*! Use this function to specify a hook function that is called for sending \
     packets in gateway mode
 *  \param  f  Pointer to the output function to be used as output function. \
     NULL resets to default.
 */
void
  ZWIR_GatewaySetOutputFunction ( ZWIR_GatewayOutputFunction_t  f );


// ***************************************************************************
/*! Call this function in gateway mode to enable transport layer protocol \
     processing in gateway mode.
 *  \param  data    Raw data of network layer packet
 *  \param  size    Number of data bytes
 *  \return Returns true if packet has been processed or false otherwise.
 */
bool
  ZWIR_GatewayProcessPacket ( uint8_t*  data,
                              uint16_t  size );

// ***************************************************************************
/*! Call this function in gateway mode to prepare the stack for processing
     of packets coming in not from the PAN side of the network.
 */
void
  ZWIR_GatewayPrepareSecondaryInput ( void );

// ***************************************************************************
/*! Type defining the callback format for duty cycle warnings
 */
typedef  void ( * ZWIR_DutyCycleCallback_t ) ( uint32_t );

// ***************************************************************************
/*! This function defines a duty cycle threshold for the transmit duty cycle
     whose exceedance triggers a call to the function callback function
     specified with ZWIR_SetDutyCycleWarning.
     If percentage is set to 0 or callback is set to NULL, no warning will be
     triggered. Otherwise callback will be called once per second as long as
     the 1h duty cycle exceeds the valued defined with the percentage argument.

    \param percentage  duty cycle threshold for triggering duty cycle warings
                       (the value must be specified as 1/1000 percent, thus
                       percentage=1000 sets a threshold of 1%)
    \param callback    This is the function that should be called when the
                       duty cycle threshold is exceeded.
 */
void
  ZWIR_SetDutyCycleWarning ( uint32_t                             percentage,
                             ZWIR_DutyCycleCallback_t callback );

// ***************************************************************************
/*! Use this function to obtain the textual representation of the FCCID. 
 *  \return NULL terminated string, containing the FCCID.
*/
char const*
  ZWIR_GetFCCID ( void );
                                         

typedef  bool  ( *ZWIR_ActivityCheckCallback_t ) ( void );

void
  ZWIR_SetActivityCheckCallback ( ZWIR_ActivityCheckCallback_t  callback );

typedef enum { ZWIR_neAppReceive,
               ZWIR_neAppTransmit,
               ZWIR_neIPv6Receive,
               ZWIR_neIPv6Transmit,
               ZWIR_neMACReceive,
               ZWIR_neMACTransmit }  ZWIR_NetEvent_t;

void
  ZWIR_NetEventCallback ( ZWIR_NetEvent_t event );

ZWIR_PANAddress_t*
  ZWIR_NeighborCacheLookup ( ZWIR_IPv6Address_t*  ipv6Address );

void
  ZWIR_NeighborCacheDefine ( ZWIR_IPv6Address_t*  ipv6Address,  
                             ZWIR_PANAddress_t*   panAddress);

                             
void
  ZWIR_Flash_Unlock ( );
void
  ZWIR_Flash_Lock ( );
void const* const
  ZWIR_Flash_GetStart ( );
uint32_t
  ZWIR_Flash_GetSize ( );
bool
  ZWIR_Flash_PageErase ( void const* const  addr );
bool
  ZWIR_Flash_Write ( void const* const  dst, void const* const  src, uint32_t const  size );
  
#ifdef __cplusplus
}
#endif


// these macros are for backward compatibility with older API versions
#define ZWIR_Sleep(x) ZWIR_PowerDown ( ZWIR_pSleepAfterActivities, x )
#define ZWIR_Standby(x) ZWIR_PowerDown ( ZWIR_pStandby, x )

static __attribute__ (( deprecated )) ZWIR_AlternativeAddressType_t const  ZWIR_anyAddr = ZWIR_aatAny;
static __attribute__ (( deprecated )) ZWIR_AlternativeAddressType_t const  ZWIR_panAddr = ZWIR_aatEUI64;
static __attribute__ (( deprecated )) ZWIR_AlternativeAddressType_t const  ZWIR_ethAddr = ZWIR_aatEUI48;


/**
These declarations replace the old
  typedef
    enum {
      ZWIR_tp5dBm	  =   5,
      ZWIR_tp0dBm   =   0,
      ZWIR_tpM10dBm = -10,
      ZWIR_tpM16dBm = -16,
      ZWIR_tpM26dBm = -26,
    } ZWIR_TransmitPower_t;
*/
static __attribute__ (( deprecated )) int const ZWIR_tp5dBm	  =   5;  /*!<   5 dBm transmit power; Note: not available at ZWIR45x1 */
static __attribute__ (( deprecated )) int const ZWIR_tp0dBm   =   0;  /*!<   0 dBm transmit power */
static __attribute__ (( deprecated )) int const ZWIR_tpM10dBm = -10;  /*!< -10 dBm transmit power */
static __attribute__ (( deprecated )) int const ZWIR_tpM16dBm = -16;  /*!< -16 dBm transmit power */
static __attribute__ (( deprecated )) int const ZWIR_tpM26dBm = -26;  /*!< -26 dBm transmit power */

#endif
