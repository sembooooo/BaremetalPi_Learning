# BaremetalPi_Learning  
#### these are somethings which i feel they are no where mentioned but because of a person called deboer and raspberry pi baremetal forum  i got to know this. So i thought to write it here would help people like me. 
every one who is wishing to start multi core programming via baremetal c on raspberry pi ,should know one thing. 
Before that 
thanks to baremetal forum guys and especially "Deboer" who helped me in learning this and it took me a while to understand.

lets start from here
the below link gives us the boot sequence of the raspberry pi . First go through it 
https://raspberrypi.stackexchange.com/questions/10442/what-is-the-boot-sequence

Next, in that sequence before kernel starts booting it is written that GPU looks into the config.txt and sets up accordingly
link for config.txt file and go through boot which in present a little below https://www.raspberrypi.org/documentation/configuration/config-txt/  
In that config.txt there is something called as "KERNEL_OLD". If this KERNEL_OLD =1 then the GPU will load the kernel.img file at the address 0x0 by making all four cores point at 0x0.
 ### what does all four cores point to 0x0 means?

As the kernel.elf file is loaded from 0x0 instructions are present from 0x0 and all four cores will start to execute the instructions that are present from 0x0

if KERNEL_OLD =0 then 
1.the GPU will load the kernel file a 0x8000 
2.will make CORE-0 to point at that address i.e.,. 0x8000
3.and it makes other cores [CORE-1 ,CORE-2, CORE-3 ] to loop over mailbox-3.

### what is the condition to come out of the loop?
To know this first we need to know what a mailbox is.
There are actually two types of mailboxes 
1. Those that are present in GPU 
2. Those that are present in bcm28xx chip.
Here i am referring to the second category mailboxes
in raspberry pi every core is given  3 Mailboxes. In order to write into them we need to write in one address 
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
All the cores ( cores 1,2,3)  will do this except CORE-0. 


So after hearing all this story a small doubt comes to every one we are not writing any code but who is doing this. there should be some instructions written by some one which will do this. 
Yes without instructions nothing happens and this is provided by the raspberrypi foundation or one can also say that it is already present on the board and if you want to have a look over that file then follow the link below
https://github.com/raspberrypi/tools/tree/master/armstubs 
you can look into armstubs files

i think by now you got to know why will they go ? still not understood why then continue reading 
Now if we want our cores to do different things then we write code, place it some where in memory, and 
write the starting location in those mailboxes so that every core runs the code which we want them to run.

Remember only CORE-0 is released and put at 0x8000 where our kernel.elf , our instructions , are present. 
Its starts executing those instructions as soon as it comes there. 

### So one more question who will write the addresses in those mailboxes ?
who else only CORE-0 and it is the only resource we have. Because all the other cores are in a loop over those mailboxes.

### How do you command it to write ? 
simple include those instructions in the kernel.img file and thats it. CORE-0 will execute them one by one and will do the
job for you. If you dont want that to write then dont ask it to write. its that simple 

### If your KERNEL_OLD=0 ,what happens if we dont write the memory addresses in those mailboxes for CORE -1, CORE-2 ,CORE-3 ?
Nothing catastrophic happens mostly you will end up with only one CORE and that is your CORE-0. You will not have multicore working. It will be like a single processor. 
Apart from this nothing happens.
