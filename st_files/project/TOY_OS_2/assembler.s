0x0800059C B510      PUSH          {r4,lr}
0x0800059E 4604      MOV           r4,r0
    99:         numberoftasks++; 
   100:           
   101:           
   102:          /* 
   103:          1. There should be a variable in the kernel telling us how many tasks are present. 
   104:          By this we will get to know whether there is space to allow one more task to create or to return 0  
   105:          */ 
0x080005A0 481E      LDR           r0,[pc,#120]  ; @0x0800061C
0x080005A2 8800      LDRH          r0,[r0,#0x00]
0x080005A4 1C40      ADDS          r0,r0,#1
0x080005A6 B200      SXTH          r0,r0
0x080005A8 491C      LDR           r1,[pc,#112]  ; @0x0800061C
0x080005AA 8008      STRH          r0,[r1,#0x00]
   106:          if( numberoftasks < NUMTHREADS) 
   107:          { 
   108:                  /* 
   109:                  if this is the first thread that we are creating then we the thread. next is to pointed to that thread only as there are no other threads. 
   110:                  */ 
0x080005AC 4608      MOV           r0,r1
0x080005AE F9B00000  LDRSH         r0,[r0,#0x00]
0x080005B2 2803      CMP           r0,#0x03
0x080005B4 DA2F      BGE           0x08000616
   111:                  if( numberoftasks == 0) 
   112:                  { 
0x080005B6 4608      MOV           r0,r1
0x080005B8 8800      LDRH          r0,[r0,#0x00]
0x080005BA B918      CBNZ          r0,0x080005C4
   113:                          Thread[0].next = &Thread[0]; 
   114:                  } 
   115:                  else 
   116:                  { 
0x080005BC 4818      LDR           r0,[pc,#96]  ; @0x08000620
0x080005BE 4601      MOV           r1,r0
0x080005C0 6048      STR           r0,[r1,#0x04]
0x080005C2 E015      B             0x080005F0
   117:                         Thread[numberoftasks-1].next = &Thread[numberoftasks]; 
0x080005C4 4816      LDR           r0,[pc,#88]  ; @0x08000620
0x080005C6 4915      LDR           r1,[pc,#84]  ; @0x0800061C
0x080005C8 F9B11000  LDRSH         r1,[r1,#0x00]
0x080005CC EB0001C1  ADD           r1,r0,r1,LSL #3
0x080005D0 4812      LDR           r0,[pc,#72]  ; @0x0800061C
0x080005D2 F9B00000  LDRSH         r0,[r0,#0x00]
0x080005D6 1E40      SUBS          r0,r0,#1
0x080005D8 4A11      LDR           r2,[pc,#68]  ; @0x08000620
0x080005DA EB0200C0  ADD           r0,r2,r0,LSL #3
0x080005DE 6041      STR           r1,[r0,#0x04]
   118:                                 Thread[numberoftasks].next=&Thread[0]; 
   119:                  } 
   120:                  /* 
   121:                         As we have created a new thread or task we have link the last TCB to the current TCB and the current TCB to first TCB  
   122:                         in order to maintain the linked list.  
   123:                  */ 
   124:                   
   125:                  /* Set up the stack for the thread */ 
0x080005E0 4610      MOV           r0,r2
0x080005E2 4601      MOV           r1,r0
0x080005E4 4A0D      LDR           r2,[pc,#52]  ; @0x0800061C
0x080005E6 F9B22000  LDRSH         r2,[r2,#0x00]
0x080005EA EB0101C2  ADD           r1,r1,r2,LSL #3
0x080005EE 6048      STR           r0,[r1,#0x04]
   126:                  SetInitialStack(STK_PT); 
0x080005F0 480C      LDR           r0,[pc,#48]  ; @0x08000624
0x080005F2 8800      LDRH          r0,[r0,#0x00]
0x080005F4 F7FFFED4  BL.W          SetInitialStack (0x080003A0)
   127:                  stack[STK_PT][STACKSIZE-2] = (uint32_t)(task); 
0x080005F8 480A      LDR           r0,[pc,#40]  ; @0x08000624
0x080005FA 8800      LDRH          r0,[r0,#0x00]
0x080005FC EBC01000  RSB           r0,r0,r0,LSL #4
0x08000600 4909      LDR           r1,[pc,#36]  ; @0x08000628
0x08000602 EB0100C0  ADD           r0,r1,r0,LSL #3
0x08000606 6704      STR           r4,[r0,#0x70]
   128:                  STK_PT++; 
0x08000608 4806      LDR           r0,[pc,#24]  ; @0x08000624
0x0800060A 8800      LDRH          r0,[r0,#0x00]
0x0800060C 1C40      ADDS          r0,r0,#1
0x0800060E 4905      LDR           r1,[pc,#20]  ; @0x08000624
0x08000610 8008      STRH          r0,[r1,#0x00]
   129:                  return 0; 
   130:          } 
   131:          else 
   132:                  return 1; 
   133:           
   134:  
0x08000612 2000      MOVS          r0,#0x00
   135: } 
0x08000614 BD10      POP           {r4,pc}
   132:                  return 1; 
0x08000616 2001      MOVS          r0,#0x01
0x08000618 E7FC      B             0x08000614
   132:                  return 1; 
0x0800065E 2001      MOVS          r0,#0x01
0x08000660 E7FC      B             0x0800065C
0x08000662 0000      DCW           0x0000
0x08000664 0004      DCW           0x0004
0x08000666 2000      DCW           0x2000
0x08000668 000C      DCW           0x000C
0x0800066A 2000      DCW           0x2000
0x0800066C 0006      DCW           0x0006
0x0800066E 2000      DCW           0x2000
0x08000670 0024      DCW           0x0024
0x08000672 2000      DCW           0x2000
    69:         OS_Init(); 
0x08000674 F7FFFE5E  BL.W          OS_Init (0x08000334)
    70:         ToyOS_CreateTask(&Task1); 
0x08000678 4806      LDR           r0,[pc,#24]  ; @0x08000694
0x0800067A F7FFFFB3  BL.W          ToyOS_CreateTask (0x080005E4)
    71:         ToyOS_CreateTask(&Task2); 
0x0800067E 4806      LDR           r0,[pc,#24]  ; @0x08000698
0x08000680 F7FFFFB0  BL.W          ToyOS_CreateTask (0x080005E4)
    72:         ToyOS_CreateTask(&Task3); 
0x08000684 4805      LDR           r0,[pc,#20]  ; @0x0800069C
0x08000686 F7FFFFAD  BL.W          ToyOS_CreateTask (0x080005E4)
    73:         OS_Launch(); 
0x0800068A F7FFFE61  BL.W          OS_Launch (0x08000350)
    74:         while(1); 
0x0800068E BF00      NOP           
0x08000690 E7FE      B             0x08000690
0x08000692 0000      DCW           0x0000
0x08000694 04FD      DCW           0x04FD
0x08000696 0800      DCW           0x0800
0x08000698 0555      DCW           0x0555
0x0800069A 0800      DCW           0x0800
0x0800069C 059D      DCW           0x059D
0x0800069E 0800      DCW           0x0800
0x080006A0 F04F7040  MOV           r0,#0x3000000
0x080006A4 EEE10A10  VMSR           FPSCR, r0
0x080006A8 4770      BX            lr
0x080006AA 0000      MOVS          r0,r0
0x080006AC 06CC      DCW           0x06CC
0x080006AE 0800      DCW           0x0800
0x080006B0 0000      DCW           0x0000
0x080006B2 2000      DCW           0x2000
0x080006B4 000C      DCW           0x000C
0x080006B6 0000      DCW           0x0000
0x080006B8 01D4      DCW           0x01D4
0x080006BA 0800      DCW           0x0800
0x080006BC 06D8      DCW           0x06D8
0x080006BE 0800      DCW           0x0800
0x080006C0 000C      DCW           0x000C
0x080006C2 2000      DCW           0x2000
0x080006C4 07E4      DCW           0x07E4
0x080006C6 0000      DCW           0x0000
0x080006C8 01F0      DCW           0x01F0
0x080006CA 0800      DCW           0x0800
0x080006CC 0001      MOVS          r1,r0
0x080006CE 0000      MOVS          r0,r0
0x080006D0 FFFF0000  DCD           0x0000FFFF
0x080006D4 0000      MOVS          r0,r0
0x080006D6 0000      MOVS          r0,r0
