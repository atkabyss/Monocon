/*=================================================================
	3E29 �R��W�j
	�ۑ茤���ppg 
	
	���C���g���[�X�̂�
=================================================================
#################################################################
	
	���퓮�삵��pg

	do {
		if(checkRPHSW() == WLINE && checkLPHSW() == WLINE)	fowrd();
		if(checkRPHSW() == BLINE)	left();
		if(checkLPHSW() == BLINE)	right();
		
/*		if(checkRPHSW() == BLINE){	//�E�Z���TON
			delay10ms(30);		// �`���^�����O�h�~
			rf++; //�E�t���O�ɉ��Z
		}
		if(checkLPHSW() == BLINE){	//���Z���TON
			delay10ms(30);		// �`���^�����O�h�~
			lf++; //���t���O�ɉ��Z
		}/*
	} while(PSW == SWOFF);
	delay1ms(30);

#################################################################*/
#include <p18f2550.h>
#include <delays.h>

//�|�[�g
#define YLED	LATCbits.LATC0		// RC0�@�o�͂ŉ��FLED
#define RLED	LATCbits.LATC1		// RC1�@�o�͂ŐԐFLED
#define PSW 	PORTCbits.RC2		// RC2�@���͂Ń^�N�gSW
//���t���N�^
#define RPHSW	PORTAbits.RA0		// �E
#define CPHSW	PORTAbits.RA1		// ��
#define LPHSW	PORTAbits.RA2		// ��
#define RPHLED	LATAbits.LATA5		// �E�C���W�P�[�^
#define CPHLED	LATCbits.LATC0		// ���C���W�P�[�^
#define LPHLED	LATCbits.LATC1		// ���C���W�P�[�^
//���[�^
#define RDCM	LATBbits.LATB1		// 	�E
#define LDCM	LATBbits.LATB0		// 	��
#define RDCMLED	LATCbits.LATC7		// 	�E�C���W�P�[�^
#define LDCMLED	LATCbits.LATC6		// 	�E�C���W�P�[�^
//ONOFF
#define BLINE	0
#define WLINE	!BLINE
#define SWON	0
#define SWOFF	!SWON
#define LEDOFF	0
#define LEDON	!LEDOFF
#define DCMOFF	0;
#define DCMON	!DCMOFF

//�֐��̐錾
void init(void);
void allLed(char);
char checkRPHSW(void);	//�E�t�H�g���t���N�^
char checkCPHSW(void);	//���t�H�g���t���N�^
char checkLPHSW(void);	//���t�H�g���t���N�^
void delay1ms(unsigned char);
void delay10ms(unsigned char);
void delay100ms(unsigned char);
void delay1s(unsigned char);
void fowrd(void);	//���[�^�O�i
void right(void);	//���[�^�E��]
void left(void);	//���[�^����]
void Cline(void);	//�����|�C���g�����o

//�ϐ��̐錾�Ə�����
int ff=0,			//�t���O����p�t���O
	rf=0,			//�E�Z���T�t���O
	lf=0;			//���Z���T�t���O
char pf=0,
	cnt=0;
