#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.c"

void SetInitSettings();

void externalinterrupt(void){

        int a=GPIOIntStatus(GPIO_PORTF_BASE, true); // pin control

        if(a==16) // pf4 has been pressed
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,2);
            SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_TIMER0);
        }

        else if (a==1) // pf0 has been pressed
        {
            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,4);
            SysCtlPeripheralSleepDisable(SYSCTL_PERIPH_TIMER0);
        }


        GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);

}


int main(void){

        SetInitSettings();

        while(1){}
}


void SetInitSettings(){

        SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // with no api, SYSCTL_RCGCGPIO_R|=0x20;
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // pin 1-2-3 is output


        HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
        HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01; // for unlock pf4 and pf0

        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4); // pf0 and pf4 input
        GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);// pull up

        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0); //leds closed

        // 5 function for interrupt, 2 of them are global and 3 of them are local

        IntMasterEnable();
        IntEnable(INT_GPIOF);

        GPIOIntTypeSet(GPIO_PORTF_BASE,GPIO_PIN_0|GPIO_PIN_4, GPIO_FALLING_EDGE); // falling edge interrupt
        GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
        GPIOIntRegister(GPIO_PORTF_BASE, externalinterrupt);

        //SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_GPIOF);
        //SysCtlSleepPowerSet(SYSCTL_FLASH_LOW_POWER|SYSCTL_SRAM_LOW_POWER);
        //SysCtlPeripheralClockGating(true);
        //SysCtlSleep();

        SysCtlDeepSleepClockSet(SYSCTL_DSLP_OSC_MAIN|SYSCTL_DSLP_DIV_1);
        SysCtlPeripheralDeepSleepEnable(SYSCTL_PERIPH_GPIOF);
        SysCtlPeripheralClockGating(true);
        SysCtlDeepSleep();

}

