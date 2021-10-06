/*======================================================================
	�X�e�b�s���O���[�^��CW�ɉ�]
======================================================================*/
#include <p18f4550.h>
#include <delays.h>

//���萔�̒�`
//�X�e�b�s���O���[�^�̗㎥��`
char STM[] = {0x01, 0x02, 0x04, 0x08};

/*--------------------------------------
	���C���֐�
--------------------------------------*/
void main(void)
{
	// ���ϐ��̒�`
	char i;
	
	//�����������
	ADCON1 |= 0x0F; //AD�R���o�[�^OFF
	
	//�����o�͂̐ݒ�
	TRISA = 0b11000000; //A�|�[�gRA0-5�͏o��(0)
	TRISB = 0b00000000; //B�|�[�g�͂��ׂďo��(0)
	TRISC = 0b11111100; //C�|�[�g��RC0,1�݂̂��o��(0)
	TRISD = 0b00000000; //D�|�[�g�͂��ׂďo��(0)
	TRISE = 0b11111000; //E�|�[�g�͂��ׂďo��(0)
	
	// ���|�[�g�̏����� ���ׂ�0
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	//��4��7SEG������
	LATBbits.LATB2 = 1;
	LATBbits.LATB3 = 1;
	LATBbits.LATB4 = 1;
	LATBbits.LATB5 = 1;
	i = 0;
	while(1){
		if(PORTCbits.RC2 == 0){ //�^�N�g�X�C�b�`ON
			LATD = 0b00010000; //DC���[�^��CW���Z�b�g
			LATDbits.LATD7 = 0;
			LATDbits.LATD7 = 1;
			LATDbits.LATD7 = 0;
			}
		else{
			LATD = 0b00000000; //DC���[�^��STOP���Z�b�g
			LATDbits.LATD7 = 0;
			LATDbits.LATD7 = 1;
			LATDbits.LATD7 = 0;
		}
	}
}
