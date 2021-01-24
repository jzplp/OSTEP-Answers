* **问题 1 答案**  
答案太长不完整列出了，仅列出页表的项目数。
```
[testjz@localhost vm-paging]$ ./paging-linear-translate.py -P 1k -a 1m -p 512m -v -n 0
1024项
[testjz@localhost vm-paging]$ ./paging-linear-translate.py -P 1k -a 2m -p 512m -v -n 0
2048项
[testjz@localhost vm-paging]$ ./paging-linear-translate.py -P 1k -a 4m -p 512m -v -n 0
4096项

[testjz@localhost vm-paging]$ ./paging-linear-translate.py -P 1k -a 1m -p 512m -v -n 0
1024项
[testjz@localhost vm-paging]$ ./paging-linear-translate.py -P 2k -a 1m -p 512m -v -n 0
512项
[testjz@localhost vm-paging]$ ./paging-linear-translate.py -P 4k -a 1m -p 512m -v -n 0
256项
```
页表大小随着地址空间的增大而增大，随着页大小的增大而减小。  
如果使用很大的页，会产生很多内部碎片，空间同样被浪费了。  

* **问题 2 答案**  
答案太长省略了，执行程序即可看到结果。  
增加百分比，更多的地址转换成功。  

* **问题 3 答案**  
这三个都存在正确的转换，因此都不能算“错误”。但是三个的组合都不太合理。  
1和2：地址空间太小，只能容下4个页。  
3：页大小有点大了。  

* **问题 4 答案**  
```
[testjz@localhost vm-paging]$ ./paging-linear-translate.py -P 1k -a 16k -p 8k -v -c
ARG seed 0
ARG address space size 16k
ARG phys mem size 8k
ARG page size 1k
ARG verbose True
ARG addresses -1

Error: physical memory size must be GREATER than address space size (for this simulation)
```
会报错，提示物理内存大小应该大于地址空间大小。
