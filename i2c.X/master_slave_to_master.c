#include<pic18.h>
void i2c_init()
{
SSPSTAT=0x00;//1000
SSPCON1=0x28;//
SSPCON2=0x00;
SSPADD=49;
}
void i2c_start()
{
SEN=1;
while(SEN==1);//
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
void txn(char a)
{
		while(TXIF==0);//stage
		TXREG=a;
}

void main()
{
	int i;
    char a;

	SPBRG=129;
	TXSTA=0x24;
	RCSTA=0x90;
	    TRISC=0x18;
for(i=0;i<=10000;i++);
i2c_init();
i2c_start();//start slavead+R/w  
i2c_data(0x33);//0x32 
a=i2c_read(0);
txn(a);
a=i2c_read(1);
txn(a);
i2c_stop();
while(1) 	
{

}
}