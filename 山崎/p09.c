#include<p18f4550.h>
#include<delays.h>

char Led7seg[] ={
	0b00100000, //a
	0b00000011, //b
	0b01000110, //c
	0b00100001, //d
	0b00000100, //e
	0b00001110, //f
	0b11111111, //��\��
};

void main(void)
{
	char i;
	
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
	
	i = 0;  //a�̃Z�b�g
	
while(1){
	
	LATD = Led7seg[i];  //�f�[�^�̃Z�b�g
	LATBbits.LATB3 = 0; //�\��
		Delay10KTCYx(120); //��1�b�̒x��
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
	
	if(PORTAbits.RA4 == 0){  //�^�N�g���͎���i�����Z
		i++;
		
		if(i >= 6){  //f����a
			i = 0;
		}
	}
}
}