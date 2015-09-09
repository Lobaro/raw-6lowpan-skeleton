# 6LoWPAN RAW SDK Skeleton Project 
http://www.lobaro.com

# Usage:
a) Install https://launchpad.net/gcc-arm-embedded toolchain

b) on windows: Install CooCox IDE 1.7.8

c) on windows: Open Project File

# (!)Please note(!):
This SDK is intended for experienced embedded programmers!

Please visit "http://www.lobaro.com" for complete solutions based on the
"constrained application protocol" (CoAP). These solutions are much easier
to use because minimal to zero knowledge of embedded device programming is needed.
  
#Firmware Description:
The Firmware opens a udp6 socket on local port #5684 and prints any received
data on UART1/USB Port of "LOBARO IPV6 UNIVERSAL BOX" @115200 Baud.
Additionally the acknowledge string "Lobaro OK!" is send back to the sender via UDP6.
  
#API Documentation:
Please refer to "ext_libs/ZWIR45xx_Stack/doc/" for further information
about ZMDIs raw 6LoWPAN Stack. Particularly useful might be the file
"ZWIR451x_ProgGuide_Rev_1_90.pdf".
