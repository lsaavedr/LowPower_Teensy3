LowPower_Teensy3 Library - Edge
========================
 This is the latest code that should get branched if you want too contribute. Only the latest Teensyduino release will be used. Older versions of Teensyduino may or may not compile and work.
 
<h4>Currently used Teensyduino Version: 1.18</h4> 

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