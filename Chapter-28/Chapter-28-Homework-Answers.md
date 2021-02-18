* **问题 1 答案**  
汇编代码尝试使用书类似中图28.1代码的方式来设置锁。

* **问题 2 答案**  
```
[testjz@localhost threads-locks]$ ./x86.py -p flag.s -R ax,bx -M flag,count -c
ARG seed 0
ARG numthreads 2
ARG program flag.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG procsched 
ARG argv 
ARG load address 1000
ARG memsize 128
ARG memtrace flag,count
ARG regtrace ax,bx
ARG cctrace False
ARG printstats False
ARG verbose False


 flag count      ax    bx          Thread 0                Thread 1         

    0     0       0     0   
    0     0       0     0   1000 mov  flag, %ax
    0     0       0     0   1001 test $0, %ax
    0     0       0     0   1002 jne  .acquire
    1     0       0     0   1003 mov  $1, flag
    1     0       0     0   1004 mov  count, %ax
    1     0       1     0   1005 add  $1, %ax
    1     1       1     0   1006 mov  %ax, count
    0     1       1     0   1007 mov  $0, flag
    0     1       1    -1   1008 sub  $1, %bx
    0     1       1    -1   1009 test $0, %bx
    0     1       1    -1   1010 jgt .top
    0     1       1    -1   1011 halt
    0     1       0     0   ----- Halt;Switch -----  ----- Halt;Switch -----  
    0     1       0     0                            1000 mov  flag, %ax
    0     1       0     0                            1001 test $0, %ax
    0     1       0     0                            1002 jne  .acquire
    1     1       0     0                            1003 mov  $1, flag
    1     1       1     0                            1004 mov  count, %ax
    1     1       2     0                            1005 add  $1, %ax
    1     2       2     0                            1006 mov  %ax, count
    0     2       2     0                            1007 mov  $0, flag
    0     2       2    -1                            1008 sub  $1, %bx
    0     2       2    -1                            1009 test $0, %bx
    0     2       2    -1                            1010 jgt .top
    0     2       2    -1                            1011 halt
```
可以按预期工作。  

* **问题 3 答案**  
```
[testjz@localhost threads-locks]$ ./x86.py -p flag.s -R ax,bx -M flag,count -a bx=2,bx=2 -c
ARG seed 0
ARG numthreads 2
ARG program flag.s
ARG interrupt frequency 50
ARG interrupt randomness False
ARG procsched 
ARG argv bx=2,bx=2
ARG load address 1000
ARG memsize 128
ARG memtrace flag,count
ARG regtrace ax,bx
ARG cctrace False
ARG printstats False
ARG verbose False


 flag count      ax    bx          Thread 0                Thread 1         

    0     0       0     2   
    0     0       0     2   1000 mov  flag, %ax
    0     0       0     2   1001 test $0, %ax
    0     0       0     2   1002 jne  .acquire
    1     0       0     2   1003 mov  $1, flag
    1     0       0     2   1004 mov  count, %ax
    1     0       1     2   1005 add  $1, %ax
    1     1       1     2   1006 mov  %ax, count
    0     1       1     2   1007 mov  $0, flag
    0     1       1     1   1008 sub  $1, %bx
    0     1       1     1   1009 test $0, %bx
    0     1       1     1   1010 jgt .top
    0     1       0     1   1000 mov  flag, %ax
    0     1       0     1   1001 test $0, %ax
    0     1       0     1   1002 jne  .acquire
    1     1       0     1   1003 mov  $1, flag
    1     1       1     1   1004 mov  count, %ax
    1     1       2     1   1005 add  $1, %ax
    1     2       2     1   1006 mov  %ax, count
    0     2       2     1   1007 mov  $0, flag
    0     2       2     0   1008 sub  $1, %bx
    0     2       2     0   1009 test $0, %bx
    0     2       2     0   1010 jgt .top
    0     2       2     0   1011 halt
    0     2       0     2   ----- Halt;Switch -----  ----- Halt;Switch -----  
    0     2       0     2                            1000 mov  flag, %ax
    0     2       0     2                            1001 test $0, %ax
    0     2       0     2                            1002 jne  .acquire
    1     2       0     2                            1003 mov  $1, flag
    1     2       2     2                            1004 mov  count, %ax
    1     2       3     2                            1005 add  $1, %ax
    1     3       3     2                            1006 mov  %ax, count
    0     3       3     2                            1007 mov  $0, flag
    0     3       3     1                            1008 sub  $1, %bx
    0     3       3     1                            1009 test $0, %bx
    0     3       3     1                            1010 jgt .top
    0     3       0     1                            1000 mov  flag, %ax
    0     3       0     1                            1001 test $0, %ax
    0     3       0     1                            1002 jne  .acquire
    1     3       0     1                            1003 mov  $1, flag
    1     3       3     1                            1004 mov  count, %ax
    1     3       4     1                            1005 add  $1, %ax
    1     4       4     1                            1006 mov  %ax, count
    0     4       4     1                            1007 mov  $0, flag
    0     4       4     0                            1008 sub  $1, %bx
    0     4       4     0                            1009 test $0, %bx
    0     4       4     0                            1010 jgt .top
    0     4       4     0                            1011 halt
```
循环次数变为两次，还是可以按预期工作。  

