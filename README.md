# AVR_Drivers
### This repository contains drivers for the AVR ATmega32 microcontroller. The drivers are divided into three directories:

- MCAL: This directory contains drivers for the AVR ATmega32's Microcontroller Abstraction Layer. It abstracts away the low-level hardware details of the mcu, providing a higher-level interface for working with hardware peripherals. The drivers included in this directory are:

    * ADC
    * GPIO
    * i2C
    * ICU
    * SPI
    * Timer
    * USART
     such as
    
- HAL: This directory contains drivers for the AVR ATmega32's Hardware Abstraction Layer. It provides an even higher-level interface for working with commonly used hardware peripherals. The drivers included in this directory are:

    * Button
    * Buzzer
    * EEPROM
    * Keypad
    * LCD
    * Motors
    * Sensors
    * Seven_Segment
    
    
- Utils: This directory contains commonly used macros and standard types used by the drivers.

Feel free to use these drivers in your AVR ATmega32 projects. If you encounter any issues or have any suggestions, please create an issue on this repository.
