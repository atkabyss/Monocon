#include<p18f4550.h>
#include<delays.h>

char Led7seg[] = {       //7�Z�O�����gLED�̕\������
	0b01110111,      //ON
	0b00101011,      //OFF
};

//////////////////���C���֐�////////////////////
void main(void)
{
	ADCON1 |= 0x0F;  //AD�R���o�[�^�̏�����
	
	TRISA = 0b11111000;    //���o�͂̐���
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
	PORTA = 0;    //�|�[�g�̏�����
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	LATBbits.LATB2 = 1;     //7�Z�O�����gLED�̕\��OFF
	LATBbits.LATB3 = 1;
	LATBbits.LATB4 = 1;
	LATBbits.LATB5 = 1;

while(1){
	
	if(PORTAbits.RA4 = 0){
		LATD = Led7seg[0];
		LATBbits.LATB2 = 0;
	}
    
	if(PORTAbits.RA4 = 1){
		LATD = Led7seg[1];
		LATBbits.LATB2 = 0;
	}
}
}
