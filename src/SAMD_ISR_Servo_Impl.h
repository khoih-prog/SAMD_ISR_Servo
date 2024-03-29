/****************************************************************************************************************************
  SAMD_ISR_Servo_Impl.h
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

#pragma once

#ifndef SAMD_ISR_Servo_Impl_HPP
#define SAMD_ISR_Servo_Impl_HPP

//#include "SAMD_ISR_Servo.h"
#include <string.h>

#ifndef ISR_SERVO_DEBUG
  #define ISR_SERVO_DEBUG               1
#endif

#define DEFAULT_SAMD_TIMER_NO           TIMER_TC3       // TIMER_TC3 for many boards

static SAMD_ISR_Servo SAMD_ISR_Servos;  // create servo object to control up to 16 servos

//////////////////////////////////////////////////

void SAMD_ISR_Servo_Handler()
{
  SAMD_ISR_Servos.run();
}

//////////////////////////////////////////////////

SAMD_ISR_Servo::SAMD_ISR_Servo()
  : numServos (-1), _timerNo(DEFAULT_SAMD_TIMER_NO)
{
}

//////////////////////////////////////////////////

void SAMD_ISR_Servo::run()
{
  static int servoIndex;

  for (servoIndex = 0; servoIndex < MAX_SERVOS; servoIndex++)
  {
    if ( servo[servoIndex].enabled  && (servo[servoIndex].pin <= SAMD_MAX_PIN) )
    {
      if ( timerCount == servo[servoIndex].count )
      {
        // PWM to LOW, will be HIGH again when timerCount = 1
        digitalWrite(servo[servoIndex].pin, LOW);
      }
      else if (timerCount == 1)
      {
        // PWM to HIGH, will be LOW again when timerCount = servo[servoIndex].count
        digitalWrite(servo[servoIndex].pin, HIGH);
      }
    }
  }

  // Reset when reaching 20000us / 10us = 2000
  if (timerCount++ >= REFRESH_INTERVAL / TIMER_INTERVAL_MICRO)
  {
    timerCount = 1;
  }
}

//////////////////////////////////////////////////

// find the first available slot
// return -1 if none found
int8_t SAMD_ISR_Servo::findFirstFreeSlot()
{
  // all slots are used
  if (numServos >= MAX_SERVOS)
    return -1;

  // return the first slot with no count (i.e. free)
  for (int servoIndex = 0; servoIndex < MAX_SERVOS; servoIndex++)
  {
    if (servo[servoIndex].enabled == false)
    {
      ISR_SERVO_LOGDEBUG1("Index =", servoIndex);

      return servoIndex;
    }
  }

  // no free slots found
  return -1;
}

//////////////////////////////////////////////////

int8_t SAMD_ISR_Servo::setupServo(const uint8_t& pin, const uint16_t& min, const uint16_t& max)
{
  int servoIndex;

  if (pin > SAMD_MAX_PIN)
    return -1;

  if (numServos < 0)
    init();

  servoIndex = findFirstFreeSlot();

  if (servoIndex < 0)
    return -1;

  pinMode(pin, OUTPUT);

  servo[servoIndex].pin        = pin;
  servo[servoIndex].min        = min;
  servo[servoIndex].max        = max;
  servo[servoIndex].count      = min / TIMER_INTERVAL_MICRO;
  servo[servoIndex].position   = 0;
  servo[servoIndex].enabled    = true;

  numServos++;

  ISR_SERVO_LOGDEBUG3("Index =", servoIndex, ", count =", servo[servoIndex].count);
  ISR_SERVO_LOGDEBUG3("min =", servo[servoIndex].min, ", max =", servo[servoIndex].max);

  return servoIndex;
}

//////////////////////////////////////////////////

bool SAMD_ISR_Servo::setPosition(const uint8_t& servoIndex, const uint16_t& position)
{
  if (servoIndex >= MAX_SERVOS)
    return false;

  // Updates interval of existing specified servo
  if ( servo[servoIndex].enabled && (servo[servoIndex].pin <= SAMD_MAX_PIN) )
  {
    servo[servoIndex].position  = position;
    servo[servoIndex].count     = map(position, 0, 180, servo[servoIndex].min,
                                      servo[servoIndex].max) / TIMER_INTERVAL_MICRO;

    ISR_SERVO_LOGDEBUG1("Idx =", servoIndex);
    ISR_SERVO_LOGDEBUG3("cnt =", servo[servoIndex].count, ", pos =", servo[servoIndex].position);

    return true;
  }

  // false return for non-used numServo or bad pin
  return false;
}

//////////////////////////////////////////////////

// returns last position in degrees if success, or -1 on wrong servoIndex
int SAMD_ISR_Servo::getPosition(const uint8_t& servoIndex)
{
  if (servoIndex >= MAX_SERVOS)
    return -1;

  // Updates interval of existing specified servo
  if ( servo[servoIndex].enabled && (servo[servoIndex].pin <= SAMD_MAX_PIN) )
  {
    ISR_SERVO_LOGERROR1("Idx =", servoIndex);
    ISR_SERVO_LOGERROR3("cnt =", servo[servoIndex].count, ", pos =", servo[servoIndex].position);

    return (servo[servoIndex].position);
  }

  // return 0 for non-used numServo or bad pin
  return -1;
}

//////////////////////////////////////////////////

// setPulseWidth will set servo PWM Pulse Width in microseconds, correcponding to certain position in degrees
// by using PWM, turn HIGH 'pulseWidth' microseconds within REFRESH_INTERVAL (20000us)
// min and max for each individual servo are enforced
// returns true on success or -1 on wrong servoIndex
bool SAMD_ISR_Servo::setPulseWidth(const uint8_t& servoIndex, uint16_t& pulseWidth)
{
  if (servoIndex >= MAX_SERVOS)
    return false;

  // Updates interval of existing specified servo
  if ( servo[servoIndex].enabled && (servo[servoIndex].pin <= SAMD_MAX_PIN) )
  {
    if (pulseWidth < servo[servoIndex].min)
      pulseWidth = servo[servoIndex].min;
    else if (pulseWidth > servo[servoIndex].max)
      pulseWidth = servo[servoIndex].max;

    servo[servoIndex].count     = pulseWidth / TIMER_INTERVAL_MICRO;
    servo[servoIndex].position  = map(pulseWidth, servo[servoIndex].min, servo[servoIndex].max, 0, 180);

    ISR_SERVO_LOGERROR1("Idx =", servoIndex);
    ISR_SERVO_LOGERROR3("cnt =", servo[servoIndex].count, ", pos =", servo[servoIndex].position);

    return true;
  }

  // false return for non-used numServo or bad pin
  return false;
}

//////////////////////////////////////////////////

// returns pulseWidth in microsecs (within min/max range) if success, or 0 on wrong servoIndex
uint16_t SAMD_ISR_Servo::getPulseWidth(const uint8_t& servoIndex)
{
  if (servoIndex >= MAX_SERVOS)
    return 0;

  // Updates interval of existing specified servo
  if ( servo[servoIndex].enabled && (servo[servoIndex].pin <= SAMD_MAX_PIN) )
  {
    ISR_SERVO_LOGERROR1("Idx =", servoIndex);
    ISR_SERVO_LOGERROR3("cnt =", servo[servoIndex].count, ", pos =", servo[servoIndex].position);

    return (servo[servoIndex].count * TIMER_INTERVAL_MICRO );
  }

  // return 0 for non-used numServo or bad pin
  return 0;
}

//////////////////////////////////////////////////

void SAMD_ISR_Servo::deleteServo(const uint8_t& servoIndex)
{
  if ( (numServos == 0) || (servoIndex >= MAX_SERVOS) )
  {
    return;
  }

  // don't decrease the number of servos if the specified slot is already empty
  if (servo[servoIndex].enabled)
  {
    memset((void*) &servo[servoIndex], 0, sizeof (servo_t));

    servo[servoIndex].enabled   = false;
    servo[servoIndex].position  = 0;
    servo[servoIndex].count     = 0;
    // Intentional bad pin, good only from 0-16 for Digital, A0=17
    servo[servoIndex].pin       = SAMD_WRONG_PIN;

    // update number of servos
    numServos--;
  }
}

//////////////////////////////////////////////////

bool SAMD_ISR_Servo::isEnabled(const uint8_t& servoIndex)
{
  if (servoIndex >= MAX_SERVOS)
    return false;

  if (servo[servoIndex].pin > SAMD_MAX_PIN)
  {
    // Disable if something wrong
    servo[servoIndex].pin     = SAMD_WRONG_PIN;
    servo[servoIndex].enabled = false;
    return false;
  }

  return servo[servoIndex].enabled;
}

//////////////////////////////////////////////////

bool SAMD_ISR_Servo::enable(const uint8_t& servoIndex)
{
  if (servoIndex >= MAX_SERVOS)
    return false;

  if (servo[servoIndex].pin > SAMD_MAX_PIN)
  {
    // Disable if something wrong
    servo[servoIndex].pin     = SAMD_WRONG_PIN;
    servo[servoIndex].enabled = false;
    return false;
  }

  if ( servo[servoIndex].count >= servo[servoIndex].min / TIMER_INTERVAL_MICRO )
    servo[servoIndex].enabled = true;

  return true;
}

//////////////////////////////////////////////////

bool SAMD_ISR_Servo::disable(const uint8_t& servoIndex)
{
  if (servoIndex >= MAX_SERVOS)
    return false;

  if (servo[servoIndex].pin > SAMD_MAX_PIN)
    servo[servoIndex].pin     = SAMD_WRONG_PIN;

  servo[servoIndex].enabled = false;

  return true;
}

//////////////////////////////////////////////////

void SAMD_ISR_Servo::enableAll()
{
  // Enable all servos with a enabled and count != 0 (has PWM) and good pin

  for (int servoIndex = 0; servoIndex < MAX_SERVOS; servoIndex++)
  {
    if ( (servo[servoIndex].count >= servo[servoIndex].min / TIMER_INTERVAL_MICRO ) && !servo[servoIndex].enabled
         && (servo[servoIndex].pin <= SAMD_MAX_PIN) )
    {
      servo[servoIndex].enabled = true;
    }
  }
}

//////////////////////////////////////////////////

void SAMD_ISR_Servo::disableAll()
{
  // Disable all servos
  for (int servoIndex = 0; servoIndex < MAX_SERVOS; servoIndex++)
  {
    servo[servoIndex].enabled = false;
  }
}

//////////////////////////////////////////////////

bool SAMD_ISR_Servo::toggle(const uint8_t& servoIndex)
{
  if (servoIndex >= MAX_SERVOS)
    return false;

  servo[servoIndex].enabled = !servo[servoIndex].enabled;

  return true;
}

//////////////////////////////////////////////////

int8_t SAMD_ISR_Servo::getNumServos()
{
  return numServos;
}

#endif  // SAMD_ISR_Servo_Impl_HPP
