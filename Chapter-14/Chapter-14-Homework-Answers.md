* **问题 1 答案**  
[答案代码](14.1.c)
```C
#include<stdlib.h>
int main()
{
	int * p = NULL;
	free(p);
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./14.1
```
无任何输出或者错误提示

* **问题 2 答案**  
执行结果
```
(gdb) run
Starting program: /home/testjz/OS_test/./14.1 
[Inferior 1 (process 28177) exited normally]
```

* **问题 3 答案**  
执行结果
```
[testjz@localhost OS_test]$ valgrind --leak-check=yes ./14.1
==28207== Memcheck, a memory error detector
==28207== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==28207== Using Valgrind-3.16.1 and LibVEX; rerun with -h for copyright info
==28207== Command: ./14.1
==28207== 
==28207== 
==28207== HEAP SUMMARY:
==28207==     in use at exit: 0 bytes in 0 blocks
==28207==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==28207== 
==28207== All heap blocks were freed -- no leaks are possible
==28207== 
==28207== For lists of detected and suppressed errors, rerun with: -s
==28207== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
看起来什么都没发生。可能我目前的系统可以较好应对释放空指针的情况，所以不会报错。

* **问题 4 答案**  
[答案代码](14.4.c)
```C
#include<stdlib.h>
int main()
{
	int * p = (int *)malloc(sizeof(int));
	return 0;
}
```
gdb执行结果
```
(gdb) run
Starting program: /home/testjz/OS_test/./14.2 
[Inferior 1 (process 28324) exited normally]
```
看不出问题。
valgrind执行结果
```
[testjz@localhost OS_test]$ valgrind --leak-check=yes ./14.2
==28342== Memcheck, a memory error detector
==28342== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==28342== Using Valgrind-3.16.1 and LibVEX; rerun with -h for copyright info
==28342== Command: ./14.2
==28342== 
==28342== 
==28342== HEAP SUMMARY:
==28342==     in use at exit: 4 bytes in 1 blocks
==28342==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==28342== 
==28342== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==28342==    at 0x4C29F73: malloc (vg_replace_malloc.c:307)
==28342==    by 0x40053E: main (14.2.c:4)
==28342== 
==28342== LEAK SUMMARY:
==28342==    definitely lost: 4 bytes in 1 blocks
==28342==    indirectly lost: 0 bytes in 0 blocks
==28342==      possibly lost: 0 bytes in 0 blocks
==28342==    still reachable: 0 bytes in 0 blocks
==28342==         suppressed: 0 bytes in 0 blocks
==28342== 
==28342== For lists of detected and suppressed errors, rerun with: -s
==28342== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
检测出了内存泄漏问题。

