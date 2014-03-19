/**********************************************************
 *  ** NOTICE!!! You must make IntervalTimer class "Private"
 *  ** members "Protected" members. Then uncomment 
 *  ** IntervalTimer_LP class in LowPower_Teensy3.h file.
 *
 *  Puts the processor into Wait (VLPW) mode aka... Sleep.
 *  All system interrupts will exit this sleep mode. 
 *
 *  This example puts the CPU at 2MHz then uses LowPower_Teensy3 
 *  IntervalTimer_LP port to wake the processor from Sleep mode.
 *  Serial1 is also reconfigured to work at 2MHz using the
 *  HardwareSerial_LP class.
 *
 *  Tested and compiled under Arduino 1.0.5 and 
 *  Teensyduino 1.18
 *********************************************************/
#include <LowPower_Teensy3.h>
#include <Time.h> 

uint16_t threshold;
long blinkRate = 500000;

TEENSY3_LP LP = TEENSY3_LP();
HardwareSerial_LP Uart_lp = HardwareSerial_LP();
IntervalTimer_LP timer_lp;

void intervalTimerCallback() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  LP.CPU(TWO_MHZ);
  Uart_lp.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Uart_lp.print("Sleep Advanced \n");
  Uart_lp.flush();
  /*****************************************************
   * Setup IntervalTimer to wake from Sleep mode.
   *****************************************************/
  timer_lp.begin(intervalTimerCallback, blinkRate);
}

void loop() {
  /*****************************************************
   * Sleep for 5 secs
   *****************************************************/
  LP.Sleep();
  Uart_lp.println("Wakey Wakey");
  Uart_lp.flush();
}