#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/hibernate.h"

int main(void){


        SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE); // peripheral unit active
        // we are using an m4 with a hibernation module

        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4); //pin0 and pin4 input
        GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU); // pin0 ve pin4 pull-up

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0); //led not lit


        HibernateEnableExpClk(SysCtlClockGet()); // first function
        // purpose is wake from sleep with wake-up pin
        HibernateGPIORetentionEnable(); // helps maintain pin states when waking up from sleep mode

        HibernateRTCSet(0);//Sets the value of the real time clock (RTC) counter.
        HibernateRTCEnable();
        HibernateRTCMatchSet(0, 5); // counter 5, 5 second when it arrives

        // floating point for 1 hour
        // mermory pwm
        // dma

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,2); //led lits
        SysCtlDelay(50000000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0);
        HibernateWakeSet(HIBERNATE_WAKE_PIN|HIBERNATE_WAKE_RTC); // wake-up unit
        // pf0 is wake-up pin

        HibernateRequest(); // sleep
        while(1){

        }


}
