/*****************************************************************************
 *   target.c:  Target C file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.07.13  ver 1.00    Prelimnary version, first Release
 *
*****************************************************************************/
#include "LPC214x.h"
#include "type.h"
#include "irq.h"
#include "target.h"

void blink_led_asm(void);

void blink_led(int);

/******************************************************************************
** Function name:		TargetInit
**
** Descriptions:		Initialize the target board; it is called in a necessary 
**						place, change it as needed
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TargetInit(void)
{
  /* Add your codes here */
  return;
}

/******************************************************************************
** Function name:		GPIOResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**				function; User may change it as needed, but may not 
**				deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void GPIOResetInit( void )
{
  /* Reset all GPIO pins to default: primary function */
  /* Exception: P1.16 (debug LED) to output */
  PINSEL0 = 0x00000000;
  PINSEL1 = 0x00000000;
  PINSEL2 = 0x00000000;
    
  IODIR0 = 0x00000000;
  IODIR1 = 0x00000000;
  IOSET0 = 0x00000000;
  IOSET1 = 0x00000000;
    
  FIO0DIR = 0x00000000;
  FIO1DIR = 0x00000000; // P1.16 is output
    
  FIO0SET = 0x00000000;
  FIO1SET = 0x00000000;
  
  SCS = 3; // enable fast GPIO

  return;        
}

/******************************************************************************
** Function name:		ConfigurePLL
**
** Descriptions:		Configure PLL switching to main OSC instead of IRC
**						at power up and wake up from power down. 
**						This routine is used in TargetResetInit() and those
**						examples using power down and wake up such as
**						USB suspend to resume, ethernet WOL, and power management
**						example
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void ConfigurePLL ( void )
{
  DWORD MValue, NValue;

  if ( PLLSTAT & (1 << 9) )
  {
    PLLCON = 1;			/* Enable PLL, disconnected */
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
  }

  VPBDIV = Fpdiv_bits;

  PLLCON = 0;				/* Disable PLL, disconnected */
  PLLFEED = 0xaa;
  PLLFEED = 0x55;
    
  PLLCFG = PLL_Value;
  PLLFEED = 0xaa;
  PLLFEED = 0x55;
      
  PLLCON = 1;				/* Enable PLL, disconnected */
  PLLFEED = 0xaa;
  PLLFEED = 0x55;


  while ( ((PLLSTAT & (1 << 10)) == 0) );	/* Check lock bit status */
    
  PLLCON = 3;				/* enable and connect */
  PLLFEED = 0xaa;
  PLLFEED = 0x55;
}

/******************************************************************************
** Function name:		TargetResetInit
**
** Descriptions:		Initialize the target board before running the main() 
**						function; User may change it as needed, but may not 
**						deleted it.
**
** parameters:			None
** Returned value:		None
** 
******************************************************************************/
void TargetResetInit(void)
{
#ifdef __DEBUG_RAM    
  MEMMAP = 0x2;			/* remap to internal RAM */
#endif

#ifdef __DEBUG_FLASH    
  MEMMAP = 0x1;			/* remap to internal flash */
#endif

  MEMMAP = 0x1;			/* remap to internal flash */

  GPIOResetInit();

  //blink_led(2);


  /* Configure PLL, switch from IRC to Main OSC */
  ConfigurePLL();

  //blink_led(3);

  /* Set memory accelerater module, tunes access to flash */
  MAMCR = 0;

#if Fcclk < 20000000
  MAMTIM = 1;
#else
#if Fcclk < 40000000
  MAMTIM = 2;
#else
  MAMTIM = 3;
#endif
#endif
  MAMCR = 2;

  init_VIC();
  //  blink_led(4);
}

void set_debug_led (void) {
  FIO1CLR = 0x00010000;
}

void clear_debug_led (void) {
  FIO1SET = 0x00010000;
}

void blink_led (int count) {
  int i,j;

  for(j=0;j<100000;j++) { }
  for(i=0;i<count;i++) {
    set_debug_led();
    for(j=0;j<100000;j++) { }
    clear_debug_led();
    for(j=0;j<100000;j++) { }
  }
  for(j=0;j<100000;j++) { }
}

/******************************************************************************
**                            End Of File
******************************************************************************/
