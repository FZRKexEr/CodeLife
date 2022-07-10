#
#  b.py
#  2022-07-06 00:34
#
#  Created by liznb
# 

def f1(l, r):
    l = l - 1
    resr = r * (1 + r) / 2
    resl = l * (1 + l) / 2
    return resr - resl

def f2(l, r):
    l = l - 1
    resr = r * (1 + r) * (2 * r + 1) / 6 
    resl = l * (1 + l) * (2 * l + 1) / 6
    return resr - resl

z = int(input())
for _ in range(z):
    n = int(input())
    i = 1
    ans = 0
    while i <= n:
        nxt = n // (n // i) + 1
        l = i
        r = nxt - 1
        ans = ans + (f2(l, r) - f1(l, r)) / 2 * (n // i)
        ans = ans + ((r - l + 1) * (n + 1) * n - (2 * n + 1) * (n // i) * f1(l, r)) / 2
        ans = ans + (((n // i) ** 2) * f2(l, r)) / 2
        i = nxt
    print(int(ans))
