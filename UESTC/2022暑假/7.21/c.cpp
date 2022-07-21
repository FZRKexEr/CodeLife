//
//  c.cpp
//  2022-07-21 14:31
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define int long long

struct LiZnB {
  struct Node {
    mutable int l, r; 
    mutable array<int, 2> val;

    bool operator < (const Node &oth) const  {  
      return l < oth.l;
    }
  };
  int limit;

  set<Node> st;
  vector<int> a;

  LiZnB(int l, int r, int vl, int vr, vector<int> &_a) {
    limit = r;
    st.insert({l, r, {vl, vr}});
    a = _a;
  }

  set<Node>::iterator split(int x) { 
    auto it = --st.upper_bound((Node) {x, 0, {0, 0}});
    if (it->l == x) return it;

    assert(it->l <= x && it->r >= x);

    int l = it->l, r = it -> r;
    auto val = it->val;
    st.erase(it);

    int len1 = (x - 1) - l + 1;
    int len2 = r - x + 1;

    st.insert((Node) {l, x - 1, {val[0], val[0] + len1 - 1}});
    return st.insert((Node) {x, r, {val[1] - len2 + 1, val[1]}}).first;
  }

  void assign(int l, int r, int vl, int vr) {
    auto itr = split(r + 1);  
    auto itl = split(l);
    st.erase(itl, itr); 
    st.insert({l, r, {vl, vr}});
  }

  void copy(int l, int r) {
    int len = r - l + 1;    
    auto itr = split(r + 1);
    auto backup = itr;
    auto itl = split(l);

    while (itr != st.end()) {
      itr->l += len;
      itr->r += len;
      itr++;
    }
    
    vector<Node> add;

    while (itl != backup) {
      add.push_back({(itl->l) + len, (itl->r) + len, itl->val});  
      itl++;
    }

    for (auto &it : add) st.insert(it);
    itr = split(limit + 1); 
    st.erase(itr, st.end());
    
  }

  int query(int x) {
    auto itr = split(x);  
    return a[itr->val[0]];
  }
};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int z; cin >> z;   
  while (z--) {
    int n, q; cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> a[i];  
    }

    LiZnB T(1, n, 1, n, a);
    int ans = 0; 
    for (int i = 1; i <= q; i++) {
      int k; cin >> k;   
      if (k == 1) {
        int l, r; cin >> l >> r;
        T.copy(l, r);
      } else {
        int x; cin >> x;
        ans ^= T.query(x);
      }
    }
    cout << ans << endl;
  }

  return 0;
}