* **问题 4 答案**  
结果太长，这里仅仅给出命令。  
```
./x86.py -p flag.s -R ax,bx -M flag,count -a bx=5,bx=5 -i 4 -c
```
中断频率越高（i值越低），bx越大，越容易产生不好的结果。  

* **问题 5 答案**  
获取锁
```
mov  $1, %ax        
xchg %ax, mutex     # atomic swap of 1 and mutex
test $0, %ax        # if we get 0 back: lock is free!
jne  .acquire       # if not, try again
```
释放锁
```
mov  $0, mutex
```

* **问题 6 答案**  
```
./x86.py -p test-and-set.s -i 10 -R ax,bx -M mutex,count -a bx=5 -c
```
代码一直可以按预期工作，有时会导致CPU使用率高，看代码是否在获取锁的时候重复循环即可。

* **问题 7 答案**  
结果太长，这里仅仅给出命令。  
```
./x86.py -p test-and-set.s -i 10 -R ax,bx -M mutex,count -a bx=5 -P 1100111000111000111000 -c
```
正确的事情发生了。  

* **问题 8 答案**  
可以理解，这就是Peterson算法的汇编伪代码。  

* **问题 9 答案**  
```
[testjz@localhost threads-locks]$ ./x86.py -p peterson.s -M turn,count -R bx -i 5 -a bx=0,bx=1 -c
ARG seed 0
ARG numthreads 2
ARG program peterson.s
ARG interrupt frequency 5
ARG interrupt randomness False
ARG procsched 
ARG argv bx=0,bx=1
ARG load address 1000
ARG memsize 128
ARG memtrace turn,count
ARG regtrace bx
ARG cctrace False
ARG printstats False
ARG verbose False


 turn count      bx          Thread 0                Thread 1         

    0     0       0   
    0     0       0   1000 lea flag, %fx
    0     0       0   1001 mov %bx, %cx
    0     0       0   1002 neg %cx
    0     0       0   1003 add $1, %cx
    0     0       0   1004 mov $1, 0(%fx,%bx,4)
    0     0       1   ------ Interrupt ------  ------ Interrupt ------  
    0     0       1                            1000 lea flag, %fx
    0     0       1                            1001 mov %bx, %cx
    0     0       1                            1002 neg %cx
    0     0       1                            1003 add $1, %cx
    0     0       1                            1004 mov $1, 0(%fx,%bx,4)
    0     0       0   ------ Interrupt ------  ------ Interrupt ------  
    1     0       0   1005 mov %cx, turn
    1     0       0   1006 mov 0(%fx,%cx,4), %ax
    1     0       0   1007 test $1, %ax
    1     0       0   1008 jne .fini
    1     0       0   1009 mov turn, %ax
    1     0       1   ------ Interrupt ------  ------ Interrupt ------  
    0     0       1                            1005 mov %cx, turn
    0     0       1                            1006 mov 0(%fx,%cx,4), %ax
    0     0       1                            1007 test $1, %ax
    0     0       1                            1008 jne .fini
    0     0       1                            1009 mov turn, %ax
    0     0       0   ------ Interrupt ------  ------ Interrupt ------  
    0     0       0   1010 test %cx, %ax
    0     0       0   1011 je .spin1
    0     0       0   1006 mov 0(%fx,%cx,4), %ax
    0     0       0   1007 test $1, %ax
    0     0       0   1008 jne .fini
    0     0       1   ------ Interrupt ------  ------ Interrupt ------  
    0     0       1                            1010 test %cx, %ax
    0     0       1                            1011 je .spin1
    0     0       1                            1006 mov 0(%fx,%cx,4), %ax
    0     0       1                            1007 test $1, %ax
    0     0       1                            1008 jne .fini
    0     0       0   ------ Interrupt ------  ------ Interrupt ------  
    0     0       0   1009 mov turn, %ax
    0     0       0   1010 test %cx, %ax
    0     0       0   1011 je .spin1
    0     0       0   1012 mov count, %ax
    0     0       0   1013 add $1, %ax
    0     0       1   ------ Interrupt ------  ------ Interrupt ------  
    0     0       1                            1009 mov turn, %ax
    0     0       1                            1010 test %cx, %ax
    0     0       1                            1011 je .spin1
    0     0       1                            1006 mov 0(%fx,%cx,4), %ax
    0     0       1                            1007 test $1, %ax
    0     0       0   ------ Interrupt ------  ------ Interrupt ------  
    0     1       0   1014 mov %ax, count
    0     1       0   1015 mov $0, 0(%fx,%bx,4)
    1     1       0   1016 mov %cx, turn
    1     1       0   1017 halt
    1     1       1   ----- Halt;Switch -----  ----- Halt;Switch -----  
    1     1       1                            1008 jne .fini
    1     1       1   ------ Interrupt ------  ------ Interrupt ------  
    1     1       1                            1009 mov turn, %ax
    1     1       1                            1010 test %cx, %ax
    1     1       1                            1011 je .spin1
    1     1       1                            1012 mov count, %ax
    1     1       1                            1013 add $1, %ax
    1     1       1   ------ Interrupt ------  ------ Interrupt ------  
    1     2       1                            1014 mov %ax, count
    1     2       1                            1015 mov $0, 0(%fx,%bx,4)
    0     2       1                            1016 mov %cx, turn
    0     2       1                            1017 halt
```
我看不同i值的运行情况都挺好的，没有出现不是预期的结果。不过一定要给两个线程的bx初值肤质，否则锁不起效果。  

