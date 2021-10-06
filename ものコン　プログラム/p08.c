/*======================================
���Z�����̂Â���R���e�X�g �֓��n��\�I��
�d�q��H�g�ݗ��ĕ���

�쐬�� 8��23��
�쐬�� �Έ䋱��
�����w�Z �����s�����O�H�ƍ����w�Z

�ۑ薼 �ۑ�1
�ۑ�ԍ� p01
======================================*/

#include <xc.h>
#define _XTAL_FREQ  48000000
#define l0 LATBbits.LATB0		//7seg0
#define l1 LATBbits.LATB1		//7seg1
#define l2 LATBbits.LATB2		//7seg2
#define l3 LATBbits.LATB3		//7seg3
#define TSR PORTEbits.RE2		//�ԃ^�N�g�X�C�b�`
#define TSW PORTEbits.RE1		//�g�O���X�C�b�`
#define TSB PORTEbits.RE0		//���^�N�g�X�C�b�`
#define de __delay_ms(1)

//�ϐ��̐錾
int a,b,c,d,e,f,i,k=0,k2=0;

//�֐��̐錾
void t(void);
void x(void);

void main(void){
	//PIC�̐ݒ�
	ADCON1 |= 0x0F;		//AD�R���o�[�^OFF
	
	//���o�͂̐ݒ�
	TRISA = 0b11000000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111111;
	
	//�|�[�g�̏�����
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	//4��7SEG������
	l0 = 1;
	l1 = 1;
	l2 = 1;
	l3 = 1;
	
	//�����\��
	LATD = 0b00000000;		//8��\��
	l0 = 0;
	l1 = 1;
	
	//���C���֐�
	while(1){
		for(i=1;i<1001;i++){		//10�b��
			__delay_ms(10);
			k = i / 100;
			if (k == 10) {
				k = 0;
			}
			if (k2 == 5){
				k2 = 0;	
			}
			t();
		}
		k2 = k2 + 1;
		/*
		for(i=0;i<100;i++){		//1�b��
			__delay_ms(10);
			x();
		}
		*/
	}
}

//����֐�
void t(void){
	
	if (k == 0) {
		LATD = 0b01000000;		//0��\��
		l0 = 1;
		l1 = 0;
	}
	if (k == 1) {
		LATD = 0b01111001;		//1��\��
		l0 = 1;
		l1 = 0;
		
	}
	if (k == 2) {
		LATD = 0b00100100;		//2��\��
		l0 = 1;
		l1 = 0;
	}
	if (k == 3) {
		LATD = 0b00110000;		//3��\��
		l0 = 1;
		l1 = 0;
	}
	if (k == 4) {
		LATD = 0b00011001;		//4��\��
		l0 = 1;
		l1 = 0;
	}
	if (k == 5) {
		LATD = 0b00010010;		//5��\��
		l0 = 1;
		l1 = 0;
	}
	if (k == 6) {
		LATD = 0b00000010;		//6��\��
		l0 = 1;
		l1 = 0;
	}
	if (k == 7) {
		LATD = 0b01111000;		//7��\��
		l0 = 1;
		l1 = 0;
	}
	if (k == 8) {
		LATD = 0b00000000;		//8��\��
		l0 = 1;
		l1 = 0;
	}
	if (k == 9) {
		LATD = 0b00010000;		//9��\��
		l0 = 1;
		l1 = 0;
	}	
	
	de;
	
	if (k2 == 0) {
		LATD = 0b01000000;		//0��\��
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 1) {
		LATD = 0b01111001;		//1��\��
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 2) {
		LATD = 0b00100100;		//2��\��
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 3) {
		LATD = 0b00110000;		//3��\��
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 4) {
		LATD = 0b00011001;		//4��\��
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 5) {
		LATD = 0b00010010;		//5��\��
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 6) {
		LATD = 0b00000010;		//6��\��
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 7) {
		LATD = 0b01111000;		//7��\��
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 8) {
		LATD = 0b00000000;		//8��\��
		l0 = 0;
		l1 = 1;

	}
	if (k2 == 9) {
		LATD = 0b00010000;		//9��\��
		l0 = 0;
		l1 = 1;

	}
	
	de;
	
}

/*
void x(void){
	LATD = 0b00011001;		//4��\��
	l0 = 0;
	l1 = 1;
	de;
		
	LATD = 0b01111111;		//����
	l0 = 1;
	l1 = 1;
}
*/
