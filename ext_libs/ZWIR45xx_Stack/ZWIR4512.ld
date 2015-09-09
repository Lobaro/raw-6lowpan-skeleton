/****************************************************************************/
/*  Linker command file for STM32                                           */
/****************************************************************************/

GROUP(
 libm.a
 libgcc.a
 libc.a
 libZWIR45xx-6LoWPAN.a
/* libZWIR45xx-NetMA2.a */
 libZWIR451x-GPIO.a
 libZWIR451x-UART1.a
 libZWIR451x-UART2.a
 libZWIR451x-SPI1.a
/* libZWIR451x-NetMA2-Ext.a */
 libZWIR451x-OTAU.a
 libZWIR4512.a
)

/* Memory Definitions STM32F103RC  */
MEMORY {
  FLASH (xr)     : ORIGIN = 0x08000000, LENGTH = 0x00040000
  stack (xw)     : ORIGIN = 0x20000000, LENGTH = 0x00001400
  ram   (xw)     : ORIGIN = 0x20001400, LENGTH = 0x0000AC00
}

/* GCC LD bugfix */
__originStack = ORIGIN ( stack ) + 0;
__originFlash = ORIGIN ( FLASH ) + 0;
__originRam = ORIGIN ( ram ) + 0;

/** Number of flash pages reserved for non-volatile parameter storage
 *  This memory will not be affected by firmware over the air updates
 */
__nvReservedPageCount = 1;

/* Define size of one page of flash memory*/
__mcuFlashPageSize = 0x800;

/* Define stack start address*/
__estack = __originStack + LENGTH ( stack );

/* Compute the length of flash required for non-volatile parameter storage */
__nvReservedFlashSize = __nvReservedPageCount * __mcuFlashPageSize;

SECTIONS {
  
  .update_code : {
    _otau_start = .;
    KEEP ( *(.otau_isr_vectors .otau_isr_vectors.*) );
    start = .;
    KEEP ( *(.otau_startup .otau_startup.*) );
    KEEP ( *(.otau_permanent .otau_permanent.*) );
  } >FLASH
  __otauUsed = SIZEOF (.update_code) > 0;

  ASSERT ( SIZEOF (.update_code) < 0x7c0, "Invariant OTAU code too big (maximum allowed length is 0x7c0 bytes)" )

  .interface_seg :  {
    . = __otauUsed ? 0x7c0 - SIZEOF (.update_code) : 0;
    KEEP ( *(.otau_interface .otau_interface.*) );
  } >FLASH 

  .status_seg ALIGN ( __mcuFlashPageSize ):  {
    KEEP ( *(.otau_status_seg .otau_status_seg.*) );
  } >FLASH

  /* vector-table containing initial SP and PC */
  .isr_vector ALIGN ( __mcuFlashPageSize ) : {
    __ldISRVectorStart__ = .;
    KEEP ( *(.isr_vectors) )
  } >FLASH

  .boot_init : {
    start = (start != _otau_start) ? start : . ;
    *(.boot_init .boot_init.*)
  } >FLASH

  .init : {
    . = ALIGN ( 4 );
    *(.init .init.*)
    . = ALIGN ( 4 );
  } > FLASH

  .text : {
    . = ALIGN ( 4 );
    *(.text .text.* .glue_7t .glue_7 .gnu.linkonce.t.* .gcc_except_table)
    *(.rodata)
    *(.rodata*)
    *(.rodata.str1.4)
    . = ALIGN ( 4 );
  } > FLASH

  .ARM.extab ALIGN ( 4 )  : { *(.ARM.extab* .gnu.linkonce.armextab.*) } > FLASH
   __exidx_start = .;
  .ARM.exidx ALIGN ( 4 )  : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } > FLASH
   __exidx_end = .;
  _end = .;

  __RAM_startup_init_data__ = ALIGN ( 4 );

