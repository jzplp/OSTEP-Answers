* **问题 1 答案**  
这里只给出简单例子，其它自行实验即可。
```
[testjz@localhost dist-afs]$ ./afs.py -C 2 -n 2 -s 12 -f 2 -c
ARG seed 12
ARG numclients 2
ARG numsteps 2
ARG numfiles 2
ARG readratio 0.5
ARG actions 
ARG schedule 
ARG detail 0

[(1, 'a', 0), (3, 0), (4, 0), (1, 'b', 1), (2, 1), (4, 1)]
[(1, 'a', 0), (2, 0), (4, 0), (1, 'a', 1), (3, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
file:b contains:1
                                                        open:a [fd:0]
                                                        read:0 -> 0
                                                        close:0
                                                        open:a [fd:1]
                            open:a [fd:0]
                            write:0 0 -> 2
                            close:0
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 0, 'dirty': False, 'refcnt': 1}}
                                                        write:1 0 -> 3
                            open:b [fd:1]
                                                        close:1
                            invalidate file:a cache: {'a': {'valid': True, 'data': 2, 'dirty': False, 'refcnt': 0}, 'b': {'valid': True, 'data': 1, 'dirty': False, 'refcnt': 1}}
                            read:1 -> 1
                            close:1
file:a contains:3
file:b contains:1
```

* **问题 2 答案**  
```
[testjz@localhost dist-afs]$ ./afs.py -C 2 -f 1 -s 2 -c -d 3
ARG seed 2
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions 
ARG schedule 
ARG detail 3

[(1, 'a', 0), (3, 0), (4, 0), (1, 'a', 1), (2, 1), (4, 1)]
[(1, 'a', 0), (3, 0), (4, 0), (1, 'a', 1), (2, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
                                                        open:a [fd:0]
getfile:a c:c1 [0]

                                                        write:0 0 -> 1

                                                        close:0
putfile:a c:c1 [1]

                            open:a [fd:0]
getfile:a c:c0 [1]

                            write:0 1 -> 2

                            close:0
putfile:a c:c0 [2]
callback: c:c1 file:a
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 1, 'dirty': False, 'refcnt': 0}}
                                                        invalidate a

                                                        open:a [fd:1]
getfile:a c:c1 [2]

                                                        read:1 -> 2

                                                        close:1

                            open:a [fd:1]

                            read:1 -> 2

                            close:1

file:a contains:2
```
当写文件然后关闭时，被写入的文件在其他客户端有副本时，发生回调。  

* **问题 3 答案**  
```
[testjz@localhost dist-afs]$ ./afs.py -C 2 -f 1 -s 3 -c -d 7
ARG seed 3
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions 
ARG schedule 
ARG detail 7

[(1, 'a', 0), (3, 0), (4, 0), (1, 'a', 1), (3, 1), (4, 1)]
[(1, 'a', 0), (2, 0), (4, 0), (1, 'a', 1), (3, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
                            open:a [fd:0]
getfile:a c:c0 [0]
                            [a: 0 (v=1,d=0,r=1)]

                            write:0 0 -> 1
                            [a: 1 (v=1,d=1,r=1)]

                                                        open:a [fd:0]
getfile:a c:c1 [0]
                                                        [a: 0 (v=1,d=0,r=1)]

                            close:0
putfile:a c:c0 [1]
callback: c:c1 file:a
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 0, 'dirty': False, 'refcnt': 1}}
                                                        invalidate a
                                                        [a: 0 (v=0,d=0,r=1)]
                            [a: 1 (v=1,d=0,r=0)]

                                                        read:0 -> 0
                                                        [a: 0 (v=0,d=0,r=1)]

                            open:a [fd:1]
                            [a: 1 (v=1,d=0,r=1)]

                                                        close:0

                            write:1 1 -> 2
                            [a: 2 (v=1,d=1,r=1)]

                                                        open:a [fd:1]
getfile:a c:c1 [1]
                                                        [a: 1 (v=1,d=0,r=1)]

                                                        write:1 1 -> 3
                                                        [a: 3 (v=1,d=1,r=1)]

                                                        close:1
putfile:a c:c1 [3]
callback: c:c0 file:a
                            invalidate file:a cache: {'a': {'valid': True, 'data': 2, 'dirty': True, 'refcnt': 1}}
                            invalidate a
                            [a: 2 (v=0,d=1,r=1)]
                                                        [a: 3 (v=1,d=0,r=0)]

                            close:1
putfile:a c:c0 [2]
callback: c:c1 file:a
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 3, 'dirty': False, 'refcnt': 0}}
                                                        invalidate a
                                                        [a: 3 (v=0,d=0,r=0)]
                            [a: 2 (v=1,d=0,r=0)]

file:a contains:2
```

