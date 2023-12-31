//*****************************************************************************
// LPC15xx Microcontroller Startup code for use with LPCXpresso IDE
//
// Version : 150706
//*****************************************************************************
//
// Copyright 2013-2015, 2019, 2020 NXP
// All rights reserved.
//
// NXP Confidential. This software is owned or controlled by NXP and may only be
// used strictly in accordance with the applicable license terms.
//
// By expressly accepting such terms or by downloading, installing, activating
// and/or otherwise using the software, you are agreeing that you have read, and
// that you agree to comply with and are bound by, such license terms.
// 
// If you do not agree to be bound by the applicable license terms, then you may not
// retain, install, activate or otherwise use the software.
//*****************************************************************************

#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#else
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
    extern void __libc_init_array(void);
}
#endif
#endif

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
#if defined (__cplusplus)
extern "C" {
#endif

//*****************************************************************************
#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
// Declaration of external SystemInit function
extern void SystemInit(void);
#endif

//*****************************************************************************
//
// Forward declaration of the default handlers. These are aliased.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions
//
//*****************************************************************************
void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void MemManage_Handler(void);
WEAK void BusFault_Handler(void);
WEAK void UsageFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void DebugMon_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
//
// Forward declaration of the specific IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
//*****************************************************************************
// Note: The names used for the IRQ Handlers in the LPCXpresso LPC15xx startup
// code did not originally match those used by the LPCOpen LPC15xx packages.
// Now default to using LPCOpen IRQ Handler names. But allow the use of the
// previous names if necessary for legacy code by undefining the below symbol
#define USE_LPCOPEN_IRQHANDLER_NAMES

#if defined (USE_LPCOPEN_IRQHANDLER_NAMES)
void WDT_IRQHandler(void) ALIAS(IntDefaultHandler);
void BOD_IRQHandler(void) ALIAS(IntDefaultHandler);
void FMC_IRQHandler(void) ALIAS(IntDefaultHandler);
void EEPROM_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT4_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT5_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT6_IRQHandler(void) ALIAS(IntDefaultHandler);
void PIN_INT7_IRQHandler(void) ALIAS(IntDefaultHandler);
void RIT_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void MRT_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_FIQHandler(void) ALIAS(IntDefaultHandler);
void USBWakeup_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0A_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0B_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_THCMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_OVR_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1A_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1B_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_THCMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_OVR_IRQHandler(void) ALIAS(IntDefaultHandler);
void DAC_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP0_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP1_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP2_IRQHandler(void) ALIAS(IntDefaultHandler);
void ACMP3_IRQHandler(void) ALIAS(IntDefaultHandler);
void QEI_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_ALARM_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_WAKE_IRQHandler(void) ALIAS(IntDefaultHandler);
#else
void WDT_IRQHandler(void) ALIAS(IntDefaultHandler);
void BOD_IRQHandler(void) ALIAS(IntDefaultHandler);
void FLASH_IRQHandler(void) ALIAS(IntDefaultHandler);
void EEPROM_IRQHandler(void) ALIAS(IntDefaultHandler);
void DMA_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void GINT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT4_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT5_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT6_IRQHandler(void) ALIAS(IntDefaultHandler);
void PININT7_IRQHandler(void) ALIAS(IntDefaultHandler);
void RIT_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT1_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT2_IRQHandler(void) ALIAS(IntDefaultHandler);
void SCT3_IRQHandler(void) ALIAS(IntDefaultHandler);
void MRT_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART0_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART1_IRQHandler(void) ALIAS(IntDefaultHandler);
void UART2_IRQHandler(void) ALIAS(IntDefaultHandler);
void I2C0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI0_IRQHandler(void) ALIAS(IntDefaultHandler);
void SPI1_IRQHandler(void) ALIAS(IntDefaultHandler);
void CAN0_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_IRQHandler(void) ALIAS(IntDefaultHandler);
void USB_FIQHandler(void) ALIAS(IntDefaultHandler);
void USBWakeup_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_SEQA_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_SEQB_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_THCMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC0_OVR_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_SEQA_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_SEQB_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_THCMP_IRQHandler(void) ALIAS(IntDefaultHandler);
void ADC1_OVR_IRQHandler(void) ALIAS(IntDefaultHandler);
void DAC_IRQHandler(void) ALIAS(IntDefaultHandler);
void CMP0_IRQHandler(void) ALIAS(IntDefaultHandler);
void CMP1_IRQHandler(void) ALIAS(IntDefaultHandler);
void CMP2_IRQHandler(void) ALIAS(IntDefaultHandler);
void CMP3_IRQHandler(void) ALIAS(IntDefaultHandler);
void QEI_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_ALARM_IRQHandler(void) ALIAS(IntDefaultHandler);
void RTC_WAKE_IRQHandler(void) ALIAS(IntDefaultHandler);
#endif
//*****************************************************************************
//
// The entry point for the application.
// __main() is the entry point for Redlib based applications
// main() is the entry point for Newlib based applications
//
//*****************************************************************************
#if defined (__REDLIB__)
extern void __main(void);
#endif
extern int main(void);
//*****************************************************************************
//
// External declaration for the pointer to the stack top from the Linker Script
//
//*****************************************************************************
extern void _vStackTop(void);

//*****************************************************************************
//
// External declaration for LPC MCU vector table checksum from  Linker Script
//
//*****************************************************************************
WEAK extern void __valid_user_code_checksum();

//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif
//*****************************************************************************
//
// The vector table.
// This relies on the linker script to place at correct location in memory.
//
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);
__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
	// Core Level - CM3
	&_vStackTop,                       // The initial stack pointer
	ResetISR,                          // The reset handler
	NMI_Handler,                       // The NMI handler
	HardFault_Handler,                 // The hard fault handler
	MemManage_Handler,                 // The MPU fault handler
	BusFault_Handler,                  // The bus fault handler
	UsageFault_Handler,                // The usage fault handler
    __valid_user_code_checksum,        // LPC MCU Checksum
	0,                                 // Reserved
	0,                                 // Reserved
	0,                                 // Reserved
	SVC_Handler,                       // SVCall handler
	DebugMon_Handler,                  // Debug monitor handler
	0,                                 // Reserved
	PendSV_Handler,                    // The PendSV handler
	SysTick_Handler,                   // The SysTick handler

    // Chip Level - LPC15xx
