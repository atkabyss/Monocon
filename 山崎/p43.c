/*============��{���============
H22 ���Z�����̂Â���R���e�X�g
�d�q��H�g������@�֓��n��\�I��

�쐬�����F8��8��
�쐬�ҁF�R��W�j
�����w�Z�F�s���r��H�ƍ����w�Z

�t�@�C�����Fp42.c
�ۑ�ԍ��F5��
================================*/
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2 //����7�Z�O�����gLED
#define L3 LATBbits.LATB3 //�E��7�Z�O�����gLED
#define L4 LATBbits.LATB4
#define L5 LATBbits.LATB5
#define L7 LATDbits.LATD7
#define D1k Delay1KTCYx(120) //��0.1ms�̒x��
#define D10k Delay10KTCYx(120) //��1ms�̒x��
#define GSW PORTAbits.RA5 //�΃^�N�g
#define HSW PORTAbits.RA4 //�z�g�C���^���v�^

//==�萔�̐錾==
char L7s[] = { //7�Z�O�����gLED�̕\���ݒ�
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
char STMR[] = {0x08,0x04,0x02,0x01}; //�X�e�b�s���O���[�^���E��]
char STML[] = {0x01,0x02,0x04,0x08}; //�X�e�b�s���O���[�^������]

//==�ϐ��̐錾==
char a,b,c,i,j,k,l,t;

//==�֐��̐錾==
void dd(void); //���E��7�Z�O�����gLED�𓯎��ɕ\��
void stmr(void);
void stml(void);

//===========���C���֐�==========
void main(void){
	
	ADCON1 |= 0x0F; //AD�R���o�[�^OFF

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
	a = 0; //�x������
	b = 0; //�t���O�p
	c = 0;
	i = 0; //����7�Z�O�����gLED�\������
	j = 0; //�E��7�Z�O�����gLED�\������
	k = 0; //�X�e�b�s���O���[�^�̉�]����
	l = 0;
	t = 0; //�������p
	
while(1){
	if(t == 0){
		LATD = L7s[i];
		L3 = 0;
		t = 1;
	}
	
	if(GSW == 0){
		b = 1;
	}
	
	if(b == 1){
		for(a = 0;a < 48;a++){
			i++;
			LATD = L7s[i];
			L3 = 0;
			D1k;
			L3 = 1;
			
			stmr();
			
			if(i > 2){
				i = 3;
				while(1){
					L3 = 0;
				}
				}
			}
		}
	}
}
//==�֐��̐錾==
void dd(void){ //���E��7�Z�O�����gLED�𓯎��ɕ\��
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
	for(c = 0;c < 48;c++){
		LATD = STMR[k];
		L7 = 0;
		L7 = 1;
		L7 = 0;
		LATD = L7s[i];
		L3 = 0;
		D1k;
		L3 = 1;
		
		k++;
		
		if(k > 4){
			k = 0;
		}
	}
}
void stml(void);