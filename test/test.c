#include <msp430g2553.h>

int main(void) {

	volatile int i;
	
	WDTCTL = WDTPW | WDTHOLD;
	P1DIR |= 0b01000001;
	P1OUT |= 0b01011001;

	P1REN |= BIT4;
	P1REN |= BIT3;

	P1IE |= BIT4;
	P1IE |= BIT3;

	P1IES |= BIT4;
	P1IES |= BIT3;

	P1IFG = 0x00;
	P1IFG &= ~BIT3;
	P1IFG &= ~BIT4;

	_BIS_SR(CPUOFF + GIE);

	for (;;) {
		//P1OUT  ^= 0x01;
		for (i = 0; i < 0x6000; i++);
	}	
}

#pragma vector = PORT1_VECTOR
__interrupt void port_1(void) {
	if (P1IFG & BIT3) {
		P1OUT ^= 0x01;
		P1IFG &= ~BIT3;
	}
	if (P1IFG & BIT4) {
		P1OUT ^= BIT6;
		P1IFG &= ~BIT4;
	}
}

