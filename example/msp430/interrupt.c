
#include "msp430g2553.h"

#define LED (BIT0 | BIT6)
#define BUTTON BIT3

int main( void )
{
	__disable_interrupt();
	WDTCTL = WDTPW + WDTHOLD;
	//
	P1DIR |= LED;
	P1OUT |= LED;

	//初始化按钮
	P1REN |= BUTTON;
	P1IES |= BUTTON;
	P1IE  |= BUTTON;

	__enable_interrupt();  

	while(1)
		_BIS_SR(LPM0_bits);	//进入低功耗模式0
}

#pragma vector=PORT1_VECTOR
__interrupt void i(void)
{
	P1IFG &= ~(BUTTON);
	P1OUT ^= LED;
}
