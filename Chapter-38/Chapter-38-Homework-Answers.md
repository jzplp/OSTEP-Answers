* **问题 1 答案**  
```
[testjz@localhost file-raid]$ ./raid.py -n 5 -L 5 -R 20 -5 LS  -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 5
ARG reqSize 4k
ARG workload rand
ARG writeFrac 0
ARG randRange 20
ARG level 5
ARG raid5 LS
ARG reverse False
ARG timing False

16 1
LOGICAL READ from addr:16 size:4096
  read  [disk 0, offset 5]  
8 1
LOGICAL READ from addr:8 size:4096
  read  [disk 0, offset 2]  
10 1
LOGICAL READ from addr:10 size:4096
  read  [disk 2, offset 3]  
15 1
LOGICAL READ from addr:15 size:4096
  read  [disk 3, offset 5]  
9 1
LOGICAL READ from addr:9 size:4096
  read  [disk 1, offset 3]  

[testjz@localhost file-raid]$ ./raid.py -n 5 -L 5 -R 20 -5 LA -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 5
ARG reqSize 4k
ARG workload rand
ARG writeFrac 0
ARG randRange 20
ARG level 5
ARG raid5 LA
ARG reverse False
ARG timing False

16 1
LOGICAL READ from addr:16 size:4096
  read  [disk 1, offset 5]  
8 1
LOGICAL READ from addr:8 size:4096
  read  [disk 3, offset 2]  
10 1
LOGICAL READ from addr:10 size:4096
  read  [disk 2, offset 3]  
15 1
LOGICAL READ from addr:15 size:4096
  read  [disk 0, offset 5]  
9 1
LOGICAL READ from addr:9 size:4096
  read  [disk 1, offset 3]  
```
RAID5的左对称和左不对称布局有较大区别，详情上网搜索一下即可。    

* **问题 2 答案**  
```
[testjz@localhost file-raid]$ ./raid.py -n 5 -L 0 -C 8192 -R 20 -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 8192
ARG numRequests 5
ARG reqSize 4k
ARG workload rand
ARG writeFrac 0
ARG randRange 20
ARG level 0
ARG raid5 LS
ARG reverse False
ARG timing False

16 1
LOGICAL READ from addr:16 size:4096
  read  [disk 0, offset 4]  

8 1
LOGICAL READ from addr:8 size:4096
  read  [disk 0, offset 2]  

10 1
LOGICAL READ from addr:10 size:4096
  read  [disk 1, offset 2]  

15 1
LOGICAL READ from addr:15 size:4096
  read  [disk 3, offset 3]  

9 1
LOGICAL READ from addr:9 size:4096
  read  [disk 0, offset 3]  


[testjz@localhost file-raid]$ ./raid.py -n 5 -L 0 -C 16384 -R 20 -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 16384
ARG numRequests 5
ARG reqSize 4k
ARG workload rand
ARG writeFrac 0
ARG randRange 20
ARG level 0
ARG raid5 LS
ARG reverse False
ARG timing False

16 1
LOGICAL READ from addr:16 size:4096
  read  [disk 0, offset 4]  

8 1
LOGICAL READ from addr:8 size:4096
  read  [disk 2, offset 0]  

10 1
LOGICAL READ from addr:10 size:4096
  read  [disk 2, offset 2]  

15 1
LOGICAL READ from addr:15 size:4096
  read  [disk 3, offset 3]  

9 1
LOGICAL READ from addr:9 size:4096
  read  [disk 2, offset 1]  
```

* **问题 3 答案**  
```
[testjz@localhost file-raid]$ ./raid.py -n 5 -L 0 -R 20 -r  -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 5
ARG reqSize 4k
ARG workload rand
ARG writeFrac 0
ARG randRange 20
ARG level 0
ARG raid5 LS
ARG reverse True
ARG timing False

16 1
LOGICAL READ from addr:16 size:4096
  read  [disk 0, offset 4]  

8 1
LOGICAL READ from addr:8 size:4096
  read  [disk 0, offset 2]  

10 1
LOGICAL READ from addr:10 size:4096
  read  [disk 2, offset 2]  

15 1
LOGICAL READ from addr:15 size:4096
  read  [disk 3, offset 3]  

9 1
LOGICAL READ from addr:9 size:4096
  read  [disk 1, offset 2]  
```

