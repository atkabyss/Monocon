//=====================
//2013.7.31
//H23 �ۑ�4
//�r��H�ƍ����w�Z
//�R��W�j
//=====================
#include<p18f4550.h>
#include<delays.h>

#define sw4 PORTAbits.RA4 //"PORTAbits.RA4"��"sw4"�Ƃ��Ē�`
#define sw5 PORTAbits.RA5 //"PORTAbits.RA5"��"sw5"�Ƃ��Ē�`
 
//==�ϐ��̐錾==
char i;

//==�֐��̐錾==
void DCMc(void);  //DC���[�^�̉�]����
void DCMcr(void);  //DC���[�^�̋t��]����
void DCMs(void);  //DC���[�^�̒�~����

//==============���C���֐�===============
void main(void)
{
	ADCON1 |= 0x0F; //AD�R���o�[�^��OFF
	
//===============���o�͂̐ݒ�============
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//============�|�[�g�̏�����=============
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
//======���ׂĂ�7�Z�O�����gLED��OFF======
	LATBbits.LATB2 = 1;
	LATBbits.LATB3 = 1;
	LATBbits.LATB4 = 1;
	LATBbits.LATB5 = 1;
	
while(1){
	if(sw4 == 0 && sw5 == 0){
		DCMc();
	}
	
	if(sw4 == 0 && sw5 == 1){
		DCMcr();
	}
	
	if(sw4 == 1){
		DCMs();
	}
}
}
//==�֐��̐錾==
void DCMc(void){
	char a;
	LATD = 0b00010000;  
	LATDbits.LATD7 = 0;
	LATDbits.LATD7 = 1;
	LATDbits.LATD7 = 0;
	Delay1KTCYx(120);
	for(a=0;a<4;a++){
	LATD = 0b00000000;  
	LATDbits.LATD7 = 0;
	LATDbits.LATD7 = 1;
	LATDbits.LATD7 = 0;
		Delay1KTCYx(120);
	}
}

void DCMcr(void){
	LATD = 0b00100000;  
	LATDbits.LATD7 = 0;
	LATDbits.LATD7 = 1;
	LATDbits.LATD7 = 0;
}

void DCMs(void){
	LATD = 0b00000000;  
	LATDbits.LATD7 = 0;
	LATDbits.LATD7 = 1;
	LATDbits.LATD7 = 0;
}
