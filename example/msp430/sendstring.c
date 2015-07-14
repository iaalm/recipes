#include <msp430g2553.h>

/* Demo UART application.  After you press the button, this transmits
 * a "Hello, world!" string to the computer at 2400 bps.
 */

#define   RED_LED   BIT0
#define   GRN_LED   BIT6

#define   BUTTON    BIT3

#define   TXD       BIT1
#define   RXD       BIT2

/* Ticks per bit.  Use the following values based on speed:
 * 9600 bps ->  12
 * 2400 bps ->  52
 * 1200 bps -> 104
 * I did not have success with slower speeds, like 300 bps.
 */
#define   TPB      52

int TXWord;
unsigned char bitcnt = 0;

/* function prototypes */
void initUart( void );
void sendByte( unsigned char b );
void sendString( const char *str );

void main(void) {
    /* stop the watchdog timer */
    WDTCTL = WDTPW + WDTHOLD;

    /* LEDs off, but later we'll blink them as we send bits */
    P1DIR |= RED_LED+GRN_LED;
    P1OUT &= ~ (RED_LED + GRN_LED );

    initUart();

    /* We'll use the button to let the chip know we're ready to communicate.
     * Direction is receive, clear interrupt flag, and
     * interrupts are enabled.
     */
    P1DIR &= ~BUTTON;
    P1IFG &= ~BUTTON;
    P1IE |= BUTTON;
    P1REN |= BUTTON;
    P1OUT |= BUTTON;

    for( ; ; ) {
        /* go to sleep until button press */
        __bis_SR_register( LPM3_bits + GIE );
        sendString( "Hello, world!\r\n" );
    }
}

void initUart( void ) {
    /* Set up transmit as output pin and set it high */
    P1OUT |= TXD;
    P1DIR |= TXD;

    /* set up the clocks for 1 Mhz */
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL2 &= ~(DIVS_3);

    /* Set timer A to use count up mode 4 Mhz / 8 = 500 Khz. */
    TACTL = TASSEL_2 + MC_1 + ID_3 + TACLR;

    /* Set ticks-per-bit to specify communication speed */
    TACCR0 = TPB;
}

void sendByte( unsigned char b ) {
    /* load the byte */
    TXWord = b;
    /* add stop bit */
    TXWord |= 0x100;
    /* add start bit */
    TXWord <<= 1;

    /* 1 start bit + 8 data bits + 1 stop bit */
    bitcnt = 10;

    /* clear the counter, clear interrupt flag, and tell Timer A0 to
     * start triggering interrupts
     */
    TACTL |= TACLR;
    TACCTL0 &= ~CCIFG;
    TACCTL0 |= CCIE;

    /* sleep until message sent */
    while( TACCTL0 & CCIE ) {
        __bis_SR_register( LPM0_bits + GIE );
    }
}

/* Sends a string of characters to the computer */
void sendString( const char *str ) {
    char *c = str;

    for( ; *c ; c++ ) {
        sendByte( *c );
    }
}


/* This continuously sends bits of the TXWord starting from the
 * least significant bit (the 0 start bit).  One bit is sent every
 * time the handler is activated.
 */
void TimerA0 (void) __attribute__((interrupt(TIMER0_A0_VECTOR)));
void TimerA0(void) {
    TACCTL0 &= ~CCIFG;

    if( ! bitcnt ) {
        /* no bits left, turn off interrupts and wake up */
        TACCTL0 &= ~ CCIE;
        __bic_SR_register_on_exit( LPM0_bits );
        return;
    } else {
        /* send least significant bit */
        if( TXWord & 0x01 ) {
            P1OUT |= TXD;
            P1OUT |= RED_LED;           // for testing
            P1OUT &= ~ GRN_LED;         // for testing
        } else {
            P1OUT &= ~TXD;
            P1OUT |= GRN_LED;           // for testing
            P1OUT &= ~ RED_LED;         // for testing
        }

        /* shift word to remove one bit */
        TXWord >>= 1;
        bitcnt --;
    }
}

/* A button press triggers this interrupt, which wakes
 * up the main program to send a message.
 */
void Port_1 (void) __attribute__((interrupt(PORT1_VECTOR)));
void Port_1(void) {
    P1IFG &= ~BUTTON;

    /* wake up the main program */
     __bic_SR_register_on_exit( LPM3_bits );
}
