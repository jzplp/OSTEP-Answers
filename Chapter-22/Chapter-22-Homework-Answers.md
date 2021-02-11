* **问题 1 答案**  
结果太长，这里仅仅给出命令。  
```
./paging-policy.py -s 0 -n 10 -p FIFO -c
./paging-policy.py -s 1 -n 10 -p FIFO -c
./paging-policy.py -s 2 -n 10 -p FIFO -c

./paging-policy.py -s 0 -n 10 -p LRU -c
./paging-policy.py -s 1 -n 10 -p LRU -c
./paging-policy.py -s 2 -n 10 -p LRU -c

./paging-policy.py -s 0 -n 10 -p OPT -c
./paging-policy.py -s 1 -n 10 -p OPT -c
./paging-policy.py -s 2 -n 10 -p OPT -c
```

* **问题 2 答案**  
序列为：1，2，3，4，5，6 即可。  
像这种会造成抖动的序列，需要至少增大到序列个数才行。  

* **问题 3 答案**  
[答案代码 genRandom.py](genRandom.py)
```python
#! /usr/bin/env python
import random 
Max =  10
num =  10

arr = []
for i in range(0, num):
    t = random.randint(0, Max - 1)
    arr.append(t)
print(arr)

file = open('./1.txt', 'w')

for i in arr:
    file.write(str(i) + '\n')

file.close()
```
测试命令：
```
./paging-policy.py -f 1.txt -p FIFO -c
./paging-policy.py -f 1.txt -p LRU -c
./paging-policy.py -f 1.txt -p OPT -c
```
结果预计和图22.2无局部性负载的情况相似。  

* **问题 4 答案**  
[答案代码 genLocalRandom.py](genLocalRandom.py)
```python
#! /usr/bin/env python
import random 
Max =  10
num =  10
randCite = 0.8
randomHotPage = 0.2

arr = []

numlist = set(range(0, Max))
hotPage = set()
coldPage = set()

while len(hotPage) < int(Max * randomHotPage):
    i = random.choice(list(numlist))
    hotPage.add(i)
coldPage = numlist - hotPage
print(hotPage)
print(coldPage)
hotPage = list(hotPage)
coldPage = list(coldPage)

for i in range(0, num):
    if(random.random() > randCite):
        t = random.choice(coldPage)
    else:
        t = random.choice(hotPage)
    arr.append(t)
print(arr)

file = open('./1.txt', 'w')

for i in arr:
    file.write(str(i) + '\n')

file.close()
```
测试命令：
```
./paging-policy.py -f 1.txt -p LRU -c
./paging-policy.py -f 1.txt -p RAND -c
./paging-policy.py -f 1.txt -p CLOCK -c
```
类似于图22.3，LRU的表现略好于RAND。  
经过不完全测试，CLOCK bit为1时表现差于LRU，提高bit时出现好于LRU的情况，且在一定数值内bit越高表现越好。  

* **问题 5 答案**  
命令执行结果：（省略上面的大量内存记录）
```
==5192== 
==5192== Counted 0 calls to main()
==5192== 
==5192== Jccs:
==5192==   total:         96,040
==5192==   taken:         47,991 (50%)
==5192== 
==5192== Executed:
==5192==   SBs entered:   92,692
==5192==   SBs completed: 62,247
==5192==   guest instrs:  468,723
==5192==   IRStmts:       2,930,905
==5192== 
==5192== Ratios:
==5192==   guest instrs : SB entered  = 50 : 10
==5192==        IRStmts : SB entered  = 316 : 10
==5192==        IRStmts : guest instr = 62 : 10
==5192== 
==5192== Exit code:       0
```
上面的内存记录的说明可以看Valgrind源代码中lackey/lk_main.c文件最上面的注释。但是这个最后的总结我没找到说明，因此没看懂。  
测试缓存过程省略。 