#if defined (USE_LPCOPEN_IRQHANDLER_NAMES)
    WDT_IRQHandler,                    //  0 - Windowed watchdog timer
    BOD_IRQHandler,                    //  1 - BOD
    FMC_IRQHandler,                    //  2 - Flash controller
    EEPROM_IRQHandler,                 //  3 - EEPROM controller
    DMA_IRQHandler,                    //  4 - DMA
    GINT0_IRQHandler,                  //  5 - GINT0
    GINT1_IRQHandler,                  //  6 - GINT1
    PIN_INT0_IRQHandler,               //  7 - PIO INT0
    PIN_INT1_IRQHandler,               //  8 - PIO INT1
    PIN_INT2_IRQHandler,               //  9 - PIO INT2
    PIN_INT3_IRQHandler,               // 10 - PIO INT3
    PIN_INT4_IRQHandler,               // 11 - PIO INT4
    PIN_INT5_IRQHandler,               // 12 - PIO INT5
    PIN_INT6_IRQHandler,               // 13 - PIO INT6
    PIN_INT7_IRQHandler,               // 14 - PIO INT7
    RIT_IRQHandler,                    // 15 - RIT
    SCT0_IRQHandler,                   // 16 - State configurable timer
    SCT1_IRQHandler,                   // 17 - State configurable timer
    SCT2_IRQHandler,                   // 18 - State configurable timer
    SCT3_IRQHandler,                   // 19 - State configurable timer
    MRT_IRQHandler,                    // 20 - Multi-Rate Timer
    UART0_IRQHandler,                  // 21 - UART0
    UART1_IRQHandler,                  // 22 - UART1
    UART2_IRQHandler,                  // 23 - UART2
    I2C0_IRQHandler,                   // 24 - I2C0 controller
    SPI0_IRQHandler,                   // 25 - SPI0 controller
    SPI1_IRQHandler,                   // 26 - SPI1 controller
    CAN_IRQHandler,                    // 27 - C_CAN0
    USB_IRQHandler,                    // 28 - USB IRQ
    USB_FIQHandler,                    // 29 - USB FIQ
    USBWakeup_IRQHandler,              // 30 - USB wake-up
    ADC0A_IRQHandler,                  // 31 - ADC0 sequence A completion
    ADC0B_IRQHandler,                  // 32 - ADC0 sequence B completion
    ADC0_THCMP_IRQHandler,             // 33 - ADC0 threshold compare
    ADC0_OVR_IRQHandler,               // 34 - ADC0 overrun
    ADC1A_IRQHandler,                  // 35 - ADC1 sequence A completion
    ADC1B_IRQHandler,                  // 36 - ADC1 sequence B completion
    ADC1_THCMP_IRQHandler,             // 37 - ADC1 threshold compare
    ADC1_OVR_IRQHandler,               // 38 - ADC1 overrun
    DAC_IRQHandler,                    // 39 - DAC
    ACMP0_IRQHandler,                  // 40 - Analog Comparator 0
    ACMP1_IRQHandler,                  // 41 - Analog Comparator 1
    ACMP2_IRQHandler,                  // 42 - Analog Comparator 2
    ACMP3_IRQHandler,                  // 43 - Analog Comparator 3
    QEI_IRQHandler,                    // 44 - QEI
    RTC_ALARM_IRQHandler,              // 45 - RTC alarm
    RTC_WAKE_IRQHandler,               // 46 - RTC wake-up
