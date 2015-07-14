#include "msp430g2553.h"
#define Bitime (13*4)

#define     TXD                   BIT1                      // TXD on P1.1
#define     RXD                   BIT2                      // RXD on P1.2

#define DEBUG


#define     BUTTON                BIT3
#define     BUTTON_IE             P1IE
#define     TIMER_PWM_PERIOD      2000  

unsigned char BitCnt;
unsigned int TXByte;
void main()
{
	volatile unsigned short i;
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
#ifdef DEBUG
	P1DIR |= BIT6 + BIT0;
	P1OUT &= ~(BIT6 + BIT0);
#endif
	//初始化时钟
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
	BCSCTL2 &= ~(DIVS_3);

	BCSCTL1 |= DIVA_1;                        // ACLK/2
	BCSCTL3 |= LFXT1S_2;                      // ACLK = VLO

	/*
	TACCR0 = 1200;                             //   
	TACTL = TASSEL_1 | MC_1;                  // TACLK = SMCLK, Up mode.  
	TACCTL1 = CCIE + OUTMOD_3;                // TACCTL1 Capture Compare
	TACCR1 = 600;  
	*/

	//串口相关
	TACCTL0 = OUT;                              // TXD Idle as Mark
	TACTL = TASSEL_2 + MC_2 + ID_3;           // SMCLK/8, continuous mode
	P1SEL |= TXD + RXD;                       //
	P1DIR |= TXD;                             //  

	__enable_interrupt();			//开中断
	while(1)
	{
		TXByte = 'a';
		BitCnt = 0xA;                             // Load Bit counter, 8data + ST/SP

		/* Simulate a timer capture event to obtain the value of TAR into the TACCR0 register */
		TACCTL0 = CM_1 + CCIS_2  + SCS + CAP + OUTMOD0;   	//capture on rising edge, initially set to GND as input // clear CCIFG flag
		TACCTL0 |= CCIS_3; 						//change input to Vcc, effectively rising the edge, triggering the capture action

		while (!(TACCTL0 & CCIFG));				//allowing for the capturing//updating TACCR0.

		TACCR0 += Bitime ;                           // Some time till first bit
		TXByte |= 0x100;                          // Add mark stop bit to TXByte
		TXByte = TXByte << 1;                     // Add space start bit
		TACCTL0 =  CCIS0 + OUTMOD0 + CCIE;          // TXD = mark = idle

		while ( TACCTL0 & CCIE );                   // Wait for TX completion
#ifdef DEBUG
	P1OUT ^= BIT6;
#endif
		//i = 5;
		i = 1;
		while(i--);
#ifdef DEBUG
	P1OUT ^= BIT6;
#endif
	}

}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
#ifdef DEBUG
	P1OUT ^= BIT0;
#endif
    TACCR0 += Bitime;                         // Add Offset to TACCR0
    if (TACCTL0 & CCIS0)                      // TX on CCI0B?
    {
      if ( BitCnt == 0)
      {         
        P1SEL &= ~(TXD+RXD);
        TACCTL0 &= ~ CCIE ;                   // All bits TXed, disable interrupt
      }  
      
      else
      {
        TACCTL0 |=  OUTMOD2;                  // TX Space
        if (TXByte & 0x01)
        TACCTL0 &= ~ OUTMOD2;                 // TX Mark
        TXByte = TXByte >> 1;
        BitCnt --;
      }
    }
}

/*
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
    IE1 &= ~WDTIE;                   // disable interrupt 
    IFG1 &= ~WDTIFG;                 // clear interrupt flag 
    WDTCTL = WDTPW + WDTHOLD;        // put WDT back in hold state 
}
*/

