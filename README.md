#LowPower_Teensy3 Library - Edge

>This is the latest code that should get branched if you want too contribute. Only the latest Teensyduino release will be used. Older versions of Teensyduino may or may not compile and work.

<h4>Currently used Teensyduino Version: 1.18</h4> 

<h3>ChangeLog beta v1.3:</h3>
1.  Added Idle function for lowering current during user waiting loops<br>
2.  Now Low Power "delay" and "delayMicroseconds" sleeps with minimal impact on precision.<br>

<h3>ChangeLog beta v1.2:</h3>
1.  Using Bitband to set peripheral clocks<br>
2.  Added support for IntervalTimer, delay, delayMicroseconds for dynamic CPU scaling<br>
3.  Added support for HardwareSerial at 16,8,4,2 MHz<br>
4.  Changed "Run" function to "CPU", now you can choose the frequency to run the CPU<br>

<h3>ChangeLog beta v1.1:</h3>
1.  Added all digital wakeup capable pins for DeepSleep and Hibernate function<br>
2.  User can now use a callback function for DeepSleep and Hibernate<br>
3.  Added Sleep function, now any interrupt can wake the processor<br>
4.  Improved code performance<br>
5.  New examples for Sleep function<br>

<h3>ChangeLog Stable v1.0:</h3>
1.  Fixed where VLPR was not being retained because of LPWUI bit not being set right<br>
2.  Added feature to enable LPWUI bit to exit VLPR with any interrupt<br>
3.  Fixed issue with VLPR locking up system if being called before exiting VLPR<br>
4.  Disabled USB Regulator Standby mode during Low Power<br>
5.  Cleaned up library code.<br>

<h3>ChangeLog Beta2:</h3>
1.  Added struct to store sleep configurations<br>
2.  Added RTC Alarm wake<br>
3.  Added TSI wake<br>
4.  Put usb regulator in standby for VLPR<br>
5.  Got rid of stand alone LPTMR timer functions<br>
6.  Cleaned up the library and example codes<br>
7.  New examples added<br>
8.  Defined GPIO wake pin names<br>

<h1>General Usage</h1>
<h3>Functions:</h3>
```c 
void CPU(uint32_t freq);
# Allows for dynamic changing of the CPU, BUS and MEM speed to lower avarege 
# power consumption. There are 5 speeds that the user can choose from: 2 MHz, 
# 4 MHz, 8 MHz, 16 MHz, F_CPU MHz. These #defines have been added for the user 
# convenience for "freq" parm, else the use the complete frequency.
1. TWO_MHZ
2. FOUR_MHZ
3. EIGHT_MHZ
4. SIXTEEN_MHZ
``` 
```c
void Idle();
# Use this function in any waiting loops such as waiting for Serial data, this 
# will lower the current consumption slightly while having a little impact on 
# performance. This can be used at any CPU speed.
```
```c
void Sleep();
# Most versitle low power mode, any system interrupt will exit this sleep mode. 
# Interrupts must be setup before hand such as attachInterrupt().
```
```c
uint32_t DeepSleep(uint32_t wakeType, uint32_t time_pin, uint16_t threshold = 0, ISR myCallback = defaultCallback);

uint32_t DeepSleep(uint32_t wakeType, uint32_t time_pin, ISR myCallback);

void DeepSleep(sleep_block_t* configuration);
# Lowest current consumption sleep mode without a reset. Only certian digital 
# Pins or Periphereals can wake the cpu from this sleep mode. You will notice 
# that there are three functions, the two top functions are basic usage where 
# second one is just overloaded function. The last one is uses a configuration 
# structure so many wake sources can be configured along with many individual 
# configurations.
```
```c
void Hibernate(uint32_t wakeType, uint32_t time_pin, uint16_t threshold = 0, ISR myCallback = defaultCallback);

void Hibernate(uint32_t wakeType, uint32_t time_pin, ISR myCallback);

void Hibernate(sleep_block_t* configuration);
# Lowest current consumption sleep mode with a reset. Only certian digital 
# Pins or Periphereals can wake the cpu from this sleep mode. You will notice 
# that there are three functions, the two top functions are basic usage where 
# second one is just overloaded function. The last one is uses a configuration 
# structure so many wake sources can be configured along with many individual 
# configurations.
```
```c
void PrintSRS(Stream *port);
# Use this to print what caused the reset of the Teensy. Useful in dubugging.
```
```c
static uint32_t micros();
# 'Port' of the Teensy Core 'micros()' function for use at CPU speeds less than 24MHz.
```
```c
static inline void delay(uint32_t msec);
# 'Port' of the Teensy Core 'delay('time')' function for use lowering the current
# consumption by sleeping for small bit of time while waiting for this delay to 
# timeout. Also use this if you use the 'CPU()' function since recalibrates the 
# delay for whatever cpu speed you are at.
```
```c
static void delayMicroseconds(uint32_t usec);
```
<h4>Examples:</h4>
TODO...
<h4>Pitfalls and Problems:</h4>
TODO...
