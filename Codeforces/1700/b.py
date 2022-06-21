#
#  b.py
#  2022-06-19 22:12
#
#  Created by liznb
# 

import math

t = int(input())
for i in range(t):
    n = int(input())
    val = int(input())
    if n == 1:
        if val < 9:
            print(val + 1)
        else:
            print(val + 2)
    else:
        goal1 = int(math.pow(10, n)) + 1
        goal2 = int(math.pow(10, n - 1)) + goal1; 
        if n != 2:
            goal2 = goal2 + int(math.pow(10, 1))
        ans = str(goal1 - val)
        if len(ans) != n:
            ans = str(goal2 - val)
            print(ans)
        else:
            print(ans)
     
