/*
 *  rtc.h
 *  Teensy3
 *
 */

#ifndef __RTC_H__
#define __RTC_H__
/********************************************************************/
#include "mk20dx128.h"
#include "mk20dx128_ext.h"
#include "bitband.h"

#define RTC_IER_TAIE_BIT   0x02
/********************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
    // function prototypes
    static inline void rtc_alarm(unsigned long) __attribute__((always_inline, unused));
    static inline void rtc_alarm(unsigned long sec) {
        if (!BITBAND_U32(RTC_IER, RTC_IER_TAIE_BIT)) BITBAND_U32(RTC_IER, RTC_IER_TAIE_BIT) = 1;
        //if (!(RTC_IER & RTC_IER_TAIE_MASK)) BITBAND_U32(RTC_IER, RTC_IER_TAIE_BIT) = 1;
        RTC_TAR = rtc_get() + (sec - 1);
    }
    
    static inline void rtc_stop(void) __attribute__((always_inline, unused));
    static inline void rtc_stop(void) {
        BITBAND_U32(RTC_IER, RTC_IER_TAIE_BIT) = 0;
        //RTC_IER &= ~RTC_IER_TAIE_MASK;
    }
#ifdef __cplusplus
}
#endif
/********************************************************************/
#endif /* __RTC_H__ */
