/*
 *  lptm.h
 *  Teensy3
 *
 */

#ifndef __LPTMR_H__
#define __LPTMR_H__
/********************************************************************/
#include <inttypes.h>
#include "mk20dx128.h"
#include "mk20dx128_ext.h"
#include "bitband.h"

#define SIM_SCGC5_LPTIMER_BIT 0x00
#define OSC32KCLK_BIT        19//~0xC0000u
#define RTC_OSC_BIT          19//0x80000u
#define LPO_OSC_BIT          19//0xC0000u

#define IRCS_BIT             0x00
#define EREFS_BIT            0x02

#define IRCLKEN_BIT          0x01

#define EREFSTEN_BIT         0x05
#define ERCLKEN_BIT          0x07

#define LPTMR_PBYP_BIT       0x02
#define LPTMR_TCF_BIT        0x02
#define LPTMR_TIE_BIT        0x06

#define LPTMR_MCGIRCLK       (uint8_t)0x0
#define LPTMR_LPO            (uint8_t)0x1
#define LPTMR_ERCLK32K       (uint8_t)0x2
#define LPTMR_OSCERCLK       (uint8_t)0x3
#define LPTMR_PBYP           (uint8_t)0x4
#define LPTMR_PRESCALE(n)    (uint8_t)(((n) & 0x0F) << 3)

#define LPTMR_TCF            (uint8_t)0x80
#define LPTMR_TIE            (uint8_t)0x40
#define LPTMR_TEN            (uint8_t)0x00
/********************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
    // function prototypes
    /* Low Power Timer LPTM Functions */
    static inline void lptmr_init(void) __attribute__((always_inline, unused));
    static inline void lptmr_init(void) {
        /****************************MCG*****************************/
        //BITBAND_U8(MCG_C1, IRCLKEN_BIT) = 1;    // internal ref clock active in stop mode
        //BITBAND_U8(MCG_C1, IRCLKEN_BIT) = 0;    // not active in stop mode
        
        // seems not to effect anything
        //MCG_C2 &= ~MCG_C2_IRCS;     // slow internal ref clock
        BITBAND_U8(MCG_C2, IRCS_BIT) = 0;         // slow internal ref clock
        //BITBAND_U8(MCG_C2, IRCS_BIT) = 1;       // fast internal ref clock
        
        // Super Hard fault if set to use "External Reference Clock".
        // but lucky the Internal Oscillator is set by default
        //MCG_C2 |= MCG_C2_EREFS;    // default through reset
        BITBAND_U8(MCG_C2, EREFS_BIT) = 1;        // default through reset
        //BITBAND_U8(MCG_C2, EREFS_BIT) = 0;      // ****CRASH!!!!**** could only recover by power cycling
        /************************************************************/
        
        /***************************SIM******************************/
        //BITBAND_U32(SIM_SOPT1, OSC32KCLK_BIT) = 0;
        //BITBAND_U32(SIM_SOPT1, OSC32KCLK_BIT-1) = 0;
        //SIM_SOPT1 &= OSC32KCLK;  // using OSC32KCLK
        
        //BITBAND_U32(SIM_SOPT1, LPO_OSC_BIT) = 1;
        //BITBAND_U32(SIM_SOPT1, LPO_OSC_BIT-1) = 1;
        //SIM_SOPT1 |= LPO_OSC;    // using LPO_OSC
        
        BITBAND_U32(SIM_SOPT1, RTC_OSC_BIT) = 1;
        //SIM_SOPT1 |= RTC_OSC_BIT;      // using RTC_OSC
        /************************************************************/
        
        /***************************OSC******************************/
        //BITBAND_U8(OSC0_CR, EREFSTEN_BIT) = 1;
        //OSC0_CR |= OSC_EREFSTEN;   // External reference stop enable - OSCERCLK remains enabled when MCU enters stop modes
        
        //BITBAND_U8(OSC0_CR, ERCLKEN_BIT) = 1;
        //OSC0_CR |= OSC_ERCLKEN;    // Enable external reference clock (OSCERCLK), PAGE 533
        //OSC0_CR |= OSC_EREFSTEN   // External reference stop enable - OSCERCLK remains enabled when MCU enters stop modes
        //| OSC_ERCLKEN;            // Enable external reference clock (OSCERCLK), PAGE 533
        /************************************************************/
        if (!BITBAND_U32(SIM_SCGC5, SIM_SCGC5_LPTIMER_BIT)) { BITBAND_U32(SIM_SCGC5, SIM_SCGC5_LPTIMER_BIT) = 1; }
        LPTMR0_CSR=0x00;
        LPTMR0_PSR=0x00;
        LPTMR0_CMR=0x00;
        
        //BITBAND_U32(LPTMR0_PSR, LPTMR_PBYP_BIT) = 1;
        //LPTMR0_PSR |= LPTMR_PBYP;       // prescaler is bypassed
        
        BITBAND_U32(LPTMR0_PSR, LPTMR_PBYP_BIT) = 0;
        //LPTMR0_PSR &= ~LPTMR_PBYP;      // prescaler is not bypassed
        
        LPTMR0_PSR |= LPTMR_PRESCALE(8);  // set the prescaler from (2 - 65536)
        
        //LPTMR0_PSR |= LPTMR_MCGIRCLK;   // internal ref clock
        //LPTMR0_PSR |= LPTMR_LPO;        // 1kHz clock
        LPTMR0_PSR |= LPTMR_ERCLK32K;     // secondary external ref clock
        //LPTMR0_PSR |= LPTMR_OSCERCLK;   // external ref clock
    }

    
    static inline void lptmr_start(uint32_t) __attribute__((always_inline, unused));
    static inline void lptmr_start(uint32_t period){
        if (!BITBAND_U32(SIM_SCGC5, SIM_SCGC5_LPTIMER_BIT)) { BITBAND_U32(SIM_SCGC5, SIM_SCGC5_LPTIMER_BIT) = 1; }
        
        // Clear Timer Compare Flag
        // Timer Interrupt
        // then start timer
        BITBAND_U32(LPTMR0_CSR, LPTMR_TCF_BIT) = 1;
        BITBAND_U32(LPTMR0_CSR, LPTMR_TIE_BIT) = 1;
        //LPTMR0_CSR = (LPTMR_TCF | LPTMR_TIE);
        
        LPTMR0_CMR = period;
        
        BITBAND_U32(LPTMR0_CSR, LPTMR_TEN) = 1;
        //LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;
    }
    
    static inline void lptmr_stop(void) __attribute__((always_inline, unused));
    static inline void lptmr_stop(void) {
        BITBAND_U32(LPTMR0_CSR, LPTMR_TCF) = 1;
        //LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;
        
        BITBAND_U32(LPTMR0_CSR, LPTMR_TEN) = 0;
        //LPTMR0_CSR &= ~LPTMR_CSR_TEN_MASK;
        
        if (BITBAND_U32(SIM_SCGC5, SIM_SCGC5_LPTIMER_BIT)) { BITBAND_U32(SIM_SCGC5, SIM_SCGC5_LPTIMER_BIT) = 0; }
    }
#ifdef __cplusplus
}
#endif
/********************************************************************/
#endif /* defined(__LPTMR_H__) */
