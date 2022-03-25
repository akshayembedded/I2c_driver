#include <avr/io.h>
#include <util/delay.h>
void i2c_init();
char i2c_statusw();
void trans(char a)
{
	while((UCSRA&0x20)==0);//UDR empty when 5th bit in UCSRA is 1
	UDR=a;
}
void i2c_statusr(char a);
int main(void)
{
	char a;
UCSRC=0x86;//1<<URSEL|1<<UCZ1|1<<UCZ2
UCSRA=1<<U2X;
UCSRB=(1<<TXEN);
UBRRL=103;
UBRRH=0;


	DDRD=0xff;

	i2c_init();
	a=i2c_statusw();
	trans(a);
	a=i2c_statusw();
	trans(a);
	while(1)
	{

	}
}

void i2c_init()
{
	DDRC=0;//1111 1111
	TWAR=0x32;// 0001 000 0   0110 1000 0x61

	TWCR=0x44;//ack

	TWCR|=0x80;//TWCR=TWCR|10
	while((TWCR&(0x80))==0);//slave address
}

char i2c_statusw()//master to slave
{
	TWCR=0x44;//
	TWCR|=0x80;
	while((TWCR&(0x80))==0);//
	return TWDR;
	//1 clear flag bit lpc2138/avr 0 1
}

void i2c_statusr(char a)
{
	TWDR=a;
	TWCR=0x44;//
	TWCR|=0x80;
	while((TWCR&(0x80))==0);
	//1 clear flag bit lpc2138/avr 0 1
}