* **问题 5 答案**  
[答案代码](14.5.c)
```C
#include<stdlib.h>
int main()
{
	int * data = (int *)malloc(100*sizeof(int));
	data[100] = 0;
	free(data);
	return 0;
}
```
gdb执行结果
```
(gdb) run
Starting program: /home/testjz/OS_test/./14.5 
[Inferior 1 (process 28575) exited normally]
```
看不出问题。
valgrind执行结果
```
[testjz@localhost OS_test]$ valgrind --leak-check=yes ./14.5
==28593== Memcheck, a memory error detector
==28593== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==28593== Using Valgrind-3.16.1 and LibVEX; rerun with -h for copyright info
==28593== Command: ./14.5
==28593== 
==28593== Invalid write of size 4
==28593==    at 0x40059D: main (14.5.c:5)
==28593==  Address 0x52051d0 is 0 bytes after a block of size 400 alloc'd
==28593==    at 0x4C29F73: malloc (vg_replace_malloc.c:307)
==28593==    by 0x40058E: main (14.5.c:4)
==28593== 
==28593== 
==28593== HEAP SUMMARY:
==28593==     in use at exit: 0 bytes in 0 blocks
==28593==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==28593== 
==28593== All heap blocks were freed -- no leaks are possible
==28593== 
==28593== For lists of detected and suppressed errors, rerun with: -s
==28593== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
检测到无效写入错误。

* **问题 6 答案**  
[答案代码](14.6.c)
```C
#include<stdlib.h>
#include<stdio.h>
int main()
{
	int * p = (int *)malloc(100*sizeof(int));
	p[1] = 10;
	p[90] = 20;
	free(p);
	printf("%d %d\n", p[1],p[90]);
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./14.6
10 20
```
结果输出了数字的值。
valgrind执行结果
```
[testjz@localhost OS_test]$ valgrind --leak-check=yes ./14.6
==28718== Memcheck, a memory error detector
==28718== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==28718== Using Valgrind-3.16.1 and LibVEX; rerun with -h for copyright info
==28718== Command: ./14.6
==28718== 
==28718== Invalid read of size 4
==28718==    at 0x400607: main (14.6.c:9)
==28718==  Address 0x52051a8 is 360 bytes inside a block of size 400 free'd
==28718==    at 0x4C2B06D: free (vg_replace_malloc.c:538)
==28718==    by 0x4005FC: main (14.6.c:8)
==28718==  Block was alloc'd at
==28718==    at 0x4C29F73: malloc (vg_replace_malloc.c:307)
==28718==    by 0x4005CE: main (14.6.c:5)
==28718== 
==28718== Invalid read of size 4
==28718==    at 0x400611: main (14.6.c:9)
==28718==  Address 0x5205044 is 4 bytes inside a block of size 400 free'd
==28718==    at 0x4C2B06D: free (vg_replace_malloc.c:538)
==28718==    by 0x4005FC: main (14.6.c:8)
==28718==  Block was alloc'd at
==28718==    at 0x4C29F73: malloc (vg_replace_malloc.c:307)
==28718==    by 0x4005CE: main (14.6.c:5)
==28718== 
10 20
==28718== 
==28718== HEAP SUMMARY:
==28718==     in use at exit: 0 bytes in 0 blocks
==28718==   total heap usage: 1 allocs, 1 frees, 400 bytes allocated
==28718== 
==28718== All heap blocks were freed -- no leaks are possible
==28718== 
==28718== For lists of detected and suppressed errors, rerun with: -s
==28718== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```
检测到了两个无效读取。

* **问题 7 答案**  
[答案代码](14.7.c)
```C
#include<stdlib.h>
int main()
{
	int * p = (int *)malloc(100*sizeof(int));
	free(p+50);
	return 0;
}
```
执行结果
```
[testjz@localhost OS_test]$ ./14.7
*** Error in `./14.7': free(): invalid pointer: 0x000000000094a0d8 ***
======= Backtrace: =========
/lib64/libc.so.6(+0x81679)[0x7fe6ce387679]
./14.7[0x4005a5]
/lib64/libc.so.6(__libc_start_main+0xf5)[0x7fe6ce328505]
./14.7[0x4004b9]
======= Memory map: ========
00400000-00401000 r-xp 00000000 fd:03 4535                               /home/testjz/OS_test/14.7
00600000-00601000 r--p 00000000 fd:03 4535                               /home/testjz/OS_test/14.7
00601000-00602000 rw-p 00001000 fd:03 4535                               /home/testjz/OS_test/14.7
0094a000-0096b000 rw-p 00000000 00:00 0                                  [heap]
7fe6c8000000-7fe6c8021000 rw-p 00000000 00:00 0 
7fe6c8021000-7fe6cc000000 ---p 00000000 00:00 0 
7fe6ce0f0000-7fe6ce105000 r-xp 00000000 fd:00 78                         /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fe6ce105000-7fe6ce304000 ---p 00015000 fd:00 78                         /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fe6ce304000-7fe6ce305000 r--p 00014000 fd:00 78                         /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fe6ce305000-7fe6ce306000 rw-p 00015000 fd:00 78                         /usr/lib64/libgcc_s-4.8.5-20150702.so.1
7fe6ce306000-7fe6ce4c9000 r-xp 00000000 fd:00 144179                     /usr/lib64/libc-2.17.so
7fe6ce4c9000-7fe6ce6c9000 ---p 001c3000 fd:00 144179                     /usr/lib64/libc-2.17.so
7fe6ce6c9000-7fe6ce6cd000 r--p 001c3000 fd:00 144179                     /usr/lib64/libc-2.17.so
7fe6ce6cd000-7fe6ce6cf000 rw-p 001c7000 fd:00 144179                     /usr/lib64/libc-2.17.so
7fe6ce6cf000-7fe6ce6d4000 rw-p 00000000 00:00 0 
7fe6ce6d4000-7fe6ce6f6000 r-xp 00000000 fd:00 144172                     /usr/lib64/ld-2.17.so
7fe6ce8dc000-7fe6ce8df000 rw-p 00000000 00:00 0 
7fe6ce8f3000-7fe6ce8f5000 rw-p 00000000 00:00 0 
7fe6ce8f5000-7fe6ce8f6000 r--p 00021000 fd:00 144172                     /usr/lib64/ld-2.17.so
7fe6ce8f6000-7fe6ce8f7000 rw-p 00022000 fd:00 144172                     /usr/lib64/ld-2.17.so
7fe6ce8f7000-7fe6ce8f8000 rw-p 00000000 00:00 0 
7fffb1d06000-7fffb1d27000 rw-p 00000000 00:00 0                          [stack]
7fffb1dc1000-7fffb1dc3000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
已放弃(吐核)
```
直接报错。不需要工具就能找到这个问题。

* **问题 8 答案**  
这就是类似C++中vector的数据结构。 
特性类似数组，可以实现O(1)的访问或者尾部新增，但是如果空间满了需要realloc的时候需要O(n)的时间。

* **问题 9 答案**  
无答案。
