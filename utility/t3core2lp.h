//
//  T3core2LP.h
//  teensy_18_RC1
//
//  Created by colin on 1/29/14.
//  Copyright (c) 2014 iwater. All rights reserved.
//

#ifndef teensy_18_RC1_T3core2LP_h
#define teensy_18_RC1_T3core2LP_h
#include "Arduino.h"
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
        uint32_t n;
        if (usec == 0) return;
        else if (f_cpu >= 24000000) {
            n = usec * (f_cpu/3000000);
        }
        else {
            float cpu = f_cpu;
            n = usec * (cpu/3000000);
        }
        
        asm volatile(
                     "L_%=_delayMicroseconds_lp:"          "\n\t"
                     "subs   %0, #1"                    "\n\t"
                     "bge    L_%=_delayMicroseconds_lp"	"\n"
                     : "+r" (n) :
                     );
        
    }
#ifdef __cplusplus
}
#endif
#endif
