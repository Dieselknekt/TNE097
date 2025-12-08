#include <msp430g2553.h>

void main(void)
{
    WDTCTL = WDTPW | WDTTMSEL | WDTSSEL | WDTCNTCL | WDTIS0;
    // WDTTMSEL = timer mode, WDTSSEL = SMCLK, WDTIS0 = interval

    IE1 |= WDTIE;              // Enable WDT interrupt

    P1DIR |= BIT0;

    __bis_SR_register(GIE);

    for (;;)
    {
        __no_operation();
    }
}

#pragma vector = WDT_VECTOR
__interrupt void WDT_ISR(void)
{
    P1OUT ^= BIT0;             // toggle P1.0

    /* Different interval settings in main:
    // WDTCTL = WDTPW | WDTTMSEL | WDTSSEL | WDTCNTCL | WDTIS0;
    // WDTCTL = WDTPW | WDTTMSEL | WDTSSEL | WDTCNTCL | WDTIS1;
    // WDTCTL = WDTPW | WDTTMSEL | WDTSSEL | WDTCNTCL | (WDTIS0 | WDTIS1);
    */
}
