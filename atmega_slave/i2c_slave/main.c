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



	DDRD=0xff;

	i2c_init();
	i2c_statusr(PINA);
	i2c_statusr(PIND);
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