#else
    WDT_IRQHandler,                    //  0 - Windowed watchdog timer
    BOD_IRQHandler,                    //  1 - BOD
    FLASH_IRQHandler,                  //  2 - Flash controller
    EEPROM_IRQHandler,                 //  3 - EEPROM controller
    DMA_IRQHandler,                    //  4 - DMA
    GINT0_IRQHandler,                  //  5 - GINT0
    GINT1_IRQHandler,                  //  6 - GINT1
    PININT0_IRQHandler,                //  7 - PIO INT0
    PININT1_IRQHandler,                //  8 - PIO INT1
    PININT2_IRQHandler,                //  9 - PIO INT2
    PININT3_IRQHandler,                // 10 - PIO INT3
    PININT4_IRQHandler,                // 11 - PIO INT4
    PININT5_IRQHandler,                // 12 - PIO INT5
    PININT6_IRQHandler,                // 13 - PIO INT6
    PININT7_IRQHandler,                // 14 - PIO INT7
    RIT_IRQHandler,                    // 15 - RIT
    SCT0_IRQHandler,                   // 16 - State configurable timer
    SCT1_IRQHandler,                   // 17 - State configurable timer
    SCT2_IRQHandler,                   // 18 - State configurable timer
    SCT3_IRQHandler,                   // 19 - State configurable timer
    MRT_IRQHandler,                    // 20 - Multi-Rate Timer
    UART0_IRQHandler,                  // 21 - UART0
    UART1_IRQHandler,                  // 22 - UART1
    UART2_IRQHandler,                  // 23 - UART2
    I2C0_IRQHandler,                   // 24 - I2C0 controller
    SPI0_IRQHandler,                   // 25 - SPI0 controller
    SPI1_IRQHandler,                   // 26 - SPI1 controller
    CAN0_IRQHandler,                   // 27 - C_CAN0
    USB_IRQHandler,                    // 28 - USB IRQ
    USB_FIQHandler,                    // 29 - USB FIQ
    USBWakeup_IRQHandler,              // 30 - USB wake-up
    ADC0_SEQA_IRQHandler,              // 31 - ADC0 sequence A completion
    ADC0_SEQB_IRQHandler,              // 32 - ADC0 sequence B completion
    ADC0_THCMP_IRQHandler,             // 33 - ADC0 threshold compare
    ADC0_OVR_IRQHandler,               // 34 - ADC0 overrun
    ADC1_SEQA_IRQHandler,              // 35 - ADC1 sequence A completion
    ADC1_SEQB_IRQHandler,              // 36 - ADC1 sequence B completion
    ADC1_THCMP_IRQHandler,             // 37 - ADC1 threshold compare
    ADC1_OVR_IRQHandler,               // 38 - ADC1 overrun
    DAC_IRQHandler,                    // 39 - DAC
    CMP0_IRQHandler,                   // 40 - Analog Comparator 0
    CMP1_IRQHandler,                   // 41 - Analog Comparator 1
    CMP2_IRQHandler,                   // 42 - Analog Comparator 2
    CMP3_IRQHandler,                   // 43 - Analog Comparator 3
    QEI_IRQHandler,                    // 44 - QEI
    RTC_ALARM_IRQHandler,              // 45 - RTC alarm
    RTC_WAKE_IRQHandler,               // 46 - RTC wake-up
#endif
}; /* End of g_pfnVectors */

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors")))
void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = 0;
}

//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the location of various points in the "Global Section Table". This table is
// created by the linker via the Code Red managed linker script mechanism. It
// contains the load address, execution address and length of each RW data
// section and the execution and length of each BSS (zero initialized) section.
//*****************************************************************************
extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;


//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void
ResetISR(void) {

    //
    // Copy the data sections from flash to SRAM.
    //
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

    // Load base address of Global Section Table
    SectionTableAddr = &__data_section_table;

    // Copy the data sections from flash to SRAM.
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }
    // At this point, SectionTableAddr = &__bss_section_table;
    // Zero fill the bss segment
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }
    
    // Optionally enable Cortex-M3 SWV trace (off by default at reset)
    // Note - your board support must also set up the switch matrix 
    // so that SWO is output on the appropriate pin for your hardware
#if !defined (DONT_ENABLE_SWVTRACECLK)
	// Write 0x00000001 to TRACECLKDIV – Trace divider
	volatile unsigned int *TRACECLKDIV = (unsigned int *) 0x400740D8;
	*TRACECLKDIV = 1;
#endif

#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
    SystemInit();
#endif

#if defined (__cplusplus)
    //
    // Call C++ library initialisation
    //
    __libc_init_array();
#endif

#if defined (__REDLIB__)
    // Call the Redlib library, which in turn calls main()
    __main() ;
#else
    main();
#endif

    //
    // main() shouldn't return, but if it does, we'll just enter an infinite loop
    //
    while (1) {
        ;
    }
}

//*****************************************************************************
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void){ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void MemManage_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void BusFault_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void UsageFault_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void SVC_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void DebugMon_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void)
{ while(1) {}
}

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void IntDefaultHandler(void)
{ while(1) {}
}



