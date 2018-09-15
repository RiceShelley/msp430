#include <msp430g2553.h>

int main(void) {

	volatile int j = 0;
	
	WDTCTL = WDTPW + WDTHOLD;

	P1DIR |= BIT0;
	P1DIR |= BIT1;
	P1DIR |= BIT2;

	//P1OUT = 0x0;

	P1OUT |= BIT0;
	//P1OUT |= BIT1;

	P1SEL |= BIT2;

	TA0CCR0 = 1000;
	TA0CCTL1 = OUTMOD_7;
	TA0CCR1 = 700;

	TA0CTL = TASSEL_2 + MC_1;
	//__bis_SR_register(LPM0_bits);

	for (;;) {	
		P1OUT ^= BIT0;
		P1OUT ^= BIT1;

		for (j = 0; j < 0x6000; j++);
	}	
	
}
