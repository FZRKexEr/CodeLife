//
//  main.cpp
//  C-我，不是说了能力要平均值么
//
//  Created by LiZnB on 2020/12/13.
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;

long long a[3 * N];
long long temp[3 * N];

long long Sort(int l, int r) {
    if (l == r) return 0ll;
    int mid = l + (r - l) / 2;
    long long ans = 0ll;
    ans += Sort(l, mid);
    ans += Sort(mid + 1, r);
    int p1 = l, p2 = mid + 1, p = l;
    
    while (p1 <= mid || p2 <= r) {
        while (p1 <= mid && (p2 > r || a[p1] < a[p2])) {
            temp[p++] = a[p1++];
        }
        while ((p2 <= r) && (p1 > mid || a[p2] <= a[p1])) {
            if (p1 <= mid) ans += 1ll * mid - p1 + 1;
            temp[p++] = a[p2++];
        }
    }
    for (int i = l; i <= r; i++)
        a[i] = temp[i];
    return ans;
}

long long gcd(long long a, long long b) {
    if (!b) return a;
    return gcd(b, a % b);
}

int main(void) {
  // freopen("in.txt", "r", stdin);
    memset(a, 0ll, sizeof(a));
    int n, k, val;
    long long s = 0ll;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val);
        s += 1ll * val;
        a[i] = s - 1ll * i * k; // !!!!! 写成i * k 直接爆long long！
    }
    long long ans = Sort(0, n);
    long long all = 1ll * (1 + n) * n / 2;
    long long g;
    
    
    g = gcd(all, ans);
    
    printf("%lld/%lld", ans / g, all / g);
    
    return 0;
}
