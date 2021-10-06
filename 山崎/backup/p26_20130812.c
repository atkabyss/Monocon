//=========================
//2013.8.2
//H24�֓���� �ۑ�3
//�r��H�ƍ����w�Z
//�R��W�j
//=========================
#include<p18f4550.h>
#include<delays.h>
                                               
#define L2 LATBbits.LATB2  //"LATBbits.LATB2"��"L2"�Ƃ��Ē�`
#define L3 LATBbits.LATB3  //"LATBbits.LATB3"��"L3"�Ƃ��Ē�`
#define L4 LATBbits.LATB4  //"LATBbits.LATB4"��"L4"�Ƃ��Ē�`
#define L5 LATBbits.LATB5  //"LATBbits.LATB5"��"L5"�Ƃ��Ē�`
#define L7 LATDbits.LATD7  //"LATDbits.LATD7"��"L7"�Ƃ��Ē�`
#define D1k Delay1KTCYx(120)  //"Delay1KTCYx(120)"��"D1k"�Ƃ��Ē�`
#define D10k Delay10KTCYx(120)  //"Delay10KTCYx(120)"��"D10k"�Ƃ��Ē�`
#define R3 PORTAbits.RA3  //"PORTAbits.RA3"��"R3"�Ƃ��Ē�`
#define R4 PORTAbits.RA4  //"PORTAbits.RA4"��"R4"�Ƃ��Ē�`
#define R5 PORTAbits.RA5  //"PORTAbits.RA5"��"R5"�Ƃ��Ē�`
#define L7s Led7seg  //"Led7seg"��"L7s"�Ƃ��Ē�`

//==�萔�̐錾==
char L7s[] = {
	0b01000000,  //0
	0b01111001,  //1
	0b00100100,  //2
	0b00110000,  //3
	0b00011001,  //4
	0b00010010,  //5 
	0b00000010,  //6
	0b01011000,  //7
	0b00000000,  //8
	0b00010000,  //9
	0b00001001,  //H
	0b01000111,  //L
	0b01111111,  //��\��
};
char STMl[] = {0x08, 0x04, 0x02, 0x01};
char STMr[] = {0x01, 0x02, 0x04, 0x08};

//==�ϐ��̐錾==
char a,b,i,j,k,l;

//==�֐��̐錾==
void STML(void);
void STMR(void);
void DCML(void);
void DCMR(void);
void dd(void);

//==============���C���֐�==============
void main(void){
	
	ADCON1 |= 0x0F;  //AD�R���o�[�^��OFF
	
//=============���o�͂̐ݒ�=============
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//============�|�[�g�̏�����============
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
	a = 0;  //�t���O�p�ϐ�
	b = 0;  //�t���O�p�ϐ�
	i = 0;
	j = 0;
	k = 0;
	l = 0;
	
while(1){
	if(R5 == 0){
		STML();
	}
	
	if(R5 == 1){
		a = 0;
	}
	
}
}
//==�֐��̐錾==
void STML(void){
	for(a=0;a<48;a++){  //�X�e�b�s���O���[�^�����v����1��]������
		LATD = STMl[k];
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k;  //�E���h�~��wait 
		
		k++;
		
		if(k >= 4){
			k = 0;
		}
		
		if(R5 == 1){
			a = 50;
		}
	}
}
void STMR(void){
	for(a=0;a>48;a++){  //�X�e�b�s���O���[�^�𔽎��v����1��]������
		LATD = STMr[k];
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k;  //�E���h�~��wait
		
		k++;
		
		if(k >= 4){
			k = 0;
		}
	}
}
void DCML(void){  //DC���[�^�����v���ɉ�]
	LATD = 0b00100000;
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
}
	
void DCMR(void){  //DC���[�^�𔽎��v���ɉ�]
	LATD = 0b00010000;
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
}
	
void dd(void){  //7�Z�O�����gLED�̗�����\��
	LATD = L7s[i];
	L2 = 0;
	L3 = 1;
	D1k;
	LATD = L7s[j];
	L3 = 0;
	L2 = 1;
	D1k;
}