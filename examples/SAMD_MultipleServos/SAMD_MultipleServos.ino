/****************************************************************************************************************************
  SAMD_MultipleServos.ino
  For :
  - SAMD21-based boards such as Nano-33-IoT, SAMD Zero, Seeeduino XIAO, etc.
  - SAMD51-based boards such as Adafruit Itsy-Bitsy M4, Metro M4, Seeeduino WIO-Terminal, etc.
  
  Written by Khoi Hoang

  Built by Khoi Hoang https://github.com/khoih-prog/SAMD_ISR_Servo
  Licensed under MIT license
*****************************************************************************************************************************/

/****************************************************************************************************************************
   From ESP32 Servo Example Using Arduino ESP32 Servo Library
   John K. Bennett
   March, 2017

   Different servos require different pulse widths to vary servo angle, but the range is
   an approximately 500-2500 microsecond pulse every 20ms (50Hz). In general, hobbyist servos
   sweep 180 degrees, so the lowest number in the published range for a particular servo
   represents an angle of 0 degrees, the middle of the range represents 90 degrees, and the top
   of the range represents 180 degrees. So for example, if the range is 1000us to 2000us,
   1000us would equal an angle of 0, 1500us would equal 90 degrees, and 2000us would equal 1800
   degrees.

   - Circuit:
   Servo motors have three wires: power, ground, and signal. The power wire is typically red,
   the ground wire is typically black or brown, and the signal wire is typically yellow,
   orange or white. Since the SAMD can supply limited current at only 3.3V, and servos draw
   considerable power, we will connect servo power to the VBat pin of the SAMD (located
   near the USB connector). THIS IS ONLY APPROPRIATE FOR SMALL SERVOS.

   We could also connect servo power to a separate external power source (as long as we connect all of 
   the grounds (SAMD, servo, and external power).
   In this example, we just connect SAMD ground to servo ground. The servo signal pins
   connect to any available GPIO pins on the SAMD (in this example, we use pins (D1-D6).

   In this example, we assume four Tower Pro SG90 small servos.
   The published min and max for this servo are 500 and 2400, respectively.
   These values actually drive the servos a little past 0 and 180, so
   if you are particular, adjust the min and max values to match your needs.
   Experimentally, 800 and 2450 are pretty close to 0 and 180.
*****************************************************************************************************************************/

#if !( defined(ARDUINO_SAMD_ZERO) || defined(ARDUINO_SAMD_MKR1000) || defined(ARDUINO_SAMD_MKRWIFI1010) \
      || defined(ARDUINO_SAMD_NANO_33_IOT) || defined(ARDUINO_SAMD_MKRFox1200) || defined(ARDUINO_SAMD_MKRWAN1300) || defined(ARDUINO_SAMD_MKRWAN1310) \
      || defined(ARDUINO_SAMD_MKRGSM1400) || defined(ARDUINO_SAMD_MKRNB1500) || defined(ARDUINO_SAMD_MKRVIDOR4000) \
      || defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS) || defined(__SAMD51__) || defined(__SAMD51J20A__) \
      || defined(__SAMD51J19A__) || defined(__SAMD51G19A__) || defined(__SAMD51P19A__)  \
      || defined(__SAMD21E15A__) || defined(__SAMD21E16A__) || defined(__SAMD21E17A__) || defined(__SAMD21E18A__) \
      || defined(__SAMD21G15A__) || defined(__SAMD21G16A__) || defined(__SAMD21G17A__) || defined(__SAMD21G18A__) \
      || defined(__SAMD21J15A__) || defined(__SAMD21J16A__) || defined(__SAMD21J17A__) || defined(__SAMD21J18A__) )
  #error This code is designed to run on SAMD21/SAMD51 platform! Please check your Tools->Board setting.
#endif

#define ISR_SERVO_DEBUG             2

// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "SAMD_ISR_Servo.h"

// TIMER_TC3 for SAMD51, TIMER_TC3/TIMER_TCC for SAMD21
#define USING_SAMD_TIMER            TIMER_TC3

// Published values for SG90 servos; adjust if needed
#define MIN_MICROS        800
#define MAX_MICROS        2450

#define SERVO_PIN_1       A0
#define SERVO_PIN_2       A1
#define SERVO_PIN_3       A2
#define SERVO_PIN_4       A3
#define SERVO_PIN_5       A4
#define SERVO_PIN_6       A5

typedef struct
{
  int     servoIndex;
  uint8_t servoPin;
} ISR_servo_t;

#define NUM_SERVOS            6

ISR_servo_t ISR_servo[] =
{
  { -1, SERVO_PIN_1 }, { -1, SERVO_PIN_2 }, { -1, SERVO_PIN_3 }, { -1, SERVO_PIN_4 }, { -1, SERVO_PIN_5 }, { -1, SERVO_PIN_6 }
};

void setup()
{
  for (int index = 0; index < NUM_SERVOS; index++)
  {
    pinMode(ISR_servo[index].servoPin, OUTPUT);
    digitalWrite(ISR_servo[index].servoPin, LOW);
  }
  
  Serial.begin(115200);
  while (!Serial);

  delay(200);

  Serial.print(F("\nStarting SAMD_MultipleServos on ")); Serial.println(BOARD_NAME);
  Serial.println(SAMD_ISR_SERVO_VERSION);

  // SAMD51 always uses TIMER_TC3
  SAMD_ISR_Servos.useTimer(USING_SAMD_TIMER);
  
  for (int index = 0; index < NUM_SERVOS; index++)
  {
    ISR_servo[index].servoIndex = SAMD_ISR_Servos.setupServo(ISR_servo[index].servoPin, MIN_MICROS, MAX_MICROS);

    if (ISR_servo[index].servoIndex != -1)
    {
      Serial.print(F("Setup OK, Servo index = ")); Serial.println(ISR_servo[index].servoIndex);
    }
    else
    {
      Serial.print(F("Setup Failed, Servo index = ")); Serial.println(ISR_servo[index].servoIndex);
    }
  }

  SAMD_ISR_Servos.setReadyToRun();
}

void loop()
{
  int position;      // position in degrees

  for (position = 0; position <= 180; position += 10)
  {
    // goes from 0 degrees to 180 degrees
    // in steps of 10 degree
    for (int index = 0; index < NUM_SERVOS; index++)
    {
      SAMD_ISR_Servos.setPosition(ISR_servo[index].servoIndex, position);
    }
    
    // waits 1s for the servo to reach the position
    delay(1000);
  }

  delay(5000);
}