* **问题 4 答案**  
```
[testjz@localhost file-raid]$ ./raid.py -n 5 -L 4 -R 20 -r -S 8k -W seq -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 5
ARG reqSize 8k
ARG workload seq
ARG writeFrac 0
ARG randRange 20
ARG level 4
ARG raid5 LS
ARG reverse True
ARG timing False

0 2
LOGICAL READ from addr:0 size:8192
  read  [disk 0, offset 0]    read  [disk 1, offset 0]  
2 2
LOGICAL READ from addr:2 size:8192
  read  [disk 2, offset 0]    read  [disk 0, offset 1]  
4 2
LOGICAL READ from addr:4 size:8192
  read  [disk 1, offset 1]    read  [disk 2, offset 1]  
6 2
LOGICAL READ from addr:6 size:8192
  read  [disk 0, offset 2]    read  [disk 1, offset 2]  
8 2
LOGICAL READ from addr:8 size:8192
  read  [disk 2, offset 2]    read  [disk 0, offset 3]  

[testjz@localhost file-raid]$ ./raid.py -n 5 -L 4 -R 20 -r -S 12k -W seq -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 5
ARG reqSize 12k
ARG workload seq
ARG writeFrac 0
ARG randRange 20
ARG level 4
ARG raid5 LS
ARG reverse True
ARG timing False

0 3
LOGICAL READ from addr:0 size:12288
  read  [disk 0, offset 0]    read  [disk 1, offset 0]    read  [disk 2, offset 0]  
3 3
LOGICAL READ from addr:3 size:12288
  read  [disk 0, offset 1]    read  [disk 1, offset 1]    read  [disk 2, offset 1]  
6 3
LOGICAL READ from addr:6 size:12288
  read  [disk 0, offset 2]    read  [disk 1, offset 2]    read  [disk 2, offset 2]  
9 3
LOGICAL READ from addr:9 size:12288
  read  [disk 0, offset 3]    read  [disk 1, offset 3]    read  [disk 2, offset 3]  
12 3
LOGICAL READ from addr:12 size:12288
  read  [disk 0, offset 4]    read  [disk 1, offset 4]    read  [disk 2, offset 4]  

[testjz@localhost file-raid]$ ./raid.py -n 5 -L 4 -R 20 -r -S 16k -W seq -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 5
ARG reqSize 16k
ARG workload seq
ARG writeFrac 0
ARG randRange 20
ARG level 4
ARG raid5 LS
ARG reverse True
ARG timing False

0 4
LOGICAL READ from addr:0 size:16384
  read  [disk 0, offset 0]    read  [disk 1, offset 0]    read  [disk 2, offset 0]    read  [disk 0, offset 1]  
4 4
LOGICAL READ from addr:4 size:16384
  read  [disk 1, offset 1]    read  [disk 2, offset 1]    read  [disk 0, offset 2]    read  [disk 1, offset 2]  
8 4
LOGICAL READ from addr:8 size:16384
  read  [disk 2, offset 2]    read  [disk 0, offset 3]    read  [disk 1, offset 3]    read  [disk 2, offset 3]  
12 4
LOGICAL READ from addr:12 size:16384
  read  [disk 0, offset 4]    read  [disk 1, offset 4]    read  [disk 2, offset 4]    read  [disk 0, offset 5]  
16 4
LOGICAL READ from addr:16 size:16384
  read  [disk 1, offset 5]    read  [disk 2, offset 5]    read  [disk 0, offset 6]    read  [disk 1, offset 6]  
```
相比于RAID1，RAID4/5在更大的请求中工作效率更高，一般超过N/2个磁盘。  

