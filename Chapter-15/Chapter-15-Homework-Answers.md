* **问题 1 答案**  
```
[testjz@localhost vm-mechanism]$ ./relocation.py -s 1 -c

ARG seed 1
ARG address space size 1k
ARG phys mem size 16k

Base-and-Bounds register information:

  Base   : 0x0000363c (decimal 13884)
  Limit  : 290

Virtual Address Trace
  VA  0: 0x0000030e (decimal:  782) --> SEGMENTATION VIOLATION
  VA  1: 0x00000105 (decimal:  261) --> VALID: 0x00003741 (decimal: 14145)
  VA  2: 0x000001fb (decimal:  507) --> SEGMENTATION VIOLATION
  VA  3: 0x000001cc (decimal:  460) --> SEGMENTATION VIOLATION
  VA  4: 0x0000029b (decimal:  667) --> SEGMENTATION VIOLATION
```
```
[testjz@localhost vm-mechanism]$ ./relocation.py -s 2 -c

ARG seed 2
ARG address space size 1k
ARG phys mem size 16k

Base-and-Bounds register information:

  Base   : 0x00003ca9 (decimal 15529)
  Limit  : 500

Virtual Address Trace
  VA  0: 0x00000039 (decimal:   57) --> VALID: 0x00003ce2 (decimal: 15586)
  VA  1: 0x00000056 (decimal:   86) --> VALID: 0x00003cff (decimal: 15615)
  VA  2: 0x00000357 (decimal:  855) --> SEGMENTATION VIOLATION
  VA  3: 0x000002f1 (decimal:  753) --> SEGMENTATION VIOLATION
  VA  4: 0x000002ad (decimal:  685) --> SEGMENTATION VIOLATION
```
```
[testjz@localhost vm-mechanism]$ ./relocation.py -s 3 -c

ARG seed 3
ARG address space size 1k
ARG phys mem size 16k

Base-and-Bounds register information:

  Base   : 0x000022d4 (decimal 8916)
  Limit  : 316

Virtual Address Trace
  VA  0: 0x0000017a (decimal:  378) --> SEGMENTATION VIOLATION
  VA  1: 0x0000026a (decimal:  618) --> SEGMENTATION VIOLATION
  VA  2: 0x00000280 (decimal:  640) --> SEGMENTATION VIOLATION
  VA  3: 0x00000043 (decimal:   67) --> VALID: 0x00002317 (decimal: 8983)
  VA  4: 0x0000000d (decimal:   13) --> VALID: 0x000022e1 (decimal: 8929)
```

* **问题 2 答案**  
```
[testjz@localhost vm-mechanism]$ ./relocation.py -s 0 -n 10 -l 930 -c 

ARG seed 0
ARG address space size 1k
ARG phys mem size 16k

Base-and-Bounds register information:

  Base   : 0x0000360b (decimal 13835)
  Limit  : 930

Virtual Address Trace
  VA  0: 0x00000308 (decimal:  776) --> VALID: 0x00003913 (decimal: 14611)
  VA  1: 0x000001ae (decimal:  430) --> VALID: 0x000037b9 (decimal: 14265)
  VA  2: 0x00000109 (decimal:  265) --> VALID: 0x00003714 (decimal: 14100)
  VA  3: 0x0000020b (decimal:  523) --> VALID: 0x00003816 (decimal: 14358)
  VA  4: 0x0000019e (decimal:  414) --> VALID: 0x000037a9 (decimal: 14249)
  VA  5: 0x00000322 (decimal:  802) --> VALID: 0x0000392d (decimal: 14637)
  VA  6: 0x00000136 (decimal:  310) --> VALID: 0x00003741 (decimal: 14145)
  VA  7: 0x000001e8 (decimal:  488) --> VALID: 0x000037f3 (decimal: 14323)
  VA  8: 0x00000255 (decimal:  597) --> VALID: 0x00003860 (decimal: 14432)
  VA  9: 0x000003a1 (decimal:  929) --> VALID: 0x000039ac (decimal: 14764)
```
界限寄存器的值最小设置为930.

* **问题 3 答案**  
题目翻译错误，问题应该是问基址寄存器base的最大值。
```
[testjz@localhost vm-mechanism]$ ./relocation.py -s 1 -n 10 -l 100 -b 16284 -c

ARG seed 1
ARG address space size 1k
ARG phys mem size 16k

Base-and-Bounds register information:

  Base   : 0x00003f9c (decimal 16284)
  Limit  : 100

Virtual Address Trace
  VA  0: 0x00000089 (decimal:  137) --> SEGMENTATION VIOLATION
  VA  1: 0x00000363 (decimal:  867) --> SEGMENTATION VIOLATION
  VA  2: 0x0000030e (decimal:  782) --> SEGMENTATION VIOLATION
  VA  3: 0x00000105 (decimal:  261) --> SEGMENTATION VIOLATION
  VA  4: 0x000001fb (decimal:  507) --> SEGMENTATION VIOLATION
  VA  5: 0x000001cc (decimal:  460) --> SEGMENTATION VIOLATION
  VA  6: 0x0000029b (decimal:  667) --> SEGMENTATION VIOLATION
  VA  7: 0x00000327 (decimal:  807) --> SEGMENTATION VIOLATION
  VA  8: 0x00000060 (decimal:   96) --> VALID: 0x00003ffc (decimal: 16380)
  VA  9: 0x0000001d (decimal:   29) --> VALID: 0x00003fb9 (decimal: 16313)
```
16k-100=16284.

* **问题 4 答案**  
```
[testjz@localhost vm-mechanism]$ ./relocation.py -s 1 -n 10 -l 100 -b 499900 -a 500000 -p 500001 -c

ARG seed 1
ARG address space size 500000
ARG phys mem size 500001

Base-and-Bounds register information:

  Base   : 0x0007a0bc (decimal 499900)
  Limit  : 100

Virtual Address Trace
  VA  0: 0x0001066e (decimal: 67182) --> SEGMENTATION VIOLATION
  VA  1: 0x00067724 (decimal: 423716) --> SEGMENTATION VIOLATION
  VA  2: 0x0005d3bf (decimal: 381887) --> SEGMENTATION VIOLATION
  VA  3: 0x0001f22e (decimal: 127534) --> SEGMENTATION VIOLATION
  VA  4: 0x0003c7a5 (decimal: 247717) --> SEGMENTATION VIOLATION
  VA  5: 0x00036de9 (decimal: 224745) --> SEGMENTATION VIOLATION
  VA  6: 0x0004f8a4 (decimal: 325796) --> SEGMENTATION VIOLATION
  VA  7: 0x00060479 (decimal: 394361) --> SEGMENTATION VIOLATION
  VA  8: 0x0000b751 (decimal: 46929) --> SEGMENTATION VIOLATION
  VA  9: 0x0000375d (decimal: 14173) --> SEGMENTATION VIOLATION
```
这个数字太随机了，看不出效果。

* **问题 5 答案**  
```
虚拟地址必须小于界限寄存器，值才是有效的。  
