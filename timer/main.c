#include <msp430g2253.h>

int control = 0;

int main(void) {
	WDTCTL = WDTPW + WDTHOLD;	// stop that watchdog
	DCOCTL = 0;			// Sellect lowest DCOx and MODx
	BCSCTL1 = CALBC1_1MHZ;		// set range
	DCOCTL = CALDCO_1MHZ;		// set DCO step + modulation

	P1DIR |= BIT0;
	P1DIR |= BIT6;
	P1OUT &= ~BIT0;
	P1OUT &= ~BIT6;

	TA0CCR0 |= 3000;
	TA0CCTL0 |= CCIE;
	TA0CTL |= TASSEL_1 + MC_1;

	_BIS_SR(LPM0_bits + GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void) {
	control++;
	P1OUT ^= BIT0;
	if (control == 4) {
		P1OUT ^= BIT6;
		control = 0;
	}
}
