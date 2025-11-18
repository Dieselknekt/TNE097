#include <msp430g2553.h>

/*
Use Timer_A TACCRx and overflow interrupts to generate independent timing intervals (square
waveforms). Use the following configuration
• TACCR0 and TACCR1 output units are selected with port pins P1.1 and P1.2.
• P1.1 and P1.2 are configured as toggle mode.
• Interrupts are enabled with TACCR0 and TACCR1.
• In the interrupt service routine, the offset is loaded to generate the own defined interval.
• Timer_A overflow ISR is used to toggle P1.0.
• Configure TACCRO and TACCR1 for the following frequencies:
    o P1.1 = ~ 1MHz/(2*200) or ~2500Hz (Toggle on EQU0)
    o P1.2 = ~ 1MHz/(2*1000) or ~500Hz (Toggle on EQU1)
    o P1.0 = overflow ~ 1MHz/(2*65536) ~8Hz
• Check the result in oscilloscope.
 */


 /*
1MHz/2500Hz = 200 ticks,
1MHz/500Hz = 1000 ticks.
1MHz/(2*8Hz) = 62500 ticks (roughly 65536).
Set TACCR0 and TACCR1 to these values respectively, and use overflow for P1.0.
 */
volatile unsigned int offset0 = 200;   // needed for 2500 Hz square wave
volatile unsigned int offset1 = 1000;  // needed for 500 Hz square wave

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog

    P1DIR |= BIT0 | BIT1 | BIT2; // P1.0, P1.1, P1.2 as outputs
    P1OUT &= ~(BIT0 | BIT1 | BIT2); // start all low and defined

    TACCTL0 = CCIE; // CCR0 interrupt enabled
    TACCTL1 = CCIE; // CCR1 interrupt enabled

    // Set initial compare values: schedule first events after `offset` ticks
    TACCR0 = offset0;  // first CCR0 match at TAR == offset0
    TACCR1 = offset1;  // first CCR1 match at TAR == offset1

    // Timer: SMCLK, continuous mode, enable overflow interrupt
    TACTL = TASSEL_2 + MC_2 + TAIE;

    _BIS_SR(LPM0_bits + GIE); // Enter LPM0 with interrupts enabled
}

// CCR0 vector
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    
    P1OUT ^= BIT1;      // Toggle P1.1
    TACCR0 += offset0;  // set next target
}

// CCR1 and overflow vector
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
    switch (TAIV)
    {
    case 2: // CCR1
        P1OUT ^= BIT2;      // Toggle P1.2
        TACCR1 += offset1;  // set next target
        break;
    case 4: // CCR2 (not used)
        break;
    case 10: // Timer overflow (TAIFG)
        P1OUT ^= BIT0; // Toggle P1.0
        break;
    default:
        break;
    }
}
