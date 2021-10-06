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
#define _XTAL_FREQ	48000000			//48MHz __dealy_ms(): MAX 16
										//		__delay_us(): MAX 16426

// ���|�[�g�̒�`
// �{�[�h�ɕt������Ă���|�[�g�̒�`
#define SW0		PORTCbits.RC2
#define YLED	LATCbits.LATC0
#define RLED	LATCbits.LATC1


// �t�H�g�Z���T�֌W

#define R1PHSW		PORTEbits.RE		// ���O�t�H�g�Z���T
#define R0PHSW		PORTEbits.RE0		// �E�O�t�H�g�Z���T
#define C1PHSW		PORTEbits.RE1		// ���t�H�g�Z���T**
#define L0PHSW		PORTEbits.RE2		// ���O�t�H�g�Z���T**
#define L1PHSW		PORTEbits.RE		// ���O�t�H�g�Z���T

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


// ���֐��̐錾
// ���������[�`��
void init(void);

// �x���֌W
void delay1ms(unsigned char);
void delay10ms(unsigned char);
void delay100ms(unsigned char);
void delay1s(unsigned char);
void forwardPwm(char);

// ���C�g���[�X�J�[�̐���
#define forward		{lmIN1=1;lmIN2=0;rmIN1=1;rmIN2=0;}
#define lTurn		{lmIN1=1;lmIN2=1;rmIN1=1;rmIN2=0;}//**
#define rTurn		{lmIN1=1;lmIN2=0;rmIN1=1;rmIN2=1;}//**
#define stop		{lmIN1=0;lmIN2=0;rmIN1=0;rmIN2=0;}
#define sStop		{lmIN1=1;lmIN2=1;rmIN1=1;rmIN2=1;}


/*--------------------------------------
	���C���֐�
--------------------------------------*/
void main(void)
{
	// PIC�̏�����
	init();
	
	
	// �� ���[�^�̑O�i
	forward;
	delay1s(2);
	lTurn;
	delay1s(2);
	rTurn;
	delay1s(2);
	PORTDbits.RD5 = 1;
	PORTDbits.RD6 = 1;
	PORTDbits.RD7 = 1;
	delay1s(2);
	
	
	// �� ���[�^�̒�~
	stop;
	
	
	// �� �Z���T�̊��x�������[�`��
	//RLED=LED_ON
	do {
		if(R0PHSW == SW_ON && C1PHSW == SW_OFF && L0PHSW == SW_OFF){
			PORTDbits.RD5 = 1;
		delay100ms(1);}
		if(R0PHSW == SW_OFF && C1PHSW == SW_ON && L0PHSW == SW_OFF){
			PORTDbits.RD6 = 1;
		delay100ms(1);}
		if(R0PHSW == SW_OFF && C1PHSW == SW_OFF && L0PHSW == SW_ON){
			PORTDbits.RD7 = 1;
		delay100ms(1);}
		LATD = 0;
		
		
		
		
	} while(SW0 == SW_OFF);
	delay1ms(30);				// �`���^�����O�h�~
	//RLED=LED_OFF
	// OFF�ɂȂ�܂�(ON�̊ԌJ��Ԃ�)
	while(SW0 == SW_ON);
	delay1ms(30);				// �`���^�����O�h�~
	
	// �� ���C���g���[�X���[�h
	while(1){
	do{
		forwardPwm(95);
	}while(SW0 == SW_OFF);
	delay1ms(30);
	
	while(SW0 == SW_ON);
	delay1ms(30);
	
	do{
		forwardPwm(100);
	}while(SW0 == SW_OFF);
	delay1ms(30);
	
	while(SW0 == SW_ON);
	delay1ms(30);
	}
	// �� ���C���g���[�X�I����̏���
	STOP;
	while(1) {
		// ��LED�̓_��
		RLED = LED_ON;
		delay100ms(5);
		RLED = LED_OFF;
		delay100ms(5);
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
