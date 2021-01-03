* **问题 1 答案**  
由于结果太长，这里只写出命令。  
```
./lottery.py -j 3 -s 1 -c
./lottery.py -j 3 -s 2 -c
./lottery.py -j 3 -s 3 -c
```

* **问题 2 答案**  
由于结果太长，这里只写出命令。  
```
./lottery.py -l 10:1,10:100 -c
```
在工作1完成之前，工作0基本没有机会运行。这种不平衡会造成进程饥饿现象。

* **问题 3 答案**  
由于结果太长，这里只写出命令和简化结果。  
```
./lottery.py -l 100:100,100:100 -s 1 -c
--> JOB 1 DONE at time 196
--> JOB 0 DONE at time 200

./lottery.py -l 100:100,100:100 -s 2 -c
--> JOB 1 DONE at time 190
--> JOB 0 DONE at time 200

./lottery.py -l 100:100,100:100 -s 3 -c
--> JOB 0 DONE at time 196
--> JOB 1 DONE at time 200

./lottery.py -l 100:100,100:100 -s 4 -c
--> JOB 1 DONE at time 199
--> JOB 0 DONE at time 200
```
我觉得还是挺公平的。


* **问题 4 答案**  
由于结果太长，这里只写出命令和简化结果。  
```
./lottery.py -l 100:100,100:100 -s 1 -q 10 -c
--> JOB 1 DONE at time 160
--> JOB 0 DONE at time 200

./lottery.py -l 100:100,100:100 -s 2 -q 10 -c
--> JOB 0 DONE at time 190
--> JOB 1 DONE at time 200

./lottery.py -l 100:100,100:100 -s 3 -q 10 -c
--> JOB 1 DONE at time 190
--> JOB 0 DONE at time 200

./lottery.py -l 100:100,100:100 -s 4 -q 10 -c
--> JOB 0 DONE at time 190
--> JOB 1 DONE at time 200
```
由于量子规模变大，相当于工作长度缩短了，因此进程的不公平性增加。  


* **问题 5 答案**  
用步长调度程序制作图表，如果选取调度周期作为采样时间点，那么图表会是精确的完全公平直线。  
如果同时选用非调度周期作为时间点，那么在直线附近会有一些起伏，且起伏程度越来越小。  
