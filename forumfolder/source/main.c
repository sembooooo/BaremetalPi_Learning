#define GPIO_BASE 0x3F200000UL
#define GPFSEL1 2
#define GPSET0 9
#define GPCLR0 12
/*----------------------MAILBOXES WRITE SET REGISTERS --------------------------*/
#define CORE0_MAILBOX0 (volatile unsigned int *)  0x400000c0
#define CORE1_MAILBOX0 (volatile unsigned int *)  0X400000d0
/*------------------------------------------------------------------------------*/
volatile unsigned int *gpio=(unsigned int *)GPIO_BASE;
unsigned int  *mailbox;
void led_on(void); // this function blinks an LED
void delay(void);
int main()
{
	mailbox=(unsigned int *)CORE1_MAILBOX0;
	*mailbox=led_on;
	while(1);
	return 0;
}

void led_on()
{

	gpio[GPFSEL1]|=(1<<18);  // This makes the PIN16 an output
	
	while(1)
	{
		gpio[GPSET0]|=(1<<16);
		delay();
		gpio[GPCLR0]|=(1<<16);
		delay();
	}
}

void delay()
{
	unsigned int count=0;
	for(count=0;count<=500000;count++);
}
