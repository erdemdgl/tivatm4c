#include "stdbool.h"
#include "stdint.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "Lcd.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"

void SetInitSettings();
void format_time(char *buffer, int hour, int minute, int second);
void timerinterruptfunc();

volatile int hour = 0;
volatile int minute = 0;
volatile int second = 0;



int main(void) {

        SetInitSettings();
        Lcd_init();
        Lcd_Goto(1,1);
        Lcd_Puts("Timer with Tiva");

        while(1){}

}

void SetInitSettings(){


        SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); // 50 Mhz

        // Timer settings
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
        TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
        TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());

        // Interrupt settings
        IntMasterEnable();
        IntEnable(INT_TIMER0A);
        TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
        TimerIntRegister(TIMER0_BASE, TIMER_A, timerinterruptfunc);
        TimerEnable(TIMER0_BASE, TIMER_A);


}

void format_time(char *buffer, int hour, int minute, int second) {


        buffer[0] = '0' + (hour / 10);
        buffer[1] = '0' + (hour % 10);
        buffer[2] = ':';
        buffer[3] = '0' + (minute / 10);
        buffer[4] = '0' + (minute % 10);
        buffer[5] = ':';
        buffer[6] = '0' + (second / 10);
        buffer[7] = '0' + (second % 10);
        buffer[8] = '\0';


}

void timerinterruptfunc(){


        TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT); // Clear interrupt flag

        second++;
        if (second == 60) {
            second = 0;
            minute++;
            }
        if (minute == 60) {
            minute = 0;
            hour++;
            }
        if (hour == 24) {
            hour = 0;
            }


        char buffer[9];         // Format time and print on LCD
        format_time(buffer, hour, minute, second);

        Lcd_Goto(2,9);
        Lcd_Puts(buffer);


}
