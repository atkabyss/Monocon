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
#define TSW PORTEbits.RE1		//���^�N�g�X�C�b�`
#define TSB PORTEbits.RE0		//���^�N�g�X�C�b�`
#define de __delay_ms(1)

//�ϐ��̐錾
int a,b,c,d,e,f,i,k=0,k2=0;

//�֐��̐錾
void t(void);
void x(void);
void Time(void);

//�֐��̐錾
char Led7seg[] ={
	0b01111110,
	0b01111101,
	0b01111011,
	0b01110111,
	0b01101111,
	0b01011111,
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
	
	while(1){
		if(TSW == 0 && TSB == 1){
			LATD = 0b11000000;
			l0 = 0;
			l1 = 1;
			__delay_ms(10);
			
			LATD = 0b11000000;
			l0 = 1;
			l1 = 0;
			__delay_ms(10);
			
			for(i=0;i<10;i++){
				LATD = 0b11000000;
				l0 = 0;
				l1 = 1;
				__delay_ms(10);
				
				LATD = 0b01111111;
				l0 = 1;
				l1 = 1;
				__delay_ms(10);
			}
		}else{
			LATD = 0b11000000;
			l0 = 0;
			l1 = 0;
		}	
		
		if(TSW == 1 && TSB == 0){
			LATD = 0b11000000;
			l0 = 0;
			l1 = 1;
			__delay_ms(10);
			
			LATD = 0b11000000;
			l0 = 1;
			l1 = 0;
			__delay_ms(10);
			
			for(i=0;i<8;i++){
				LATD = 0b11000000;
				l0 = 1;
				l1 = 0;
				__delay_ms(10);
				
				LATD = 0b11111111;
				l0 = 1;
				l1 = 1;
				__delay_ms(10);
			}
		}else{
			LATD = 0b11000000;
			l0 = 0;
			l1 = 0;
		}	
	}
}