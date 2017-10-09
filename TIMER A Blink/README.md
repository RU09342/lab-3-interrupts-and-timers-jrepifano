# TIMER A Blink
In my implementation of the code, I have the timer in continuous mode. Each time the counter overflows back down to 0, the LED is toggled.

Below is the code for the G2553:

#include<msp430.h>

#define LEDDIR P1DIR
#define LEDOUT P1OUT
#define LED0 BIT0

int main(void)
{

    WDTCTL = WDTPW + WDTHOLD;                // Disable Watchdog Timer
    LEDDIR |= LED0;                           // Set the LED to an output
    CCTL0 = CCIE;                            // CCR0 interrupt enabled
    TACTL = TASSEL_2 + MC_2;                 // SMCLK set to continuous mode

    __enable_interrupt();                    // Enables General Interrupt

}


#pragma vector=TIMER0_A0_VECTOR               //Interrupt routine

__interrupt void Timer_A (void)
{

  LEDOUT ^= LED0;                           // Flip LED

}
