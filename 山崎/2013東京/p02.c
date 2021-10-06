/*================��{���=================
����25�N�x�@���Z�����̂Â���R���e�X�g
�d�q��H�g������@�����s���

�쐬�����F8��10��
�쐬�ҁF2�ԁ@�R��W�j
�����w�Z�F�����s���r��H�ƍ����w�Z

�t�@�C�����Fp02.c
�ۑ�ԍ��F2��
=========================================*/
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2 //����7�Z�O�����gLED
#define L3 LATBbits.LATB3 //�E��7�Z�O�����gLED
#define L4 LATBbits.LATB4
#define L5 LATBbits.LATB5
#define L7 LATDbits.LATD7
#define D1k Delay1KTCYx(120) //��0.1ms�̒x��
#define D10k Delay10KTCYx(120) //��1ms�̒x��
#define GSW PORTAbits.RA5 //�΃^�N�g�X�C�b�`
#define OSW PORTAbits.RA3 //��^�N�g�X�C�b�`

//==�萔�̐錾==
char L7s[] = { //7�Z�O�����gLED�̕\������
	0b01000000, //0
	0b01111001, //1
	0b00100100, //2
	0b00010010, //5
	0b00000000, //8
	0b01111110, //�C���~�l�[�V�����p�^�[��1
	0b01111101, //�C���~�l�[�V�����p�^�[��2
	0b01111011, //�C���~�l�[�V�����p�^�[��3
	0b01110111, //�C���~�l�[�V�����p�^�[��4
	0b01101111, //�C���~�l�[�V�����p�^�[��5
	0b01011111, //�C���~�l�[�V�����p�^�[��6
	0b00101011, //OFF
	0b01110111, //ON
	0b01111111, //��\��
};
char STMR[] = {0x08,0x04,0x02,0x01}; //�X�e�b�s���O���[�^���E��]
char STML[] = {0x01,0x02,0x04,0x08}; //�X�e�b�s���O���[�^������]
	
//==�ϐ��̐錾==
char a,b,i,j,k,f;

//==�֐��̐錾==
void dd(void); //7�Z�O�����gLED�̗����𓯎��ɕ\��
void stmr(void); //�X�e�b�s���O���[�^���E��]
void stml(void); //�X�e�b�s���O���[�^������]
void dcmr(void); //DC���[�^���E��]

//=================���C���֐�=================
void main(void)
{
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
	a = 0; //�X�e�b�s���O���[�^�̉�]����p
	b = 0; //���g�p
	i = 0; //����7�Z�O�����gLED�\���p
	j = 0; //�E��7�Z�O�����gLED�\���p
	k = 0; //���g�p
	f = 0; //�t���O�p
	
while(1){
	if(OSW == 1 && GSW == 1){ //�΃^�N�g�X�C�b�`�ƞ�^�N�g�X�C�b�`��OFF�̂Ƃ�
		LATD = L7s[0]; //�f�[�^�̃Z�b�g
		L2 = 0; //����7�Z�O�����gLED�̓_��
	}
	if(OSW == 0 && GSW == 1){ //�΃^�N�g�X�C�b�`��ON�A��^�N�g�X�C�b�`��OFF�̂Ƃ�
		LATD = L7s[1]; //�f�[�^�̃Z�b�g
		L2 = 0; //����7�Z�O�����gLED�̓_��
	}
	if(OSW == 1 && GSW == 0){ //�΃^�N�g�X�C�b�`��OFF�A��^�N�g�X�C�b�`��ON�̂Ƃ�
		LATD = L7s[1]; //�f�[�^�̃Z�b�g
		L2 = 0; //����7�Z�O�����gLED�̓_��
	}
	if(OSW == 0 && GSW == 0){ //�΃^�N�g�X�C�b�`�ƞ�^�N�g�X�C�b�`��ON�̂Ƃ�
		LATD = L7s[2]; //�f�[�^�̃Z�b�g
		L2 = 0; //����7�Z�O�����gLED�̓_��
	}
}
}
//==�֐��̐錾==
void dd(void){ //7�Z�O�����gLED�̗����𓯎��ɕ\��
	LATD = L7s[i]; //����7�Z�O�����gLED�̃f�[�^���Z�b�g
	L2 = 0; //����7�Z�O�����gLED��ON
	L3 = 1; //�E��7�Z�O�����gLED��OFF
	D1k; //�E���h�~�̒x��
	LATD = L7s[j]; //�E��7�Z�O�����gLED�̃f�[�^���Z�b�g
	L2 = 1; //����7�Z�O�����gLED��OFF
	L3 = 0; //�E��7�Z�O�����gLED��ON
	D1k; //�E���h�~�̒x��
}
void stmr(void){ //�X�e�b�s���O���[�^���E��]
	LATD = STMR[a]; //�f�[�^�̃Z�b�g
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k; //�E���h�~�̒x��
	
	a++;
	
	if(a > 4){ //4�ȏ�̃f�[�^���Ȃ�����0�ɖ߂�
		a = 0;
	}
}
void stml(void){ //�X�e�b�s���O���[�^������]
	LATD = STML[a]; //�f�[�^�̃Z�b�g
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k; //�E���h�~�̒x��
	
	a++;
	
	if(a > 4){ //4�ȏ�̃f�[�^���Ȃ�����0�ɖ߂�
		a = 0;
	}
}
void dcmr(void){ //DC���[�^���E��]
	LATD = 0b00100000; //�f�[�^�̃Z�b�g
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k; //�E���h�~�̒x��
}
