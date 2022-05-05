//
//  treap.cpp
//  2022-04-28 02:11
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

struct Treap {

  struct Node {
    array<int, 2> son; 
    int pri, key;
  };

  vector<Node> tree; 

  // 把整棵树分裂成 小于等于 key的和 大于key 的   
  array<int, 2> split(int u, int key) {
    if (tree[u].key <= key) {
       
    } else {
            
    }
  }

};

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
    
   
  return 0;
}
