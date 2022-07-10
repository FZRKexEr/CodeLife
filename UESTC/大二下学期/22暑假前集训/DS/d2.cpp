#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);

  vector<int> a;   
  int n; cin >> n; 

  for (int i = 1; i <= n; i++) {
    int o, x; cin >> o >> x;
    if (o == 1) {
      a.insert(lower_bound(a.begin(), a.end(), x + 1), x);
    } else if (o == 2) {
      a.erase(lower_bound(a.begin(), a.end(), x));
    } else if (o == 3) {
      cout << lower_bound(a.begin(), a.end(), x) - a.begin() + 1 << endl;
    } else if (o == 4) {
      cout << a[x - 1] << endl;
    } else if (o == 5) {
      auto it = lower_bound(a.begin(), a.end(), x);
      if (it == a.begin()) cout << "NOT FOUND" << endl;
      else cout << *(--it) << endl;
    } else if (o == 6) {
      auto it = upper_bound(a.begin(), a.end(), x);
      if (it == a.end()) cout << "NOT FOUND" << endl;
      else cout << *it << endl;
    }
  }
   
  return 0;
}
