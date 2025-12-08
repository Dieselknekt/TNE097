/*
The following code use timer to generate square wave in Lab 2. In this code, the watchdog timer is disabled by the line: WDTCTL = WDTPW + WDTHOLD;
Change the following code so that:
• Enable the watchdog timer
• Configure the watchdog as
  o Watchdog mode
  o WDT clock source from SMCLK
• Find a place to “kick the dog” all the time before the watchdog timer fires and reset the device.


*/

#include <msp430g2553.h>

int a = 0;

void main(void)
{
    //WDTCTRL = WDTPW + WDTHOLD // Stop WDT
    WDTCTL = WDTPW | WDTSSEL | WDTCNTCL;  // Watchdog: watchdog mode, SMCLK, clear counter

    P1DIR |= 0x01;              // P1.0 output

    TACCTL0 = CCIE;             // TACCR0 interrupt enabled
    TACCR0  = 50000;
    TACTL   = TASSEL_2 + MC_1;  // SMCLK, up mode

    __bis_SR_register(GIE); // Global interrupt enable

    for (;;)
    {
      //_BIS_SR(GIE);  
      // Kick the dog before timeout
        WDTCTL = WDTPW | WDTSSEL | WDTCNTCL;
        __no_operation();
    }
}

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    if (a == 10)
      {P1OUT ^= 0x01; a=0;}
    else
        a++;
}
