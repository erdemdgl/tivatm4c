#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include <string.h>
#include <stdio.h>
#include "driverlib/timer.h"
#include "inc/hw_ints.h"
#include "Lcd.h"
#include "driverlib/adc.h"

// Global variables

char clock[9] = "00:00:00";     // Start time
bool newclock = false;          // Has the new time information been sent?
bool updateclock = true;        // Should the clock be constantly updated
uint32_t adcValue = 0;

void updateLCD();
void initSystem();


int main(void) {

    initSystem();

    while (1) {}
}


void UART0Handler(void) {

        UARTIntClear(UART0_BASE, UART_INT_RX | UART_INT_RT);

        static char buffer[16]; // buffer for commands and clock data
        static int index = 0;


        while (UARTCharsAvail(UART0_BASE)) {
            char receivedChar = UARTCharGet(UART0_BASE);

            if (receivedChar == '\n') {
                buffer[index] = '\0'; // Add null-terminator
                index = 0;


                if (strcmp(buffer, "RESET_SYSTEM") == 0) {
                LCDTemizle();
                strcpy(clock, "00:00:00");
                newclock = false;
                updateclock = true;
                adcValue = 0;
                }


                else if (strlen(buffer) == 8 && buffer[2] == ':' && buffer[5] == ':') {
                strcpy(clock, buffer);
                newclock = true;
                updateclock = true;
                }
                }
            else {
                if (index < sizeof(buffer) - 1) {
                buffer[index++] = receivedChar;
                }
                }
            }
}


void sendTimeandAdc() {

        TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Clear interrupt flag
        char buffer[16];
        int i;

        ADCProcessorTrigger(ADC0_BASE, 3);
        while (!ADCIntStatus(ADC0_BASE, 3, false)) {}
        ADCIntClear(ADC0_BASE, 3);
        ADCSequenceDataGet(ADC0_BASE, 3, &adcValue);

        snprintf(buffer, sizeof(buffer), "Time:%s ADC:%03d\n", clock,adcValue); // Send clock to computer through UART

        for (i = 0; buffer[i] != '\0'; i++) {
            UARTCharPut(UART0_BASE, buffer[i]);
            }


        if (newclock) { // If new time information is received, start the clock from scratch
            newclock = false;
            }

        else if (updateclock) {

            int hour, min, sec;
            sscanf(clock, "%2d:%2d:%2d", &hour, &min, &sec);

            sec++;
            if (sec == 60)
                { sec = 0; min++; }
            if (min == 60)
                { min = 0; hour++; }
            if (hour == 24)
                { hour = 0; }

            snprintf(clock, sizeof(clock), "%02d:%02d:%02d", hour, min, sec);
            }

        updateLCD();
}


void updateLCD() {

        char buffer[16];

        LCDgit(0, 0); // First row and column
        lcdyaz("UART-ADC");

        LCDgit(1, 0); // Second row, first column
        snprintf(buffer, sizeof(buffer), "T:%04d", adcValue); // ADC value, 4 digits
        lcdyaz(buffer);

        LCDgit(1, 8); // Second row, eighth column
        lcdyaz(clock);
}


void initSystem() {

        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); // 50 Mhz

        // Timer settings
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
        TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
        TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());

        // Interrupt settings
        IntMasterEnable();
        IntEnable(INT_TIMER0A);
        TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
        TimerIntRegister(TIMER0_BASE, TIMER_A, sendTimeandAdc);
        TimerEnable(TIMER0_BASE, TIMER_A);


        // UART Settings
        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        GPIOPinConfigure(GPIO_PA0_U0RX); // RX Pin
        GPIOPinConfigure(GPIO_PA1_U0TX); // TX Pin
        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
        UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
        UARTIntRegister(UART0_BASE, UART0Handler);
        UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
        IntMasterEnable();


        SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
        ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
        ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
        ADCSequenceEnable(ADC0_BASE, 3);
        ADCIntClear(ADC0_BASE, 3);


        // LCD settings
        LCDilkayarlar();
        LCDTemizle();
}