* **问题 5 答案**  
```
[testjz@localhost file-raid]$ ./raid.py -n 100 -L 0 -R 1000 -W rand -t -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload rand
ARG writeFrac 0
ARG randRange 1000
ARG level 0
ARG raid5 LS
ARG reverse False
ARG timing True


disk:0  busy:  93.02  I/Os:    24 (sequential:0 nearly:13 random:11)
disk:1  busy: 100.00  I/Os:    25 (sequential:1 nearly:11 random:13)
disk:2  busy:  98.54  I/Os:    26 (sequential:0 nearly:16 random:10)
disk:3  busy:  96.45  I/Os:    25 (sequential:0 nearly:17 random:8)

STAT totalTime 177.6

[testjz@localhost file-raid]$ ./raid.py -n 100 -L 1 -R 1000 -W rand -t -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload rand
ARG writeFrac 0
ARG randRange 1000
ARG level 1
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy:  86.52  I/Os:    24 (sequential:0 nearly:8 random:16)
disk:1  busy: 100.00  I/Os:    26 (sequential:0 nearly:11 random:15)
disk:2  busy:  91.91  I/Os:    25 (sequential:0 nearly:7 random:18)
disk:3  busy:  93.28  I/Os:    25 (sequential:0 nearly:8 random:17)

STAT totalTime 226.3


[testjz@localhost file-raid]$ ./raid.py -n 100 -L 4 -R 1000 -W rand -t -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload rand
ARG writeFrac 0
ARG randRange 1000
ARG level 4
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy:  96.95  I/Os:    32 (sequential:0 nearly:17 random:15)
disk:1  busy:  99.41  I/Os:    34 (sequential:0 nearly:20 random:14)
disk:2  busy: 100.00  I/Os:    34 (sequential:0 nearly:22 random:12)
disk:3  busy:   0.00  I/Os:     0 (sequential:0 nearly:0 random:0)

STAT totalTime 235.9

[testjz@localhost file-raid]$ ./raid.py -n 100 -L 5 -R 1000 -W rand -t -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload rand
ARG writeFrac 0
ARG randRange 1000
ARG level 5
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy:  91.33  I/Os:    24 (sequential:0 nearly:11 random:13)
disk:1  busy:  97.52  I/Os:    25 (sequential:1 nearly:10 random:14)
disk:2  busy: 100.00  I/Os:    26 (sequential:0 nearly:14 random:12)
disk:3  busy:  97.97  I/Os:    25 (sequential:0 nearly:12 random:13)

STAT totalTime 197.2
```

* **问题 6 答案**  
```
[testjz@localhost file-raid]$ ./raid.py -n 100 -L 5 -R 5000 -W rand -t -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload rand
ARG writeFrac 0
ARG randRange 5000
ARG level 5
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy:  73.09  I/Os:    24 (sequential:0 nearly:3 random:21)
disk:1  busy:  60.92  I/Os:    19 (sequential:0 nearly:1 random:18)
disk:2  busy: 100.00  I/Os:    33 (sequential:0 nearly:4 random:29)
disk:3  busy:  78.29  I/Os:    24 (sequential:0 nearly:0 random:24)

STAT totalTime 309.6
```
增加磁盘数量后，邻近的频率变少，因此速度变慢。  

