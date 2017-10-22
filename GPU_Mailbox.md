This doc contains some information regarding the mailboxes in raspberry pi.
##### Disclaimer: This is not the information which i found exclusively but i felt to write it in an order which i understand.
##### so i am writing this. 
##### my main source is https://github.com/raspberrypi/firmware/wiki

## GPU mailboxes:
There is sufficient information available on this. Thanks to LeonDeboer, Ultibo creator guys , last but not least Alex chadwick.

This is the first type of mailbox which i was referring to in the Baremetal_2.md file in my Git.
### Mailboxe
Mailboxes are the primary means of communication between the ARM and the VideoCore firmware running on the GPU. For a list of the available mailboxes, see here.

A mailbox contains some channels in it. Each channel has some purpose. 
0: Power management
1: Framebuffer
2: Virtual UART
3: VCHIQ
4: LEDs
5: Buttons
6: Touch screen
7: Counter
8: Property tags (ARM -> VC)
9: Property tags (VC -> ARM)
                                             

#### Why all these ? whats the importance ? 
Let me tell you my experience with mailboxes. 
I started to write an LED blinking code on raspberry pi 3. But there is no direct GPIO connection to that LED. That means you cannot
write normal LED blinking program as you do for other raspberyy pi 1 or 2.
There might me other ways of doing tihs but the only way i got to know is to use the channel 4 LED in a mailbox and to make an LED light up. 



