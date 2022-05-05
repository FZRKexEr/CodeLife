#
#  generate.py
#  2022-05-04 13:24
#
#  Created by liznb
# 

import random
n = 10
t = n + 10;
print(n, t)

ord = 'ABC'
cnt = 0
for i in range(t - n):
    l = random.randint(2, n - 1)
    r = random.randint(l + 1, n)
    o = random.randint(0, 2)
    if o == 2:
        if cnt > 10:
            print('C')
            cnt = cnt - 1
        else:
            cnt = cnt + 1
            print('A', l, r, random.randint(1, 10))
    
    if o == 1:
        print('B', random.randint(1, n))
    if o == 0:
        cnt = cnt + 1
        print('A', l, r, random.randint(1, 10))

for i in range(n):
   print("B", i + 1) 
