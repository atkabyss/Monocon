//==========================
//2013.7.30
//H23 �ۑ�5
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
#define D1k Delay1KTCYx(120)  //"Delay1KTCYx(120)"��"D1k"�Ƃ��Ē�`

//==�萔�̐錾==
char Led7seg[] = {  //7�Z�O�����gLED�̕\������
	0b01000000,  //0
	0b01111001,  //1
	0b00111111,  //-
};
char STML[] = {0x08,0x04,0x02,0x01}; //�X�e�b�s���O���[�^���E��]

//==�ϐ��̐錾==
char i,j,k,l,ts;

//==�֐��̐錾==
void STML1(void);  //�X�e�b�s���O���[�^��1��]
void DD(void);  //7�Z�O�����gLED�̗�����\��

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
	i = 0;  
	j = 2;
	k = 2;
	ts = 0;  //�t���O�p
	
while(1)
{   
	L2 = 0;
	L3 = 0;	
	DD();
	
	if(R4 == 0 && ts == 0){
		ts = 1;  //�v���O�������s���̃^�N�g�X�C�b�`�̓��͂�����
		j = 0;
		k = 0;
		STML1();
		
		if(k>2){  //2�i���̌J��オ�菈��
			k = 0;
			j++;
		}
		
		DD();
		ts = 0;  //�^�N�g�X�C�b�`�̓��͂�����
}
}
}
//==�֐��̐錾==
void STML1(void){  //�X�e�b�s���O���[�^���E������1��]
	for(l=0;l<48;l++){
	LATD = STML[i];  //�f�[�^�̃Z�b�g
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;  //�E���h�~��wait
	i++;
	if(i>=4){  //4�ȏ�̃f�[�^�����݂��Ȃ�����
		i = 0;
		k++;  //�X�e�b�s���O���[�^�̉�]����1�����Z
	}
	}
}

void DD(void){  //7�Z�O�����gLED�̗�����\��
	LATD = Led7seg[j];  //����7�Z�O�����gLED�̃f�[�^���Z�b�g
	L2 = 0;  //����7�Z�O�����gLED��_��
	L3 = 1;  //�E��7�Z�O�����gLED������
	D1k;
	LATD = Led7seg[k];  //�E��7�Z�O�����gLED�̃f�[�^���Z�b�g
	L3 = 0;  //�E��7�Z�O�����gLED��_��
	L2 = 1;  //����7�Z�O�����gLED������
	D1k;
	L2 = 1;
	L3 = 1;
}
