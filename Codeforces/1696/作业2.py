#
#  作业2.py
#  2022-06-26 01:26
#
#  Created by liznb
# 

def sol(k, c):
    ans = 0
    money = [1, 5, 10, 20, 50, 100]
    for i in range(5, -1, -1):
        c[i] = int(c[i])
        while k >= money[i] and c[i] > 0:
            k = k - money[i]
            c[i] = c[i] - 1
            ans = ans + 1
    return ans 
    

if __name__ == "__main__":
    k = int(input("输入k:"))
    c = input("输入 c0 到 c5 :").split()
    print(sol(k, c)) 
    
    
    
