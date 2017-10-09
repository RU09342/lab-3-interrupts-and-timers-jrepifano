#include <msp430.h>
#include <msp430fr5994.h>

#define LED     BIT0
#define BUTTON  BIT6

int init = 0;
int count = 0;
int overflows = 0;
int n = 0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= LED; // LED Output

    P5DIR &= ~BUTTON; // Button input
    P5REN |= BUTTON; // Enable resistor for button
    P5OUT |= BUTTON; // Set resistor as a pull up

    P5IES |= BUTTON; // Start ISR on button press
    P5IE |= BUTTON; // Enable interrupt for button

    TB0CCTL0 = CCIE;
    TB0CTL = TBSSEL_2 + MC_1 + ID_1; // Divides SMclk by 2 set in up mode
    n = 250000 / 10;
    TB0CCR0 = n; // Will work out to be about 10Hz

    __enable_interrupt();

    __bis_SR_register(LPM0 + GIE); // enable interrupts in LPM0

}

// TIMER ISR
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer_B0(void)
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
#pragma vector = PORT5_VECTOR
__interrupt void PORT_5(void)
{
    init = 1;
    overflows = 0;
    P5IFG &= ~BUTTON; // Clear interrupt flag
}
