#!/usr/bin/env python
import os
i = 1
while i < 2000 :
	print '\npage num ' + str(i)
	val = os.system('./19.2 ' + str(i) + ' ' + str(10000))
	i = i * 2
