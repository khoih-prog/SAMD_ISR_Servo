# SAMD_ISR_Servo Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/SAMD_ISR_Servo.svg?)](https://www.ardu-badge.com/SAMD_ISR_Servo)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/SAMD_ISR_Servo.svg)](https://github.com/khoih-prog/SAMD_ISR_Servo/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/SAMD_ISR_Servo/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/SAMD_ISR_Servo.svg)](http://github.com/khoih-prog/SAMD_ISR_Servo/issues)



<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>
<a href="https://profile-counter.glitch.me/khoih-prog/count.svg" title="Total khoih-prog Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog/count.svg" style="height: 30px;width: 200px;"></a>
<a href="https://profile-counter.glitch.me/khoih-prog-SAMD_ISR_Servo/count.svg" title="SAMD_ISR_Servo Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog-SAMD_ISR_Servo/count.svg" style="height: 30px;width: 200px;"></a>


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
5. Add example [multiFileProject](examples/multiFileProject) to demo for multiple-file project
6. Update examples accordingly
7. Update `Packages' Patches`

### Releases v1.0.0

1. Basic 16 ISR-based servo controllers using 1 hardware timer for SAMD-based board
2. Support to both SAMD21 and SAMD51

