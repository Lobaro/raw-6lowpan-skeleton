#ifndef _NETMA2_H_
#define _NETMA2_H_

#include <ZWIR45xx-6LoWPAN.h>



// ***************************************************************************
/*! Set the port for the NetMA handler.
 *
 * \param port              Port
 */

void  
 ZWIR_NetMA_SetPort ( uint16_t  port );



// ***************************************************************************
/*! Hook called in case of an NetMA packet. Implement this to provide application
 *  specific handling of NetMA packets. Return true if the application handled the
 *  NetMA packet or false to perform default NetMA packet handling.
 *
 *  \param data  Pointer tor the NetMA packet.
 *  \param size  Size of the NetMA packet
 *  \return true if NetMA packet was handled or false if default handling is required.
 */
bool
 ZWIR_NetMA_ResponseHandler ( uint8_t const*  data,  uint16_t  size );


// ***************************************************************************
/*! Filter function for NetMA Packets to analyze the NetMA header.
 *
 * \param data              Pointer to NetMA packet
 * \param dataLength        Length of NetMA packet
 * \param dataOffset        Pointer to NetMA packet header length
 * \return                  1 drop packet, 0 continue processing
 */

bool
 ZWIR_NetMA_Filter ( uint8_t* data, uint16_t  size, uint8_t*  dataOffset );


/** *************************************************************************
 *  Send out a network discovery packet which all nodes must reply to. The
 *   replies are handled by the callback function passed as argument.
 *  \deprecated
 ** *************************************************************************/
void
  ZWIR_DiscoverNetwork ( ZWIR_DiscoveryCallback_t  callback,
                         uint8_t                   responseInterval );
 
 
#endif //_NETMA2_H_
