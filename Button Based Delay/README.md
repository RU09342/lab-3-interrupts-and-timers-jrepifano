# Button Based Delay
My implementation of the button based delay was a little half assed. Instead of using another capture compare register, I just compared overflows.
The timer is set to continous mode, when the button is pressed down it counts how many times it overflows.
When the button is released it toggles the LEDs for the amount of overflows that occured while the button was pressed down.

I worked with Damon Boorstein and Brenden Nugent on this one, I had issues getting the clock frequency correct with dividing and all that.

Below is the commented code for the G2553:

#include <msp430.h>
#include <msp430g2553.h>

#define LED     BIT0
#define BUTTON  BIT3

int init = 0;
int count = 0;
int overflows = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    P1DIR |= LED; // LED Output

    P1DIR &= ~BUTTON; // Button input
    P1REN |= BUTTON; // Enable resistor for button
    P1OUT |= BUTTON; // Set resistor as a pull up

    P1IES |= BUTTON; // Start ISR on button press
    P1IE |= BUTTON; // Enable interrupt for button

    TA0CCTL0 = CCIE;
    TA0CTL = TASSEL_2 + MC_1 + ID_1; // Divides SMclk by 2 set in up mode
    TA0CCR0 = 250000 / 10; // Will work out to be about 10Hz

    __enable_interrupt();

    __bis_SR_register(LPM0 + GIE); // enable interrupts in LPM0

}

// TIMER ISR
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    if (init > 0)
    {
        if (P1IN & BUTTON) // if button isnt pressed clear variables
        {
            init = 0;
            count = 0;
        }

        else    // count how many interrupt cycles there are while the button is pressed down
        {
            P1OUT |= LED;
            overflows++;
        }


    }

    else //now while the button isnt pressed down start another counter
    {
        if (count == overflows) // when the two counts equal each other flip the LED
        {
            P1OUT ^= LED;
            count = 0;
        }

        else
            count++;
    }
}

// Button ISR
#pragma vector = PORT1_VECTOR
__interrupt void PORT_1(void)
{
    init = 1;
    overflows = 0;
    P1IFG &= ~BUTTON; // Clear interrupt flag
}
