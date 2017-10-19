# BaremetalPi_Learning
every one who is wishing to start multi core programming via baremetal c on raspberry pi ,should know one thing. 
Before that 
thanks to baremetal forum guys and especially "Deboer" who helped me in learning this and it took me a while to understand.

lets start from here
the below link gives us the boot sequence of the raspberry pi . First go through it 
https://raspberrypi.stackexchange.com/questions/10442/what-is-the-boot-sequence

Next, in that sequence before kernel starts booting it is written that GPU looks into the config.txt and sets up accordingly 
In that config.txt there is something called as "KERNEL_OLD". If this KERNEL_OLD =1 then the GPU will load the kernel.img file at the address 0x0 by making all four cores point at 0x0.
[  what does all four cores point to 0x0 means?   ] 
As the kernel.elf file is loaded from 0x0 instructions are present from 0x0 and all four cores will start to execute the instructions that are present from 0x0

if KERNEL_OLD =0 then 
1.the GPU will load the kernel file a 0x8000 
2.will make CORE-0 to point at that address i.e.,. 0x8000
3.and it makes other cores [CORE-1 ,CORE-2, CORE-3 ] to loop over mailbox-3.

[ why do they loop and until what is the condition to come out of the loop?  ]
To know this first we need to know what a mailbox is.
Mailbox is a  means of communication between GPU and our ARM Processor. 
in raspberry pi every core has 3 Mailboxes. In order to write into them we need to write in one address 
and in order to read or clear them we need to do this at other address. 
here below i have given for all cores mailbox 3
0x4000_008C Core 0 Mailbox 3 write - set (WO)
0x4000_00CC Core 0 Mailbox 3 read & write - high - to -clear

0x4000_009C Core 1 Mailbox 3 write - set (WO)
0x4000_00DC Core 1 Mailbox 3 read & write - high - to -clear

0x4000_00AC Core 2 Mailbox 3 write - set (WO)
0x4000_00EC Core 2 Mailbox 3 read & write - high - to -clear

0x4000_00BC Core 3 Mailbox 3 write - set (WO)
0x4000_00FC Core 3 Mailbox 3 read & write - high - to -clear
for more details on this see the doc qA7_rev3.4.pdf .
https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2836/QA7_rev3.4.pdf
 
so now its like if you want to write something into core0- mailbox3 you have to write 0x4000_008C and
if you want to clear the data then you want to write at the address 0x4000_00CC. Check the document so that you
will get to know what write -high- to -clear and write- set means

if KERNEL_OLD=0 then our cores 1,2,3 will be looping at their respective mailboxes
the loop can described like this 
1. A core will read the mailbox
2. if the data read is non zero then the core will jump to that particular address and will start executing the code.
3. if is zero, repeat from step1
All the cores will do this. 

Now if we want our cores to do different things then we can code, place it some where in memory, and 
write the starting location in those mailboxes so that every core runs the code which you want them to run.
