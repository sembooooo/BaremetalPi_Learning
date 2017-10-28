Once again thanks to deboer for explaining this stuff to me. 

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

and all this stuff you will get in the wiki link which is given above. 
Pretty much huh ... These are not hardware mailboxes. This is some firmware running on the GPU and the GPU things are not revealed
outside only less details are revelead. 

So the above link also explains the way to communicate with that particular firmware so called "MAILBOX" 
To put everything simple we write what ever we write in some array and pass address of that array. 
There is a format to send that array. i will be explaining you  that later in this file but first let me tell you my experience with 
this mailboxes.


#### Why all these ? whats the importance ? 
Let me tell you my experience with mailboxes. 
I started to write an LED blinking code on raspberry pi 3. But there is no direct GPIO connection to that LED. That means you cannot
write normal LED blinking program as you do for other raspberyy pis' 1 or 2.
There might me other ways of doing tihs but the only way i got to know is to use the property tags from ARM to VC in a mailbox and to make an LED light up. 

#### So how do we do that ?
As i said we will write all the information in some array which will follow some rules. 
so how to write it. 
So if you go through the link you might have come to somethings called buffer interface, tags and all such stuff.








