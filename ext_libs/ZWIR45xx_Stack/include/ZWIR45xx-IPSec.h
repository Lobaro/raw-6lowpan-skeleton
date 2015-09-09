/** **************************************************************************
 *
 *  Copyright (c) 2012 Zentrum Mikroelektronik Dresden AG
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
 *  \file   ZWIR451x-IPSec.h
 *  \brief  Type and function declarations for IPSec.
 *
 *****************************************************************************/


#ifndef __IPSEC_H__
#define __IPSEC_H__

#include <ZWIR45xx-6LoWPAN.h>


typedef enum {
  ZWIRSEC_eDroppedICMP        = 0x0500,
  ZWIRSEC_eDroppedPacket      = 0x0501,
  ZWIRSEC_eUnknownSPI         = 0x0502,
  ZWIRSEC_eReplayedPacket     = 0x0503,
  ZWIRSEC_eCorruptedPacket    = 0x0504  
} ZWIRSEC_ErrorCode_t;


/** ************************************************************************* 
 *  Enumeration of authentication algorithms
 ** *************************************************************************/
typedef
  enum __attribute__ (( packed )) {
    ZWIRSEC_authNull      = 0,
    ZWIRSEC_authAESXCBC96 = 5
  } ZWIRSEC_AuthenticationAlgorithm_t;

/** ************************************************************************* 
 *  Enumeration of encryption algorithms
 ** *************************************************************************/
typedef
  enum __attribute__ (( packed )) {
    ZWIRSEC_encNull     = 11,
    ZWIRSEC_encAESCTR   = 13,
    ZWIRSEC_encAESGCM16 = 20
  } ZWIRSEC_EncryptionAlgorithm_t;

/** ************************************************************************* 
 *  Enumeration of policy types
 ** *************************************************************************/
typedef
  enum __attribute__ (( packed )) {
    ZWIRSEC_ptOutputApply  = 0x11, /*!< outbound traffic - secure with IPsec */
    ZWIRSEC_ptOutputBypass = 0x12, /*!< outbound traffic - bypass */
    ZWIRSEC_ptOutputDrop   = 0x13, /*!< outbound traffic - drop */
    ZWIRSEC_ptInputApply   = 0x21, /*!< incoming trafffic - secure with IPsec */
    ZWIRSEC_ptInputBypass  = 0x22, /*!< incoming traffic - bypass */
    ZWIRSEC_ptInputDrop    = 0x23  /*!< incoming traffic - drop */
  } ZWIRSEC_PolicyType_t;

/** ************************************************************************* 
 *  Enumeration of protocols
 ** *************************************************************************/
typedef
  enum __attribute__ (( packed )) {
    ZWIR_protoAny    = 0, 
    ZWIR_protoTCP    = 6,  
    ZWIR_protoUDP    = 17,  
    ZWIR_protoICMPv6 = 58
  } ZWIR_Protocol_t;



/** ************************************************************************* 
 *  Encryption suite descriptor structure
 ** *************************************************************************/
typedef
  struct {
    ZWIRSEC_EncryptionAlgorithm_t  algo;
    uint8_t                        key  [ 16 ];
    uint8_t                        nonce [ 4 ];
  } ZWIRSEC_EncryptionSuite_t;
     
/** ************************************************************************* 
 *  Authentication suite descriptor structure
 ** *************************************************************************/
typedef
  struct {
    ZWIRSEC_AuthenticationAlgorithm_t  algo;
    uint8_t                            key [ 16 ];
  } ZWIRSEC_AuthenticationSuite_t;    

/** ************************************************************************* 
 *  Type for internal security association handler
 ** *************************************************************************/
typedef
  uint8_t  ZWIRSEC_SecurityAssociation_t;

/** ************************************************************************* 
 *  Add a security policy to the security policy database.
 *  \param type     determines the policy typ
 *  \param addr     this is the address the security policy should be applied to
 *  \param prefix   determines how many of the leading address bits are \
                    considered for the address computation
 *  \param proto    determines the protocol this security policy applies to
 *  \param lowPort  determines the lower bound of the valid port range
 *  \param highPort determines the upper bound of the valid port range
 *  \param sa       controls which security association is assigned to the \
                    policy. For automatic creation of policies using IKEv2 \
                    pass NULL.
 *  \return  The function returns a security policy handle in case of \
             success or 0xff otherwise
 ** *************************************************************************/
uint8_t 
  ZWIRSEC_AddSecurityPolicy ( ZWIRSEC_PolicyType_t            type, 
                              ZWIR_IPv6Address_t*             addr,
                              uint8_t                         prefix,
                              ZWIR_Protocol_t                 proto,
                              uint16_t                        lowPort,
                              uint16_t                        highPort,
                              ZWIRSEC_SecurityAssociation_t  sa );

/** ************************************************************************* 
 *  Remove a security policy from the security policy database.
 *  \param handle   The handle generated during creation of the policy to be \
                    deleted
 ** *************************************************************************/
void
  ZWIRSEC_RemoveSecurityPolicy ( uint8_t  sp );
  
  
/** ************************************************************************* 
 *  Add a security association to the security association database.
 *  \param spi           A unique security policy index to be selected by \
                         the application
 *  \param replayCheck   determines if replay checks are performed
 *  \param enc           determines the encryption suite
 *  \param auth          determines the authentication suite to be used
 *  \return  The function returns a security association handle in case of \
             success or NULL otherwise
 ** *************************************************************************/
ZWIRSEC_SecurityAssociation_t  
  ZWIRSEC_AddSecurityAssociation ( uint32_t                        spi, 
                                   uint8_t                         replayCheck,
                                   ZWIRSEC_EncryptionSuite_t*      enc,
                                   ZWIRSEC_AuthenticationSuite_t*  auth );

/** ************************************************************************* 
 *  Remove a security association from the security association database.
 *  \param sa  handle to the security association to be deleted
 ** *************************************************************************/
void  
  ZWIRSEC_RemoveSecurityAssociation ( ZWIRSEC_SecurityAssociation_t  sa );

#endif // __IPSEC_H__