/*======================================
	���C���֐�
======================================*/
void main(void)
{
	init();			//PIC�̏�����

	allLed(LEDON);	//LED�_���m�F
	delay1s(1);
	allLed(LEDOFF);
	
	do {			//�Z���T�̊��x�������[�`��
		checkRPHSW();
		checkCPHSW();
		checkLPHSW();
	} while(PSW == SWOFF);
	delay1ms(30);				//�`���^�����O�h�~
	
	while(PSW == SWON);			//ON�ɂȂ�܂Ōp��
	delay1ms(30);				//�`���^�����O�h�~
	
	do {		//���C���g���[�X
		if(checkRPHSW() == WLINE && checkLPHSW() == WLINE)	fowrd();
		if(checkRPHSW() == BLINE)	left();
		if(checkLPHSW() == BLINE)	right();
		
		} while(PSW == SWOFF);
	delay1ms(30);				//�`���^�����O�h�~
	
	//����A�n�_�ł̓���
	while(pf == 3){
		PORTBbits.RB4 = 0; //���[�^
		PORTBbits.RB5 = 0; //���[�^
		PORTBbits.RB7 = 0; //LED�C���~pt1
	}
	
	//B�n�_�ł̓���
	while(pf == 4){
		if(cnt == 0){
		PORTBbits.RB6 = 0; //LED�C���~pt2
		}
		delay1s(3);
		cnt = 1;
		if(cnt == 1){
		PORTBbits.RB6 = 0; //LED�C���~pt2��~
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
	//ON�ɂȂ�܂�
	while(PSW == SWON);
	delay1ms(30);				//�`���^�����O�h�~
	
	
	//���C���g���[�X�I����̏���
	RDCM = DCMOFF;
	LDCM = DCMOFF;
	allLed(LEDOFF);
	while(1) {
		// ��LED�̓_��
		RLED = LEDON;
		delay100ms(5);
		RLED = LEDOFF;
		delay100ms(5);
	}
	
	while(1);
}
//�O�i
void fowrd(void)
{
	RDCMLED = LEDON;	RDCM = DCMON;
	LDCMLED = LEDON;	LDCM = DCMON;
}

//�E��]
void right(void)
{
	RDCMLED = LEDOFF;	RDCM = DCMOFF;
	LDCMLED = LEDON;	LDCM = DCMON;
}

//����]
void left(void)
{
	RDCMLED = LEDON;	RDCM = DCMON;
	LDCMLED = LEDOFF;	LDCM = DCMOFF;
}

//�E�Z���T�`�F�b�N
char checkRPHSW(void)
{
	char mode;
	
	if(RPHSW == WLINE) {
		mode = WLINE;
		RPHLED = LEDON;
	}
	else {
		mode = BLINE;
		RPHLED = LEDOFF;
	}
	
	return mode;
}

//���Z���T�`�F�b�N
char checkCPHSW(void)
{
	char mode;
	
	if(CPHSW == WLINE) {
		mode = WLINE;
		CPHLED = LEDON;
	}
	else {
		mode = BLINE;
		CPHLED = LEDOFF;
	}
	
	return mode;
}

//���Z���T�`�F�b�N
char checkLPHSW(void)
{
	char mode;
	
	if(LPHSW == WLINE) {
		mode = WLINE;
		LPHLED = LEDON;
	}
	else {
		mode = BLINE;
		LPHLED = LEDOFF;
	}
	
	return mode;
}

//���ׂĂ�LED�𐧌�
void allLed(char mode)
{
	RPHLED  = mode;
	CPHLED  = mode;
	LPHLED  = mode;
	RDCMLED = mode;
	LDCMLED = mode;
}
//PIC�̏�����
void init(void)
{
	ADCON1 |= 0x0F;	//AD�R���o�[�^OFF
	
	//���o�͂̐ݒ�
	//C�|�[�g��USB���ڑ�����Ă���̂Œ��� 0�ŏo��
	TRISA = 0b11000111;
	TRISB = 0b00000000;
	TRISC = 0b00111100;

	//�|�[�g�̏�����
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
}

//1ms�̒x��
void delay1ms(unsigned char unit)
{
	unsigned char i;
	for(i=0; i<unit; i++) {
		Delay100TCYx(120);
	}
}

//10ms�̒x��
void delay10ms(unsigned char unit)
{
	unsigned char i;
	for(i=0; i<unit; i++) {
		Delay1KTCYx(120);	//10ms
	}
}

//100ms�̒x��
void delay100ms(unsigned char unit)
{
	unsigned char i;
	for(i=0; i<unit; i++) {
		Delay10KTCYx(120);	//100ms
	}
}

//1s�̒x��
void delay1s(unsigned char unit)
{
	unsigned char i, j;
	for(j=0; j<unit; j++) {
		for(i=0; i<10; i++) {
			Delay10KTCYx(120);	//100ms
		}
	}
}

void Cline(void){	//�����|�C���g�����o
	if(RPHSW == BLINE && LPHSW == BLINE){
		delay100ms(1);
		if(RPHSW == BLINE && LPHSW == BLINE){
			pf++;
		}
	delay1ms(30);				//�`���^�����O�h�~
	}
}

