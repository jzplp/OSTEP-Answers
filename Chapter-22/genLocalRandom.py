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
