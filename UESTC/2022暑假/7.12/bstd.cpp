#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>
#include <queue>
using namespace std;

char s[52][52];
vector<int> con[5002];

stack<int> st;
int idx[5002], low[5002], sid[5002]; int vc, sc;
bool ins[5002];

vector<int> scn[2502];
vector<pair<int, int>> sat;

bool vs[2502]; queue<int> q;

void dfs(int v){
  idx[v] = low[v] = ++vc;
  st.push(v); ins[v] = true;

  for(int w : con[v]){
    if(idx[w] == 0){ dfs(w); low[v] = min(low[v], low[w]); }
    else if(ins[w]) low[v] = min(low[v], idx[w]);
  }

  if(low[v] == idx[v]){
    for(;;){
      int w = st.top(); st.pop(); ins[w] = false;
      sid[w] = sc; if(w == v) break;
    }
    sc++;
  }
}

int main(){
  int N, M; scanf("%d%d", &N, &M);

  int bx = 0, by = 0;

  for(int i = 0; i < N; i++){
    scanf("%s", s[i]);
    for(int j = 0; j < M; j++){
      if(s[i][j] == 'O'){ bx = i; by = j; }
    }
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(s[i][j] == '#') continue;

      int now = i * M + j, x, y;

      x = i; y = j; while(y > 0 && s[x][y - 1] != '#') y--;
      con[now].push_back(x * M + y);

      x = i; y = j; while(x > 0 && s[x - 1][y] != '#') x--;
      con[now].push_back(x * M + y);

      x = i; y = j; while(y < M - 1 && s[x][y + 1] != '#') y++;
      con[now].push_back(x * M + y);

      x = i; y = j; while(x < N - 1 && s[x + 1][y] != '#') x++;
      con[now].push_back(x * M + y);
    }
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(s[i][j] != '#' && idx[i * M + j] == 0) dfs(i * M + j);
    }
  }


  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(s[i][j] == '#') continue;

      int x = i * M + j, xid = sid[x];
      for(int y : con[x]){
        int yid = sid[y]; if(xid != yid) scn[xid].push_back(yid);
      }
    }
  }

  for(int i = 0; i < sc; i++){
    sort(scn[i].begin(), scn[i].end());
    scn[i].erase(unique(scn[i].begin(), scn[i].end()), scn[i].end());
  }

  int bid = sid[bx * M + by];

  sat.push_back({bid, bid});
  for(int i = bid + 1; i < sc; i++) sat.push_back({i + sc, i + sc});

  for(int n = 0; n < sc; n++){
    for(int i = 0; i < sc; i++) vs[i] = false;

    q.push(n); vs[n] = true;
    while(!q.empty()){
      int x = q.front(); q.pop();
      for(int y : scn[x]){
        if(!vs[y]){ q.push(y); vs[y] = true; }
      }
    }

    for(int i = 0; i < n; i++){
      if(!vs[i]) sat.push_back({i + sc, n + sc});
    }
  }

  for(int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      if(s[i][j] == '*'){
        sat.push_back({sid[con[i * M + j][0]], sid[con[i * M + j][1]]});
      }
    }
  }

  int sc_ = sc;

  for(int i = 0; i < 2 * sc; i++){
    con[i].clear();
    idx[i] = 0; low[i] = 0; sid[i] = 0;
  }
  vc = 0; sc = 0;

  for(auto &pp : sat){
    int x = pp.first, y = pp.second;
    int x_ = x < sc_ ? x + sc_ : x - sc_;
    int y_ = y < sc_ ? y + sc_ : y - sc_;

    con[x_].push_back(y); con[y_].push_back(x);
  }

  for(int i = 0; i < 2 * sc_; i++) if(idx[i] == 0) dfs(i);

  bool ans = true;
  for(int i = 0; ans && i < sc_; i++) if(sid[i] == sid[sc_ + i]) ans = false;

  puts(ans ? "YES" : "NO");
  return 0;
}