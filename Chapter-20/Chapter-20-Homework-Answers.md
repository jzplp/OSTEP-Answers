* **问题 1 答案**  
还是只需要一个寄存器即可。   

* **问题 2 答案**  
结果太长，这里仅仅给出命令。  
```
./paging-multilevel-translate.py -s 0 -c
./paging-multilevel-translate.py -s 1 -c
./paging-multilevel-translate.py -s 2 -c
```

* **问题 3 答案**  
缓存是经常访问或者最近访问的内存保存缓存中，由于页表或者多级页表会经常访问的（因为请求内存的次数很多），因此是会导致大量缓存命中的。  
当然如果程序本身很少访问页表，TLB基本全部命中，那么页表的访问次数很少很少，不在缓存也是合理的。  