* **问题 4 答案**  
```
[testjz@localhost dist-afs]$ ./afs.py -C 2 -A oa1:w1:c1,oa1:r1:c1 -s 1 -c 
ARG seed 1
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions oa1:w1:c1,oa1:r1:c1
ARG schedule 
ARG detail 0

[(1, 'a', 1), (3, 1), (4, 1)]
[(1, 'a', 1), (2, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
                            open:a [fd:1]
                                                        open:a [fd:1]
                                                        read:1 -> 0
                            write:1 0 -> 1
                            close:1
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 0, 'dirty': False, 'refcnt': 1}}
                                                        close:1
file:a contains:1
[testjz@localhost dist-afs]$ ./afs.py -C 2 -A oa1:w1:c1,oa1:r1:c1 -s 2 -c 
ARG seed 2
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions oa1:w1:c1,oa1:r1:c1
ARG schedule 
ARG detail 0

[(1, 'a', 1), (3, 1), (4, 1)]
[(1, 'a', 1), (2, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
                                                        open:a [fd:1]
                                                        read:1 -> 0
                            open:a [fd:1]
                            write:1 0 -> 1
                                                        close:1
                            close:1
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 0, 'dirty': False, 'refcnt': 0}}
file:a contains:1
[testjz@localhost dist-afs]$ ./afs.py -C 2 -A oa1:w1:c1,oa1:r1:c1 -s 3 -c 
ARG seed 3
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions oa1:w1:c1,oa1:r1:c1
ARG schedule 
ARG detail 0

[(1, 'a', 1), (3, 1), (4, 1)]
[(1, 'a', 1), (2, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
                            open:a [fd:1]
                                                        open:a [fd:1]
                            write:1 0 -> 1
                                                        read:1 -> 0
                                                        close:1
                            close:1
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 0, 'dirty': False, 'refcnt': 0}}
file:a contains:1
[testjz@localhost dist-afs]$ ./afs.py -C 2 -A oa1:w1:c1,oa1:r1:c1 -s 4 -c 
ARG seed 4
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions oa1:w1:c1,oa1:r1:c1
ARG schedule 
ARG detail 0

[(1, 'a', 1), (3, 1), (4, 1)]
[(1, 'a', 1), (2, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
                            open:a [fd:1]
                            write:1 0 -> 1
                            close:1
                                                        open:a [fd:1]
                                                        read:1 -> 1
                                                        close:1
file:a contains:1
```
只有客户端C0关闭后C1打开文件，才会导致读取到1。

* **问题 5 答案**  
```
[testjz@localhost dist-afs]$ ./afs.py -C 2 -A oa1:w1:c1,oa1:r1:c1 -S 01 -c 
ARG seed 0
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions oa1:w1:c1,oa1:r1:c1
ARG schedule 01
ARG detail 0

[(1, 'a', 1), (3, 1), (4, 1)]
[(1, 'a', 1), (2, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
                            open:a [fd:1]
                                                        open:a [fd:1]
                            write:1 0 -> 1
                                                        read:1 -> 0
                            close:1
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 0, 'dirty': False, 'refcnt': 1}}
                                                        close:1
file:a contains:1
[testjz@localhost dist-afs]$ ./afs.py -C 2 -A oa1:w1:c1,oa1:r1:c1 -S 100011 -c 
ARG seed 0
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions oa1:w1:c1,oa1:r1:c1
ARG schedule 100011
ARG detail 0

[(1, 'a', 1), (3, 1), (4, 1)]
[(1, 'a', 1), (2, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
                                                        open:a [fd:1]
                            open:a [fd:1]
                            write:1 0 -> 1
                            close:1
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 0, 'dirty': False, 'refcnt': 1}}
                                                        read:1 -> 0
                                                        close:1
file:a contains:1
[testjz@localhost dist-afs]$ ./afs.py -C 2 -A oa1:w1:c1,oa1:r1:c1 -S 011100 -c 
ARG seed 0
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions oa1:w1:c1,oa1:r1:c1
ARG schedule 011100
ARG detail 0

[(1, 'a', 1), (3, 1), (4, 1)]
[(1, 'a', 1), (2, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
                            open:a [fd:1]
                                                        open:a [fd:1]
                                                        read:1 -> 0
                                                        close:1
                            write:1 0 -> 1
                            close:1
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 0, 'dirty': False, 'refcnt': 0}}
file:a contains:1
```
都读到0。  

* **问题 6 答案**  
```
[testjz@localhost dist-afs]$ ./afs.py -C 2 -A oa1:w1:c1,oa1:w1:c1 -S 011100 -c 
ARG seed 0
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions oa1:w1:c1,oa1:w1:c1
ARG schedule 011100
ARG detail 0

[(1, 'a', 1), (3, 1), (4, 1)]
[(1, 'a', 1), (3, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
                            open:a [fd:1]
                                                        open:a [fd:1]
                                                        write:1 0 -> 1
                                                        close:1
                            invalidate file:a cache: {'a': {'valid': True, 'data': 0, 'dirty': False, 'refcnt': 1}}
                            write:1 0 -> 2
                            close:1
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 1, 'dirty': False, 'refcnt': 0}}
file:a contains:2
[testjz@localhost dist-afs]$ ./afs.py -C 2 -A oa1:w1:c1,oa1:w1:c1 -S 010011 -c 
ARG seed 0
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions oa1:w1:c1,oa1:w1:c1
ARG schedule 010011
ARG detail 0

[(1, 'a', 1), (3, 1), (4, 1)]
[(1, 'a', 1), (3, 1), (4, 1)]
      Server                         c0                          c1               
file:a contains:0
                            open:a [fd:1]
                                                        open:a [fd:1]
                            write:1 0 -> 1
                            close:1
                                                        invalidate file:a cache: {'a': {'valid': True, 'data': 0, 'dirty': False, 'refcnt': 1}}
                                                        write:1 0 -> 2
                                                        close:1
                            invalidate file:a cache: {'a': {'valid': True, 'data': 1, 'dirty': False, 'refcnt': 0}}
file:a contains:2
```
会导致后关闭文件的客户端写入最终被保存到文件中。
