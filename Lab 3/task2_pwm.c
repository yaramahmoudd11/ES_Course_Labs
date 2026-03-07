#define IN1  PORTB.F4
#define IN2  PORTB.F5

volatile unsigned bit btn_event ;
volatile unsigned char idx = 0;
 unsigned char duty_table[4] = {64, 128, 191, 255};

void interrupt(void)
{
    if (INTF_bit)
    {
        INTF_bit = 0;
        btn_event = 1;
    }
}
                                                                                A
void main()
{
     btn_event = 0;
    TRISB.F4 = 0;
    TRISB.F5 = 0;
    IN1 = 1;
    IN2 = 0;

    TRISB.F0 = 1;
    OPTION_REG.INTEDG = 0;
    INTF_bit = 0;
    INTE_bit = 1;
    GIE_bit  = 1;

    PWM1_Init(5000);
    PWM1_Start();
    PWM1_Set_Duty(duty_table[idx]);

    while(1)
    {
        if (btn_event)
        {
            Delay_ms(50);

            if (PORTB.F0 == 0)
            {
                idx++;
                if (idx >= 4) idx = 0;

                PWM1_Set_Duty(duty_table[idx]);

                while (PORTB.F0 == 0) { }
            }

            btn_event = 0;
        }
    }
}