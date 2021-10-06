//=====================
//2013.7.30
//�ۑ�3
//�r��H�ƍ����w�Z
//�R��W�j
//=====================
#include<p18f4550.h>
#include<delays.h>

char Led7seg[] = {
	0b01000000,    //0
	0b01111001,    //1
	0b00100100,    //2
	0b00110000,    //3
	0b00011001,    //4
	0b00010010,    //5
	0b00000010,    //6
	0b01011000,    //7
	0b00000000,    //8
	0b00010000,    //9
};

char i,j,k;   //�ϐ��̐錾

void led (void){  //7�Z�O�����gLED�̗�����_��
	LATD = Led7seg[i];
	LATBbits.LATB2 = 1;
	LATBbits.LATB3 = 0;
	Delay1KTCYx(12);
	LATD = Led7seg[j];
	LATBbits.LATB3 = 1;
	LATBbits.LATB2 = 0;
	Delay1KTCYx(12);
}

//////////////���C���֐�///////////////
void main(void){
	
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
	j = 2;
	k = 0;
	
while(1){
	if(PORTAbits.RA5 == 0){
		led();
		k = 1;
		
		if(j == 0 && i == -1){
			i = 0;
			j = 2;
			led();
		}
		
		if(j == 0 && i == -1){
			i = 9;
			led();
		}
		
		if(j == 1 && i == -1){
			i = 9;
			led();
		}
		
		if(i == -1){
			j = j - 1;
			led();
		}
		
		i= i - 1;
		
	if(k = 1){
		LATBbits.LATB2 = 0;
		LATBbits.LATB3 = 0;
	}
		}
	}
}