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
 *  \file   ZWIR45xx-IKEv2.h
 *  \brief  Function declaration for Internet Key Exchange version 2 (IKEv2).
 *
 *****************************************************************************/


#ifndef __IKEV2_H__
#define __IKEV2_H__

#include <ZWIR45xx-6LoWPAN.h>

/** *************************************************************************
 *  Add a new authentication entry for a remote device
 *  \param addr    Remote address (prefix) this entry applies to
 *  \param prefix  Number of leading bits considered for address matching
 *  \param id      Unique identifier string
 *  \param idLen   Length of the identifier string
 *  \param psk     Pre-shared key used for authentication
 *  \return        The function returns true on success or false otherwise.
 ** *************************************************************************/
bool
  ZWIRSEC_AddIKEAuthenticationEntry ( ZWIR_IPv6Address_t*  remote_adr,
                                      uint8_t                prefix,
                                      uint8_t*               id,
                                      uint8_t                id_len,
                                      uint8_t*               psk );

bool __attribute__ (( deprecated ))
  ZWIRSEC_AddIkeAuthenticationEntry ( ZWIR_IPv6Address_t*  remote_adr,
                                      uint8_t                prefix,
                                      uint8_t*               id,
                                      uint8_t                id_len,
                                      uint8_t*               psk );


#endif  // __IKEV2_H__
