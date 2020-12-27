* **问题 1 答案**  

```
[testjz@localhost cpu-intro]$ ./process-run.py -l 5:100,5:100
Produce a trace of what would happen when you run these processes:
Process 0
  cpu
  cpu
  cpu
  cpu
  cpu

Process 1
  cpu
  cpu
  cpu
  cpu
  cpu

Important behaviors:
  System will switch whenthe current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO willrun LATER (when it is its turn)

[testjz@localhost cpu-intro]$ ./process-run.py -l 5:100,5:100 -c
Time    PID: 0    PID: 1       CPU       IOs
  1    RUN:cpu     READY         1          
  2    RUN:cpu     READY         1          
  3    RUN:cpu     READY         1          
  4    RUN:cpu     READY         1          
  5    RUN:cpu     READY         1          
  6       DONE   RUN:cpu         1          
  7       DONE   RUN:cpu         1          
  8       DONE   RUN:cpu         1          
  9       DONE   RUN:cpu         1          
 10       DONE   RUN:cpu         1          
[testjz@localhost cpu-intro]$ 
```

* **问题 2 答案**  
```
[testjz@localhost cpu-intro]$ ./process-run.py -l 4:100,1:0
Produce a trace of what would happen when you run these processes:
Process 0
  cpu
  cpu
  cpu
  cpu

Process 1
  io

Important behaviors:
  System will switch whenthe current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO willrun LATER (when it is its turn)

[testjz@localhost cpu-intro]$ ./process-run.py -l 4:100,1:0 -c
Time    PID: 0    PID: 1       CPU       IOs
  1    RUN:cpu     READY         1          
  2    RUN:cpu     READY         1          
  3    RUN:cpu     READY         1          
  4    RUN:cpu     READY         1          
  5       DONE    RUN:io         1          
  6       DONE   WAITING                   1
  7       DONE   WAITING                   1
  8       DONE   WAITING                   1
  9       DONE   WAITING                   1
 10*      DONE      DONE         1
[testjz@localhost cpu-intro]$ 
```

* **问题 3 答案**  
```
[testjz@localhost cpu-intro]$ ./process-run.py -l 1:0,4:100
Produce a trace of what would happen when you run these processes:
Process 0
  io

Process 1
  cpu
  cpu
  cpu
  cpu

Important behaviors:
  System will switch whenthe current process is FINISHED or ISSUES AN IO
  After IOs, the process issuing the IO willrun LATER (when it is its turn)

[testjz@localhost cpu-intro]$ ./process-run.py -l 1:0,4:100 -c
Time    PID: 0    PID: 1       CPU       IOs
  1     RUN:io     READY         1          
  2    WAITING   RUN:cpu         1         1
  3    WAITING   RUN:cpu         1         1
  4    WAITING   RUN:cpu         1         1
  5    WAITING   RUN:cpu         1         1
  6*      DONE      DONE         1
[testjz@localhost cpu-intro]$ 
```

* **问题 4 答案**  
```
[testjz@localhost cpu-intro]$ ./process-run.py -l 1:0,4:100 -c  -S SWITCH_ON_END
Time    PID: 0    PID: 1       CPU       IOs
  1     RUN:io     READY         1          
  2    WAITING     READY                   1
  3    WAITING     READY                   1
  4    WAITING     READY                   1
  5    WAITING     READY                   1
  6*      DONE   RUN:cpu         1          
  7       DONE   RUN:cpu         1          
  8       DONE   RUN:cpu         1          
  9       DONE   RUN:cpu         1          
[testjz@localhost cpu-intro]$ 
```

* **问题 5 答案**  
```
[testjz@localhost cpu-intro]$ ./process-run.py -l 1:0,4:100 -c  -S SWITCH_ON_IO
Time    PID: 0    PID: 1       CPU       IOs
  1     RUN:io     READY         1          
  2    WAITING   RUN:cpu         1         1
  3    WAITING   RUN:cpu         1         1
  4    WAITING   RUN:cpu         1         1
  5    WAITING   RUN:cpu         1         1
  6*      DONE      DONE         1
[testjz@localhost cpu-intro]$
```

