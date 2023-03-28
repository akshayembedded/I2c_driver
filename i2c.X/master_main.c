#include<pic18.h>
void i2c_init()
{
TRISC4=TRISC3=1;
SSPSTAT=0x80;//1000
SSPCON1=0x28;//
SSPCON2=0x00;
SSPADD=49;
}
void i2c_start()
{
SEN=1;
while(SEN==1);//sen
}
void i2c_stop()
{
PEN=1;
while(PEN==1);//
}
void i2c_data(char a)
{
SSPIF=0;
SSPBUF=a;
while(SSPIF==0);
}
char i2c_read(char a)
{
RCEN=1;//receive 
while(RCEN);//
ACKDT=a;//1- NACK before stopping 0->ack
ACKEN=1;
while(ACKEN);
return SSPBUF;
}
void main()
{
	int i;
for(i=0;i<=10000;i++);
i2c_init();
i2c_start();//start slavead+R/w  
i2c_data(0x32);//0x32
i2c_data('a');
i2c_data('g');
i2c_stop();
while(1) 	
{

}
}
