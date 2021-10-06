//==========================
//2013.7.30
//H23 �ۑ�6
//�r��H�ƍ����w�Z
//�R��W�j
//==========================
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2  //"LATBbits.LATB2"��"L2"�Ƃ��Ē�`
#define L3 LATBbits.LATB3  //"LATBbits.LATB3"��"L3"�Ƃ��Ē�`
#define L4 LATBbits.LATB4  //"LATBbits.LATB4"��"L4"�Ƃ��Ē�`
#define L5 LATBbits.LATB5  //"LATBbits.LATB5"��"L5"�Ƃ��Ē�`
#define L7 LATDbits.LATD7  //"LATBbits.LATB7"��"L7"�Ƃ��Ē�`
#define R4 PORTAbits.RA4  //"PORTAbits.RA4"��"R4"�Ƃ��Ē�`
#define R5 PORTAbits.RA5  //"PORTAbits.RA5"��"R5"�Ƃ��Ē�`
#define D1k Delay1KTCYx(120)  //"Delay1KTCYx(120)"��"D1k"�Ƃ��Ē�`

//==�ϐ��̐錾==
char a;

//==�֐��̐錾==
void DCMl(void);  //DC���[�^��ᑬ��]
void DCMh(void);  //DC���[�^��������]
void DCMs(void);  //DC���[�^���~

//===============���C���֐�===============
void main(void){
	
	ADCON1 |= 0x0F;  //AD�R���o�[�^��OFF
	
//==============���o�͂̐ݒ�==============
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;                          
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//============�|�[�g�̏�����==============
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;                   
	
//======���ׂĂ�7�Z�O�����gLED������======
	L2 = 1;
	L3 = 1;
	L4 = 1;
	L5 = 1;

//==============�ϐ��̏�����==============
	a = 0;
	
while(1)
{   
	if(R4 == 0 && R5 == 0){
		DCMh();
	}
	
	if(R4 == 0 && R5 == 1){
		DCMl();
	}
	
	if(R4 == 1){
		DCMs();
	}
}
}
//==�֐��̐錾==
void DCMl(void){
	char a;
	LATD = 0b00010000;  
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
	for(a=0;a<4;a++){
		DCMs();
	}
}

void DCMh(void){
	LATD = 0b00010000;  
	L7 = 0;
	L7 = 1;
	L7 = 0;
}

void DCMs(void){
	LATD = 0b00110000;  
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
}