#
#  std.py
#  2022-04-27 00:40
#
#  Created by liznb
# 

T = int(input())
inf = float("inf")
for _ in range(T):
    N, A, B, X, Y, Z = map(int, input().split())

    Y = min(Y, X*A)
    Z = min(Z, X*B)


    #距離A * B進むときのコスト
    AB = A*B
    W = min(Y*B, Z*A)

    #距離ABをできるだけ進むより1個少ないだけ進む
    r = max(0, (N-AB) // AB)
    N -= r * AB
    base = r * W


    ans = inf
    i = 0
    while True:
        rem = N - B*i
        if rem < 0:
            break

        ans = min(ans, Z*i + Y*(rem//A) + X*(rem%A))
        i += 1



    ans += base
    print(ans)

