/*======================================================================
	�X�e�b�s���O���[�^��CW�ɉ�]
======================================================================*/
#include <p18f4550.h>
#include <delays.h>

//���萔�̒�`
//�X�e�b�s���O���[�^�̗㎥��`
char STM[] = {0x01, 0x02, 0x04, 0x08};
char Led7seg[] = {
	0b01111001,
	0b00100100,
	0b00110000,
	0b00011001,
	0b00010010,
};

/*--------------------------------------
	���C���֐�
--------------------------------------*/
void main(void)
{
	// ���ϐ��̒�`
	char i,j,k;
	
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
	j = 0;
	k = 1;
	while(1){         
		for(k=1,k<=5,k++){
			for(j=0,j<=48,j++){
			LATD = STM[i]; //�f�[�^�̃Z�b�g
			LATDbits.LATD7 = 0;
			LATDbits.LATD7 = 1;
			LATDbits.LATD7 = 0;
			
			LATD = Led7seg[k]; 
			LATBbits.LATB2 = 0;
			Delay1KTCYx(120); //�E���h�~��wait
			i++;
			if(i>=4){
				i = 0;
		}
			//while(1)
	}
	}
	}
}