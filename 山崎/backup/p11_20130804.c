#include<p18f4550.h>
#include<delays.h>

char STM[] = {0x01, 0x02, 0x04, 0x08};


void main(void)
{
	char i,j;
	
	ADCON1 |= 0x0F; //ADコンバーターオフ
	
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	                               
	LATBbits.LATB2 = 1;
	LATBbits.LATB3 = 1;
	LATBbits.LATB4 = 1;
	LATBbits.LATB5 = 1;
	
	i = 0;
	j = 0;
while(1){
         
	if(PORTAbits.RA4 == 0){
		for(i=0;i<24;i++){
		LATD = STM[j]; //セット
		LATDbits.LATD7 = 0;
		LATDbits.LATD7 = 1;
		LATDbits.LATD7 = 0;
		Delay1KTCYx(120);
		
		j++;
		
		if(j>=4){
			j = 0;
		}
	}
	}
	
	if(PORTAbits.RA3 == 0){
		for(i=0;i<=12;i++){
		LATD = STM[j]; //セット
		LATDbits.LATD7 = 0;
		LATDbits.LATD7 = 1;
		LATDbits.LATD7 = 0;
		Delay1KTCYx(120);
		
		j++;
		
		if(j>=4){
			j = 0;
		}
}
}
}
}