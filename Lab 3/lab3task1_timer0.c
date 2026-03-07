#include "../HAL/LED/LED_interface.h"
#include "../MCAL/GPIO/GPIO_interface.h"

volatile unsigned char ovf = 0;

void interrupt(void)
{
    if (T0IF_bit)
    {
        T0IF_bit = 0;
        TMR0 = 0;
        ovf++;

        // LED2 every ~1 second
        if (ovf % 31 == 0)
            PORTB.F2 = ~PORTB.F2;

        // LED1 every ~2 seconds
        if (ovf >= 62)
        {
            ovf = 0;
            PORTB.F1 = ~PORTB.F1;
        }
    }
}

void main(void)
{
    LED_Init(GPIO_PORTB, GPIO_PIN1);  // LED1 (RB1) ~2s
    LED_Init(GPIO_PORTB, GPIO_PIN2);  // LED2 (RB2) ~1s

    T0CS_bit = 0;
    PSA_bit  = 0;
    PS2_bit  = 1;
    PS1_bit  = 1;
    PS0_bit  = 1;

    TMR0     = 0;
    T0IF_bit = 0;
    T0IE_bit = 1;
    GIE_bit  = 1;

    while(1) { }
}