/*
 *  t3core2lp.h
 *  Teensy3
 *
 */
#ifndef __T3CORE2LP_H__
#define __T3CORE2LP_H__

#include "Arduino.h"
#include <arm_math.h>

#ifdef __cplusplus
extern "C" {
#endif
    uint32_t micros_lp(uint32_t f_cpu);
    
    void delay_lp(uint32_t msec, uint32_t f_cpu);
    
    static inline uint32_t millis_lp(void) __attribute__((always_inline, unused));
    static inline uint32_t millis_lp(void) {
        volatile uint32_t ret = systick_millis_count; // single aligned 32 bit is atomic;
        return ret;
    }
    
    static inline void delayMicroseconds_lp(uint32_t, uint32_t) __attribute__((always_inline, unused));
    static inline void delayMicroseconds_lp(uint32_t usec, uint32_t f_cpu) {
        if (usec == 0) return;
        uint32_t n;
        if (f_cpu == 96000000) {
            n = (usec << 4)-6;
        }
        else if (f_cpu == 48000000) {
            n = (usec << 3)-4;
        }
        else if (f_cpu == 24000000) {
            n = (usec << 2)-3;
        }
        else if (f_cpu == 16000000) {
            n = usec*2.66666666666667;
        }
        else if (f_cpu == 8000000) {
             n = usec*1.33333333333333;
        }
        else if (f_cpu == 4000000) {
            n = usec*0.66666666666667;
        }
        else if (f_cpu == 2000000) {
            n = usec*0.33333333333333;
        }
        asm volatile(
                     "L_%=_delayMicroseconds_lp:"       "\n\t"
                     "sev"                              "\n\t"
                     "wfe"                              "\n\t"
                     "subs   %0, #1"                    "\n\t"
                     "bne    L_%=_delayMicroseconds_lp"	"\n"
                     : "+r" (n) :
                     );
        
    }
#ifdef __cplusplus
}
#endif
#endif
