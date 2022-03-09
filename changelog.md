# SAMD_ISR_Servo Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/SAMD_ISR_Servo.svg?)](https://www.ardu-badge.com/SAMD_ISR_Servo)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/SAMD_ISR_Servo.svg)](https://github.com/khoih-prog/SAMD_ISR_Servo/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/SAMD_ISR_Servo/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/SAMD_ISR_Servo.svg)](http://github.com/khoih-prog/SAMD_ISR_Servo/issues)


---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v1.1.0](#releases-v110)
  * [Releases v1.0.0](#releases-v100)

 
---
---

## Changelog

### Releases v1.1.0

1. Convert to h-only style.
2. Optimize library code by using `reference-passing` instead of `value-passing`
3. Display informational warning only when `ISR_SERVO_DEBUG` > 1
4. Add support to many more boards, such as `SAMD21E1xA`, `SAMD21G1xA` and`SAMD21J1xA`
5. Update examples accordingly
6. Update `Packages' Patches`

### Releases v1.0.0

1. Basic 16 ISR-based servo controllers using 1 hardware timer for SAMD-based board
2. Support to both SAMD21 and SAMD51
