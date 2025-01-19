# Tiva TM4C Projects

This repository contains various projects and example applications built around the Texas Instruments Tiva C Series TM4C microcontrollers. The projects focus on low-level drivers, peripherals, and communication protocols.

## Features

- **ARM Cortex-M4**: Uses the high-performance TM4C series from Texas Instruments.
- **Peripheral Drivers**: Includes examples of GPIO, UART, and ADC.
- **Documentation & Comments**: Source code includes explanations and details within comment blocks.

## Requirements

- **Compiler/IDE**: TI Code Composer Studio (CCS).
- **TivaWare**: TivaWare for C Series library (provided by TI).
- **Hardware**: Tiva TM4C123G LaunchPad, 2x16 LCD, Breadboard, Potentiometer, USB Cable for connection.
- **Optional**: PuTTY and SharpDevelop for UART.

## Project Files

1. **Print on LCD**: In this project, `lcd.c` and `lcd.h` files are used for every LCD project. This project shows how to easily print text on an LCD.
2. **Timer and LCD**: Timer0 is used for the project. Time starts at 0 and every second the LCD screen is updated with the new time.
3. **Timer and UART on LCD**: With the UART serial communications protocol, the start time becomes adjustable.
4. **Timer, ADC, and UART on LCD**: In addition to the third project, the ADC value is printed on the LCD screen.
5. **Hibernate**: Hibernate function has been implemented.
6. **Sleep Modes**: Sleep mode function has been implemented. There are two modes: Sleep and Deep Sleep. Sleep mode stops the processor but allows peripherals to continue running. Deep Sleep mode stops both the processor and peripherals.

## Getting Started

Follow these steps to set up your environment and run the projects:

1. Install TI Code Composer Studio (CCS).
2. Download and install TivaWare for C Series.
3. Connect the Tiva TM4C123G LaunchPad to your computer using a USB cable.
4. Clone this repository:
   ```sh
   git clone https://github.com/erdemdgl/tivatm4c.git
