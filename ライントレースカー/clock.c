/*
=================================================================
	PIC18F4550-HIDmon 
	Microchip XC18
		
	�@�����Ӂ�
	�@1. �v���O�����]�����ɂ́A���C���g���[�X��̓d����K��OFF�ɂ���B
	�@   USB�̓d���Ɗ����A�R���s���[�^�ɑ傫�ȑ�����^���邱�Ƃ�����B
	�@2. C�|�[�g��RC4,5��USB�Ɛڑ�����Ă���̂Ŏ�舵������
	
	a.�v���O�����T�v
		�E�d���������́A�Z���T���x�������[�h�ɂȂ�B
		�E���^�N�g�X�C�b�`�������ƁA���C���g���[�X���[�h�Ɉڍs����B
	
	b.�z��
		�E3�̃Z���T�́A�E����RA0�ARA1�ARA2�ARA3�ARA4�ɐڑ�
		�E�E���[�^�̃��[�^�h���C�o�̓��� IN1��RD3�AIN2��RD4
		�E�����[�^�̃��[�^�h���C�o�̓��� IN1��RD0�AIN2��RD1
	
	c.�v���O�����̐���
		0.���[�^�̉�]�����̊m�F
		�@��2�b�ԃ��[�^����]���A�O�i����悤�ɔz����ύX
		
		1.�Z���T�̊��x�������[�h
		�@�v���O�����J�n�Ɠ����ɁA�Z���T���x�������[�h�ɓ���B
		�@������̏�ŁA���Œ��R���������ς��ɉ񂷁B
		�@LED����������܂Ŕ��Œ��R���E�ɉ񂵂Ă����B
		�@�������C����ʂ�LED���_�����邱�Ƃ��m�F
		�@
		�@�����^�N�g�X�C�b�`�������ƁA
		�@�Z���T�̊��x�������[�h���I�����āA
		�@���C���g���[�X���[�h�Ɉڍs
	
	2.���C���g���[�X���[�h
		�@RA1�Z���T�݂̂ŁA���C���g���[�X���s��
		�@
		�@�����^�N�g�X�C�b�`�������ƁA
		�@���C���g���[�X���[�h���I�����āA
		�@��~���[�h�Ɉڍs
		�@		���d���X�C�b�`��OFF�ɂ��Ă�OK
		�@
	3.��~���[�h
		�@�ԐFLED��500ms���_�ł��āA���C���g���[�X���I��
=================================================================
*/
#include <xc.h>
#define _XTAL_FREQ 48000000

// ���|�[�g�̒�`
// �{�[�h�ɕt������Ă���|�[�g�̒�`
#define SW0		PORTCbits.RC2
#define YLED	LATCbits.LATC0
#define RLED	LATCbits.LATC1


// �t�H�g�Z���T�֌W

#define R1PHSW		PORTEbits.RE0		// ���O�t�H�g�Z���T
#define R0PHSW		PORTEbits.RE		// �E�O�t�H�g�Z���T
#define C1PHSW		PORTEbits.RE1		// ���t�H�g�Z���T**
#define L0PHSW		PORTEbits.RE		// ���O�t�H�g�Z���T**
#define L1PHSW		PORTEbits.RE2		// ���O�t�H�g�Z���T

// ���[�^�֌W
// �O�i�E��i�����]����ꍇ�́A
//	�E�Ή���1	���[�^�̎��t���[�q���t�ɂ���
//	�E�Ή���2	IN1��IN2�̒�`���t�ɂ���


#define lmIN1	LATBbits.LATB2		// 	�����[�^�h���C�o�@IN1**
#define lmIN2	LATBbits.LATB3		// 	�����[�^�h���C�o�@IN2**
#define lmIN3	LATBbits.LATB		// 	�����[�^�h���C�o�@IN3
#define rmIN1	LATBbits.LATB1		// 	�E���[�^�h���C�o�@IN1
#define rmIN2	LATBbits.LATB0		// 	�E���[�^�h���C�o�@IN2
#define rmIN3	LATBbits.LATB		// 	�E���[�^�h���C�o�@IN3

// ON / OFF
#define B_LINE		1
#define W_LINE		!B_LINE

#define SW_OFF		1
#define SW_ON		!SW_OFF

#define LED_OFF		0
#define LED_ON		!LED_OFF

#define LED7OFF		1
#define LED7ON		!LED7OFF

#define M_STOP		0
#define M_CW		1
#define M_CCW		2
#define M_BRAKE		3

#define CNT500ms 65536-46875
#define COUNTER CNT500ms

// ���֐��̐錾
// ���������[�`��
void init(void);

