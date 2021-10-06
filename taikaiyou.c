/*
=================================================================
	PIC18F4550-HIDmon 
	Microchip XC18
		
	�@�����Ӂ�
	�@1. �v���O�����]�����ɂ́A���C���g���[�X��̓d����K��OFF�ɂ���B
	�@   USB�̓d���Ɗ����A�R���s���[�^�ɑ傫�ȑ�����^���邱�Ƃ�����B
	�@2. C�|�[�g��RC4,5��USB�Ɛڑ�����Ă���̂Ŏ�舵������
	
	a.�v���O�����T�v
		���C���g���[�X�J�[
		�����̃Z���T�݂̂Ń��C���g���[�X���s���B
		�v���O�����X�^�[�g���́A�Z���T�̊��x�������[�h�ŋN��
		���^�N�g�X�C�b�`�������ƁA���C���g���[�X���[�h�Ɉڍs����B
	
	b.�z��
		�E�Z���T�́A�E����RA0�ARA1�ARA2�ARA3�ARA4�ɐڑ�
		�E���[�^��̓���(PIC12F675) GP2(IN3)�AGP1(IN2)�AGP0(IN1)
		�E���[�^��̏o��(PIC12F675) GP0(IN1)->GP5(OUT1)->IN1�AGP1(IN2)->GP4(OUT2)->IN2
		�E�E�̃��[�^��� LATD3->GP0(IN1)�ALATD4->GP1(IN2)�ALATD5->GP2(IN3)
		�E���̃��[�^��� LATD0->GP0(IN1)�ALATD1->GP1(IN2)�ALATD2->GP2(IN3)
	
	c.�v���O�����̐���
		1.�Z���T�̊��x�������[�h
		�@�v���O�����J�n�Ɠ����ɁA�Z���T���x�������[�h�ɓ���B
		�@���Œ��R�𒲐����Ċ��x�𒲐�����B
			�Z���T�����ゾ�ƁA�C���W�P�[�^���_��
			�Z���T�����ゾ�ƁA�C���W�P�[�^������
		
		�@�����^�N�g�X�C�b�`�������ƁA�ԐFLED����������
		�@�Z���T�̊��x�������[�h���I������
		�@���C���g���[�X���[�h�Ɉڍs
	
	2.���C���g���[�X���[�h
		�@���FLED���_��
		�@1�̃Z���T�̂�(RA1)�ŁA���C���g���[�X���s��
		�@
		�@�����^�N�g�X�C�b�`�������ƁA���FLED����������
		�@���C���g���[�X���[�h���I������
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


//�����v�֌W
#define FLED0		PORTBbits.RB0		//�w�b�h�����v�E
#define FLED1		PORTBbits.RB1		//�w�b�h�����v��
#define PLED0		PORTBbits.RB2		//�p�g�����v�E
#define PLED1		PORTBbits.RB3		//�p�g�����v���E
#define PLED2		PORTBbits.RB4		//�p�g�����v����
#define PLED3		PORTBbits.RB5		//�p�g�����v��
#define BLED0		PORTBbits.RB6		//�o�b�N�����v�E
#define BLED1		PORTBbits.RB7		//�o�b�N�����v��

// �t�H�g�Z���T�֌W
#define R1PHSW		PORTAbits.RA0		// �E�t�H�g�Z���T
#define R0PHSW		PORTAbits.RA1		// ���t�H�g�Z���T
#define C1PHSW		PORTAbits.RA2		// ���t�H�g�Z���T
#define L0PHSW		PORTAbits.RA3		// ���t�H�g�Z���T
#define L1PHSW		PORTAbits.RA4		// ���t�H�g�Z���T

// ���[�^�֌W
// �O�i�E��i�����]����ꍇ�́A
//	�E�Ή���1	���[�^�̎��t���[�q���t�ɂ���
//	�E�Ή���2	IN1��IN2�̒�`���t�ɂ���
#define lmIN1	LATDbits.LATD0		// 	�����[�^�h���C�o�@IN1
#define lmIN2	LATDbits.LATD1		// 	�����[�^�h���C�o�@IN2
#define lmIN3	LATDbits.LATD2		// 	�����[�^�h���C�o�@IN3
#define rmIN1	LATDbits.LATD3		// 	�E���[�^�h���C�o�@IN1
#define rmIN2	LATDbits.LATD4		// 	�E���[�^�h���C�o�@IN2
#define rmIN3	LATDbits.LATD5		// 	�E���[�^�h���C�o�@IN3

// ON / OFF
#define B_LINE		1
#define W_LINE		!B_LINE

#define SW_OFF		1
#define SW_ON		!SW_OFF

#define LED_OFF		0
#define LED_ON		!LED_OFF

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


// ���C�g���[�X�J�[�̐���
#define forward		{lmIN1=1; lmIN2=0; rmIN1=1; rmIN2=0;}
#define rTurn		{lmIN1=1; lmIN2=0; rmIN1=1; rmIN2=1;}
#define lTurn		{lmIN1=1; lmIN2=1; rmIN1=1; rmIN2=0;}
#define stop		{lmIN1=0; lmIN2=0; rmIN1=0; rmIN2=0;}
#define sStop		{lmIN1=1; lmIN2=1; rmIN1=1; rmIN2=1;}
void forwardms(unsigned char);


/*--------------------------------------
	���C���֐�
--------------------------------------*/
void main(void)
{
	// PIC�̏�����
	init();
	
	// �� �O�i�E��~
	forward;
	delay1s(2);
	stop;
	
	// �� �Z���T�̊��x�������[�`��
	// RLED = LED_ON;
	do {
	} while(SW0 == SW_OFF);
	delay1ms(30);				// �`���^�����O�h�~
	// RLED = LED_OFF;
	
	// OFF�ɂȂ�܂�(ON�̊ԌJ��Ԃ�)
	while(SW0 == SW_ON);
	delay1ms(30);				// �`���^�����O�h�~
	

	// �� ���C���g���[�X���[�h
	YLED = LED_ON;
	int count = 0;
	int lineflag = 0;
	int waittime = 0;
	int linetime = 0;
	int SW = 0;
	int PLED = 0;
	int PLEDT = 0;
	do {
		if (L1PHSW == W_LINE && C1PHSW == W_LINE && R1PHSW == W_LINE) SW = 0;	//���� ���� �E��
		if (L1PHSW == W_LINE && C1PHSW == W_LINE && R1PHSW == B_LINE) SW = 1;	//���� ���� �E��
		if (L1PHSW == W_LINE && C1PHSW == B_LINE && R1PHSW == W_LINE) SW = 2;	//���� ���� �E��
		if (L1PHSW == W_LINE && C1PHSW == B_LINE && R1PHSW == B_LINE) SW = 3;	//���� ���� �E��
		if (L1PHSW == B_LINE && C1PHSW == W_LINE && R1PHSW == W_LINE) SW = 4;	//���� ���� �E��
		if (L1PHSW == B_LINE && C1PHSW == W_LINE && R1PHSW == B_LINE) SW = 5;	//���� ���� �E��
		if (L1PHSW == B_LINE && C1PHSW == B_LINE && R1PHSW == W_LINE) SW = 6;	//���� ���� �E��
		if (L1PHSW == B_LINE && C1PHSW == B_LINE && R1PHSW == B_LINE) SW = 7;	//���� ���� ����
		delay10ms(1);
		switch(SW){
			//���C����T��(����)
			case 0:{
				char dt=10;
				char i=0;;
			
					for (i=0; i<dt; i++) {
						rTurn;
					}
					for (i=dt; i<50; i++) {
						stop;
					}
				i=0;
			break;
			}
			//�����[�^�[��](�E����)
			case 1:{
			rTurn;
			break;
			}
			//(���i)
			case 2:{
			forward;
			break;
			}
			//�E���[�^�[��](C�_�F��)
			case 3:{
			rTurn;
			break;
			}
			//�E���[�^�[��](������)
			case 4:{
			lTurn;
			break;
			}
			//���C����T��(����)
			case 5:{
			forward;
			break;
			}
			//���C����T��(������)
			case 6:{
			lTurn;
			break;
			}
			//�S�����̓���
			case 7:{
			
				// �����_�̔���
				if (linetime > 6) {
					lineflag = 1;
					waittime = 0;
					linetime = 0;
				}
				else {
					linetime++;
				}
				
				forward;
				
			}
		
		}
		// �����_�̓���
		if (lineflag == 1) {
		
			//1�b�҂�
			if (waittime > 650) {
				count++;
				waittime = 0;
				lineflag = 0;
			
				//�o�b�N�����v����
				BLED0 = 0;
				BLED1 = 0;
			}
			else {
				waittime++;
			
				//�o�b�N�����v�_��
				BLED0 = 1;
				BLED1 = 1;
				stop;
			}
		
		}
		
		switch (count){
		
			// �X�^�[�g���C���̏���
			case 1:{
				
			break;
			}
			// A�_����B�_�܂ł̏���
			case 2:{
			
				//�p�g�����v�^�C�}�[
				if (PLEDT > 100) {
				
					PLED = 1;

				} else {
					
					PLEDT++;
				}
				
				//1�b���Ƀp�g�����v��؂�ւ���
				switch(PLED){
					case 0:{
						PLED0 = 0;
						PLED1 = 0;
						PLED2 = 0;
						PLED3 = 0;
						break;
					}
					case 1:{
						PLED0 = 1;
						PLED1 = 1;
						PLED2 = 1;
						PLED3 = 1;
						break;
					}
				}
				
				break;
				
			}
			// B�_�ȍ~�̏���
			case 3:{
			
				PLED0 = 0;
				PLED1 = 0;
				PLED2 = 0;
				PLED3 = 0;
				break;
			}
		
		}
	
		// �w�b�h�����v�͏�ɓ_��
		FLED0 = 1;
		FLED1 = 1;
	
	}while(SW0 == SW_OFF);
	delay1ms(30);				// �`���^�����O�h�~
	YLED = LED_OFF;
	
	// OFF�ɂȂ�܂�(ON�̊ԌJ��Ԃ�)
	while(SW0 == SW_ON);
	delay1ms(30);				// �`���^�����O�h�~
	
	
	// �� ���C���g���[�X�I����̏���
	stop;
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
	int i;
	
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
	PORTA = 0;	LATA = 0;
	PORTB = 0;	LATB = 0;
	PORTC = 0;	LATB = 0;
	PORTD = 0;	LATB = 0;
	PORTE = 0;	LATB = 0;
	
	for(i=0; i<5; i++) {
		YLED=1; RLED=1;	__delay_ms(16);
		YLED=0; RLED=0;	__delay_ms(16);
	}
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
//	forward�̌p�� ---------------
void forwardms(unsigned char unit)
{
	forward;
	unsigned char i;
	for (i=0; i<unit; i++) {
		__delay_ms(1);
	}
}