/******************************************************************************
*                                   DATA
*******************************************************************************/
   .otau_var(NOLOAD) : {
     *(.otau_var.ZMDI_otauFirmwareSeg1)
     *(.otau_var.ZMDI_otauPageCache)
     *(.otau_var.ZMDI_otauFirmwareSeg2)
     *(.otau_var);
   } >ram

  .data : AT ( __RAM_startup_init_data__ ) {
    __RAM_data_start__  = .;
    *(.data .data.* .gnu.linkonce.d.*)
    *(.init_array.00000)
    *(.init_array)
    . = ALIGN(4);
    __RAM_data_end__ = .;
  } > ram

  .tdata : AT ( __RAM_startup_init_data__ + SIZEOF(.data)) {
    __TRAM_data_start__  = .;
    *(.tdata .tdata.*)
    . = ALIGN(4);
    __TRAM_data_end__ = .;
  } > ram

  __RAM_all_data_end__ = .;
    
  _DATASize = __RAM_all_data_end__ - __RAM_data_start__;
  /******************************************************************************
*                                   .bss
*******************************************************************************/
  .bss (NOLOAD) : {
    __bss_start__ = .;
    *(.bss .bss.*)
    __bss_end__ = . ;  
  } >ram
  
  .tbss (NOLOAD) : {
    __tbss_start__ = .;
    *(.tbss .tbss.*)
    __tbss_end__ = . ;  
  } >ram
   
  PROVIDE ( end = . );    
  PROVIDE ( __heap_start__ = . );
  PROVIDE ( __heap_end__ = __originRam + LENGTH ( ram ) );
  
  /* This is to circumvent an gcc 4.4.x issue */
  /DISCARD/ : { *(.eh_*) }

/******************************************************************************
*                                   .store
*******************************************************************************/
  /* set location counter to EndOfFlash - NonVolatileMemorySize */  
  . = __originFlash + LENGTH(FLASH) - __nvReservedFlashSize;

  /* Do not rename .nvDataMemory */
  .nvDataMemory ALIGN ( __mcuFlashPageSize ) : {
    *(.NetMA_NVParameters .NetMA_NVParameters.*)
    
    /***********************************************************************
    * Uncomment the following section to use a non volatile store section.
    * Don't forget to update __nvReservedPageCount accordingly.
    ************************************************************************
      . = NEXT ( __mcuFlashPageSize );
      __store_start__ = .;
	  *(.store .store.*)
	  __store_end__ = .;
    ************************************************************************/
    
  } > FLASH
}

__mcuFlashEnd = __originFlash + LENGTH(FLASH);

__executableSize = __RAM_startup_init_data__ + _DATASize - __originFlash;

/* Executable segment - this contains the current firmware code */
__executableSegmentStart = __ldISRVectorStart__;

/* This variable defines the maximum firmware code size */
__totalFirmwareSpace = LENGTH ( FLASH ) - __nvReservedFlashSize - ( __executableSegmentStart - __originFlash );
__maxExecutableSize = __otauUsed ? __totalFirmwareSpace / 2 : __totalFirmwareSpace;

/* Compute the maximum number of pages a firmware image may occupy:
  ( flash size - invariant OTAU code - non-volatile data memory ) / 2 */
__otauMaximumImagePageCount = __maxExecutableSize / __mcuFlashPageSize;

/* Update segment - this contains a copy of the new firmware */
__updateSegmentStart = __executableSegmentStart + ( __otauMaximumImagePageCount * __mcuFlashPageSize );

/*check if there is enough space in flash memory*/
ASSERT( ( __executableSize < __maxExecutableSize ), "error: binary size too big!");

/* set thumb bit for entry symbol*/
start = start | 1;

ENTRY ( start );

/* Force the linker to link library symbols which would otherwise not be included*/
EXTERN ( g_pfnVectors ZMDI_OTAU_Interface NetMA_RXHandler NetMA_ParameterStore);
