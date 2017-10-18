# BaremetalPi_Learning
every one who is wishing to start multi core programming via baremetal c on raspberry pi ,should know one thing. 
Before that 
thanks to baremetal forum guys and especially "Deboer" who helped me in learning this and it took me a while to understand.

lets start from here
the below link gives us the boot sequence of the raspberry pi . First go through it 
https://raspberrypi.stackexchange.com/questions/10442/what-is-the-boot-sequence

Next, in that sequence before kernel starts booting it is written that GPU looks into the config.txt and sets up accordingly 
In that config.txt there is something called as "KERNEL_OLD". If this KERNEL_OLD =1 then the GPU will load the kernel.img file at the address 0x0 by making all four cores point at 0x0.

if KERNEL_OLD =0 then the GPU will load the kernel file at 0x8000 will make CORE-0 to point at that address and it makes other core [CORE-1 ,CORE-2, CORE-3 ] to loop mailbox-3.

Normally what people do is , as CORE-0 is at the address 0x8000 
