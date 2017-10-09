#include <msp430.h> 

int blahh = 0; //variable to keep track of button interrupts

void main(void)
{

WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
//PM5CTL0 &= ~LOCKLPM5;     // Disable the GPIO power-on default high-impedance mode


P1DIR |= (BIT0); // Set LEDS as outputs
P1OUT &= ~(BIT0); // Initialize the LEDs off
P2REN |= BIT1; //Enables a resistor for the button.
P2OUT |= BIT1; //Setting the resistor as a pull-up.
P2IES |= BIT1; //Sets Edge so that the button is activated when pressed down.

P2IE |= BIT1; //Sets mask so that interrupt can't be ignored

__enable_interrupt(); // enables interrupt for board

while (1) //infinite loooooooooooop
{

if(blahh > 0)
{
P1OUT ^= (BIT0); // flipping everytime it loops

__delay_cycles(100000); // slow down clock so you can actually see the blinking
}
}

}

// Interrupt routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
blahh ^= 0x01;  // flips LED so that the if statement to blink the LED is activated.
P2IFG &= ~BIT1; // Clear flag when done
P1OUT &= ~(BIT0); // Turn's LEDs off after flag is cleared.

}
