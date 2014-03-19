/*******************************************************************************
 *  rtc.c
 *  Teensy3
 *
 * Purpose:     Provides routines for RTC alarm.
 *
 *******************************************************************************/

#include "rtc.h"
/*#include "bitband.h"

#define RTC_IER_TAIE_BIT   0x02

void rtc_alarm(unsigned long sec){
    if (!(RTC_IER & RTC_IER_TAIE_MASK)) BITBAND_U32(RTC_IER, RTC_IER_TAIE_BIT) = 1;
    RTC_TAR = rtc_get() + (sec - 1);
}

void rtc_stop(void) {
    BITBAND_U32(RTC_IER, RTC_IER_TAIE_BIT) = 0;
    //RTC_IER &= ~RTC_IER_TAIE_MASK;
}
*/