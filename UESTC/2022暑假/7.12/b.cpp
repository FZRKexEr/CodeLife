//
//  b.cpp
//  2022-07-12 12:29
//
//  Created by liznb
//  

#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "/Users/liznb/algo/liznb.h"
#endif

#define Mem(x) memset(x, 0, sizeof(x));
const int N = 10010;
const int M = 2550;

struct Edge {
    int v, nxt;
    bitset<M> w; 
};

struct PIC {
    Edge edge[N * 2];
    int first[N], top;
    
    void Init() {
        memset(first, -1, sizeof(first));
        top = 0;
    }
    
    void add(int u, int v, bitset<M> w) {
        edge[top++] = (Edge) {v, first[u], w};
        first[u] = top - 1;
    }
} e1, e2;

struct Tarjan {
    int dfn[N], low[N], belong[N], ins[N], stk[N];
    int time, cnt, p;
    
    void Init() {
        Mem(dfn);
        Mem(low);
        Mem(belong);
        Mem(ins);
        Mem(stk);
        time = cnt = p = 0;
    }
    
    void tarjan(int n) {
        dfn[n] = low[n] = ++time;
        stk[++p] = n;
        ins[n] = 1;
        for (int i = e1.first[n]; i != -1; i = e1.edge[i].nxt) {
            int v = e1.edge[i].v;
            if (dfn[v] == 0) {
                tarjan(v);
                low[n] = min(low[v], low[n]);
            } else if (ins[v]){
                low[n] = min(dfn[v], low[n]);
            }
        }
        if (dfn[n] == low[n]) {
            cnt++;
            do {
                belong[stk[p]] = cnt;
                ins[stk[p--]] = 0;
            } while (stk[p + 1] != n);
        }
    }
    
} T;

signed main() {
  ios::sync_with_stdio(false); 
  cin.tie(0);
   
  int n, m; cin >> n >> m;
  vector<vector<int>> d(n, vector<int> (m)); 
  array<int, 2> S;

  vector<vector<int>> order(n + 1, vector<int> (m + 1, -1));
  vector<vector<int>> order2(n + 1, vector<int> (m + 1, -1));
  vector<vector<int>> vis(n + 1, vector<int> (m + 1, 0));

  int tot = 0, ans_cnt = 0;
  for (int i = 0; i < n; i++) {
    string s; cin >> s;
    for (int j = 0; j < m; j++) {
      if (s[j] == '#') d[i][j] = 1;
      if (s[j] == '.') d[i][j] = 0;
      if (s[j] == '*') {
        ans_cnt++;
        d[i][j] = 2;
        order[i][j] = tot++;
      }
      if (s[j] == 'O') {
        d[i][j] = 0;
        S = {i, j}; 
      }
    }
  }

  queue<array<int, 2>> que; 
  que.push(S);
  order2[S[0]][S[1]] = 0;

  int tx[] = {0, 1, 0, -1}, ty[] = {1, 0, -1, 0};

  int num = 0;

  auto get_edge = [&](int x, int y, int o) {
    array<int, 2> pos = {x, y};
    bitset<M> edge; edge.reset();
    while (d[pos[0]][pos[1]] != 1) {
      if (d[pos[0]][pos[1]] == 2) edge[order[pos[0]][pos[1]]] = 1; 
      pos[0] += tx[o];
      pos[1] += ty[o];
      if (pos[0] < 0 || pos[1] < 0) break;
      if (pos[0] >= n || pos[1] >= m) break;
    }
    pos[0] -= tx[o];
    pos[1] -= ty[o];
    if (pos == (array<int, 2>) {x, y}) return pos;
    if (order2[pos[0]][pos[1]] == -1) order2[pos[0]][pos[1]] = num++;
    e1.add(order2[x][y], order2[pos[0]][pos[1]], edge); 
    return pos;
  };

  e1.Init();
   
  vis[S[0]][S[1]] = num++; 
  while (!que.empty()) {
    auto x = que.front(); que.pop();
    for (int i = 0; i < 4; i++) {
      auto nx = get_edge(x[0], x[1], i);
      if (vis[nx[0]][nx[1]]) continue;
      vis[nx[0]][nx[1]] = 1;
      que.push(nx);
    }
  }


  T.Init();
  for (int i = 0; i < num; i++) {
    if (T.dfn[i] == 0) T.tarjan(i);
  }
  e2.Init();

  vector<bitset<M>> W(3000);
  for (int i = 0; i < num; i++) {
    W[i].reset();
  }
  for (int i = 0; i < num; i++) {
    int u = T.belong[i];
    for (int j = e1.first[i]; j != -1; j = e1.edge[j].nxt) {
      int v = T.belong[e1.edge[j].v]; 
      if (v == u) {
        W[u] |= e1.edge[j].w;
      }
    }
  }

  for (int i = 0; i < num; i++) {
    int u = T.belong[i];
    for (int j = e1.first[i]; j != -1; j = e1.edge[j].nxt) {
      int v = T.belong[e1.edge[j].v]; 
      if (v != u) {
        e2.add(u, v, W[v] | e1.edge[j].w);  
      }
    }
  }
  
  vector<bitset<M>> f(3000);
  vector<int> used(3000, 0);
  
  function<bitset<M>(int)> dfs = [&](int x) {
    if (used[x]) return f[x];
    used[x] = 1;
    f[x].reset();

    for (int i = e2.first[x]; i != -1; i = e2.edge[i].nxt) {
      int v = e2.edge[i].v;
      bitset<M> res1 = dfs(v) | e2.edge[i].w;
      if (res1.count() > f[x].count()) {
        f[x] = res1;
      }
    }
    return f[x]; 
  };

  int res = (dfs(T.belong[0]) | W[T.belong[0]]).count();

  if (res == ans_cnt) {
    cout << "YES";
  } else {
    cout << "NO";
  }
    
  return 0;
}
