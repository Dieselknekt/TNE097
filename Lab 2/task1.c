#include <msp430g2553.h>

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	P1DIR |= 0x01;            // P1.00 output
    P1OUT &= ~0x01;           // Start low and defined

	TACCTL0 = CCIE;           // TA0 CCR0 control: TACCR0 interrupt enabled

	// TACCR0 calculation: TACCR0 = SMCLK / (2 * desired_freq)
    // For 1kHz square wave output: SMLCK / (2 * 1000 Hz) = 1000000 / 2000 => TACCR0 = 500
    // For 10 Hz square wave output: SMLCK / (2 * 10 Hz) = 1000000 / 20 => TACCR0 = 50000
    // For 0.1 Hz square wave, see further below.

	TACCR0 = 500;           // TA0 capture/compare register

	TACTL = TASSEL_2 + MC_1;  // SMCLK, up mode

	_BIS_SR(LPM0_bits + GIE); // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
	P1OUT ^= 0x01;            // Toggle P1.0
}

    // For 0.1 Hz square wave output: SMLCK / (2 * 0.1 Hz) = 1000000 / 0.2 = 50000000
    // Note that 50000000 is outside of range (max 65535) - need to adjust clock or use different method of counting
    // ACLK has a frequency of 32768 Hz
    // If TACCR0 is set to match ACLK with 32768 Hz, it will take one second to reach TACCR0 = 1Hz
    // If we then toggle P1.00 on every interrupt, we get a 0.5 Hz square wave
    // Finally, if we then toggle P1.00 on every 5 interrupts, we get a 0.1 Hz square wave.

/*
Code needed for 0.1 Hz square wave output:
#include <msp430g2553.h>

volatile unsigned int count = 0;

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	P1DIR |= 0x01;            // P1.00 output
    P1OUT &= ~0x01;           // Start low and defined

	TACCTL0 = CCIE;           // TA0 CCR0 control: TACCR0 interrupt enabled

	TACCR0 = 32768;           // TA0 capture/compare register (1Hz interrupts with ACLK )

	TACTL = TASSEL_1 + MC_1;  // CHANGED: ACLK, up mode

	_BIS_SR(LPM3_bits + GIE); // Enter LPM3 (active ACLK) w/ interrupt
}

// Timer A0 interrupt service routine
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
	// Toggle only every 5 interrupts: toggle rate = 1 / 5 Hz = 0.2 Hz
	// both rising and falling edge = toggle_rate / 2 = 0.1 Hz
	count++;
    if (count >= 5) {
		count = 0;
		P1OUT ^= 0x01; // Toggle P1.0
	}
}

*/