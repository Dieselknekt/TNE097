#include <msp430g2553.h>

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	P1DIR |= 0x01;            // P1.0 output
	P1OUT &= ~0x01;           // start low , defined
    // for 20 Hz square wave output:
    // TACCR0 = SMCLK / (2 * 20 Hz) = 1000000 / 40 = 25000
	TACCTL0 = CCIE;           // Enable TACCR0 interrupt
	TACCR0  = 25000;          // First compare at 25000 ticks

	TACTL = TASSEL_2 + MC_2;  // SMCLK, continuous mode

	_BIS_SR(LPM0_bits + GIE); // Enter LPM0 with interrupts enabled
}

// CCR0 has its own interrupt vector
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
	P1OUT ^= 0x01;            // Toggle P1.0
	TACCR0 += 25000;          // increase TACCR0 by 25000 for next interrupt
}

