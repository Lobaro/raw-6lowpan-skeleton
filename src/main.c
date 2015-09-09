/** **************************************************************************
 *  Copyright (c) 2015 Lobaro UG (haftungsbeschränkt)
 *  T.Rohde
 *
 *  ### Lobaro.com 6LoWPAN RAW SDK Skeleton Project ###
 *
 *  (!)Please note(!):
 *  This SDK is intended for experienced embedded programmers!
 *  Please visit "http://www.lobaro.com" for complete solutions based on the
 *  "constrained application protocol" (CoAP). These solutions are much easier
 *  to use because minimal to zero knowledge of embedded device programming is needed.
 *
 *  Firmware Description:
 *  The Firmware opens a udp6 socket on local port #5684 and prints any received
 *  data on UART1/USB Port of "LOBARO IPV6 UNIVERSAL BOX" @115200 Baud.
 *  Additionally the acknowledge string "Lobaro OK!" is send back to the sender via UDP6.
 *
 *  API Documentation:
 *  Please refer to "ext_libs/ZWIR45xx_Stack/doc/" for further information
 *  about ZMDIs raw 6LoWPAN Stack. Particularly useful might be the file
 *  "ZWIR451x_ProgGuide_Rev_1_90.pdf".
 *
 *****************************************************************************/
#include "../ext_libs/lobaro_hal_ext.h"

char buf[500];
ZWIR_IPv6Address_t LinkLocalAdr;
ZWIR_SocketHandle_t SocketReceive = NULL;

void onSocketData( uint8_t*  data, uint16_t  size ); //callback function prototype

void PrintIPv6(ZWIR_IPv6Address_t* addr) {
	sprintf(buf, IPV6FRMT2, IPV6VALUE(*addr));
	ZWIR_UART1_Send(buf, strlen(buf));
	ZWIR_UART1_Send("\r\n",2);
}

void ZWIR_AppInitHardware ( ZWIR_ResetReason_t   reason )
{
    ZWIR_SetFrequency(ZWIR_mcu8MHz);
    ZWIR_SetOperatingMode(ZWIR_omNormal,NULL);

    //Init Stack Network Parameter
    ZWIR_SetTransmitPower(5); //+5dBm
    ZWIR_SetParameter(ZWIR_spMaxHopCount,0);                    // => Only Endnode, no Packet Forwarding
    ZWIR_SetParameter(ZWIR_spDoRouterSolicitation,0);           // => no global Routers on Network, no global IPv6 Adr needed
    ZWIR_SetParameter(ZWIR_spDoDuplicateAddressDetection,0);    // => no duplicate addresses possible
    ZWIR_SetParameter(ZWIR_spRouteMaxFailCount,3);
    ZWIR_SetParameter(ZWIR_spRouteRequestAttempts,2);
    ZWIR_SetParameter(ZWIR_spNeighborReachableTime, 0);
    ZWIR_SetParameter(ZWIR_spNeighborCacheSize, 100);
}

void ZWIR_AppInitNetworkDone ( ZWIR_ResetReason_t   reason )
{
	ZWIR_UART1_Setup(115200, 0);

//Print IPv6 address on uart1
	ZWIR_GetIPv6Addresses(&LinkLocalAdr, 1); //link local IPv6 Address of this ZWIR Module
	sprintf(buf, "- Lobaro 6LoWPAN!\r\n- LinkLocal IPv6: ");
	PrintIPv6(&LinkLocalAdr);

//Open UDP6 Receive Socket on UDP port 5684
	ZWIR_IPv6Address_t ReceiveAdr = {IPV6_UNSPECIFIED};
	SocketReceive = ZWIR_OpenSocket(&ReceiveAdr, 0, 5684, onSocketData);

	if(SocketReceive) {
		sprintf(buf, "- UDP6 RX Socket on port 5684 open!\r\n");
		ZWIR_UART1_Send(buf, strlen(buf));
	} else {
		sprintf(buf, "- Error opening UDP6 RX Socket!\r\n");
		ZWIR_UART1_Send(buf, strlen(buf));
	}

}

//Socket Receive Callback, called by 6LoWPAN Stack
void onSocketData( uint8_t*  data, uint16_t  size ){
	ZWIR_IPv6Address_t* senderAddr = ZWIR_GetPacketSenderAddress();
	uint16_t senderPort = ZWIR_GetPacketSenderPort();

//Info
	sprintf(buf, "- Received %d bytes on local port 5684 from remote port %u of host: ", size, senderPort);
	ZWIR_UART1_Send(buf, strlen(buf));
	PrintIPv6(senderAddr);
	sprintf(buf, "- Payload: \"");
	ZWIR_UART1_Send(buf, strlen(buf));
	ZWIR_UART1_Send(data, size); //simply forward data to uart1
	sprintf(buf, "\"\r\n");
	ZWIR_UART1_Send(buf, strlen(buf));

//Echo received data to remote host
//avoid ZWIR_SendUDP2 because we want to set the local port of response to
//destination port of request. The windows firewall likes it more.
	ZWIR_SocketHandle_t SocketTransmit = ZWIR_OpenSocket(senderAddr, senderPort, 5684, NULL);

	if(ZWIR_SendUDP(SocketTransmit,"Lobaro OK!",10)  == 0) {
		sprintf(buf, "- send response ERROR\r\n\r\n");
		ZWIR_UART1_Send(buf, strlen(buf));
	} else {
		sprintf(buf, "- send response OK\r\n\r\n");
		ZWIR_UART1_Send(buf, strlen(buf));
	}
	ZWIR_CloseSocket(SocketTransmit);
}

//Main "Loop"
void ZWIR_Main1000ms ( void )
{
	static uint32_t cnt = 0;

	sprintf(buf, "\r\nSeconds since power up: %lu\r\n", cnt++);
	ZWIR_UART1_Send(buf, strlen(buf));
}

/*
void ZWIR_Main100ms ( void )
{

}
*/