// �x���֌W
void delay1ms(unsigned char);
void delay10ms(unsigned char);
void delay100ms(unsigned char);
void delay1s(unsigned char);
void forwardPwm(char);
void init(void);
void initTimer0(void);
// ���C�g���[�X�J�[�̐���
#define forward		{lmIN1=1;lmIN2=0;rmIN1=1;rmIN2=0;}
#define lTurn		{lmIN1=1;lmIN2=1;rmIN1=1;rmIN2=0;}//**
#define rTurn		{lmIN1=1;lmIN2=0;rmIN1=1;rmIN2=1;}//**
#define stop		{lmIN1=0;lmIN2=0;rmIN1=0;rmIN2=0;}
#define sStop		{lmIN1=1;lmIN2=1;rmIN1=1;rmIN2=1;}

int f=0;
int c=0;
int sw=0;

/*--------------------------------------
	���C���֐�
--------------------------------------*/
void main(void)
{
	// PIC�̏�����
	init();
	
	
	// �� ���[�^�̑O�i
	initTimer0();
	INTCONbits.GIE=1;
	while(1){
		// �� ���C���g���[�X���[�h
	do{
		if(L1PHSW == W_LINE && C1PHSW == W_LINE && R1PHSW == W_LINE)	sw = 0;
		if(L1PHSW == W_LINE && C1PHSW == W_LINE && R1PHSW == B_LINE)	sw = 1;
		if(L1PHSW == W_LINE && C1PHSW == B_LINE && R1PHSW == W_LINE)	sw = 2;
		if(L1PHSW == W_LINE && C1PHSW == B_LINE && R1PHSW == B_LINE)	sw = 3;
		if(L1PHSW == B_LINE && C1PHSW == W_LINE && R1PHSW == W_LINE)	sw = 4;
		if(L1PHSW == B_LINE && C1PHSW == W_LINE && R1PHSW == B_LINE)	sw = 5;
		if(L1PHSW == B_LINE && C1PHSW == B_LINE && R1PHSW == W_LINE)	sw = 6;
		if(L1PHSW == B_LINE && C1PHSW == B_LINE && R1PHSW == B_LINE)	{sw = 7;c++;}
		delay1ms(20);
		
		switch(sw){
		case 0:
			forward;
			break;
		case 1:
			rTurn;
			break;
		case 2:
			lTurn;
			break;
		case 3:
			rTurn;
			break;
		case 4:
			lTurn;
			break;
		case 5:
			forward;
		case 6:
			lTurn;
		case 7:
			if(c == 1){
				for(f=0;f<=300;f++){
					lTurn;
					delay1ms(10);
				}
			}
		default:break;
		}
	}while(1);
		
	// �� ���C���g���[�X�I����̏���
	stop;
	while(1) {
		// ��LED�̓_��
		RLED = LED_ON;
		delay100ms(5);
		RLED = LED_OFF;
		delay100ms(5);
	}
	}
	
	while(1);
}

/*--------------------------------------
	PIC�̏��������
--------------------------------------*/
void init(void)
{
	// �����o�̓s�����f�W�^�����[�h�ɐݒ肵�܂�
	ADCON1 |= 0x0F;		// �@AD�R���o�[�^OFF
	
	// �����o�͂̐ݒ�����܂�
	// �@C�|�[�g��USB���ڑ�����Ă���̂Œ��� 0�ŏo��
	TRISA = 0b11111111;
	TRISB = 0b00000000;
	TRISC = 0b00111100;
	TRISD = 0b00000000;
	TRISE = 0b11111111;

	// ���|�[�g�̏����� ���ׂ�0
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	
}
/*----------------------------------------
	�x���֌W
------------------------------------------*/
//	1ms x unit�̃E�G�C�g ---------------
void delay1ms(unsigned char unit)
{
	unsigned char i;
	for (i=0; i<unit; i++) {
		__delay_ms(1);
	}
}
//	10ms x unit�̃E�G�C�g ---------------
void delay10ms(unsigned char unit)
{
	unsigned char i;
	for (i=0; i<unit; i++) {
		__delay_ms(10);
	}
}
//	100ms x unit�̃E�G�C�g ---------------
void delay100ms(unsigned char unit)
{
	unsigned char i, j;
	for (i=0; i<unit; i++) {
		for (j=0; j<10; j++) {
			__delay_ms(10);
		}
	}
}
//	1s x unit�̃E�G�C�g ---------------
void delay1s(unsigned char unit)
{
	unsigned char i, j, k;
	for (i=0; i<unit; i++) {
		for (j=0; j<100; j++) {
			__delay_ms(10);
		}
	}
}

void forwardPwm(char dt){
	char i;
	
	if(0<=dt && dt<=100){
		for(i=0;i<dt;i++){
			forward;
		}
		for(i=dt;i<100;i++){
			stop;
		}
	}
}

void initTimer0(void){
	char t0Init = 0b10000111;
	T0CON = t0Init;
	TMR0 = COUNTER;
	INTCONbits.TMR0IE = 1;
}

void interrupt timer0(void){
	if(INTCONbits.TMR0IF){
		INTCONbits.TMR0IE=0;
		INTCONbits.TMR0IF=0;
		
		RLED = ~RLED;
		TMR0 = COUNTER;
		INTCONbits.TMR0IE = 1;
	}
}
	