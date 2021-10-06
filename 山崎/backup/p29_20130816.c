/*============��{���============
H25�@���Z�����̂Â���R���e�X�g
�d�q��H�g������@�����s���

�쐬�����F8��6��
�쐬�ҁFNo.?? �R��W�j
�����w�Z�F�r��H�ƍ����w�Z

�t�@�C����:p29.c
�ۑ�ԍ�:2��
================================*/
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2 //����7�Z�O�����gLED
#define L3 LATBbits.LATB3 //�E��7�Z�O�����gLED
#define L4 LATBbits.LATB4
#define L5 LATBbits.LATB5
#define L7 LATDbits.LATD7 //�N���b�N�p���X
#define TGSW PORTAbits.RA5 //�g�O���X�C�b�`
#define HSW PORTAbits.RA4 //�t�H�g�C���^���v�^
#define D1k Delay1KTCYx(120) //��0.1ms�̒x��
#define D10k Delay10KTCYx(120) //��1ms�̒x��

//==�萔�̐錾==
char STMR[] = {0x08,0x04,0x02,0x01}; //�X�e�b�s���O���[�^���E��]
char STML[] = {0x01,0x02,0x04,0x08}; //�X�e�b�s���O���[�^������]
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
	0b00001000, //A
	0b00000011, //B
	0b00100111, //C
	0b00100001, //D
	0b00000110, //E
	0b00001110, //F
	0b00001001, //H
	0b01000111, //L
};
//==�ϐ��̐錾==
char a,b,i,j,t;

//==�֐��̐錾==
void dd(void); //7�Z�O�����gLED�̗����\��
void stmr(void); //�X�e�b�s���O���[�^���E��]
void seml(void); //�X�e�b�s���O���[�^������]
void dcmr(void); //DC���[�^���E��]
void dcml(void); //DC���[�^������]

/*=========================
		���C���֐�
=========================*/
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
	a = 0;
	b = 0;
	i = 10;
	j = 0;
	t = 0;
	
while(1){
	LATD = L7s[i]; //�f�[�^�̃Z�b�g
	L2 = 0; //����7�Z�O��\��
	
	if(TGSW == 0){
		LATD = L7s[i]; //�f�[�^�̃Z�b�g
		
		i++;
		
		D10k; //��1�b�̒x��
		D10k;
		D10k;
		D10k;
		D10k;
		D10k;
		D10k;
		D10k;
		D10k;
		D10k;
	
		if(i == 16){
			i = 10;
		}
	}
}
}

//==�֐��̐錾==
void dd(void){ //7�Z�O�����gLED�̗����\��
	LATD = L7s[i];
	L2 = 0;
	L3 = 1;
	D1k;
	LATD = L7s[j];
	L2 = 1;
	L3 = 0;
	D1k;
}

void stmr(void){ //�X�e�b�s���O���[�^���E��]
	for(a = 0;a < 48;a++){
		LATD = STMR[b]; //�f�[�^�̃Z�b�g
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k; //�`���^�����O�h�~�̒x��
		
		b++;
		
		if(b>4){ //4�ȏ�̃f�[�^�͂Ȃ�����0�ɖ߂�
			b = 0;
		}
	}
}

void seml(void){ //�X�e�b�s���O���[�^������]
	for(a = 0;a < 48;a++){
		LATD = STML[b]; //�f�[�^�̃Z�b�g
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k; //�`���^�����O�h�~�̒x��
		
		b++;
		
		if(b>4){ //4�ȏ�̃f�[�^�͂Ȃ�����0�ɖ߂�
			b = 0;
		}
	}
}

void dcmr(void){ //DC���[�^���E��]
	LATD = 0b00100000;
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
}

void dcml(void){ //DC���[�^���E��]
	LATD = 0b00100000;
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
}
