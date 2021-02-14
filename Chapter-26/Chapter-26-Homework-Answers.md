* **问题 1 答案**  
```
[testjz@localhost threads-intro]$ ./x86.py -p loop.s -t 1 -i 100 -R dx -c
ARG seed 0
ARG numthreads 1
ARG program loop.s
ARG interrupt frequency 100
ARG interrupt randomness False
ARG argv 
ARG load address 1000
ARG memsize 128
ARG memtrace 
ARG regtrace dx
ARG cctrace False
ARG printstats False
ARG verbose False

   dx          Thread 0         
    0   
   -1   1000 sub  $1,%dx
   -1   1001 test $0,%dx
   -1   1002 jgte .top
   -1   1003 halt
```
dx一开始是0，后来变为-1。

* **问题 2 答案**  
```
[testjz@localhost threads-intro]$ ./x86.py -p loop.s -t 2 -i 100 -R dx -a dx=3,dx=3 -c
ARG seed 0
ARG numthreads 2
ARG program loop.s
ARG interrupt frequency 100
ARG interrupt randomness False
ARG argv dx=3,dx=3
ARG load address 1000
ARG memsize 128
ARG memtrace 
ARG regtrace dx
ARG cctrace False
ARG printstats False
ARG verbose False

   dx          Thread 0                Thread 1         
    3   
    2   1000 sub  $1,%dx
    2   1001 test $0,%dx
    2   1002 jgte .top
    1   1000 sub  $1,%dx
    1   1001 test $0,%dx
    1   1002 jgte .top
    0   1000 sub  $1,%dx
    0   1001 test $0,%dx
    0   1002 jgte .top
   -1   1000 sub  $1,%dx
   -1   1001 test $0,%dx
   -1   1002 jgte .top
   -1   1003 halt
    3   ----- Halt;Switch -----  ----- Halt;Switch -----  
    2                            1000 sub  $1,%dx
    2                            1001 test $0,%dx
    2                            1002 jgte .top
    1                            1000 sub  $1,%dx
    1                            1001 test $0,%dx
    1                            1002 jgte .top
    0                            1000 sub  $1,%dx
    0                            1001 test $0,%dx
    0                            1002 jgte .top
   -1                            1000 sub  $1,%dx
   -1                            1001 test $0,%dx
   -1                            1002 jgte .top
   -1                            1003 halt
```
dx在每个线程从3到-1。由于100条指令中断一次，因此多线程的存在不影响计算。这段代码没有竞态条件。

* **问题 3 答案**  
结果太长，这里仅仅给出命令。  
```
./x86.py -p loop.s -t 2 -i 3 -R dx -a dx=3,dx=3 -r -c -s 1
./x86.py -p loop.s -t 2 -i 3 -R dx -a dx=3,dx=3 -r -c -s 2
./x86.py -p loop.s -t 2 -i 3 -R dx -a dx=3,dx=3 -r -c -s 3
```
中断频率会改变这个程序的行为。  

* **问题 4 答案**  
```
[testjz@localhost threads-intro]$ ./x86.py -p looping-race-nolock.s -t 1 -M 2000 -c
ARG seed 0
ARG numthreads 1
ARG program looping-race-nolock.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG argv 
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace 
ARG cctrace False
ARG printstats False
ARG verbose False

 2000          Thread 0         
    0   
    0   1000 mov 2000, %ax
    0   1001 add $1, %ax
    1   1002 mov %ax, 2000
    1   1003 sub  $1, %bx
    1   1004 test $0, %bx
    1   1005 jgt .top
    1   1006 halt
```
从0变为1

