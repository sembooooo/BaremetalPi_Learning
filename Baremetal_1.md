To execute your baremetal programs. We need to follow some simple steps.
1. Take an SD card convert it into FAT32 
2. place the kernel.img which you prepared.
How do you prepare one ? 
After compiling our code we will get object file from which we create our .elf file and from which we create one .img 
whose name will be kernel.img for RPi-1 kernel7.img for RPi-2 and 3(32 bit mode) and kernel8.img for RPi-3 64 bit mode
3.go to the below link and get bootcode.bin,start.elf  and place it
https://github.com/raspberrypi/firmware/tree/master/boot

4. 

thats it put your SD card into pi and then power it up enjoy your code.