* **问题 7 答案**  
```
[testjz@localhost file-raid]$ ./raid.py -n 100 -L 0 -R 1000 -W rand -t -w 100 -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload rand
ARG writeFrac 100
ARG randRange 1000
ARG level 0
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy:  93.02  I/Os:    24 (sequential:0 nearly:13 random:11)
disk:1  busy: 100.00  I/Os:    25 (sequential:1 nearly:11 random:13)
disk:2  busy:  98.54  I/Os:    26 (sequential:0 nearly:16 random:10)
disk:3  busy:  96.45  I/Os:    25 (sequential:0 nearly:17 random:8)

STAT totalTime 177.6

[testjz@localhost file-raid]$ ./raid.py -n 100 -L 1 -R 1000 -W rand -t -w 100 -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload rand
ARG writeFrac 100
ARG randRange 1000
ARG level 1
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy:  96.71  I/Os:    50 (sequential:0 nearly:21 random:29)
disk:1  busy:  96.71  I/Os:    50 (sequential:0 nearly:21 random:29)
disk:2  busy: 100.00  I/Os:    50 (sequential:0 nearly:15 random:35)
disk:3  busy: 100.00  I/Os:    50 (sequential:0 nearly:15 random:35)

STAT totalTime 424.9

[testjz@localhost file-raid]$ ./raid.py -n 100 -L 4 -R 1000 -W rand -t -w 100 -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload rand
ARG writeFrac 100
ARG randRange 1000
ARG level 4
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy:  31.95  I/Os:    64 (sequential:0 nearly:49 random:15)
disk:1  busy:  32.77  I/Os:    68 (sequential:0 nearly:54 random:14)
disk:2  busy:  32.96  I/Os:    68 (sequential:0 nearly:56 random:12)
disk:3  busy: 100.00  I/Os:   200 (sequential:0 nearly:154 random:46)

STAT totalTime 715.7

[testjz@localhost file-raid]$ ./raid.py -n 100 -L 5 -R 1000 -W rand -t -w 100 -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload rand
ARG writeFrac 100
ARG randRange 1000
ARG level 5
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy: 100.00  I/Os:   122 (sequential:1 nearly:92 random:29)
disk:1  busy:  82.33  I/Os:    96 (sequential:0 nearly:76 random:20)
disk:2  busy:  67.34  I/Os:    86 (sequential:0 nearly:69 random:17)
disk:3  busy:  79.73  I/Os:    96 (sequential:0 nearly:73 random:23)

STAT totalTime 443.6
```

* **问题 8 答案**  
```
[testjz@localhost file-raid]$ ./raid.py -n 100 -L 0 -R 1000 -W seq -t -w 100 -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload seq
ARG writeFrac 100
ARG randRange 1000
ARG level 0
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy: 100.00  I/Os:    25 (sequential:24 nearly:0 random:1)
disk:1  busy: 100.00  I/Os:    25 (sequential:24 nearly:0 random:1)
disk:2  busy: 100.00  I/Os:    25 (sequential:24 nearly:0 random:1)
disk:3  busy: 100.00  I/Os:    25 (sequential:24 nearly:0 random:1)

STAT totalTime 12.5

[testjz@localhost file-raid]$ ./raid.py -n 100 -L 1 -R 1000 -W seq -t -w 100 -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload seq
ARG writeFrac 100
ARG randRange 1000
ARG level 1
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy: 100.00  I/Os:    50 (sequential:49 nearly:0 random:1)
disk:1  busy: 100.00  I/Os:    50 (sequential:49 nearly:0 random:1)
disk:2  busy: 100.00  I/Os:    50 (sequential:49 nearly:0 random:1)
disk:3  busy: 100.00  I/Os:    50 (sequential:49 nearly:0 random:1)

STAT totalTime 15.0

[testjz@localhost file-raid]$ ./raid.py -n 100 -L 4 -R 1000 -W seq -t -w 100 -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload seq
ARG writeFrac 100
ARG randRange 1000
ARG level 4
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy: 100.00  I/Os:    68 (sequential:33 nearly:34 random:1)
disk:1  busy:  99.25  I/Os:    66 (sequential:32 nearly:33 random:1)
disk:2  busy:  99.25  I/Os:    66 (sequential:32 nearly:33 random:1)
disk:3  busy: 100.00  I/Os:   200 (sequential:33 nearly:166 random:1)

STAT totalTime 13.4

[testjz@localhost file-raid]$ ./raid.py -n 100 -L 5 -R 1000 -W seq -t -w 100 -c
ARG blockSize 4096
ARG seed 0
ARG numDisks 4
ARG chunkSize 4k
ARG numRequests 100
ARG reqSize 4k
ARG workload seq
ARG writeFrac 100
ARG randRange 1000
ARG level 5
ARG raid5 LS
ARG reverse False
ARG timing True

disk:0  busy:  99.25  I/Os:    98 (sequential:32 nearly:65 random:1)
disk:1  busy:  99.25  I/Os:    98 (sequential:32 nearly:65 random:1)
disk:2  busy: 100.00  I/Os:   100 (sequential:33 nearly:66 random:1)
disk:3  busy: 100.00  I/Os:   104 (sequential:33 nearly:70 random:1)

STAT totalTime 13.4
```