* **问题 5 答案**  
```
[testjz@localhost threads-intro]$ ./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000 -c
ARG seed 0
ARG numthreads 2
ARG program looping-race-nolock.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG argv bx=3
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace 
ARG cctrace False
ARG printstats False
ARG verbose False

 2000          Thread 0                Thread 1         
    0   
    0   1000 mov 2000, %ax
    0   1001 add $1, %ax
    1   1002 mov %ax, 2000
    1   1003 sub  $1, %bx
    1   1004 test $0, %bx
    1   1005 jgt .top
    1   1000 mov 2000, %ax
    1   1001 add $1, %ax
    2   1002 mov %ax, 2000
    2   1003 sub  $1, %bx
    2   1004 test $0, %bx
    2   1005 jgt .top
    2   1000 mov 2000, %ax
    2   1001 add $1, %ax
    3   1002 mov %ax, 2000
    3   1003 sub  $1, %bx
    3   1004 test $0, %bx
    3   1005 jgt .top
    3   1006 halt
    3   ----- Halt;Switch -----  ----- Halt;Switch -----  
    3                            1000 mov 2000, %ax
    3                            1001 add $1, %ax
    4                            1002 mov %ax, 2000
    4                            1003 sub  $1, %bx
    4                            1004 test $0, %bx
    4                            1005 jgt .top
    4                            1000 mov 2000, %ax
    4                            1001 add $1, %ax
    5                            1002 mov %ax, 2000
    5                            1003 sub  $1, %bx
    5                            1004 test $0, %bx
    5                            1005 jgt .top
    5                            1000 mov 2000, %ax
    5                            1001 add $1, %ax
    6                            1002 mov %ax, 2000
    6                            1003 sub  $1, %bx
    6                            1004 test $0, %bx
    6                            1005 jgt .top
    6                            1006 halt
```
每个线程循环3次是因为dx的值从3到0，然后停止了。  
x的最终值为6。

* **问题 6 答案**  
结果太长，这里仅仅给出命令。  
```
./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 1 -c
./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 2 -c
./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 3 -c
```
只看线程交替，是可以分析出x的最终值的。中断的确切位置很重要。  
中断发生在两个mov之间就可能引起麻烦，其余的地方是安全的。

* **问题 7 答案**  
结果太长，这里仅仅给出命令。  
```
./x86.py -p looping-race-nolock.s -t 2 -M 2000 -a bx=1 -i 1 -c
./x86.py -p looping-race-nolock.s -t 2 -M 2000 -a bx=1 -i 2 -c
./x86.py -p looping-race-nolock.s -t 2 -M 2000 -a bx=1 -i 3 -c
```
i为1时，x的最终值为1。
i为2时，x的最终值为1。
i为3时，x的最终值为2，为“正确答案”。  

* **问题 8 答案**  
结果太长，这里仅仅给出命令。  
```
./x86.py -p looping-race-nolock.s -t 2 -M 2000 -a bx=100 -i 1 -c
./x86.py -p looping-race-nolock.s -t 2 -M 2000 -a bx=100 -i 2 -c
./x86.py -p looping-race-nolock.s -t 2 -M 2000 -a bx=100 -i 3 -c
...
```
我发现，3的倍数的间隔会导致正确的答案。原因是指令的前三条必须在一起执行。  
令人惊讶的间隔，实话说都不让我惊讶。

* **问题 9 答案**  
```
[testjz@localhost threads-intro]$ ./x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000 -c
ARG seed 0
ARG numthreads 2
ARG program wait-for-me.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG argv ax=1,ax=0
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace ax
ARG cctrace False
ARG printstats False
ARG verbose False

 2000      ax          Thread 0                Thread 1         
    0       1   
    0       1   1000 test $1, %ax
    0       1   1001 je .signaller
    1       1   1006 mov  $1, 2000
    1       1   1007 halt
    1       0   ----- Halt;Switch -----  ----- Halt;Switch -----  
    1       0                            1000 test $1, %ax
    1       0                            1001 je .signaller
    1       0                            1002 mov  2000, %cx
    1       0                            1003 test $1, %cx
    1       0                            1004 jne .waiter
    1       0                            1005 halt
```
代码的行为如上。2000处的值从0变为1。  

* **问题 10 答案**  
```
[testjz@localhost threads-intro]$ ./x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000
ARG seed 0
ARG numthreads 2
ARG program wait-for-me.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG argv ax=0,ax=1
ARG load address 1000
ARG memsize 128
ARG memtrace 2000
ARG regtrace ax
ARG cctrace False
ARG printstats False
ARG verbose False

 2000      ax          Thread 0                Thread 1         
    ?       ?   
    ?       ?   1000 test $1, %ax
    ?       ?   1001 je .signaller
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   ------ Interrupt ------  ------ Interrupt ------  
    ?       ?                            1000 test $1, %ax
    ?       ?                            1001 je .signaller
    ?       ?                            1006 mov  $1, 2000
    ?       ?                            1007 halt
    ?       ?   ----- Halt;Switch -----  ----- Halt;Switch -----  
    ?       ?   1002 mov  2000, %cx
    ?       ?   1003 test $1, %cx
    ?       ?   1004 jne .waiter
    ?       ?   1005 halt
```
线程行为如上，线程0一直在循环检测2000处的值，直到中断发生。改变时间间隔，循环的次数也会改变，由于循环的代码并不修改数据，因此中断间隔越长，循环越多，CPU的利用效率越低。  
