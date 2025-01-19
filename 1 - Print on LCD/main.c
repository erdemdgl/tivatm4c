#include "stdbool.h"
#include "stdint.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "Lcd.h"

int main(void) {

        SysCtlClockSet(
                        SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ
                        | SYSCTL_OSC_MAIN); //50 MHz

        Lcd_init();
        Lcd_Goto(1,1);
        Lcd_Puts("Tiva TM4C");
        Lcd_Goto(2,1);
        Lcd_Puts("New Start");
        Lcd_Goto(2,15);
        Lcd_Puts("ED");

        while (1) {

        }
}
