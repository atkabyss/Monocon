#include<p18f4550.h>
#include<delays.h>

char Led7seg[] ={
	0b01000000, //0
	0b00010010, //5
	0b00000000, //8
	0b11111111, //��\��
};

char i,j;�@//�ϐ��錾


void led (void) //7�Z�O�����gLED�����_��
{
		LATD = Led7seg[i];
		LATBbits.LATB2 = 1;
		LATBbits.LATB3 = 0;
		Delay1KTCYx(12);
		LATD = Led7seg[j];
		LATBbits.LATB3 = 1;
		LATBbits.LATB2 = 0;
		Delay1KTCYx(12);
}



/*---------------���C���֐�--------------*/
void main(void)
{
	
	ADCON1 |= 0x0F; //AD�R���o�[�^�[�I�t
	
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
	
while(1){

	if(PORTAbits.RA3 == 0 && PORTAbits.RA4 == 0){
		i=1;
		j=2;
		led();
	}
	
	if(PORTAbits.RA3 == 0 && PORTAbits.RA4 == 1){
		i=0;
		j=2;
		led();
	}
	
	if(PORTAbits.RA3 == 1 && PORTAbits.RA4 == 0){
		i=1;
		j=0;
		led();	
	}
	
	if(PORTAbits.RA3 == 1 && PORTAbits.RA4 == 1){
		i=0;
		j=0;
		led();
	}
}
}
