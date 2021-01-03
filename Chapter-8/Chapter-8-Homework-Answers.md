* **问题 1 答案**  
```
[testjz@localhost cpu-sched-mlfq]$ ./mlfq.py -j 2 -m 10 -M 0 -n 2 -q 3 -c
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 2
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is   3
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is   3
OPTIONS boost 0
OPTIONS ioTime 5
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime   8 - ioFreq   0
  Job  1: startTime   0 - runTime   4 - ioFreq   0


Execution Trace:

[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 7 (of 8) ]
[ time 1 ] Run JOB 0 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 6 (of 8) ]
[ time 2 ] Run JOB 0 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 5 (of 8) ]
[ time 3 ] Run JOB 1 at PRIORITY 1 [ TICKS 2 ALLOT 1 TIME 3 (of 4) ]
[ time 4 ] Run JOB 1 at PRIORITY 1 [ TICKS 1 ALLOT 1 TIME 2 (of 4) ]
[ time 5 ] Run JOB 1 at PRIORITY 1 [ TICKS 0 ALLOT 1 TIME 1 (of 4) ]
[ time 6 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 4 (of 8) ]
[ time 7 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 3 (of 8) ]
[ time 8 ] Run JOB 0 at PRIORITY 0 [ TICKS 0 ALLOT 1 TIME 2 (of 8) ]
[ time 9 ] Run JOB 1 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 0 (of 4) ]
[ time 10 ] FINISHED JOB 1
[ time 10 ] Run JOB 0 at PRIORITY 0 [ TICKS 2 ALLOT 1 TIME 1 (of 8) ]
[ time 11 ] Run JOB 0 at PRIORITY 0 [ TICKS 1 ALLOT 1 TIME 0 (of 8) ]
[ time 12 ] FINISHED JOB 0

Final statistics:
  Job  0: startTime   0 - response   0 - turnaround  12
  Job  1: startTime   0 - response   3 - turnaround  10

  Avg  1: startTime n/a - response 1.50 - turnaround 11.00

```
* **问题 2 答案**  
答案结果太长，所以我只写出命令，按照命令执行即可产生答案。  
```
实例1：单个长工作
./mlfq.py -l 0,200,0 -q 10 -n 3 -c
实例2：来了一个短工作
./mlfq.py -l 0,200,0:100,20,0 -q 10 -n 3 -c
实例3：如果有I/O呢
./mlfq.py -l 0,40,2:0,200,0 -q 10 -n 3 -i 5 -c
尝试2：提升优先级 图8.5左
./mlfq.py -l 0,150,0:100,50,5:100,50,5 -q 10 -n 3 -i 5 -S -c
尝试2：提升优先级 图8.5右
./mlfq.py -l 0,150,0:100,50,5:100,50,5 -q 10 -n 3 -i 5 -S -B 50 -c
尝试3：更好的计时方式 图8.6左
./mlfq.py -l 0,200,0:30,200,9 -q 10 -n 3 -i 1 -S -c
尝试3：更好的计时方式 图8.6右
./mlfq.py -l 0,200,0:30,200,9 -q 10 -n 3 -i 1 -c
8.5 MLFQ调优及其他问题 图8.7
./mlfq.py -l 0,200,0:0,200,0 -Q 10,20,40 -n 3 -c
```

* **问题 3 答案**  
队列个数设置为1即可。  
由于结果太长，这里只写出命令。  
```
./mlfq.py -l 0,50,0:0,50,0:0,50,0 -q 10 -n 1 -c
```

* **问题 4 答案**  
由于结果太长，这里只写出命令。  
```
./mlfq.py -l 0,1000,0:300,1000,99 -q 100 -n 3 -i 1 -S -c
```

* **问题 5 答案**  
由于结果太长，这里只写出命令。  
```
./mlfq.py -l 0,200,0:0,100,5:0,100,5 -q 10 -n 3 -i 5 -B 100 -c
```

* **问题 6 答案**  
由于结果太长，这里只写出命令。  
```
./mlfq.py -l 0,50,5:0,50,5:0,50,5 -q 10 -n 3 -i 5 -S -c
./mlfq.py -l 0,50,5:0,50,5:0,50,5 -q 10 -n 3 -i 5 -S -I -c
```
如果不加-I，三个任务交替执行。如果增加了-I，则第一个和第二个任务交替执行，第三个任务没有机会被执行。
