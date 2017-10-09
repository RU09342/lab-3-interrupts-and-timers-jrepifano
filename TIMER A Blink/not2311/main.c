#include<msp430.h>
#include<msp430fr2311.h>

#define LEDDIR P1DIR
#define LEDOUT P1OUT
#define LED0 BIT0

int main(void)
{

    PM5CTL0 &= ~LOCKLPM5;

    WDTCTL = WDTPW + WDTHOLD;                // Disable Watchdog Timer
    LEDDIR |= LED0;                           // Set the LED to an output
    TB0CCTL0 = CCIE;                            // CCR0 interrupt enabled
    TBCTL = TBSSEL_2 + MC_2;                 // SMCLK set to continuous mode

    __enable_interrupt();                    // Enables General Interrupt

}


#pragma vector=TIMER0_B0_VECTOR               //Interrupt routine

__interrupt void Timer_B (void)
{

  LEDOUT ^= LED0;                           // Flip LED

}
