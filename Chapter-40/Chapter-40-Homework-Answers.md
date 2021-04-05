* **问题 1 答案**  
答案太长，这里只给出命令
```
[testjz@localhost file-implementation]$ ./vsfs.py -s 17 -c
[testjz@localhost file-implementation]$ ./vsfs.py -s 18 -c
[testjz@localhost file-implementation]$ ./vsfs.py -s 19 -c
[testjz@localhost file-implementation]$ ./vsfs.py -s 20 -c
```

* **问题 2 答案**  
答案太长，这里只给出命令
```
[testjz@localhost file-implementation]$ ./vsfs.py -s 21 -r -c
[testjz@localhost file-implementation]$ ./vsfs.py -s 22 -r -c
[testjz@localhost file-implementation]$ ./vsfs.py -s 23 -r -c
[testjz@localhost file-implementation]$ ./vsfs.py -s 24 -r -c
```
喜欢从序列的前面往后分配。

* **问题 3 答案**  
```
[testjz@localhost file-implementation]$ ./vsfs.py -d 2 -n 100 -c
ARG seed 0
ARG numInodes 8
ARG numData 2
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10
data         [(.,0) (..,0)][]

mkdir("/g");
File system out of data blocks; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -d 2 -n 100 -s 1 -c
ARG seed 1
ARG numInodes 8
ARG numData 2
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10
data         [(.,0) (..,0)][]

mkdir("/n");
File system out of data blocks; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -d 2 -n 100 -s 2 -c
ARG seed 2
ARG numInodes 8
ARG numData 2
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10
data         [(.,0) (..,0)][]

mkdir("/c");
File system out of data blocks; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -d 2 -n 100 -s 3 -c
ARG seed 3
ARG numInodes 8
ARG numData 2
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10
data         [(.,0) (..,0)][]

creat("/z");

inode bitmap  11000000
inodes       [d a:0 r:2][f a:-1 r:1][][][][][][]
data bitmap   10
data         [(.,0) (..,0) (z,1)][]

unlink("/z");

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10
data         [(.,0) (..,0)][]

creat("/s");

inode bitmap  11000000
inodes       [d a:0 r:2][f a:-1 r:1][][][][][][]
data bitmap   10
data         [(.,0) (..,0) (s,1)][]

fd=open("/s", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);
File system out of data blocks; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -d 2 -n 100 -s 4 -c
ARG seed 4
ARG numInodes 8
ARG numData 2
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10
data         [(.,0) (..,0)][]

mkdir("/f");
File system out of data blocks; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -d 2 -n 100 -s 5 -c
ARG seed 5
ARG numInodes 8
ARG numData 2
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10
data         [(.,0) (..,0)][]

mkdir("/t");
File system out of data blocks; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -d 2 -n 100 -s 6 -c
ARG seed 6
ARG numInodes 8
ARG numData 2
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10
data         [(.,0) (..,0)][]

mkdir("/g");
File system out of data blocks; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -d 2 -n 100 -s 7 -c
ARG seed 7
ARG numInodes 8
ARG numData 2
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10
data         [(.,0) (..,0)][]

creat("/r");

inode bitmap  11000000
inodes       [d a:0 r:2][f a:-1 r:1][][][][][][]
data bitmap   10
data         [(.,0) (..,0) (r,1)][]

creat("/z");

inode bitmap  11100000
inodes       [d a:0 r:2][f a:-1 r:1][f a:-1 r:1][][][][][]
data bitmap   10
data         [(.,0) (..,0) (r,1) (z,2)][]

fd=open("/z", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);
File system out of data blocks; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -d 2 -n 100 -s 8 -c
ARG seed 8
ARG numInodes 8
ARG numData 2
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10
data         [(.,0) (..,0)][]

creat("/c");

inode bitmap  11000000
inodes       [d a:0 r:2][f a:-1 r:1][][][][][][]
data bitmap   10
data         [(.,0) (..,0) (c,1)][]

fd=open("/c", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);
File system out of data blocks; rerun with more via command-line flag?
```
创建目录会失败。创建文件成功，写入文件会失败。可以创建多个文件，可以unlink。  
模拟器似乎要求必须剩下一个数据块不能被使用。  

* **问题 4 答案**  
```
[testjz@localhost file-implementation]$ ./vsfs.py -i 2 -n 100 -s 1 -c
ARG seed 1
ARG numInodes 2
ARG numData 8
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10
inodes       [d a:0 r:2][]
data bitmap   10000000
data         [(.,0) (..,0)][][][][][][][]

mkdir("/n");
File system out of inodes; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -i 2 -n 100 -s 2 -c
ARG seed 2
ARG numInodes 2
ARG numData 8
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10
inodes       [d a:0 r:2][]
data bitmap   10000000
data         [(.,0) (..,0)][][][][][][][]

mkdir("/c");
File system out of inodes; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -i 2 -n 100 -s 3 -c
ARG seed 3
ARG numInodes 2
ARG numData 8
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10
inodes       [d a:0 r:2][]
data bitmap   10000000
data         [(.,0) (..,0)][][][][][][][]

creat("/z");
File system out of inodes; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -i 2 -n 100 -s 4 -c
ARG seed 4
ARG numInodes 2
ARG numData 8
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10
inodes       [d a:0 r:2][]
data bitmap   10000000
data         [(.,0) (..,0)][][][][][][][]

mkdir("/f");
File system out of inodes; rerun with more via command-line flag?
[testjz@localhost file-implementation]$ ./vsfs.py -i 2 -n 100 -s 5 -c
ARG seed 5
ARG numInodes 2
ARG numData 8
ARG numRequests 100
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10
inodes       [d a:0 r:2][]
data bitmap   10000000
data         [(.,0) (..,0)][][][][][][][]

mkdir("/t");
File system out of inodes; rerun with more via command-line flag?
```
创建文件，创建目录都不行。  
模拟器似乎也要求必须剩下一个inode块不能被使用。  
