/*==========��{���==========
H24 ���Z�����̂Â���R���e�X�g
�d�q��H�g������@�����s���

�쐬�����F8��7��
�쐬�ҁF�R��W�j
�����w�Z�F�s���r��H�ƍ����w�Z

�t�@�C�����Fp39.c
�ۑ�ԍ��F6��
============================*/
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2 //����7�Z�O�����gLED
#define L3 LATBbits.LATB3 //�E��7�Z�O�����gLED
#define L4 LATBbits.LATB4
#define L5 LATBbits.LATB5
#define L7 LATDbits.LATD7
#define D1k Delay1KTCYx(120) //��0.1ms�̒x��
#define D10k Delay10KTCYx(120) //��1ms�̒x��
#define BSW PORTAbits.RA4 //�^�N�g
#define RSW PORTAbits.RA3 //�ԃ^�N�g

//==�萔�̐錾==
char L7s[] = { //7�Z�O�����gLED�̕\������
	0b01000000, //0
	0b01111001, //1
	0b00100100, //2
	0b00110000, //3
	0b00011001, //4
	0b00010010, //5
	0b00000010, //6
	0b01011000, //7
	0b00000000, //8
	0b00010000, //9
	0b00100000, //A
	0b00000011, //B
	0b00100111, //C
	0b00100001, //D
	0b00000100, //E
	0b00001110, //F
	0b00011100, //OFF
	0b00100011, //ON
	0b01111111, //��\��
};
char STMR[] = {0x08,0x04,0x02,0x01}; //�X�e�b�s���O���[�^���E��]
char STML[] = {0x01,0x02,0x04,0x08}; //�X�e�b�s���O���[�^������]

//==�ϐ��̐錾==
char a,b,c,i,j,k,l,m,t;

//==�֐��̐錾==
void stmr(void); //�X�e�b�s���O���[�^���E��]
void stml90(void); //�X�e�b�s���O���[�^������90�x��]
void stml180(void); //�X�e�b�s���O���[�^������180�x��]
void dd(void); //7�Z�O�����gLED�̗�����\��
void cu(void); //7�Z�O�����gLED�̃J�E���g�A�b�v

//==========���C���֐�==========
void main(void){
	
	ADCON1 |= 0x0F; //AD�R���o�[�^��OFF
	
//=====���o�͂̐ݒ�=====
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;

//=====�|�[�g�̏�����=====
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;

//=====���ׂĂ�7�Z�O�����gLED������=====
	L2 = 1;
	L3 = 1;
	L4 = 1;
	L5 = 1;
	
//==�ϐ��̏�����==
	a = 0; //�X�e�b�s���O���[�^����
	b = 0; //���g�p
	c = 0; //���g�p
	i = 0; //7�Z�O�����gLED
	j = 0; //7�Z�O�����gLED
	k = 0; //���g�p
	l = 0; //���g�p
	m = 0; //�X�e�b�s���O���[�^����
	t = 0; //���g�p
	
while(1){
	if(BSW == 0){
		stml180();
	}
	if(RSW == 0){
		stml90();
	}
	}
}
//==�֐��̐錾==
void stmr(void){ //�X�e�b�s���O���[�^���E��]
		LATD = STMR[m];
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k; //�E���h�~�̒x��

		m++;
		
		if(m >= 4){
			m = 0;
		}
}
void stml180(void){ //�X�e�b�s���O���[�^������90�x��]
	for(a = 0;a > 24;a++){
		LATD = STML[m];
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k; //�E���h�~�̒x��
			
		m++;

		if(m >= 4){
			m = 0;
		}
	}
}
void stml90(void){ //�X�e�b�s���O���[�^������90�x��]
	for(a = 0;a > 12;a++){
		LATD = STML[m];
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k; //�E���h�~�̒x��
			
		m++;

		if(m >= 4){
			m = 0;
		}
	}
}
void dd(void){ //7�Z�O�����gLED�̗�����\��
	LATD = L7s[i]; //�����f�[�^�̃Z�b�g
	L2 = 0;
	L3 = 1;
	D1k;
	LATD = L7s[j]; //�E���f�[�^�̃Z�b�g
	L2 = 1;
	L3 = 0;
	D1k;
}
void cu(void){ //7�Z�O�����gLED�̃J�E���g�A�b�v
	LATD = L7s[j];
	L3 = 0;
	
	j++;
	
	D10k;
	D10k;
	D10k;
	D10k;
	D10k;
	D10k;
	D10k;
	D10k;
	D10k;
	D10k;
	
	if(j > 15){
		j = 10;
	}
}
