#include <msp430g2553.h>

volatile unsigned int toggles_left = 0;

// En enkel ms-delay (SMCLK ≈ 1 MHz)
void delay_ms(unsigned int ms)
{
    while (ms--)
    {
        __delay_cycles(1000);   // 1000 cykler ≈ 1 ms vid 1 MHz
    }
}

void playTone(unsigned int freq, unsigned int duration_ms)
{
    // Stoppa timer först
    TA0CTL = MC_0;

    if (freq == 0)
    {
        // Tystnad
        P1OUT &= ~BIT0;
        delay_ms(duration_ms);
        return;
    }

    // Toggle-frekvens = 2 * tonfrekvens (eftersom varje två toggles = 1 period)
    // SMCLK antas 1 MHz
    unsigned int period = 1000000 / (freq * 2);

    TA0CCR0 = period;                 // period för interrupt
    TA0CCTL0 = CCIE;                  // enable CCR0 interrupt
    TA0CTL   = TASSEL_2 | MC_1;       // SMCLK, up-mode

    // Hur många toggles behövs totalt under duration_ms?
    // toggles_per_second = freq * 2
    // toggles_total = toggles_per_second * (duration_ms/1000)
    toggles_left = (freq * 2UL * duration_ms) / 1000UL;

    // Vänta tills ISR räknat ner toggles_left
    while (toggles_left > 0)
        ;

    // Stäng av tonen
    TA0CTL   = MC_0;          // stop timer
    TA0CCTL0 = 0;             // disable interrupt
    P1OUT &= ~BIT0;           // se till att buzzer är låg
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void)
{
    // Toggla P1.0 varje gång timern slår
    P1OUT ^= BIT0;

    if (toggles_left > 0)
        toggles_left--;
}

/* Mario-toner (kort intro) */
#define NOTE_E7  2637
#define NOTE_C7  2093
#define NOTE_G7  3136
#define NOTE_G6  1568

void marioIntro(void)
{
    playTone(NOTE_E7, 125);
    playTone(NOTE_E7, 125);
    playTone(0,       75);

    playTone(NOTE_E7, 125);
    playTone(0,       75);

    playTone(NOTE_C7, 125);
    playTone(NOTE_E7, 125);
    playTone(0,       75);

    playTone(NOTE_G7, 125);
    playTone(0,       150);

    playTone(NOTE_G6, 125);
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog

    P1DIR |= BIT0;              // P1.0 som utgång (buzzer +)
    P1OUT &= ~BIT0;             // börja låg

    __enable_interrupt();       // globalt enable för interrupts

    marioIntro();

    while (1)
    {
        __no_operation();
    }
}
