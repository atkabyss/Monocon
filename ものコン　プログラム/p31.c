#include <xc.h>

#define _XTAL_FREQ 48000000
#define GSW PORTAbits.RA2
#define OSW PORTAbits.RA1
#define l0 LATBbits.LATB0
#define l1 LATBbits.LATB1
#define l2 LATBbits.LATB2
#define l3 LATBbits.LATB3
#define de __delay_ms(1)

char i,k;
char STML[] = {0x08, 0x04, 0x02, 0x01};
char STMR[] = {0x01, 0x02, 0x04, 0x08};
char Led7seg[] ={
	0b10011100,
	0b10100011,
};
void teishi(void);
void dousa(void);
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
	
	LATD = Led7seg[0];
	l0 = 1;
	l1 = 0;
	while(GSW == 1);
	
	while(1){
		LATD = Led7seg[0];
		l0 = 1;
		l1 = 0;
		 dousa();
		teishi();
		
		LATD = Led7seg[0];
		l0 = 0;
		l1 = 1;
		dousa();
		teishi();
		
		LATD = Led7seg[1];
		l0 = 0;
		l1 = 1;
		dousa();
		teishi();
		
		LATD = Led7seg[1];
		l0 = 1;
		l1 = 0;
		dousa();
		teishi();
	}
}

void teishi(void){
	while(GSW == 1 ){
		if(GSW == 0) break;
		}
}

void dousa(void){
	char i;
	if(GSW == 0 && OSW == 1){
		for(i=0;i<10;i++){
			__delay_ms(10);
		}
	}
}