* **问题 10 答案**  
结果太长，这里仅仅给出命令。  
```
./x86.py -p peterson.s -M turn,count -R bx -a bx=0,bx=1 -P 0000011111 -c
./x86.py -p peterson.s -M turn,count -R bx -a bx=0,bx=1 -P 00000011111 -c
```
这两个是分别是线程0和线程1循环等待的例子，可以自行修改P试试其它情况。  

* **问题 11 答案**  
相符的。  

* **问题 12 答案**  
结果太长，这里仅仅给出命令。  
```
./x86.py -p ticket.s -a bx=1000,bx=1000 -i 5 -M count,ticket,turn -c
```
线程没出现花很长时间自旋等待锁的情况。  

* **问题 13 答案**  
结果太长，这里仅仅给出命令。  
```
./x86.py -p ticket.s -t 3 -a bx=100,bx=100,bx=100 -i 5 -M count,ticket,turn -c
```
并未发现。（太长了看的眼疼）  

* **问题 14 答案**  
结果太长，这里仅仅给出命令。  
```
./x86.py -p yield.s -M count,mutex -a bx=10,bx=10 -i 5 -c
```
经常看到锁被占用时，调用yield主动放弃CPU的情况。  

* **问题 15 答案**  
相比于test-and-set.s，多了上面的不用xchg的测试锁的步骤，这样实际上对mutex测试了两次。我猜测xchg指令对资源消费更多（时间更长）。虽然第一次没有提供测试不能提供完整的测试，但是可以排除大部分情况了，因此大部分时间都是在第一个测试处自旋，相比于xchg自旋对资源的消耗更小。  
（我的猜测不一定正确）

