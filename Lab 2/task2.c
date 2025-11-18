#include <msp430g2553.h>

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	P1DIR |= 0x01;            // P1.0 output
	P1OUT &= ~0x01;           // Start low

	// We have 0.95 Hz and need around 1.9Hz. To do this we use CCR1 compare interrupt. 
    // this gives us an an extra toggle halfway through the timer range - 
    // we get twice as many toggles per overflow.
	TACCTL1 = CCIE;          // ADDED: Enable CCR1 interrupt
	TACCR1  = 0x8000;        // Compare at half of 16-bit timer range

	// SMCLK, continuous mode, enable overflow interrupt, divide by 8
	TACTL = TASSEL_2 + MC_2 + TAIE + ID_3;

	_BIS_SR(LPM0_bits + GIE); // Enter LPM0 w/ interrupt
}

// Timer_A Interrupt Vector (TAIV) handler
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A(void)
{
	switch (TAIV)
	{
	case 2:                // TACCR1
		P1OUT ^= 0x01;     // Toggle P1.0 on CCR1 compare
		break;
	case 4:                
		break;
	case 10:               // Timer overflow
		P1OUT ^= 0x01;     // Toggle P1.0 on overflow
		break;
	}
}
