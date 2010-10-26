/*****************************************************************************
 *   target.h:  Header file for NXP LPC23xx/24xx Family Microprocessors
 *
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2006.09.20  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#ifndef __TARGET_H 
#define __TARGET_H

#ifdef __cplusplus
   extern "C" {
#endif

/* TK102-2 values */

/* System external oscillator frequency */
#define Fosc    11059200UL

     /* Multiplier for system frequency */
#define Fmult 5
     /* This goes into the MSEL bits in PLLCFG[4:0] register */
#define Fmult_bits (Fmult - 1)

     /* This goes into the PSEL bits in the PLLCFG[6:5] register */
#define Fodiv_bits 1
     /* PLL divider factor. 2 here */
#define Fodiv (1<<Fodiv_bits)

#define Fpdiv 4

/* System frequence,should be (1~32)multiples of Fosc,and should be equal or 
less than 60MHz. For TK102-2, we choose 55296000 */
#define Fcclk   (Fosc * Fmult)

/* CCO frequence,should be 2/4/8/16 multiples of Fcclk, ranged from 156MHz to 
320MHz. For TK102-2, we choose 221184000 */
#define Fcco    (Fcclk * 2 * Fodiv)

/* VPB clock frequence , must be 1/2/4 fraction of Fcclk. For TK102-2, we
choose 55296000 */
#define Fpclk   (Fcclk / Fpdiv) 


#define PLL_Value      ((Fodiv_bits<<5)|(Fmult_bits))

#define Fpclk_MHz       (Fpclk / 1000000)
#define SYS_FREQ        (Fcclk / 1000000)

/******************************************************************************
** Function name:		TargetInit
**
** Descriptions:		Initialize the target board; it is called in a 
**				necessary place, change it as needed
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern void TargetInit(void);
extern void ConfigurePLL( void );
extern void TargetResetInit(void);

#ifdef __cplusplus
   }
#endif
 
#endif /* end __TARGET_H */
/******************************************************************************
**                            End Of File
******************************************************************************/