* **问题 6 答案**  
```
[testjz@localhost cpu-intro]$ ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p
Time    PID: 0    PID: 1    PID: 2    PID: 3       CPU       IOs
  1     RUN:io     READY     READY     READY         1          
  2    WAITING   RUN:cpu     READY     READY         1         1
  3    WAITING   RUN:cpu     READY     READY         1         1
  4    WAITING   RUN:cpu     READY     READY         1         1
  5    WAITING   RUN:cpu     READY     READY         1         1
  6*     READY   RUN:cpu     READY     READY         1          
  7      READY      DONE   RUN:cpu     READY         1          
  8      READY      DONE   RUN:cpu     READY         1          
  9      READY      DONE   RUN:cpu     READY         1          
 10      READY      DONE   RUN:cpu     READY         1          
 11      READY      DONE   RUN:cpu     READY         1          
 12      READY      DONE      DONE   RUN:cpu         1          
 13      READY      DONE      DONE   RUN:cpu         1          
 14      READY      DONE      DONE   RUN:cpu         1          
 15      READY      DONE      DONE   RUN:cpu         1          
 16      READY      DONE      DONE   RUN:cpu         1          
 17     RUN:io      DONE      DONE      DONE         1          
 18    WAITING      DONE      DONE      DONE                   1
 19    WAITING      DONE      DONE      DONE                   1
 20    WAITING      DONE      DONE      DONE                   1
 21    WAITING      DONE      DONE      DONE                   1
 22*    RUN:io      DONE      DONE      DONE         1          
 23    WAITING      DONE      DONE      DONE                   1
 24    WAITING      DONE      DONE      DONE                   1
 25    WAITING      DONE      DONE      DONE                   1
 26    WAITING      DONE      DONE      DONE                   1
 27*      DONE      DONE      DONE      DONE         1

Stats: Total Time 27
Stats: CPU Busy 19 (70.37%)
Stats: IO Busy  12 (44.44%)

[testjz@localhost cpu-intro]$
```

* **问题 7 答案**  
```
[testjz@localhost cpu-intro]$ ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p
Time    PID: 0    PID: 1    PID: 2    PID: 3       CPU       IOs
  1     RUN:io     READY     READY     READY         1          
  2    WAITING   RUN:cpu     READY     READY         1         1
  3    WAITING   RUN:cpu     READY     READY         1         1
  4    WAITING   RUN:cpu     READY     READY         1         1
  5    WAITING   RUN:cpu     READY     READY         1         1
  6*    RUN:io     READY     READY     READY         1          
  7    WAITING   RUN:cpu     READY     READY         1         1
  8    WAITING      DONE   RUN:cpu     READY         1         1
  9    WAITING      DONE   RUN:cpu     READY         1         1
 10    WAITING      DONE   RUN:cpu     READY         1         1
 11*    RUN:io      DONE     READY     READY         1          
 12    WAITING      DONE   RUN:cpu     READY         1         1
 13    WAITING      DONE   RUN:cpu     READY         1         1
 14    WAITING      DONE      DONE   RUN:cpu         1         1
 15    WAITING      DONE      DONE   RUN:cpu         1         1
 16*      DONE      DONE      DONE   RUN:cpu         1          
 17       DONE      DONE      DONE   RUN:cpu         1          
 18       DONE      DONE      DONE   RUN:cpu         1          

Stats: Total Time 18
Stats: CPU Busy 18 (100.00%)
Stats: IO Busy  12 (66.67%)

[testjz@localhost cpu-intro]$
```
因为有过IO操作的进程很有可能后面也会进行IO操作，为了使CPU有效利用，应该在IO结束不久后运行该进程，使其得到继续阻塞IO的机会。

* **问题 8 答案**  
随机测试，无答案。
