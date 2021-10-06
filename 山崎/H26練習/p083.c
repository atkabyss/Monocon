/*======================================
////DDbs93rs03
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2	//l7s
#define l3 LATBbits.LATB3	//r7s
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay1KTCYx(12)
#define D1 Delay1KTCYx(120)
#define D10 Delay10KTCYx(120)
#define bs PORTCbits.RC6
#define rs PORTCbits.RC7

//=====ledst=====
char l7s[] = {
	0b01000000,	//0
	0b01111001,	//1
	0b00100100,	//2
	0b00110000,	//3
	0b00011001,	//4
	0b00010010,	//5
	0b00000010,	//6
	0b01111000,	//7
	0b00000000,	//8
	0b00010000,	//9
	0b00110110,	//Åﬂ -10
	0b00111111,	//-	-11
	0b01111111,	//ns-12
	0b01110111,	//â∫-13
	0b01111110,	//è„-14
	0b01110111,	//-15 li2
	0b01101111,	//-16
	0b01011111,	//-17
	0b01111110,	//-18
	0b01111101,	//-19
	0b01111011,	//-20
	0b00011100,	//-21 il3
	0b00100011,	//-22
};

char STMR[] = {0x08,0x04,0x02,0x01};
char STML[] = {0x01,0x02,0x04,0x08};
//=====fst=====
char a,b,c,d,f,cn;

//=====ilst=====
void led(void);
void ilm(void);
void ilm2(void);
void ilm3(void);

/*======================================
		mp
======================================*/
void main(void){

//=====adcsd=====
	ADCON1 |= 0x0F;
	
//=====i/est=====
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111000;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//=====prs=====
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
//=====al7ssd=====
	l2 = 1;
	l3 = 1;
	l4 = 1;
	l5 = 1;
	
//=====frs=====
	a = 12;
	b = 12;
	c = 12;
	d = 12;
	cn = 0;
	f = 0;
	
	while(1){
		
		if(rs == 1){
			a = 12;
			b = 12;
			c = 12;
			d = 12;
		}
		if(rs == 0){
			d = 8;
			for(cn=0;cn<125;cn++){
				led();
				led();
				if(rs == 1){
					break;
				}
			}
			d = 10;
			for(cn=0;cn<125;cn++){
				led();
				led();
				if(rs == 1){
					break;
				}
			}
			d = 11;
			for(cn=0;cn<125;cn++){
				led();
				led();
				if(rs == 1){
					break;
				}
			}
			a = 0;
			b = 0;
			c = 0;
			while(rs == 0){
				for(cn=0;cn<2;cn++){
					led();
				}
				c++;
				if(c > 9){
					c = 0;
					b++;
					if(b > 9){
						b = 0;
						a++;
						if(a > 9){
							ilm2();
						}
					}
				}
			}
		}
		if(bs == 1){
			a = 12;
			b = 12;
			c = 12;
			d = 12;
		}
		if(bs == 0){
			d = 8;
			for(cn=0;cn<125;cn++){
				led();
				led();
				if(bs == 1)	break;
			}
			d = 10;
			for(cn=0;cn<125;cn++){
				led();
				led();
				if(bs == 1)	break;
			}
			d = 11;
			for(cn=0;cn<125;cn++){
				led();
				led();
				if(bs == 1)	break;
			}
			a = 9;
			b = 9;
			c = 9;
			while(bs == 0){
				for(cn=0;cn<2;cn++){
					led();
				}
				c--;
				if(c < 0){
					c = 9;
					b--;
					if(b < 0){
						b = 9;
						a--;
						if(a < 0){
							ilm3();
						}
					}
				}
			}
		}
	}
}
/*======================================
		ilpt
======================================*/
void led(void){
	LATD = l7s[a];
	l2 = 0;
	D01;
	l2 = 1;
	LATD = l7s[b];
	l3 = 0;
	D01;
	l3 = 1;
	LATD = l7s[c];
	l4 = 0;
	D01;
	l4 = 1;
	LATD = l7s[d];
	l5 = 0;
	D01;
	l5 = 1;
}
void ilm(void){
	while(1){
		a = 13;
		b = 11;
		c = 14;
		d = 14;
		for(cn=0;cn<10;cn++)	led();
		a = 11;
		b = 14;
		c = 14;
		d = 11;
		for(cn=0;cn<10;cn++)	led();
		a = 14;
		b = 14;
		c = 11;
		d = 13;
		for(cn=0;cn<10;cn++)	led();
		a = 14;
		b = 11;
		c = 13;
		d = 13;
		for(cn=0;cn<10;cn++)	led();
		a = 11;
		b = 13;
		c = 13;
		d = 11;
		for(cn=0;cn<10;cn++)	led();
		a = 13;
		b = 13;
		c = 11;
		d = 14;
		for(cn=0;cn<10;cn++)	led();
	}
}
void ilm2(void){
	while(1){
		a = 15;
		b = 18;
		c = 12;
		d = 20;
		for(cn=0;cn<10;cn++)	led();
		a = 16;
		b = 12;
		c = 18;
		d = 15;
		for(cn=0;cn<10;cn++)	led();
		a = 17;
		b = 12;
		c = 15;
		d = 18;
		for(cn=0;cn<10;cn++)	led();
		a = 18;
		b = 15;
		c = 12;
		d = 19;
		for(cn=0;cn<10;cn++)	led();
	}
}

void ilm3(void){
	while(1){
		a = 12;
		b = 12;
		c = 21;
		d = 12;
		for(cn=0;cn<10;cn++)	led();
		a = 12;
		b = 12;
		c = 12;
		d = 21;
		for(cn=0;cn<10;cn++)	led();
		a = 12;
		b = 12;
		c = 12;
		d = 22;
		for(cn=0;cn<10;cn++)	led();
		a = 12;
		b = 12;
		c = 22;
		d = 12;
		for(cn=0;cn<10;cn++)	led();
		a = 12;
		b = 22;
		c = 12;
		d = 12;
		for(cn=0;cn<10;cn++)	led();
		a = 22;
		b = 12;
		c = 12;
		d = 12;
		for(cn=0;cn<10;cn++)	led();
		a = 21;
		b = 12;
		c = 12;
		d = 12;
		for(cn=0;cn<10;cn++)	led();
		a = 12;
		b = 21;
		c = 12;
		d = 12;
		for(cn=0;cn<10;cn++)	led();
		a = 21;
		b = 12;
		c = 12;
		d = 12;
		for(cn=0;cn<10;cn++)	led();
		a = 22;
		b = 12;
		c = 12;
		d = 12;
		for(cn=0;cn<10;cn++)	led();
		a = 12;
		b = 22;
		c = 12;
		d = 12;
		for(cn=0;cn<10;cn++)	led();
		a = 12;
		b = 12;
		c = 22;
		d = 12;
		for(cn=0;cn<10;cn++)	led();
		a = 12;
		b = 12;
		c = 12;
		d = 22;
		for(cn=0;cn<10;cn++)	led();
		a = 12;
		b = 12;
		c = 12;
		d = 21;
		for(cn=0;cn<10;cn++)	led();
	}
}