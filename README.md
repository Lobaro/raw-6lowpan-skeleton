# 6LoWPAN RAW SDK Skeleton Project
### [http://www.lobaro.com](http://www.lobaro.com)

##Firmware Description:
The Firmware opens an udp6 socket on local port #5684 and outputs any received
data on UART1/USB Port of "LOBARO IPV6 UNIVERSAL BOX" @115200 Baud.

Additionally the acknowledge string "Lobaro OK!" is send back to the sender via UDP6 on port choosen by sender.

### *Please note:*
This SDK is intended for experienced embedded programmers!

Please visit "http://www.lobaro.com" for complete solutions based on the "constrained application protocol" (CoAP). 

**These solutions are much easier to use because minimal to zero knowledge of embedded device programming is needed.**

## Usage:

###1. Install free GCC ARM Toolchain|Compiler
  * [https://launchpad.net/gcc-arm-embedded toolchain](https://launchpad.net/gcc-arm-embedded toolchain)
  
###2. Install IDE Enviroment
  * Option A: CooCox IDE 1.7.8 (Win only)  [http://www.coocox.org](http://www.coocox.org)
  * Option B: "Eclipse IDE for C/C++ Developers" (Mars)  [Free Download](http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/marsr) with "GNU ARM Eclipse" Plugin  [Free Download](http://gnuarmeclipse.github.io/)

CooCox supports programming and debuging via ST/LinkV2 JTAG adapter out of the box. This is accomplished by its internal GDB-Server. 

On pure Eclipse you have to setup an external GDB Server.


###3. Open preconfigured project file inside IDE


  

  
##API Documentation:
Please refer to [raw-6lowpan-skeleton/tree/master/ext_libs/ZWIR45xx_Stack/doc](https://github.com/Lobaro/raw-6lowpan-skeleton/tree/master/ext_libs/ZWIR45xx_Stack/doc) for further information
about ZMDIs raw 6LoWPAN Stack. 

Particularly useful might be the file "ZWIR451x-ProgGuide-Rev-1-90.pdf". 
