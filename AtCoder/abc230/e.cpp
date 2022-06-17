#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
  	int n, ans = 0; cin >> n;
  	for (int i = 1, nxt; i <= n; i = nxt) {
    	nxt = n / (n / i) + 1;
      	ans += (nxt - i) * (n / i);
    }
	cout << ans;
  	return 0;
}
