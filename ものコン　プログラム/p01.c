/*=====================================
      �X�e�b�s���O���[�^�������ɉ�]
=====================================*/
#include <xc.h>
#define _XTAL_FREQ 48000000
//�X�e�b�s���O���[�^�̗㎥��`
char stm[] = {0x01, 0x02, 0x04, 0x08};
/*--------------------------------------
 ���C���֐�
---------------------------------------*/
void main(void)
{
	//���ϐ��̒�`
	char i;            
	//�����������
	ADCON1 |= 0x0F       //AD�R���o�[�^�n�e�e
	//�����o�͂̐ݒ�����܂�
	TRISA = 0b11000000;     //A�|�[�gRA0-5�͏o��
	TRISB = 0b00000000;     //B�|�[�g�͂��ׂďo��
	TRISC = 0b11111100;     //C�|�[�g��RC0.1�̂ݏo��
	TRISD = 0b00000000;     //D�|�[�g�͂��ׂďo��
	TRISE = 0b00000111;     //E�|�[�gRE0-2�͓���
	
	//���|�[�g�̏��������ׂ�0
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	//��4��7SEG
	LATBbits.LATB2 = 0;
	LATBbits.LATB2 = 1;
	LATBbits.LATB2 = 2;
	LATBbits.LATB2 = 3;
	i = 0;             //
	while(1) {
		//�X�e�b�s���O���[�^�̉�]�P�p���X��
		LATD = stm[1];       //�f�[�^�̃Z�b�g
		LATBbits.LATD7 = 0;
		LATBbits.LATB7 = 1;
		LATBbits.LATB7 = 0;
		__delay_ms(10);
		
		i++;
		if(i>=4) { // 4�Ԉȏ�̃p�^�[���͂Ȃ��̂�
			i = 0; //0�Ԃ̃p�^�[���ɖ߂�
	
	