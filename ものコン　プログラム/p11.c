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

//�֐��̐錾
char Led7seg[] ={
	0b01000000,
	0b01111001,
	0b00100100,
	0b00110000,
};

char STM[] = {0x08, 0x04, 0x02, 0x01};
char STN[] = {0x01, 0x02, 0x04, 0x08};

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
	LATD = 0b01111001;		//8��\��
	l0 = 0;
	l1 = 1;
	
	LATD = 0b01000000;
	l0 = 1;
	l1 = 0;
	
	//���C���֐�
	while(1){
		if(TSR == 0 && TSB == 1){
			LATD = STM[i];
			LATDbits.LATD7 = 0;
			LATDbits.LATD7 = 1;
			LATDbits.LATD7 = 0;
			__delay_ms(10);
			
			i++;
			if(i>=3){
				i=0;
			}
		}
		
		if(TSR == 0 && TSB == 0){
			LATD = STN[b];
			LATDbits.LATD7 = 0;
			LATDbits.LATD7 = 1;
			LATDbits.LATD7 = 0;
			__delay_ms(10);
			
			b++;
			if(b>=3){
				b=0;
			}
		}
	}
}