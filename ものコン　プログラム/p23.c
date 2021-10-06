#include <xc.h>

#define _XTAL_FREQ 48000000
#define GSW PORTAbits.RA2
#define OSW PORTAbits.RA1
#define l0 LATBbits.LATB0
#define l1 LATBbits.LATB1
#define l2 LATBbits.LATB2
#define l3 LATBbits.LATB3
#define de __delay_ms(1)

char Led7seg[] ={
	0b11111110,
	0b11111101,
	0b11111011,
	0b11110111,
	0b11101111,
	0b11011111,
};

void teisoku(void);
void kousoku(void);


void main(void){
	ADCON1 |= 0x0F;
	
	TRISA = 0b11001110;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b00000111;
	
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	LATBbits.LATB0 = 1;
	LATBbits.LATB1 = 1;
	LATBbits.LATB2 = 1;
	LATBbits.LATB3 = 1;
	
	while(1){
			LATD = Led7seg[0];
			l0 = 1;
			l1 = 0;
			if(OSW == 1 && GSW == 1) teisoku();
			if(OSW == 0 && GSW == 1) kousoku();
			if(GSW == 0) teisoku();
		
			LATD = Led7seg[0];
			l0 = 0;
			l1 = 1;
			if(OSW == 1 && GSW == 1) teisoku();
			if(OSW == 0 && GSW == 1) kousoku();
			if(GSW == 0) teisoku();
		
			LATD = Led7seg[1];
			l0 = 0;
			l1 = 1;
			if(OSW == 1 && GSW == 1) teisoku();
			if(OSW == 0 && GSW == 1) kousoku();
			if(GSW == 0) teisoku();
		
			LATD = Led7seg[2];
			l0 = 0;
			l1 = 1;
			if(OSW == 1 && GSW == 1) teisoku();
			if(OSW == 0 && GSW == 1) kousoku();
			if(GSW == 0) teisoku();
		
			LATD = Led7seg[3];
			l0 = 0;
			l1 = 1;
			if(OSW == 1 && GSW == 1) teisoku();
			if(OSW == 0 && GSW == 1) kousoku();
			if(GSW == 0) teisoku();
		
			LATD = Led7seg[3];
			l0 = 1;
			l1 = 0;
			if(OSW == 1 && GSW == 1) teisoku();
			if(OSW == 0 && GSW == 1) kousoku();
			if(GSW == 0) teisoku();
		
			LATD = Led7seg[4];
			l0 = 1;
			l1 = 0;
			if(OSW == 1 && GSW == 1) teisoku();
			if(OSW == 0 && GSW == 1) kousoku();
			if(GSW == 0) teisoku();
		
			LATD = Led7seg[5];
			l0 = 1;
			l1 = 0;
			if(OSW == 1 && GSW == 1) teisoku();
			if(OSW == 0 && GSW == 1) kousoku();
			if(GSW == 0) teisoku();
		
		}
}

void teisoku(void){
	char i;
	for(i=0;i<20;i++){
		__delay_ms(10);
	}
}

void kousoku(void){
	char k;
	for(k=0;k<10;k++){
		__delay_ms(10);
	}
}