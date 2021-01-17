* **问题 1 答案**  
```
[testjz@localhost vm-segmentation]$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0 -c
ARG seed 0
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal:  492)
  VA  1: 0x00000061 (decimal:   97) --> SEGMENTATION VIOLATION (SEG1)
  VA  2: 0x00000035 (decimal:   53) --> SEGMENTATION VIOLATION (SEG0)
  VA  3: 0x00000021 (decimal:   33) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x00000041 (decimal:   65) --> SEGMENTATION VIOLATION (SEG1)
```
```
[testjz@localhost vm-segmentation]$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1 -c
ARG seed 1
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x00000011 (decimal:   17) --> VALID in SEG0: 0x00000011 (decimal:   17)
  VA  1: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal:  492)
  VA  2: 0x00000061 (decimal:   97) --> SEGMENTATION VIOLATION (SEG1)
  VA  3: 0x00000020 (decimal:   32) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x0000003f (decimal:   63) --> SEGMENTATION VIOLATION (SEG0)
```
```
[testjz@localhost vm-segmentation]$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2 -c
ARG seed 2
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x0000007a (decimal:  122) --> VALID in SEG1: 0x000001fa (decimal:  506)
  VA  1: 0x00000079 (decimal:  121) --> VALID in SEG1: 0x000001f9 (decimal:  505)
  VA  2: 0x00000007 (decimal:    7) --> VALID in SEG0: 0x00000007 (decimal:    7)
  VA  3: 0x0000000a (decimal:   10) --> VALID in SEG0: 0x0000000a (decimal:   10)
  VA  4: 0x0000006a (decimal:  106) --> SEGMENTATION VIOLATION (SEG1)
```

* **问题 2 答案**  
段0最高的合法虚拟地址是19。  
段1最低的合法虚拟地址是108。  
整个地址空间中对子和最高的合法地址是0和127。 
```
[testjz@localhost vm-segmentation]$ ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2 -c -A 19,20,107,108,0,127,128
ARG seed 2
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x00000013 (decimal:   19) --> VALID in SEG0: 0x00000013 (decimal:   19)
  VA  1: 0x00000014 (decimal:   20) --> SEGMENTATION VIOLATION (SEG0)
  VA  2: 0x0000006b (decimal:  107) --> SEGMENTATION VIOLATION (SEG1)
  VA  3: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal:  492)
  VA  4: 0x00000000 (decimal:    0) --> VALID in SEG0: 0x00000000 (decimal:    0)
  VA  5: 0x0000007f (decimal:  127) --> VALID in SEG1: 0x000001ff (decimal:  511)
Error: virtual address 128 cannot be generated in an address space of size 128
```

* **问题 3 答案**  
中间的省略号表示的应该都是无效，我们按这个来计算。  
只有前两个和最后两个是有效的，那么界限寄存器肯定是2。  
基址寄存器的选择范围很大， b0可以从0到124，b1可以从4到128。  
```
[testjz@localhost vm-segmentation]$ ./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15  --b0 0 --l0 2 --b1 4 --l1 2 -c
ARG seed 0
ARG address space size 16
ARG phys mem size 128

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 2

  Segment 1 base  (grows negative) : 0x00000004 (decimal 4)
  Segment 1 limit                  : 2

Virtual Address Trace
  VA  0: 0x00000000 (decimal:    0) --> VALID in SEG0: 0x00000000 (decimal:    0)
  VA  1: 0x00000001 (decimal:    1) --> VALID in SEG0: 0x00000001 (decimal:    1)
  VA  2: 0x00000002 (decimal:    2) --> SEGMENTATION VIOLATION (SEG0)
  VA  3: 0x00000003 (decimal:    3) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x00000004 (decimal:    4) --> SEGMENTATION VIOLATION (SEG0)
  VA  5: 0x00000005 (decimal:    5) --> SEGMENTATION VIOLATION (SEG0)
  VA  6: 0x00000006 (decimal:    6) --> SEGMENTATION VIOLATION (SEG0)
  VA  7: 0x00000007 (decimal:    7) --> SEGMENTATION VIOLATION (SEG0)
  VA  8: 0x00000008 (decimal:    8) --> SEGMENTATION VIOLATION (SEG1)
  VA  9: 0x00000009 (decimal:    9) --> SEGMENTATION VIOLATION (SEG1)
  VA 10: 0x0000000a (decimal:   10) --> SEGMENTATION VIOLATION (SEG1)
  VA 11: 0x0000000b (decimal:   11) --> SEGMENTATION VIOLATION (SEG1)
  VA 12: 0x0000000c (decimal:   12) --> SEGMENTATION VIOLATION (SEG1)
  VA 13: 0x0000000d (decimal:   13) --> SEGMENTATION VIOLATION (SEG1)
  VA 14: 0x0000000e (decimal:   14) --> VALID in SEG1: 0x00000002 (decimal:    2)
  VA 15: 0x0000000f (decimal:   15) --> VALID in SEG1: 0x00000003 (decimal:    3)
```

* **问题 4 答案**  
两个界限寄存器的和占有效地址空间的90%即可。而且随机生成的虚拟地址数量要大，不然样本太小。  
结果太长，这里仅仅给出命令。  
```
./segmentation.py -a 1k -n 100 --l0 460 --l1 461 -c
```

* **问题 5 答案**  
让两个界限寄存器的值为0即可。  
```
[testjz@localhost vm-segmentation]$ ./segmentation.py -a 1k -n 10 --l0 0 --l1 0 -c
ARG seed 0
ARG address space size 1k
ARG phys mem size 16k

Segment register information:

  Segment 0 base  (grows positive) : 0x0000360b (decimal 13835)
  Segment 0 limit                  : 0

  Segment 1 base  (grows negative) : 0x00003082 (decimal 12418)
  Segment 1 limit                  : 0

Virtual Address Trace
  VA  0: 0x000001ae (decimal:  430) --> SEGMENTATION VIOLATION (SEG0)
  VA  1: 0x00000109 (decimal:  265) --> SEGMENTATION VIOLATION (SEG0)
  VA  2: 0x0000020b (decimal:  523) --> SEGMENTATION VIOLATION (SEG1)
  VA  3: 0x0000019e (decimal:  414) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x00000322 (decimal:  802) --> SEGMENTATION VIOLATION (SEG1)
  VA  5: 0x00000136 (decimal:  310) --> SEGMENTATION VIOLATION (SEG0)
  VA  6: 0x000001e8 (decimal:  488) --> SEGMENTATION VIOLATION (SEG0)
  VA  7: 0x00000255 (decimal:  597) --> SEGMENTATION VIOLATION (SEG1)
  VA  8: 0x000003a1 (decimal:  929) --> SEGMENTATION VIOLATION (SEG1)
  VA  9: 0x00000204 (decimal:  516) --> SEGMENTATION VIOLATION (SEG1)
```
