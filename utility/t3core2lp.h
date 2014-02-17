/*
 *  t3core2lp.h
 *  Teensy3
 *
 */
#ifndef __T3CORE2LP_H__
#define __T3CORE2LP_H__

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
        //long n;
        //float cpu = f_cpu;
        //n = (usec * (cpu/3000000));//-32856;
        /*if (usec == 0) return;
        else if (f_cpu >= 24000000) {
            n = ((usec) * (f_cpu/3000000)) - 16;
        }
        else {
            float cpu = f_cpu;
            n = usec;//(usec * (cpu/3000000)) - 16;
        }*/
        
        asm volatile(
                     "L_%=_delayMicroseconds_lp:"       "\n\t"
                     "subs   %0, #1"                    "\n\t"
                     "bge    L_%=_delayMicroseconds_lp"	"\n"
                     : "+r" (usec) :
                     );
        
    }
#ifdef __cplusplus
}
#endif
#endif
