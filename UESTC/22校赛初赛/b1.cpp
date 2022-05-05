//
//  b.cpp
//  2022-05-04 09:29
//
//  Created by liznb
//  

#include <bits/stdc++.h>
#define int long long
#define endl '\n'
#define LOCAL
using namespace std;

#ifdef ONLINE_JUDGE
#ifndef LOCAL_TEST
#pragma GCC optimize("O3","unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#endif
#endif

vector<string> vec_splitter(string s) {
	s += ',';
  vector<string> res;
	while(!s.empty()) {
    res.push_back(s.substr(0, s.find(',')));
		s = s.substr(s.find(',') + 1);
	}
	return res;
}

void debug_out(
vector<string> __attribute__ ((unused)) args,
__attribute__ ((unused)) int idx, 
__attribute__ ((unused)) int LINE_NUM) { cerr << endl; } 
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T) {
	if(idx > 0) cerr << ", "; else cerr << "Line(" << LINE_NUM << ") ";
  stringstream ss; ss << H;
  cerr << args[idx] << " = " << ss.str();
	debug_out(args, idx + 1, LINE_NUM, T...);
}


#ifdef LOCAL
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) 2022
#endif

random_device rd; // 使用硬件熵源的随机数生成器
mt19937 seed(rd());
uniform_int_distribution<long long> U(1, 1000000000ll); // 1 - 1e9

const int MOD = 1e9 + 7;
int power(int a, int b) {
  assert(b >= 0);
  int base = a, ans = 1;
  while (b) {
    if (b & 1) ans = ans * base % MOD;
    base = base * base % MOD;
    b >>= 1;
  }
  return ans;
}

void file() {
#ifndef ONLINE_JUDGE
  freopen("in.txt", "r", stdin);
  // freopen("out.txt", "w", stdout);
#endif
}

const int N = 1e6 + 10;
const int INF = 0x3f3f3f3f;
struct Segment_Tree {
  #define tl tree[pos].l 
  #define tr tree[pos].r 
  #define tv tree[pos].val
  struct Info {
    array<int, 2> mini;
  };

  struct Tree {
    int l, r; 
    Info val;
  } tree[4 * N];  

  // 合并两个儿子
  Info merge(Info a, Info b) {
    Info res;

    vector<int> temp = {a.mini[0], a.mini[1], b.mini[0], b.mini[1]};
    sort(temp.begin(), temp.end());

    res.mini = {temp[0], temp[1]};
    return res;
  }

  void build(int pos, int l, int r, long long *arr) {
    tl = l; tr = r;    

    int m = l + (r - l) / 2;
    if (l == r) {
      tv.mini[0] = arr[l];
      tv.mini[1] = INF;
      return;
    } 
    build(pos << 1, l, m, arr);
    build(pos << 1 | 1, m + 1, r, arr);
    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
  }

  Info query(int pos, int l, int r) {
    if (tl >= l && tr <= r) {
      return tv;
    }   
    int m = tl + (tr - tl) / 2;
    Info res;

    if (l <= m && r > m) {
      res = merge(query(pos << 1, l, r), query(pos << 1 | 1, l , r));
    } else if (l > m) {
      res = query(pos << 1 | 1, l, r);
    } else if (r <= m) {
      res = query(pos << 1, l, r);
    }

    tv = merge(tree[pos << 1].val, tree[pos << 1 | 1].val);
    return res;
  }
  #undef tl
  #undef tr
  #undef tv
} ST;

int arr[N];

#define getchar() (frS==frT&&(frT=(frS=frBB)+fread(frBB,1,1<<15,stdin),frS==frT)?EOF:*frS++)char frBB[1<<15],*frS=frBB,*frT=frBB;template<typename T>inline void read(T &x){    x=0;char c=getchar();    while(!isdigit(c))c=getchar();    while(isdigit(c)){x=x*10+c-'0';c=getchar();}}/*1. 使用 read(x) 读入一个非负整数x2. 由于 fread 方法特性，本地测试时需要从文件读入，或者注释掉前两行，在提交时取消注释。*/

signed main() {
  //file();
  
  int n, q; read(n), read(q);
  
  for (int i = 1; i <= n; i++) {
    read(arr[i + 1]);
  }
  arr[1] = n;
  arr[n + 2] = n + 1;
  n = n + 2; 

  Segment_Tree T;
  T.build(1, 1, n, arr);

  for (int i = 1; i <= q; i++) {
    int l, r; read(l); read(r);
    l++, r++;  

    array<int, 2> a = T.query(1, 1, l - 1).mini; 
    array<int, 2> b = T.query(1, r + 1, n).mini;
    
    vector<int> temp = {a[0], a[1], b[0], b[1]};
    sort(temp.begin(), temp.end());
  
    printf("%lld\n", temp[1]);  
  }
   
  return 0;
}
