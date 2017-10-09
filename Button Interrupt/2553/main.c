#include <msp430.h> 

int blahh = 0; //variable to keep track of button interrupts

void main(void)
{
WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer


P1DIR |= (BIT0 + BIT6); // Set LEDS as outputs
P1OUT &= ~(BIT0 + BIT6); // Initialize the LEDs off
P1REN |= BIT3; //Enables a resistor for the button.
P1OUT |= BIT3; //Setting the resistor as a pull-up.
P1IES |= BIT3; //Sets Edge so that the button is activated when pressed down.

P1IE |= BIT3; //Sets mask so that interrupt can't be ignored

__enable_interrupt(); // enables interrupt for board

while (1) //infinite loooooooooooop
{

if(blahh > 0)
{
P1OUT ^= (BIT0 + BIT6); // flipping everytime it loops

__delay_cycles(100000); // slow down clock so you can actually see the blinking
}
}

}

// Interrupt routine for port 1
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
blahh ^= 0x01;  // flips LED so that the if statement to blink the LED is activated.
P1IFG &= ~BIT3; // Clear flag when done
P1OUT &= ~(BIT0 + BIT6); // Turn's LEDs off after flag is cleared.

}
