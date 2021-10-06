//�ۑ�3
#include<p18f4550.h>
#include<delays.h>

char Led7seg[] = {
	0b01000000,    //0
	0b00000110,    //1
	0b00100100,    //2
	0b00110000,    //3
	0b00011001     //4
	0b00010010,    //5
	0b00000010,    //6
	0b01011000,    //7
	0b00000000,    //8
	0b00010000,    //9
};	

//////////////���C���֐�///////////////
void main(void)

	char i;  //�ϐ��̐錾
	
	ADCON1 |= 0x0F;  //AD�R���o�[�^OFF
	
	TRISA = 0b11111000;  //���o�͂̏�����
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
	PORTA = 0;  //�|�[�g�̏�����
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	LATBbits.LATB2 = 1;  //���ׂĂ�7�Z�O�����gLED��OFF
	LATBbits.LATB3 = 1;
	LATBbits.LATB4 = 1;
	LATBbits.LATB5 = 1;
	i = 0;
	
while(1){
	
	LATD = Led7seg[2];
	LATBbits.LATB2 = 0;
	Delay1KTCYx(12);
	LATBbits.LATB2 = 1;
	LATD = Led7seg[0];
	LATBbits.LATB3 = 0;
	Delay1KTCYx(12);
	LATBbits.LATB3 = 1;

