//=====================
//2013.7.30
//�ۑ�3
//�r��H�ƍ����w�Z
//�R��W�j
//=====================
#include<p18f4550.h>
#include<delays.h>

#define PA PORTAbits  //"PORTAbits"��"PA"�Ƃ��Ē�`
#define Ds Delay1KTCYx(12)  //"Delay1KTCYx(12)"��"Ds"�Ƃ��Ē�`
#define Dl Delay1KTCYx(120)  //"Delay1KTCYx(120)"��"Dl"�Ƃ��Ē�`
#define L2 LATBbits.LATB2  //"LATBbits.LATB2"��"L2"�Ƃ��Ē�`
#define L3 LATBbits.LATB3  //"LATBbits.LATB3"��"L3"�Ƃ��Ē�`
#define L7 Led7seg  //"Led7seg"��"L7"�Ƃ��Ē�`

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
	0b01111111,    //��\��
};

char i,j,k;   //�ϐ��̐錾

void led (void);  //7�Z�O�����gLED�̗�����_��

	
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
	i = 10;
	j = 10;
	k = 0;
	
while(1){
	if(PA.RA5 == 0 && k==0){
		Dl;
		
		if(j>3){
			j = 2;
			i = 1;
		}
		
		i--;
		if(i==-1){
			i=9;
			j--;
			}
		if(j==-1){
			j=2;
			i=0;
			}
		k=1;
				}
	if(PA.RA5 == 1){
		Dl;
		k=0;
		}
	led();
	}
}

void led (void){  //7�Z�O�����gLED�̗�����_��
	LATD = L7[i];
	L2 = 1;
	L3 = 0;
	Ds;
	LATD = L7[j];
	L3 = 1;
	L2 = 0;
	Ds;
}
