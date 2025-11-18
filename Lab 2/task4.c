#include <msp430g2553.h>

/*
 * Task 4
 * Generate independent square waves using Timer_A CCR0, CCR1 and overflow.
 *
 * - P1.1 toggled in CCR0 ISR with offset = 200 ticks ->
 *     toggles/sec = SMCLK / 200 = 1e6 / 200 = 5000 toggles/s -> 2500 Hz square wave
 * - P1.2 toggled in CCR1 ISR with offset = 1000 ticks ->
 *     toggles/sec = SMCLK / 1000 = 1000 toggles/s -> 500 Hz square wave
 * - P1.0 toggled in Timer overflow ISR ->
 *     overflow rate = SMCLK / 65536 = 1e6 / 65536 ~= 15.258 overflows/s ->
 *     toggles/sec = 15.258 -> square wave = 15.258/2 ~= 7.629 Hz (~8 Hz)
 *
 * This file implements the continuous-mode + CCRx += offset pattern so each channel
 * keeps its own timing interval independent of the others.
 */

volatile unsigned int offset0 = 200;   // CCR0 offset (ticks) -> 2500 Hz square wave
volatile unsigned int offset1 = 1000;  // CCR1 offset (ticks) -> 500 Hz square wave

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog

    // Configure outputs
    P1DIR |= BIT0 | BIT1 | BIT2; // P1.0, P1.1, P1.2 as outputs
    P1OUT &= ~(BIT0 | BIT1 | BIT2); // start all low

    // Configure CCR interrupts (we will toggle the pins in software in ISRs)
    TACCTL0 = CCIE; // CCR0 interrupt enabled
    TACCTL1 = CCIE; // CCR1 interrupt enabled

    // Set initial compare values: schedule first events after `offset` ticks
    TACCR0 = offset0;  // first CCR0 match at TAR == offset0
    TACCR1 = offset1;  // first CCR1 match at TAR == offset1

    // Timer: SMCLK, continuous mode, enable overflow interrupt
    TACTL = TASSEL_2 + MC_2 + TAIE;

    _BIS_SR(LPM0_bits + GIE); // Enter LPM0 with interrupts enabled
}

// CCR0 has its own vector (fast handler)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    // Toggle P1.1 and schedule next event
    P1OUT ^= BIT1;      // Toggle P1.1
    TACCR0 += offset0;  // schedule next compare
}

// CCR1 and overflow share the A1 vector — dispatch using TAIV
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer_A1(void)
{
    switch (TAIV)
    {
    case 2: // CCR1
        P1OUT ^= BIT2;      // Toggle P1.2
        TACCR1 += offset1;  // schedule next compare
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
