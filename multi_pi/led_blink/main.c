
/*-----------------------MAILBOX VARIABLES------------------------------------*/
extern unsigned int CORE1_MAILBOX;   				/* This is our CORE1 mailbox variable */
extern unsigned int CORE2_MAILBOX;   				/* This is our CORE2 mailbox variable */
extern unsigned int CORE3_MAILBOX;   				/* This is our CORE3 mailbox variable */
/*----------------------MAILBOXES WRITE SET REGISTERS --------------------------*/
#define CORE1_MAILBOX3 0X4000009CUL
#define CORE2_MAILBOX3 0X400000ACUL
#define CORE3_MAILBOX3 0X400000BCUL
/*-------------------------enumerated data type for mailbox channels----------*/

typedef enum {
	MB_CHANNEL_POWER	= 0X0;				// Mailbox Channel 0: Power
	MB_CHANNEL_FRAMEBUFFER  = 0X1;				// Mailbox Channel 1: FrameBuffer
	MB_CHANNEL_VUART	= 0X2;				// Mailbox Channel 2: Virtual UART
	MB_CHANNEL_VCHIQ	= 0X3;				// Mailbox Channel 3: VCHIQ
	MB_CHANNEL_LED		= 0X4;				// Mailbox Channel 4: LED
	MB_CHANNEL_BUTTONS 	= 0x5,				// Mailbox Channel 5: Buttons Interface
	MB_CHANNEL_TOUCH 	= 0x6,				// Mailbox Channel 6: Touchscreen Interface
	MB_CHANNEL_COUNT 	= 0x7,				// Mailbox Channel 7: Counter
	MB_CHANNEL_TAGS 	= 0x8,				// Mailbox Channel 8: Tags (ARM to VC)
	MB_CHANNEL_GPU 		= 0x9,				// Mailbox Channel 9: Tags (VC to ARM)
} MAILBOX_CHANNEL;
/*----------------------------Structure to  GPU Mailbox------------------------*/
typedef struct __attribute__((__packed__,aligned(4))) _PI_MAILBOX_
{
        const uint32_t Read0;                                   // 0x00         Read data from VC to ARM
        uint32_t Unused[3];                                     // 0x04-0x0F
        uint32_t Peek0;                                         // 0x10
        uint32_t Sender0;                                       // 0x14
        uint32_t Status0;                                       // 0x18         Status of VC to ARM
        uint32_t Config0;                                       // 0x1C        
        uint32_t Write1;                                        // 0x20         Write data from ARM to VC
        uint32_t Unused2[3];                                    // 0x24-0x2F
        uint32_t Peek1;                                         // 0x30
        uint32_t Sender1;                                       // 0x34
        uint32_t Status1;                                       // 0x38         Status of ARM to VC
        uint32_t Config1;                                       // 0x3C 

} PI_MAILBOX;

/*------------------------main function-----------------------------------------------------*/

