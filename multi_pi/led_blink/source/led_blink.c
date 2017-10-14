#define GPIO_BASE 0x3F200000UL
#define GPFSEL1 2
#define GPSET0 9
#define GPCLR0 12
/*----------------------MAILBOXES WRITE SET REGISTERS --------------------------*/
#define CORE0_MAILBOX0  0x40000080UL
#define CORE1_MAILBOX0  0X40000090UL
/*------------------------------------------------------------------------------*/
volatile unsigned int *gpio=(unsigned int *)GPIO_BASE;
unsigned int  *mailbox;
void LED_blink(void); // this function blinks an LED
void delay(void);
void main()
{
	mailbox=(unsigned int *)CORE1_MAILBOX0;
}

void led_on()
{
	unsigned int count;
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
	for(;count=50000;count++);
}
