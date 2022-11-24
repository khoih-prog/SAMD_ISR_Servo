/****************************************************************************************************************************
  SAMD_FastTimerInterrupt.h
  For :
  - SAMD21-based boards such as Nano-33-IoT, SAMD Zero, Seeeduino XIAO, etc.
  - SAMD51-based boards such as Adafruit Itsy-Bitsy M4, Metro M4, Seeeduino WIO-Terminal, etc.

  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/SAMD_ISR_Servo
  Licensed under MIT license

  Based on SimpleTimer - A timer library for Arduino.
  Author: mromani@ottotecnica.com
  Copyright (c) 2010 OTTOTECNICA Italy

  Based on BlynkTimer.h
  Author: Volodymyr Shymanskyy

  Version: 1.1.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      21/08/2021 Initial coding for SAMD21/SAMD51 boards
  1.1.0   K Hoang      09/03/2022 Convert to h-only style. Optimize code
*****************************************************************************************************************************/
/*
  SAMD21

  The Timer/Counter for Control Applications (TCC) module provides a set of timing and counting related functionality, such as the
  generation of periodic waveforms, the capturing of a periodic waveform's frequency/duty cycle, software timekeeping for periodic
  operations, waveform extension control, fault detection etc.
  The counter size of the TCC modules can be 16- or 24-bit depending on the TCC instance

  1) Nano-33-IoT SAMD21G18A
  .arduino15/packages/arduino/tools/CMSIS-Atmel/1.2.0/CMSIS/Device/ATMEL/samd21/include/samd21g18a.h
   #define TC3  ((Tc *)0x42002C00UL)

*/
#pragma once

#ifndef SAMD_FastTimerInterrupt_h
#define SAMD_FastTimerInterrupt_h

#include "SAMD_FastTimerInterrupt.hpp"
#include "SAMD_FastTimerInterrupt_Impl.h"


#endif    // SAMD_FastTimerInterrupt_h
