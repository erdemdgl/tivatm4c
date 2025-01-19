This repository contains various projects and example applications built around the Texas Instruments Tiva C Series TM4C microcontrollers. The projects focus on low-level drivers, peripherals, and communication protocols such as LED control, button inputs, UART, and more.


**FEATURES:**

ARM Cortex-M4: Uses the high-performance TM4C series from Texas Instruments.

Peripheral Drivers: Includes examples of GPIO, UART and ADC.

Documentation & Comments: Source code includes explanations and details within comment blocks.



**REQUIREMENTS:**

Compiler/IDE: TI Code Composer Studio (CCS).

TivaWare: TivaWare for C Series library (provided by TI).

Hardware: Tiva TM4C123G LaunchPad, 2x16 LCD, Breadbord, Potentiometer, USB Cable for connection

Optional: PuTTY and SharpDevelop for UART

**PROJECT FILES:**
1 - Print on LCD: In this projects, lcd.c and lcd.h files has been used for every LCD project. This project show you that can easily print text on LCD.

2 - Timer and LCD: Timer0 has been used for project. Time has been started on 0 and every 1 second LCD screen has been updated with new time.

3 - Timer and UART on LCD: With UART seral communications protocol, start time became adjustable.

4 - Timer, ADC and UART on LCD: Addition to third project,ADC value has been printed on LCD screen.

5 - Hibernate: Hibernate function has been adjusted.

6 - Sleep Modes: Sleep mode function has been adjusted. There is 2 mode, Sleep and Deep Sleep. Sleep mode is a mode in which the processor is stopped, but the peripherals continue to run. Deep Sleep mode saves more energy by stopping both the processor and most peripherals.
